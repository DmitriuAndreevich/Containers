/*
* 
*
* 
* 
*/
#pragma once
#include <stdexcept>


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

	String(String&& other) : _data(other._data),_size(other._size),_capacity(other._capacity) {
		other._data = nullptr;
		other._size = 0;
		other._capacity = 0;
	}

	~String() {
		delete[] _data;
	}


	bool is_empty() const {
		return _capacity == 0;
	}

	size_t size() const {
		return _size;
	}

	void reserve(size_t new_capacity) {

	}

	void resize(size_t new_size, String& default_value) {

	}

	void shrink_to_fit() {

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

	char operator[](size_t index) {
		if (index >= _size) {
			throw std::out_of_range("Index out of bounds");
		}
		return _data[index];
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
