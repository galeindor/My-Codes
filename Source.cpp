/*ex3b
biggest sub tree that contain nodes from the same quarter
=====================================================
this program is creating a sorted binary tree from input
* input stops at end of file
then the program prints the point of the node that is the root of
the biggest sub tree that all it's nodes are in the same quarter.
* if both left and right sub trees that fullfil this condition are
* in the same size , left side node will be returned.
*/

//--------------------include section-------------------------
#include <iostream>
#include <cstdlib>
#include <iomanip>

//--------------------using section-------------------------

using std::cin;
using std::cout;
using std::endl;
using std::cerr;

//-----------------structs section---------------------------
struct Point
{
	int _x; // x value of the point
	int _y; // y value of the point
};
struct Node
{
	int _id; // id for the node
	struct Point* _data; // a point linked to the node.
	struct Node* _left, * _right;
	// pointers to nodes to create a binary tree. 
};

//-------------------------prototypes---------------------

Node* build_tree();
Node* new_node(int id, int x, int y);
Point* new_point(int x, int y);
void insert_node(Node*& root, Node* node);
void print_point(const Node* root);
void free_tree(Node* root);
bool same_quarter(Point* point1, Point* point2);
bool same_sign(int num1, int num2);
Node* same_quarter_tree(Node* root, int& size);
Node* compare(Node*, Node*, int, int, int&);
bool check_root(Node* root, Point* point);
//------------------ main --------------------------------
int main()
{
	Node* root;
	root = build_tree();
	Node* node = NULL;
	int size;
	if (root != NULL)
		node = same_quarter_tree(root, size);
	print_point(node);
	free_tree(root);
	return EXIT_SUCCESS;
}

//==========================================================================

// this func returns a pointer to the root of the largest
// sub-tree where all the points are in the same quarter.

Node* same_quarter_tree(Node* root, int& size)
{
	if (!root)
	{
		size = 0;
		return nullptr; //if root is null,return null
	}

	int size_l, size_r;

	Node* left_sub = same_quarter_tree(root->_left, size_l);
	Node* right_sub = same_quarter_tree(root->_right, size_r);


	if (check_root(root, root->_data) && left_sub == root->_left && right_sub == root->_right)
	{
		size = size_l + size_r + 1;
		return root;
	}

	/*
	left_sub = the root of the largest sub tree from the left side
	of the root that fullfil that all nodes are in the same quater.

	right_sub = the root of the largest sub tree from the right side
	of the root that fullfil that all nodes are in the same quater.
	*/

	return compare(left_sub, right_sub, size_l, size_r, size);

	// return the bigger subtree.
}



//==========================================================================
// compare the size of the trees and return the larger tree

Node* compare(Node* left, Node* right, int size_l, int size_r, int& max)
{
	if (size_r > size_l)
		// if right sub tree is bigger than the left subtree
	{
		max = size_r;
		return right;
	}
	else
		// if left sub tree is bigger or equal to the right subtree
	{
		max = size_l;
		return left;
	}
}

//==========================================================================

// this function returns if all the nodes of
// a tree are in the same quarter.
// root - the tree , point - the point of the first node.

bool check_root(Node* root, Point* point)
{
	if (!root)
		return true;

	bool is_left = true;
	bool is_right = true;
	Node* left = root->_left;
	Node* right = root->_right;
	if (left && !same_quarter(root->_data, left->_data))
		is_left = false;
	if (right && !same_quarter(root->_data, right->_data))
		is_right = false;
	return  (is_left && is_right);
}


//==========================================================================
// returns if both points are in the same quarter

bool same_quarter(Point* p1, Point* p2)
{
	return (same_sign(p1->_x, p2->_x) && same_sign(p1->_y, p2->_y));
}

//==========================================================================

// returns if both numbers are signed or both unsigned.
bool same_sign(int num1, int num2)
{
	return (((num1 >= 0) && (num2 >= 0)) || ((num1 <= 0) && (num2 <= 0)));
}

//==========================================================================

Node* build_tree()
{
	Node* root = NULL;
	int id, x, y;
	// inputs of the _id , _x , _y values of points in the struct.
	if (cin.eof())
		return nullptr;
	cin >> id >> x >> y;
	while (!cin.eof())
	{
		Node* node = new_node(id, x, y);
		insert_node(root, node);
		cin >> id >> x >> y;
	}
	return root;

}

//==========================================================================
// create a new node and allocate memory . this func
// will allocate memory for a node and set its values
// to the parameters.
Node* new_node(int id, int x, int y)
{
	Node* node = new (std::nothrow) Node;
	if (!node)
	{
		cerr << "problem in allocation" << endl;
		exit(EXIT_FAILURE);
	}
	node->_id = id;
	node->_data = new_point(x, y);
	node->_left = node->_right = NULL;
	return node;
}

//==========================================================================

void insert_node(Node*& root, Node* node)
{
	if (!root) // if found the place, enter node.
		root = node;
	else if (node->_id <= root->_id)
		insert_node(root->_left, node); // if lower value , go left.
	else
		insert_node(root->_right, node); // if higher value , go right.
}

//==========================================================================
// print the data point of the node.
void print_point(const Node* root)
{
	if (!root)
	{
		cout << "0 0" << endl; // print 0 0 if root is null.
		return;
	}
	cout << root->_data->_x << " " << root->_data->_y << endl;
	// print the point.
}

//==========================================================================
// free the memory allocated to the nodes.
void free_tree(Node* root)
{
	if (!root) // if the root is null, finish the run.
		return;

	free_tree(root->_left); // free left sub tree
	free_tree(root->_right); // free right sub tree.
	delete root->_data; // free the memory for the points.
	delete root;
}

//==========================================================================

// allocate memory for the 
Point* new_point(int x, int y)
{
	Point* point = new (std::nothrow) Point;
	if (!point)
	{
		cerr << "problem in allocation" << endl;
		exit(EXIT_FAILURE);
	}
	point->_x = x;
	point->_y = y;
	return point;
}
