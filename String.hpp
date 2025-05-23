/*
*  String Documentation
*
*  The String class is a dynamic string implementation with automatic memory management.
*  Provides C-style string operations with bounds checking and resizing capabilities.
*
*  Key Features:
*    - Dynamic memory expansion/shrinking for efficient storage.
*    - Bounds-checked element access via at() and operator[].
*    - Common string operations: insert, erase, replace, concatenation.
*    - Explicit capacity management (reserve/resize/shrink_to_fit).
*    - Move semantics for efficient resource transfer.
*    - Full RAII compliance with proper copy/move semantics.
*
*  Notes:
*    - Throws std::out_of_range for invalid positions in at() and modifier methods.
*    - Maintains null terminator for C-string compatibility.
*    - Move operations leave source object in valid empty state.
*    - Not thread-safe for concurrent modifications.
*    - All operations maintain string integrity (null-termination and size constraints).
*/
#pragma once
#include <stdexcept>



#include <iostream>


class String {
private:
	char* _data;
	size_t _size;
	size_t _capacity;

public:
	//Constructor and destructor
	String() : _size(0), _capacity(1) {
		_data = new char[_capacity];
		_data[0] = '\0';
	}

	String(const char* str) : _size(0), _capacity(10) {
		if (str == nullptr) {
			throw std::invalid_argument("nullptr passed to constructor");
		}

		if (str == nullptr) {
			_size = 0;
			_capacity = 1;
			_data = new char[_capacity];
			_data[0] = '\0';
			return;
		}

		size_t str_size = 0;
		while (str[str_size] != '\0') {
			++str_size;
		}

		_capacity = str_size + 1;
		_size = str_size;
		_data = new char[_capacity];
		for (size_t i = 0; i < _size; ++i) {
			_data[i] = str[i];
		}
		_data[_size] = '\0';
	}

	String(const String& other) : _size(other._size), _capacity(other._capacity) {
		_data = new char[_capacity];
		for (size_t i = 0; i <= _size; ++i) {
			_data[i] = other._data[i];
		}
	}

	String(String&& other) noexcept : _data(other._data),_size(other._size),_capacity(other._capacity) {
		other._data = nullptr;
		other._size = 0;
		other._capacity = 0;
	}

	~String() {
		delete[] _data;
	}


	char& at(size_t index) {
		if (index < 0 || index >= _size) {
			throw std::out_of_range("Index out of bounds");
		}
		return _data[index];
	}

	const char& at(size_t index) const {
		if (index >= _size) {
			throw std::out_of_range("Index out of bounds");
		}
		return _data[index];
	}

	void erase(size_t pos, size_t n) {
		if (pos >= _size) {
			throw std::out_of_range("Index out of bounds");
		}


		for (size_t i = pos; i < _size; ++i) {
			if (i + n == _size) {
				break;
			}
			_data[i] = _data[i + n];
		}
		_size -= n;
		_data[_size] = '\0';
	}

	void replace(size_t pos, size_t len, const String& str) {
		if (pos >= _size) {
			throw std::out_of_range("Index out of bounds");
		}

		if (len != str.size()) {
			throw std::out_of_range("Incorrect length of input str");
		}

		if (pos + len >= _capacity) {
			reserve((pos + len + 1) * 2);
		}

		size_t j = 0;
		for (size_t i = pos; j < len; ++i) {
			_data[i] = str._data[j];
			++j;
		}

		_size = std::max(_size, pos + len);
		_data[_size] = '\0';
	}

	void push_back(char ch) {
		if (_size + 1 >= _capacity) {
			reserve((_size + 1) * 2);
		}

		_data[_size] = ch;
		++_size;
		_data[_size] = '\0';
	}

	void pop_back() {
		if(_size == 0){ throw std::out_of_range("Removing an element from an empty array"); }
		--_size;
	}

	void clear() {
		_size = 0;
		_data[0] = '\0';
	}

	void insert(size_t pos, const String& str) {
		if (pos > _size) {
			throw std::out_of_range("Index out of bounds");
		}

		const size_t other_size = str.size();

		if (_size + other_size + 1 >= _capacity) {
			reserve((_size + other_size + 1) * 2);
		}

		for (size_t i = _size; i > pos; --i) {
			_data[i + other_size - 1] = _data[i - 1];
		}

		size_t j = 0;
		for (size_t i = pos; j < other_size; ++i) {
			_data[i] = str._data[j];
			++j;
		}


		_size += other_size;
		_data[_size] = '\0';
	}

	bool is_empty() const {
		return _size == 0;
	}

	size_t size() const {
		return _size;
	}

	size_t capacity() const {
		return _capacity;
	}

	void reserve(size_t new_capacity) {
		if (new_capacity <= _capacity) { return; }

		char* new_data = new char[new_capacity];
		for (size_t i = 0; i < _size;++i) {
			new_data[i] = _data[i];
		}
		new_data[_size] = '\0';

		delete[] _data;
		_data = new_data;
		_capacity = new_capacity;

	}

	void resize(size_t new_size, char default_value) {
		if (new_size == _size) { return; }

		if (new_size < _size) {
			_size = new_size;
			_data[_size] = '\0';
		}
		else {
			reserve(new_size + 1);
			for (size_t i = _size; i < new_size; ++i) {
				_data[i] = default_value;
			}
			_size = new_size;
			_data[_size] = '\0';
		}

	}

	void shrink_to_fit() {
		if (_capacity == _size + 1) return;

		char* new_data = new char[_size + 1];
		for (size_t i = 0; i < _size; ++i) {
			new_data[i] = _data[i];
		}
		new_data[_size] = '\0';

		delete[] _data;
		_data = new_data;
		_capacity = _size + 1;
	}

	//------------------------------- O P E R A T O R S -------------------------------------------------
	String& operator=(const String& other) {
		if (this == &other) { return *this; }

		delete[] _data;

		_size = other._size;
		_capacity = other._capacity;

		_data = new char[_capacity];
		for (size_t i = 0; i <= _size;++i) {
			_data[i] = other._data[i];
		}

		return *this;
	}

	String& operator=(String&& other) {
		if (this == &other) return *this;

		delete[] _data;

		_size = other._size;
		_capacity = other._capacity;
		_data = other._data;

		other._size = 0;
		other._capacity = 0;
		other._data = nullptr;
		
		return *this;
	}

	String& operator+=(const String& other) {
		if (other._size == 0) { return *this; }

		reserve(_capacity + other.size() + 1);

		for (size_t i = 0; i < other.size(); ++i) {
			_data[_size + i] = other._data[i];
		}
		_size += other.size();
		_data[_size] = '\0';

		return *this;
	}

	char& operator[](size_t index) {
		return at(index);
	}

	const char& operator[](size_t index) const {
		return at(index);
	}
	
	bool operator==(const String& other) const {
		if (_size != other._size) {
			return false;
		}

		for (size_t i = 0; i < _size; ++i) {
			if (_data[i] != other._data[i]) {
				return false;
			}
		}
		return true;
	}

	bool operator!=(const String& other) const {
		return !(*this == other);
	}

	friend String operator+(const String& left, const String& right){
		String tmp(left);
		tmp += right;
		return tmp;
	}

};
