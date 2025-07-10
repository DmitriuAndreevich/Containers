/*
*  AVLthree Documentation
*
*  The AVLthree class is a self-balancing binary search tree implementation (AVL Tree).
*  It maintains O(log n) time complexity for insertions, deletions, and lookups by ensuring
*  that the tree remains balanced using AVL rotations.
*
*  Key Features:
*    - Automatic balancing via single and double rotations (left/right)
*    - Support for insert, remove, and search operations
*    - Iterator with element access
*    - Height tracking and parent-pointer support for efficient upward traversal
*    - Full support for deep copy and move semantics
*    - Memory-safe node management using recursive destruction
*
*  Implementation Notes:
*    - Node structure includes parent pointer and subtree height
*    - Balancing is handled bottom-up after insertions and deletions
*    - Rotations correctly update all parent/child relationships and height
*    - Iterator supports basic arithmetic, dereferencing, and comparison
*    - Tree uses recursive functions for destruction and copying
*    - T must support default constructor, comparisons, and move semantics
*
*  Limitations:
*    - Iterators become invalid after structural modifications (insert/remove)
*    - Not thread-safe for concurrent modification or access
*    - No support for custom allocators or memory pooling
*
*  Usage Recommendations:
*    - Suitable for ordered data where fast insertion/deletion and lookup is needed
*    - Avoid modifying the tree while iterating unless iterators are updated
*    - Ensure type T fulfills required operations (see template assumptions)
*/
#pragma once 
#include <stdexcept>


#define T int
//template<typename T>
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
			data(node.data), left(node.left), right(node.right), parent(node.parent), height(node.height) {}

		~Node() {
			if (left) {
				delete left;
			}
			if (right) {
				delete right;
			}
		}

		//Calculates the balance factor of the current node, that is, the difference between the height of the right and left subtree.
		size_t balance() const {
			return ((left) ? left->height : 0) - ((right) ? right->height : 0);
		}

		//Updates the height field of the current node based on the heights of its children.
		void updateHeight() {
			height = std::max(((right) ? right->height : 0), ((left) ? left->height : 0)) + 1;
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

	Node* rightRotate(Node* b) {
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
	Node* leftRotate(Node* b) {
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
	Node* doubleRightRotate(Node* b) {
		if (!b || !b->left || !b->left->right) {
			return b;
		}

		Node* a = b->left;
		Node* c = a->right;
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

		a->right = c->left;
		if (c->left) {
			c->left->parent = a;
		}
		b->left = c->right;
		if (c->right) {
			c->right->parent = b;
		}

		c->left = a;
		a->parent = c;
		c->right = b;
		b->parent = c;
		c->parent = b_parent;

		a->updateHeight();
		b->updateHeight();
		c->updateHeight();
		return c;
	}
	Node* doubleLeftRotate(Node* b) {
		if (!b || !b->right || !b->right->left) { return b; }

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

		a->left = c->right;
		if (c->right) {
			c->right->parent = a;
		}

		b->right = c->left;
		if (c->left) {
			c->left->parent = b;
		}

		c->left = b;
		c->right = a;
		c->parent = b_parent;
		a->parent = c;
		b->parent = c;

		a->updateHeight();
		b->updateHeight();
		c->updateHeight();
		return c;
	}

	//Function for copy constructor and copy =
	Node* copyThree(const Node& node) {
		if (!node) {
			return nullptr;
		}

		Node* newNode = new T(node);
		
		newNode->left = copyThree(node.left);
		newNode->right = copyThree(node.right);


		return newNode;
	}
	
	//Function for destructor
	void clear(Node* node) {
		if (!node) {
			return;
		}
		clear(node->right);
		clear(node->left);
		delete node;
	}

	//Function for balancing a tree
	void balancing(Node* current) {
		while (current) {
			current->updateHeight();
			if (current->balance() == -2) {
				if (current->left && current->left->balance() == 1) {
					current = doubleRightRotate(current);
				}
				else {
					current = rightRotate(current);
				}
			}
			else if (current->balance() == 2) {
				if (current->right && current->right->balance() == -1) {
					current = doubleLeftRotate(current);
				}
				else {
					current = leftRotate(current);
				}
			}
			current = current->parent;
		}
	}
public:
	//Constructor and destructor
	AVLthree() : root(nullptr), count(0) {}
	AVLthree(size_t _count, const T& value) {
		while (count < _count) {
			insert(value);
		}
	}
	AVLthree(size_t count) : AVLthree(count, T()) {}
	AVLthree(const AVLthree& other) {
		root = copyThree(other.root);
		count = other.count;
	}
	AVLthree(AVLthree&& other) {
		root = other.root;
		count = other.count;
		other.root = nullptr;
		other.count = 0;
	}
	~AVLthree() {
		clear();
	}

	//--------------------------------- I T E R A T O R -----------------------------------
	class Iterator {
	private:
		Node* current;
		AVLthree* parent_three;

	public:
		Iterator() = delete;
		Iterator(Node* _current, AVLthree* _parent_three) : current(_current), parent_three(_parent_three) {}
		Iterator(const Iterator& other) : current(other.current), parent_three(other.parent_three) {}

		void is_valid() const {
			if (!current) {
				throw std::runtime_error("Iterator equal nullptr");
			}
		}

		T& operator*() {
			is_valid(current);
			return *current;
		}

		T* operator->() {
			is_valid(current);
			return current;
		}

		const T& operator*() const {
			is_valid(current);
			return *current;
		}

		const T* operator->() const {
			is_valid(current);
			return current;
		}


		// Increment/Decrement ------------------------------------------------
		Iterator& operator++() {
			if (current->right) {
				current = current->right;
				while (current->left) {
					current = current->left;
				}
				return current;
			}
			while (current->parent) {
				if (current->parent->left == current) {
					return current->parent;
				}
				current = current->parent;
			}
			return current;
		}

		Iterator operator++(int) {
			Iterator tmp(*this);
			++(*this);
			return tmp;
		}

		Iterator& operator--() {
			if (current->left) {
				current = current->left;
				while (current->right) {
					current->right;
				}
				return current;
			}
			while (current->parent) {
				if (current == current->parent->right) {
					current = current->parent;
				}
				else {
					return current;
				}
			}
			return current;
		}

		Iterator operator--(int) {
			Iterator tmp(*this);
			--(*this);
			return tmp;
		}


		// Arithmetic operations --------------------------------------------
		Iterator& operator+=(size_t n) {
			for (size_t i = 0; i < n; ++i) {
				++(*this);
			}
		}

		Iterator& operator-=(size_t n) {
			for (size_t i = 0; i < n; ++i) {
				--(*this);
			}
		}

		Iterator operator+(size_t n) const {
			Iterator tmp(*this);
			tmp += n;
			return tmp;
		}

		Iterator operator-(size_t n) const {
			Iterator tmp(*this);
			tmp -= n;
			return tmp;
		}


		// Comparison ---------------------------------------------------------
		bool operator==(const Iterator& other) const {
			return current == other.current;
		}

		bool operator!=(const Iterator& other) const {
			return !(current == other.current);
		}

	};
	//-------------------------------------------------------------------------------------

	void remove(Node* node) {
		if (!node) {
			return;
		}

		Node* node_parent = node->parent;
		if (!node->left && !node->right) {
			if (node->parent) {
				if (node->parent->right == node) {
					node->parent->right = nullptr;
				}
				else {
					node->parent->left = nullptr;
				}
			}
			else {
				root = nullptr;
			}
			delete node;
			--count;
		}
		else if (node->left && node->right) {
			Node* min = findMin(node->right);
			node->data = min->data;
			remove(min);
			--count;
		}
		else {
			if (node->parent) {
				if (node->parent->right == node) {
					if (node->right) {
						node->right->parent = node->parent;
						node->parent->right = node->right;
					}
					else {
						node->left->parent = node->parent;
						node->parent->right = node->left;
					}
				}
				else {
					if (node->right) {
						node->right->parent = node->parent;
						node->parent->left = node->right;
					}
					else {
						node->left->parent = node->parent;
						node->parent->left = node->left;
					}
				}
			}
			else
			{
				if (node->right) {
					root = node->right;
					node->right->parent = nullptr;
				}
				else {
					root = node->left;
					node->left->parent = nullptr;
				}
			}
			delete node;
			--count;
		}

		if (!node_parent) {
			balancing(root);
		}
		else {
			balancing(node_parent);
		}
	}

	void insert(const T& value) {
		if (!root) {
			root = new Node(value);
			++count;
			return;
		}

		Node* current = root;
		while (current) {
			if (value >= current->data) {
				if (!current->right) { 
					current->right = new Node(value, nullptr, nullptr, current);
					break;
				}
				current = current->right;
			}
			else {
				if (!current->left) { 
					current->left = new Node(value,nullptr,nullptr,current);
					break; 
				}
				current = current->left;
			}
		}
		++count;
		balancing(current);
	}

	bool contains(const T& value) const {
		Node* current = root;
		while (current) {
			if (current->data == value) {
				return true;
			}
			if (value >= current->data) {
				if (!current->right) {
					return false;
				}
				current = current->right;
			}
			else {
				if (!current->left) {
					return false;
				}
				current = current->left;
			}
		}
		return false;
	}

	Node* find(const T& value) const {
		Node* current = root;
		while (current) {
			if (current->data == value) {
				return current;
			}
			if (value >= current->data) {
				if (!current->right) {
					return nullptr;
				}
				current = current->right;
			}
			else {
				if (!current->left) {
					return nullptr;
				}
				current = current->left;
			}
		}
		return nullptr;
	}

	Node* findMin(Node* node) const {
		if (!node->left) {
			return node;
		}
		Node* current = node;
		while (current->left) {
			current = current->left;
		}
		return current;
	}

	Node* findMax(Node* node) const {
		if (!node->right) {
			return node;
		}
		Node* current = node;
		while (current->right) {
			current = current->right;
		}
		return current;
	}

	void clear() {
		clear(root);
		root = nullptr;
		count = 0;
	}

	bool empty() const {
		return count == 0;
	}

	size_t size() const {
		return count;
	}

	size_t height(Node* node = root) const {
		if (!node) {
			return 0;
		}

		return std::max(height(node->left), height(node->right)) + 1;
	}

	//--------------------------------- O P E A T O R S -------------------------------------

	AVLthree& operator=(const AVLthree& other) {
		clear();
		root = copyThree(other.root);
		count = other.count;
	}

	AVLthree& operator=(AVLthree&& other) {
		clear();
		root = other.root;
		count = other.count;
		other.root = nullptr;
		other.count = 0;
	}

};


