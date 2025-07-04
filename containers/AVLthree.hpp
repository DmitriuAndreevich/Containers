/*
*
* 
* 
* 
*/

/*
*  type T must have :
*   - default constructor
*   - move semantic
*/
#pragma once 
#include <stdexcept>
#include <initializer_list>

template<typename T>
class AVLthree {
private:
	struct Node {
		T data;
		Node* left;
		Node* right;
		Node* parent;
		int height = 1;

		Node() : left(nullptr), right(nullptr), parent(nullptr), height(1) {}
		Node(const T& _data, Node* _left = nullptr, Node* _right = nullptr, Node* _parent = nullptr, int _height = 1) :
		 data(_data), left(_left), right(_right), parent(_parent), height(_height) {}
		Node(const Node& node) :
			data(node._data), left(node._left), right(node._right), parent(node._parent), height(node._height) {}

		~Node() {
			if (left) {
				delete left;
			}
			if (right) {
				delete right;
			}
		}

		//Calculates the balance factor of the current node, that is, the difference between the height of the right and left subtree.
		int balance() const {
			return ((left) ? left->height : 0) - ((right) ? right->height : 0);
		}

		//Updates the height field of the current node based on the heights of its children.
		void updateHeight() {
			height = std::max( ((right) ? right->height : 0), ((left) ? left->height : 0) ) + 1;
		}

		Node* minNode() const {
			Node* current = this;
			while (left) {
				current = current->left;
			}
			return current;
		}

		Node* maxNode() const {
			Node* current = this;
			while (right) {
				current = current->right;
			}
			return current;
		}

		bool isLeaf() const {
			return (!left) && (!right);
		}

		Node* next() const {
			if (right) {
				return right->minNode();
			}
			Node* current = this;
			Node* p = parent;
			while (p) {
				if (current == p->left) {
					break;
				}
				current = p;
				p = current->parent;
			}
			return p;
		}
	 };
	
	Node* root = nullptr;
	size_t count = 0;

	Node* rightRotate(Node* b);
	Node* leftRotate(Node* b);
	Node* doubleRightRotate(Node* b);
	Node* doubleLeftRotate(Node* b);
public:

	//Constructor and destructor
	AVLthree();
	AVLthree(size_t count, const T& value);
	AVLthree(size_t count) : AVLthree(count, T()) {}
	AVLthree(const AVLthree& other);
	AVLthree(AVLthree&& other);
	AVLthree(std::initializer_list<T> init);
	~AVLthree();


	//--------------------------------- I T E R A T O R -----------------------------------

	class Iterator {
	private:
		Node* current;
		AVLthree* parent_three;

	public:





	};


	//-------------------------------------------------------------------------------------






	//....

	void remove(Node* node) {
		//...
	}

	





};



//template<typename T>
typename AVLthree::Node* AVLthree::rightRotate(typename AVLthree::Node* b) {
	if (!b || !b->left) { return b; }
	Node* a = b->left;
	Node* b_parent = b->parent;

	if (root == b) {
		root = a;
	}
	else {
		if (b == b_parent->left) {
			b_parent->left = a;
		}
		else {
			b_parent->right = a;
		}
	}

	b->parent = a;
	b->left = a->right;
	if (a->right) {
		a->right->parent = b;
	}
	a->right = b;
	a->parent = b_parent;
	b->updateHeight();
	a->updateHeight();
	return a;
}


//template<typename T>
typename AVLthree::Node* AVLthree::leftRotate(typename AVLthree::Node* b) {
	if (!b || !b->right) { return b; }
	Node* a = b->right;
	Node* b_parent = b->parent;

	if (root == b) {
		root = a;
	}
	else {
		if (b == b_parent->left) {
			b_parent->left = a;
		}
		else {
			b_parent->right = a;
		}
	}

	b->right = a->left;
	if (a->left) {
		a->left->parent = b;
	}
	a->left = b;
	b->parent = a;
	a->parent = b_parent;
	b->updateHeight();
	a->updateHeight();
	return a;
}


//template<typename T>
typename AVLthree::Node* AVLthree::doubleRighttRotate(typename AVLthree::Node* b) {
	if (!b || !b->left)


}


//template<typename T>
typename AVLthree::Node* AVLthree::doubleLeftRotate(typename AVLthree::Node* b) {
	if (!b || !b->right) { return b; }

	Node* a = b->right;
	Node* c = a->left;
	Node* b_parent = b->parent;

	if (root == b) {
		root = c;
	}
	else {
		if (b == b_parent->left) {
			b_parent->left = c;
		}
		else {
			b_parent->right = c;
		}
	}



}

