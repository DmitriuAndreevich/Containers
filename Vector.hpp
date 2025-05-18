/*
*  Vector Documentation
*
*  The Vector class is a dynamic array implementation with automatic resizing.
*  Supports bounds-checked iterators and basic STL-like container operations.
*
*  Key Features:
*    - Dynamic memory expansion/shrinking.
*    - Bounds checking for element access
*    - Support for random-access iterators.
*    - Capacity and size management.
*
*  Notes:
*    - Iterators throw std::out_of_range on out-of-bounds access.
*    - Existing iterators are invalidated when capacity changes.
*    - Not thread-safe.
*/

/*
*  type T must have :
*   - copy constructor
*   - operator = (copy)
*/
#pragma once
#include <stdexcept>


template <typename T>
class Vector {
private:
    T* _data;
    size_t _capacity;
    size_t _size;


    bool is_trivial_T = std::is_trivially_destructible_v<T>;
    //Private methods

public:
    //Constructor and destructor
    Vector() : _capacity(10), _size(0) {
        _data = new T[_capacity];
    }

    Vector(const Vector<T> vec) : _size(vec._size), _capacity(vec._capacity) {
        _data = new T[_capacity];
        for (size_t i = 0; i < _size; ++i) {
            new (&_data[i]) T(vec._data[i]);
        }
    }

    ~Vector() {
        delete[] _data;
    }

    //--------------------------------- I T E R A T O R -----------------------------------
    class Iterator {
    private:
        Vector<T>& _container;  // Reference to the parent container
        T* _ptr;                // Current position pointer

        // Check for out-of-bounds access
        void _check_bounds(size_t pos) const {
            if (pos >= _container._size) {
                throw std::out_of_range("Iterator out of bounds");
            }
        }

    public:
        // Types for STL compatibility
        using iterator_category = std::random_access_iterator_tag;
        using value_type = T;
        //difference_type — это безопасный и универсальный способ работать с расстояниями между итераторами, 
        // поддерживающий все возможные сценарии, включая отрицательные значения
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        Iterator(Vector<T>& container, T* ptr)
            : _container(container), _ptr(ptr) {}

        // Basic operations ---------------------------------------------------
        reference operator*() const {
            _check_bounds(_ptr - _container._data);  // _container._data points to the start of the array
            return *_ptr;
        }

        pointer operator->() const {
            _check_bounds(_ptr - _container._data);
            return _ptr;
        }

        // Increment/Decrement ------------------------------------------------
        Iterator& operator++() {
            _check_bounds(_ptr - _container._data);
            ++_ptr;
            return *this;
        }

        Iterator operator++(int) {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        Iterator& operator--() {
            _check_bounds(_ptr - _container._data);
            --_ptr;
            return *this;
        }

        Iterator operator--(int) {
            Iterator tmp = *this;
            --(*this);
            return tmp;
        }

        // Arithmetic operations --------------------------------------------
        Iterator operator+(difference_type n) const {
            Iterator tmp = *this;
            tmp += n;
            return tmp;
        }

        Iterator operator-(difference_type n) const {
            Iterator tmp = *this;
            tmp -= n;
            return tmp;
        }

        difference_type operator-(const Iterator& other) const {
            return _ptr - other._ptr;
        }

        Iterator& operator+=(difference_type n) {
            _ptr += n;
            _check_bounds(_ptr - _container._data);
            return *this;
        }

        Iterator& operator-=(difference_type n) {
            _ptr -= n;
            _check_bounds(_ptr - _container._data);
            return *this;
        }

        // Comparison ---------------------------------------------------------
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



    T& at(size_t index) const {
        if (index >= _size) { throw std::out_of_range("Iterator out of bounds"); }
        return _data[index];
    }

    T& back() const {
        return _data[_size - 1];
    }

    Iterator begin() const {
        return Iterator(*this, _data);
    }

    size_t capacity() {
        return _capacity;
    }

    const Iterator cbegin() const {
        return Iterator(*this, _data);
    }

    const Iterator cend() const {
        return Iterator(*this, _data + _size);
    }

    void clear() {
        if (!is_trivial_T) { //if T not trivial
            for (size_t i = 0; i < _size;++i) {
                _data[i].~T();
            }
        }
        _size = 0;
    }

    Iterator data() {
        return Iterator(*this, _data);
    }

    void emplace_back(T&& element) {
        if (_size + 1 > _capacity) {
            reserve(_capacity == 0 ? 1 : _capacity * 2);
        }

        _data[_size] = std::move(element);
        ++_size;
    }

    void emplace_back(const T& element) {
        if (_size + 1 > _capacity) {
            reserve(_capacity == 0 ? 1 : _capacity * 2);
        }

        _data[_size] = element;
        ++_size;
    }

    bool empty() {
        return _size == 0;
    }

    Iterator end() const {
        return Iterator(*this, _data + _size);
    }

    void erase(Iterator& first, Iterator& last) {
        if (first < begin() || first > end() || first > last) {
            throw std::out_of_range("Iterator out of bounds");
        }

        if (!is_trivial_T) {
            for (auto it = first; it != last; ++it) {
                it->~T();
            }
        }

        size_t difference = last - first;
        for (auto it = last + 1; it != end(); ++it) {
            *(it - difference) = std::move(*it);
        }

        _size -= difference;
        if (!is_trivial_T) {
            for (size_t i = _size; i < _size + difference; ++i) {
                _data[i].~T();
            }
        }
    }

    void erase(Iterator& position) {
        if (position < begin() || position > end()) {
            throw std::out_of_range("Iterator out of bounds");
        }

        //delete current object
        if (!is_trivial_T) {
            position->~T();
        }

        for (auto it = position; it != end() - 1; ++it) {
            *it = std::move(*(it + 1));
        }

        --_size;
        if (!is_trivial_T) {
            _data[_size].~T();
        }
    }

    T* front() {
        return (!empty()) ? &_data[0] : nullptr;
    }

    void insert(const T& element, const Iterator position) {
        if (position < begin() || position > end()) {
            throw std::out_of_range("Iterator out of bounds");
        }

        if (_size + 1 > _capacity) {
            reserve(_capacity == 0 ? 1 : _capacity * 2);
        }

        size_t pos_index = position - begin();
        for (size_t i = _size - 1; i >= pos_index; --i) {
            _data[i + 1] = _data[i];
        }

        _data[pos_index] = element;
        ++_size;
    }

    size_t max_size() {
        return _capacity;
    }

    void pop_back() {
        if (!empty()) {
            if (!is_trivial_T) {
                _data[_size - 1].~T();
            }
            --_size;
        }
    }

    void push_back(const T& element) {
        emplace_back(element);
    }

    void reserve(size_t new_capacity) {
        if (new_capacity <= _capacity) { return; }

        T* new_data = new T[new_capacity];
        for (size_t i = 0; i < _size; ++i) {
            new_data[i] = _data[i];
        }
        delete[] _data;
        _data = new_data;
        _capacity = new_capacity;
    }

    void resize(size_t new_size, const T& default_value) {
        if (new_size < _size) {
            if (!is_trivial_T) {
                for (size_t i = new_size; i < _size; ++i) {
                    _data[i].~T();
                }
            }
            _size = new_size;
            return;
        }

        if (new_size > _capacity) {
            reserve(new_size);
        }
        for (size_t i = _size; i < new_size; ++i) {
            new (&_data[i]) T(default_value);
        }
        _size = new_size;
    }

    void shrink_to_fit() {
        _capacity = _size;
    }

    size_t size() {
        return _size;
    }

    void swap(Vector& other) noexcept {
        std::swap(_data, other._data);
        std::swap(_size, other._size);
        std::swap(_capacity, other._capacity);
    }

    //------------------------------- O P E R A T O R S -------------------------------------------------

    T& operator[](size_t index) {
        return _data[index];
    }

    Vector& operator=(const Vector& right) {
        if (this == &right) { 
            return *this;
        }
        delete[] _data;
        _size = right._size;
        _capacity = right._capacity;

        _data = new T[_capacity];
        for (size_t i = 0; i < _size; ++i) {
            _data[i] = right._data[i];
        }

        return *this;
    }

    Vector& operator=(Vector&& right) {
        if (this == &right) {
            return *this;
        }

        delete[] _data;

        _data = std::move(right._data);
        _size = right._size;
        _capacity = right._capacity;

        right._data = nullptr;
        right._size = 0;
        right._capacity = 0;

        return *this;
    }

};
