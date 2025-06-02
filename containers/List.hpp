/*
*
* 
* 
* 
* 
*/
#pragma once 
#include <stdexcept>
#include <initializer_list>

#define T std::string

//template<typename T>
class List {
private:
	size_t _size;
	struct Node {
		T _data;
		Node* _next;
		Node* _prev;

		Node(const T& data_ = T(),Node* next_ = nullptr, Node* prev_ = nullptr) : _data(data_), _next(next_), _prev(prev_) {}
		Node(T&& data_, Node* next_ = nullptr, Node* prev_ = nullptr) : _data(std::move(data_)), _next(next_), _prev(prev_) {}
	};
	Node* _head;
	Node* _tail;
public:
	List() : _size(1), Node(new Node(T(),nullptr,nullptr)) {}
	List(size_t size, const T& data_);
	List(const List& other);
	List(List&& other);
	List(std::initializer_list<T> init);
	~List();










};


