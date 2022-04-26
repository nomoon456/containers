#ifndef NODE_H
#define NODE_H
#include <iostream>
#include "Pair.hpp"


template <class T>
class Node;

//AVL Tree
template <class T, class kc,class A = std::allocator<Node<T> > >
class AVL{
public:
    typedef typename T::first_type ftype;
    typedef typename T::second_type stype;
    

    AVL():
    _head(NULL), 
    _size(0),
    _capacity(0){};

    AVL(const AVL &ref){
        *this = ref;
    }
    AVL &operator=(const AVL &ref){
        _head = ref._head;
        _dummyNode = ref._dummyNode;
        _alloc = ref._alloc;
        _size = ref._size;
        _capacity = ref._capacity;
        return (*this);
    }
    ~AVL(){
    };

    void freeAVL(Node<T> *node){
        if (node){
            freeAVL(node->_left);
            freeAVL(node->_right);
            _alloc.destroy(node);
            _alloc.deallocate(node,1);
        }
    }
	void freeDummyNode(){
		if (_dummyNode){
		//detach dummy node from the avl
		Node<T> *curr;
        if (_head){
		    curr = minValNode(_head);
		    if (curr){
		    	curr->_left = NULL;
		    }
		    curr = maxValNode(_head);
		    if (curr){
		    	curr->_right = NULL;
		    	_dummyNode->_parent = NULL;
		    }
        }
		//free dummy node
			_alloc.destroy(_dummyNode);
			_alloc.deallocate(_dummyNode, 1);
			_dummyNode = NULL;
		}
	}

    int height(Node<T> *node){
        if (node == NULL)
            return (0);
        return (node->_height);
    }

    int max (int a, int b){
        return ((a > b) ? a : b);
    }

    bool key_comp(Node<T> *n1, Node<T> *n2){
        return (n1->_pair.first > n2->_pair.first);
    }

    int getBalance(Node<T> *node){
        if (node == NULL)
            return (0);
        return (height(node->_left) - height(node->_right));
    }

    Node<T> *find(Node<T> *node, ftype first)const {
        if (node == NULL)
            return (NULL);
        if (node->_pair.first == first)
            return (node);
        Node<T> *n1 = find(node->_left, first);
        if (n1)
            return (n1);
        Node<T> *n2 = find(node->_right, first);
        return (n2);
    }

    Node<T> *newNode(T pair){
        Node<T> *node = _alloc.allocate(1);
        _alloc.construct(node, Node<T>(pair));
        return (node);
    }

    Node<T> *rightRotate(Node<T> *node){
        Node<T> *sub_node = node->_left;
        Node<T> *tmp = sub_node->_right;
        Node<T> *parent = node->_parent;

        sub_node->_right = node;
        node->_left = tmp;
        node->_parent = sub_node;
        sub_node->_parent = parent;
        if (node->_left)
            node->_left->_parent = node; 

        node->_height = max(height(node->_left), height(node->_right)) + 1;
        sub_node->_height = max(height(sub_node->_left), height(sub_node->_right)) + 1;
        return (sub_node);
    }

    Node<T> *leftRotate(Node<T> *node){
        Node<T> *sub_node = node->_right;
        Node<T> *tmp = sub_node->_left;
        Node<T> *parent = node->_parent;
        
        sub_node->_left = node;
        node->_right = tmp;
        node->_parent = sub_node;
        sub_node->_parent = parent;
        if (node->_right)
            node->_right->_parent = node; 

        node->_height = max(height(node->_left), height(node->_right)) + 1;
        sub_node->_height = max(height(sub_node->_left), height(sub_node->_right)) + 1;
        return (sub_node);
    }

    Node<T> *insert (Node <T> *node, T pair){
        if (node == NULL){
            _size++;
             return (newNode(pair));
        }
        if (pair.first < node->_pair.first){
            Node<T> *lchild = insert(node->_left, pair);
            node->_left = lchild;
            lchild->_parent  = node;
            // node->_left = insert(node->_left, pair);
        }
        else if (pair.first > node->_pair.first){
            Node<T> *rchild = insert(node->_right, pair);
            node->_right = rchild;
            rchild->_parent  = node;
            // node->_right = insert(node->_right, pair);
        }
        else 
            return (node);
        node->_height = 1 + max(height(node->_left), height(node->_right));
        int balance = getBalance(node);

        // left left
        if (balance > 1 && pair.first < node->_left->_pair.first)
            return (rightRotate(node));
        //right right
        if (balance < -1 && pair.first > node->_right->_pair.first)
            return (leftRotate(node));
        // left right
        if (balance > 1 && pair.first > node->_left->_pair.first){
            node->_left = leftRotate(node->_left);
            return (rightRotate(node));
        }
        // right left
        if (balance < -1 && pair.first < node->_right->_pair.first){
            node->_right = rightRotate(node->_right);
            return (leftRotate(node));
        }
        return (node);
    }

    Node<T> *minValNode(Node<T> *node)const{
        Node<T> *curr = node;

        while(curr->_left != NULL && curr->_left != _dummyNode)
            curr = curr->_left;
        return (curr);
    }

    Node<T> *maxValNode(Node<T> *node){
        Node<T> *curr = node;

        while(curr->_right != NULL && curr->_right != _dummyNode)
            curr = curr->_right;
        return (curr);
    }

    Node<T> *deleteNode(Node<T> *node, ftype first){
        if (node == NULL)
            return (node);
        if (first < node->_pair.first){
            node->_left = deleteNode(node->_left, first);
        }
        else if (first > node->_pair.first){
            node->_right = deleteNode(node->_right, first);
        }
        else {
                // std::cout << "node parent: " << node->_parent->_pair.first << std::endl;
                // std::cout << "node parent left: " << node->_parent->_left->_pair.first << std::endl; 
                // std::cout << "node parent right: " << node->_parent->_right->_pair.first << std::endl; 
            if (!node->_left || !node->_right){
                Node<T> *tmp = node->_left ? node->_left : node->_right;
                /*
                 0 child  
                */
                if (!tmp){
                // std::cout << "0 child" << std::endl;
                    tmp = node;
                    node = NULL;
                }
                /*
                 1 child  
                */
                else{
                // std::cout << "1 child" << std::endl;
                // std::cout << "node parent: " << node->_parent->_pair.first << std::endl;
                // std::cout << "node parent left: " << node->_parent->_left->_pair.first << std::endl; 
                // std::cout << "node parent right: " << node->_parent->_right->_pair.first << std::endl; 

                // std::cout << "node: " << node->_pair.first << std::endl;
                // std::cout << "tmp: " << tmp->_pair.first << std::endl;


                    tmp->_parent = node->_parent;
                    if (node->_parent && node->_parent->_left == node){
                        // node->_parent->_right = tmp ? tmp : node->_parent->_left = tmp;
                        tmp->_parent->_left = tmp;
                    }
                    else if (node->_parent && node->_parent->_right == node){
                        tmp->_parent->_right = tmp;
                    }
                // std::cout << "node parent: " << node->_parent->_pair.first << std::endl;
                // std::cout << "node parent left: " << node->_parent->_left->_pair.first << std::endl; 
                // std::cout << "node parent right: " << node->_parent->_right->_pair.first << std::endl; 
                    _alloc.destroy(node);
                    _alloc.deallocate(node,1);
                    --_size;
                    return (tmp);
                    // *node = *tmp;
                }
                --_size;
                _alloc.destroy(tmp);
                _alloc.deallocate(tmp,1);
            }
                /*
                 2 child  
                */
            else {
                // std::cout << "2 child" << std::endl;
                Node<T> *tmp (minValNode(node->_right));
			    tmp->_parent = node->_parent;
			    tmp->_left = node->_left;
			    if (node->_right != NULL && node->_right->_pair.first != tmp->_pair.first){
			    	node->_right->_left = NULL;
			    	tmp->_right = node->_right;
			    }
			    _alloc.construct(node, *tmp);
			    if (node->_right != NULL)
			    	node->_right->_parent = node;
			    _alloc.destroy(tmp);
			    _alloc.deallocate(tmp, 1);
                    --_size;
                node->_right = deleteNode(node->_right, node->_pair.first);
            }
        }
        if (node == NULL)
            return (node);
        node->_height = 1 + max(height(node->_left), height(node->_right));
        int balance = getBalance(node);
        //left left
        if (balance > 1 && getBalance(node->_left) >= 0)
            return (rightRotate(node));
        //left right
        if (balance > 1 && getBalance(node->_left) < 0){
            node->_left = leftRotate(node->_left);
            return (rightRotate(node));
        }
        //right right
        if (balance < -1 && getBalance(node->_right) <= 0)
            return (leftRotate(node));
        //right left
        if (balance < -1 && getBalance(node->_right) > 0){
            node->_right = rightRotate(node->_right);
            return (leftRotate(node));
        }
        return (node);
    }

    void print(Node<T> *node){
        if (node != NULL){
            std::cout << node->_pair.first << " =";
            std::cout <<" "<< node->_pair.second ;
            if (node->_parent != NULL )
                std::cout <<" parent: "<< node->_parent->_pair.first;
            else
                std::cout <<" parent: 0";
            std::cout << std::endl;
						std::cout << "node: " << node << std::endl;
						std::cout << "node right: " << node->_right << std::endl;
						std::cout << "node left " << node->_left << std::endl;
						std::cout << "-------------------" << std::endl;
            print(node->_left);
            print(node->_right);
        }
    }

    size_t getSize()const {return (_size);}
    
public:
    Node<T> *_head;
    Node<T> *_dummyNode;
    A _alloc;
    kc _key_compare;
    size_t _size;
    size_t _capacity;
};

// Node of AVL Tree
template <class T>
class Node{
public:

    Node(){
        _parent = NULL;
        _left = NULL;
        _right = NULL;
        _height = 0;
    };

    Node(T pair):_pair(pair){
        _parent = NULL;
        _left = NULL;
        _right = NULL;
        _height = 1;
    };

    Node(const Node &ref):_pair(ref._pair){
        *this = ref;
    }

    Node &operator=(const Node &ref){
        _parent = ref._parent;
        _left = ref._left;
        _right = ref._right;
        _height = ref._height;
				// _pair = ref._pair;
        return (*this);
    }
    ~Node(){};

    T   _pair;
    Node *_parent;
	Node *_left;
	Node *_right;
	int _height;
};


#endif