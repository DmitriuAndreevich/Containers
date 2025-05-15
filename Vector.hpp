/*
*  Documentation
*
* 
* 
* 
* 
*
*
*
*
*/
#pragma once
#include <stdexcept>


template <typename T>
class Vector {
private:
	T* _data;
	size_t _capacity;
	size_t _size;

	//Private methods

	void resize(size_t new_capacity) {
        if (new_capacity == _capacity) { return; }

        if (new_capacity < _capacity) {
            size_t count;
            for (size_t i = _size - 1; i > new_capacity;--i) {
                _data[i].~T();
                ++count;
            }
            _size -= count;
        }
        else {
            T* new_data = new T[new_capacity];
            for (size_t i = 0; i < _size; ++i) {
                new_data[i] = _data[i];
            }
            delete[] _data;
            _data = new_data;
        }

        _capacity = new_capacity;
	}

public:
	//Constructor and destructor
	Vector() : capacity(10), count(0) {
		data = new T[capacity];
	}

	~Vector() {
		delete[] data;
	}
    
	//Iterator
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

    };


    T& at(size_t index) const {
        if (index >= _size) { throw std::out_of_range("Iterator out of bounds"); }
        return data[index];
    }

    T& back() const {
        return data[_size - 1];
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
        for (size_t i = 0; i < _size;++i) {
            _data[i].~T();
        }
        _size = 0;
    }

    Iterator data() {
        return Iterator(*this, _data);
    }

    void emplace(T element, const Iterator position) {
        //...
    }

    Iterator end() const {
        return Iterator(*this, _data + _size);
    }




};
