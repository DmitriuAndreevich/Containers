/*
*
* 
* 
* 
* 
*/
#pragma once
#include <stdexcept>
#include "Vector.hpp"

template<typename T>
class Stack{
private:
	T* _data;
	size_t _size;
	size_t _capacity;
public:
	Stack():_size(0) , _capacity(10), _data(new T[_capacity]) {}
	Stack(size_t capacity) : _size(0), _capacity(capacity), _data(new T[_capacity]) {}
	Stack(std::initializer_list<T> init) :
		_size(init.size()), 
		_capacity(init.size() > 0 ? init.size() * 2 : 10),
		_data(new T[_capacity])
    {
        size_t i = 0;
        try {
            for (const auto& item : init) {
                new (&_data[i]) T(item);
                ++i;
            }
        }
        catch (...) {
            delete[] _data;
            throw;
        }
    }

    




};
