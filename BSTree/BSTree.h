#include<assert.h>

template<class K,class V>
struct BSTreeNode
{
	K _key;
	V _value;
	BSTreeNode<K, V>* _left;
	BSTreeNode<K, V>* _right;

	BSTreeNode(const K& key, const V&value)
		: _key(key)
		, _value(value)
		, _left(NULL)
		, _right(NULL)
	{}
};
template <class K, class V>
class BSTree
{
	typedef BSTreeNode<K, V> Node;
protected:
	Node* _root;
public:
	BSTree()
		:_root(NULL)
	{}
	~BSTree()
	{}
public:
	bool Insert(const K& key, const V& value)
 	{
		if (_root == NULL)
		{
			_root = new Node(key, value);
			return true;
		}

		Node* cur = _root;
		Node* parent = NULL;
		//寻找插入位置 
		while (cur)
		{

			if (cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_key > key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
				return false;
		}
		//插入 
		if (parent->_key < key)
			parent->_right = new Node(key, value);
		else
			parent->_left = new Node(key, value);
		return true;
	}

	bool Remove(const K& key)
	{
		if (_root == NULL)
		{
			return false;
		}
		else if ((_root->_left==NULL) && (_root->_right==NULL))
		{
			delete _root;
			_root = NULL;
			return true;
		}

		Node* parent = NULL;
		Node* del = _root;

		while (del)//寻找要删除的结点
		{
			if (del->_key > key)
			{
				parent = del;
				del = del->_left;
			}
			else if (del->_key < key)
			{
				parent = del;
				del = del->_right;
			}
			else
				break;
		}
		if (del)
		{
			if (del->_left == NULL)
			{
				if (del == _root)
					_root = del->_right;
				else
				{
					if (del == parent->_left)
						parent->_left = del->_right;
					else
						parent->_right = del->_right;
				}
			}
			else if (del->_right == NULL)
			{
				if (del == _root)
					_root = del->_left;
				else
				{
					if (del == parent->_left)
						parent->_left = del->_left;
					else
						parent->_right = del->_left;
				}
				
			}
			else
			{
				//右子数中序遍历的第一个节点和del交换，然后再删除
				Node* fInOrder = del->_right;
				Node* parent = del;

				while (fInOrder->_left)//寻找右子树中序遍历的第一个结点
				{
					parent = fInOrder;
					fInOrder = fInOrder->_left;
				}
				swap(del->_key, fInOrder->_key);
				swap(del->_value, fInOrder->_value);
				del = fInOrder;

				if (fInOrder == parent->_left)
					parent->_left = fInOrder->_right;
				else
					parent->_right = fInOrder->_right;
			}
		}
		delete del;
	}
	Node* Find_R(const K& key)
	{
		return _Find_R(_root,key);
	}
	Node* _Find_R(Node* _root, const K& key)
	{
		if (_root == NULL)
			return NULL;

		Node* cur = _root;
		if (cur->_key > key)
			return _Find_R(_root->_left, key);
		else if (cur->_key < key)
			return _Find_R(_root->_right, key);
		else
		{
			cout << "找到结点" << endl;
			return _root;
		}
	}
public:
	bool Insert_R(const K& key, const V& value)
	{
		return _Insert_R(_root,key,value);
	}
	bool _Insert_R(Node* _root, const K& key, const V&value)
	{
		if (_root == NULL)
		{
			_root = new Node(key, value);
			return true;
		}
		if (_root->_key < key)
		{
			return _Insert_R(_root->_right, key, value);
		}
		else if (_root->_key > key)
		{
			return _Insert_R(_root->_left, key, value);
		}
		else
			return false;
	}
	bool Remove_R(const K& key)
	{
		return _Remove_R(_root,key);
	}
	bool _Remove_R(Node*& _root, const K& key)
	{
		if(_root == NULL)
			return false;
		if (_root->_key < key)
			return _Remove_R(_root->_right, key);
		else if (_root->_key > key)
			return _Remove_R(_root->_left, key);
		else
		{
			Node* del = _root;

			if (_root->_left == NULL)
				_root = _root->_right;
			else if (_root->_right == NULL)
				_root = _root->_left;
			else
			{
				Node* fInOrder = _root->_right;
				while (fInOrder->_left)
				{
					fInOrder = fInOrder->_left;
				}
				swap(del->_key, fInOrder->_key);
				swap(del->_value, fInOrder->_value);
				return _Remove_R(_root->_right, key);
			}
		}
	}
public:
	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}
	void _InOrder(Node* _root)
	{
		if (_root == NULL)
		{
			return;
		}
		_InOrder(_root->_left);
		cout << _root->_key<<" ";
		_InOrder(_root->_right);
	}
};

void test()
{
	int a[] = {53,17,9,45,23,78,65,94,81,88};
	BSTree<int, double> t1;

	for (int i = 0; i < (sizeof(a) / sizeof(int)); ++i)
	{
		/*t1.Insert_R(a[i], a[i]);*/
		t1.Insert(a[i], a[i]);
	}
	t1.InOrder();
	t1.Find_R(9);
	/*t1.Remove_R(53);
	t1.InOrder();*/

}
