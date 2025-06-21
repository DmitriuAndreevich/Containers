/*
*  Deque Documentation
*
*  The Deque class is a double-ended queue implementation using a dynamic circular buffer.
*  Supports efficient insertion and deletion at both ends and provides random-access iterators.
*
*  Key Features:
*    - Dynamic memory expansion/shrinking for efficient storage.
*    - Bounds-checked element access via at() and operator[].
*    - Support for random-access iterators with bounds checking.
*    - Constant time insertion and deletion at both ends (amortized).
*    - Capacity and size management (reserve, resize, shrink_to_fit).
*    - Full RAII compliance with proper copy/move semantics.
*
*  Notes:
*    - Iterators throw std::out_of_range on out-of-bounds access.
*    - Existing iterators are invalidated when capacity changes (reallocation occurs).
*    - Not thread-safe for concurrent modifications.
*    - The underlying storage is a contiguous array (circular buffer).
*    - When reallocation occurs, elements are rearranged to start at index 0.
*/
#include <stdexcept>
#include <initializer_list>
#include <cstring>


template<typename T>
class Deque {
private:
	size_t _size;
	size_t _capacity;

	size_t front_index;
	size_t back_index;

	T* _data;
public:
	Deque() : _size(0), _capacity(10), front_index(0), back_index(0), _data(new T[_capacity]) {}
	Deque(size_t capacity) : _size(0), _capacity(capacity), front_index(0), back_index(0),_data(new T[_capacity]) {}
	Deque(const Deque& other) : _size(other._size), _capacity(other._capacity),
		front_index(other.front_index), back_index(other.back_index), _data(new T[_capacity]) {
		for (size_t i = front_index; i < _size;++i) {
			_data[i] = other._data[i];
		}
	}
	Deque(Deque&& other) noexcept : _size(other._size), _capacity(other._capacity) ,
		front_index(other.front_index), back_index(other.back_index), _data(other._data) {
		other._size = 0;
		other._capacity = 10;
		other.front_index = 0;
		other.back_index = 0;
		other._data = nullptr;
	}
	Deque(std::initializer_list<T> init) : _size(init.size()), _capacity(init.size() > 10 ? init.size() * 2 : 10),
		front_index(0), back_index(init.size() - 1), _data(new T[_capacity]) {

		size_t i = 0;
		try {
			for (const auto& it : init) {
				_data[i] = it;
				++i;
			}
		}
		catch (...) {
			delete[] _data;
			throw;
		}
	}
	~Deque() {
		delete[] _data;
	}


	//--------------------------------- I T E R A T O R -----------------------------------
	class Iterator {
	private:
		Deque* _container;
		T* _ptr;

		void _check_bounds(size_t pos) const {
			if (pos > _container->back_index || pos < _container->front_index) {
				throw std::out_of_range("Iterator out of bounds");
			}
		}

	public:

		Iterator(T* ptr, Deque* container) : _ptr(ptr),_container(container) {}

		T& operator*() {
			_check_bounds(_ptr - _container->_data);
			return *_ptr;
		}

		T* operator->() {
			_check_bounds(_ptr - _container._data);
			return &_ptr;
		}

		const T& operator*() const {
			_check_bounds(_ptr - _container->_data);
			return *_ptr;
		}

		const T* operator->() const {
			_check_bounds(_ptr - _container._data);
			return &_ptr;
		}


		// Increment/Decrement ------------------------------------------------

		Iterator& operator++() {
			_check_bounds(_ptr - _container->_data);
			++_ptr;
			return *this;
		}

		Iterator& operator--() {
			_check_bounds(_ptr - _container->_data);
			--_ptr;
			return *this;
		}

		Iterator operator++(int) {
			Iterator tmp = *this;
			++(*this);
			return tmp;
		}

		Iterator operator--(int) {
			Iterator tmp = *this;
			--(*this);
			return tmp;
		}


		// Arithmetic operations ----------------------------------------------

		Iterator& operator+=(size_t n) {
			_ptr += n;
			_check_bounds(_ptr - _container->_data);
			return *this;
		}

		Iterator& operator-=(size_t n) {
			if (_ptr == &_container->_data[_container->back_index + 1]) {
				_ptr = &_container->_data[_container->back_index];
				return *this;
			}
			_ptr -= n;
			_check_bounds(_ptr - _container->_data);
			return *this;
		}

		Iterator operator+(size_t n) const {
			Iterator tmp = *this;
			tmp += n;
			return tmp;
		}

		Iterator operator-(size_t n) const {
			Iterator tmp = *this;
			tmp -= n;
			return tmp;
		}

		size_t operator+(const Iterator& other) const {
			return _ptr + other._ptr;
		}

		size_t operator-(const Iterator& other) const {
			return _ptr - other._ptr;
		}

		// Comparison ---------------------------------------------------------
		Iterator& operator=(const Iterator& other) {
			_ptr = other._ptr;
			_container = other._container;
			return *this;
		}


		bool operator==(const Iterator& other) const {
			return _ptr == other._ptr;
		}

		bool operator!=(const Iterator& other) const {
			return !(*this == other);
		}

		bool operator<(const Iterator& other) const {
			return _ptr < other._ptr;
		}

		bool operator>(const Iterator& other) const {
			return other < *this;
		}

		bool operator<=(const Iterator& other) const {
			return !(other < *this);
		}

		bool operator>=(const Iterator& other) const {
			return !(*this < other);
		}
	};

	//-------------------------------------------------------------------------------------


	//Adding elements :
	void push_back(const T& value) {
		if (_size >= _capacity) {
			reserve(_capacity < 10 ? 10 : _capacity * 2);
		}

		if (empty()) {
			front_index = 0;
			back_index = 0;
			_data[back_index] = value;
		}else {
			size_t new_index = (back_index + 1) % _capacity;
			_data[new_index] = value;
			back_index = new_index;
		}

		++_size;
	}

	void push_front(const T& value) {
		if (_size >= _capacity) {
			reserve(_capacity < 10 ? 10 : _capacity * 2);
		}

		if (empty()) {
			front_index = 0;
			back_index = 0;
			_data[front_index] = value;
		}else {
			size_t new_index = (front_index - 1 + _capacity) % _capacity;
			_data[new_index] = value;
			front_index = new_index;
		}
		++_size;
	}

	void insert(const Iterator& pos, const T& value) {
		if (pos == begin()) {
			push_front(value);
			return;
		}
		if (pos == end()) {
			push_back(value);
			return;
		}

		if (_size + 1 >= _capacity) {
			reserve(_capacity < 10 ? 10 : _size * 2);
		}
		size_t position = pos - begin();
		for (size_t i = back_index + 1; i > position; --i) {
			_data[i] = _data[i - 1];
		}
		
		_data[position] = value;
		++_size;
		++back_index;
	}

	void insert(const Iterator& pos, size_t count, const T& value) {
		if (count == 0) { return; }

		if (_size + count >= _capacity) {
			reserve(_capacity < 10 ? 10 : _size + count + _size / 2);
		}

		if (pos == begin()) {
			_size += count;
			while (count > 0) {
				push_front(value);
				--count;
			}
			return;
		}
		if (pos == end()) {
			_size += count;
			while (count > 0) {
				push_back(value);
				--count;
			}
			return;
		}

		size_t position = &*pos - _data;
		size_t j = 0;
		for (size_t i = back_index + count; j < _size - position; --i) {
			_data[i] = _data[i - count];
			++j;
		}
		for (size_t i = 0; i < count; ++i) {
			_data[position++] = value;
		}
		_size += count;
		back_index += count;
	}



	//Access to elements:

	T& front() {
		if (empty()) {
			throw std::out_of_range("Deque is empty");
		}
		return _data[front_index];
	}

	const T& front() const {
		if (empty()) {
			throw std::out_of_range("Deque is empty");
		}
		return _data[front_index];
	}

	T& back() {
		if (empty()) {
			throw std::out_of_range("Deque is empty");
		}
		return _data[back_index];
	}

	const T& back() const {
		if (empty()) {
			throw std::out_of_range("Deque is empty");
		}
		return _data[back_index];
	}

	Iterator begin() {
		return empty() ? end() : Iterator(&_data[front_index], this);
	}

	Iterator end() {
		if (empty()) {
			return Iterator(_data, this);
		}
		return Iterator(&_data[back_index + 1], this);
	}

	const Iterator begin() const {
		return empty() ? end() : Iterator(&_data[front_index], this);
	}

	const Iterator end() const {
		if (empty()) {
			return Iterator(_data, this);
		}
		return Iterator(&_data[back_index + 1], this);
	}

	T& at(size_t pos) {
		if (pos > back_index || pos < front_index) {
			throw std::out_of_range("Iterator out of bounds");
		}
		return _data[pos];
	}

	const T& at(size_t pos) const {
		if (pos >= back_index || pos <= front_index) {
			throw std::out_of_range("Iterator out of bounds");
		}
		return _data[pos];
	}


	//Removing items:
	
	void pop_back() {
		if (empty()) {
			throw std::out_of_range("pop_back on empty deque");
		}

		_data[back_index].~T();
		--_size;

		if (empty()) {
			front_index = 0;
			back_index = 0;
		}
		else {
			back_index = (back_index + _capacity - 1) % _capacity;
		}
	}

	void pop_front() {
		if (empty()) {
			throw std::out_of_range("pop_front on empty deque");
		}

		_data[front_index].~T();
		--_size;

		if (empty()) {
			front_index = 0;
			back_index = 0;
		}
		else {
			front_index = (front_index + 1) % _capacity;
		}

	}

	void erase(const Iterator& pos) {
		if (pos == begin()) {
			pop_front();
			return;
		}
		if (pos == end()) {
			pop_back();
			return;
		}

		size_t position = pos - begin();
		_data[position].~T();
		for (size_t i = position; i < back_index - 1; ++i) {
			_data[i] = _data[i + 1];
		}
		--_size;
		--back_index;
	}

	void erase(const Iterator first, const Iterator& last) {
		if (first > last) {
			throw std::out_of_range("Iterator out of bounds");
		}
		if (first == last) {
			erase(first);
		}

		size_t pos_start = first - begin();
		size_t pos_finish = last - begin();
		size_t difference = pos_finish - pos_start;
		for (size_t i = pos_start; i < pos_finish; ++i) {
			_data[i].~T();
			if (i + difference <= back_index) {
				_data[i] = _data[i + difference];
			}
		}
		_size -= difference;
		back_index -= difference;
	}


	//Other methods :

	bool empty() const {
		return _size == 0;
	}

	size_t size() const {
		return _size;
	}

	size_t max_size() const {
		return _capacity;
	}

	void reserve(size_t new_capacity) {
		if (new_capacity <= _capacity) { return; }

		T* new_data = new T[new_capacity]();
		size_t new_index = 0;
	
		if (!empty()) {
			size_t current = front_index;
			for (size_t i = 0; i < _size; ++i) {
				new_data[new_index++] = _data[current];
				current = (current + 1) % _capacity;
			}
		}

		delete[] _data;
		_data = new_data;
		_capacity = new_capacity;
		front_index = 0;
		back_index = (_size == 0) ? 0 : _size - 1;
	}

	void resize(size_t count, const T& value = T()) {
		if (count == _size) { return; }

		if (count > _size) {
			if (_size + count >= _capacity) {
				reserve(_capacity < 10 ? 10 : _size + count + 10);
			}

			size_t count_add = count - _size;
			for (size_t i = 0; i < count_add; ++i) {
				push_back(value);
			}
		}
		else {
			size_t count_remove = _size - count;
			for (size_t i = 0; i < count_remove; ++i) {
				pop_back();
			}
		}
	}

	void clear() {
		if (_data) {
			delete[] _data;
		}
		_capacity = 10;
		_size = 0;
		front_index = 0;
		back_index = 0;
		_data = new T[_capacity];
	}

	//----------------------------------------- O P E R A T O R S ------------------------------------------------
	Deque& operator=(const Deque& other){
		if (this != &other) {
			delete[] _data;

			_size = other._size;
			_capacity = other._capacity;
			front_index = other.front_index;
			back_index = other.back_index;

			_data = new T[_capacity];
			if (other._data) {
				memcpy(_data, other._data, _capacity * sizeof(T));
			}
		}
		return *this;
	}

	Deque& operator=(Deque&& other) noexcept {
		if (this != &other) {
			delete[] _data;

			_data = other._data;
			_size = other._size;
			_capacity = other._capacity;
			front_index = other.front_index;
			back_index = other.back_index;

			other._data = nullptr;
			other._size = 0;
			other._capacity = 10;
			other.front_index = 0;
			other.back_index = 0;
		}
		return *this;
	}

	T& operator[](size_t pos) {
		return at(pos);
	}

};
