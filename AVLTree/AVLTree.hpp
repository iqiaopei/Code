#include<assert.h>

template<class K,class V>
struct AVLTreeNode
{
	K _key;
	V _value;

	AVLTreeNode<K, V>* _left;
	AVLTreeNode<K, V>* _right;
	AVLTreeNode<K, V>* _parent;
	int _bf;//平衡因子：右-左

	AVLTreeNode(const K& key, const V&value)
		: _key(key)
		, _value(value)
		, _left(NULL)
		, _right(NULL)
		, _parent(NULL)
		, _bf(0)
	{}
};

template<class K, class V>
class AVLTree
{
	typedef AVLTreeNode<K, V> Node;
protected:
	Node* _root;
public:
	AVLTree()
		: _root(NULL)
	{}
	~AVLTree()
	{}
public:
	bool Insert(const K& key,const V& value)
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
			if (cur->_key > key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else if (cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else
				false;
		}
		//将cur插在叶子结点下面，并连接起来
		cur = new Node(key, value);
		if (parent->_key > key)
		{
			parent->_left = cur;
			cur->_parent = parent;
		}
		else
		{
			parent->_right = cur;
			cur->_parent = parent;
		}
		//调整平衡因子
		bool isRotate = false;
		while (parent)
		{
			if (parent->_left == cur)
				--parent->_bf;
			else
				++parent->_bf;
			//如果平衡因子不为0,1，-1，就调整
			if (parent->_bf == 0)
				break;
			else if (parent->_bf == 1 || parent->_bf == -1)
			{
				cur = parent;
				parent = cur->_parent;
			}
			else//说明需要调整
			{
				isRotate = true;
				if (parent->_bf == 2)
				{
					if (cur->_bf == 1)
						_RotateL(parent);
					else
						_RotateRL(parent);
				}
				else
				{
					if (cur->_bf == -1)
						_RotateR(parent);
					else
						_RotateLR(parent);
				}
			}
			break;
		}
		if (isRotate)//把旋转之后的各结点关系连接起来
		{
			Node* _pNode = parent->_parent;

			if (_pNode == NULL)
			{
				_root = parent;
			}
			else
			{
				if (_pNode->_key > parent->_key)
					_pNode->_right = parent;
				else
					_pNode->_left = parent;
			}
		}
		return true;
	}
public:
	int Hight(Node* _root)
	{
		if (_root == NULL)
			return 0;
		int left = Hight(_root->_left) - 1;
		int right = Hight(_root->_right) - 1;

		return left > right ? left : right;
	}
	void isBalance()
	{
		_isBalance(_root);
	}
	bool _isBalance(Node* _root)
	{
		if (_root == NULL)
			return true;
		int left = Hight(_root->_left);
		int right = Hight(_root->_right);
		int bf = abs(left - right);

		if (bf > 1)
			return false;
		if (bf != abs(_root->_bf))
		{
			cout << "bf有错误" << endl;
			return false;
		}
		cout << _root->_bf <<endl;
		return _isBalance(_root->_left) && _isBalance(_root->_right);
	}
	void InOrder()
	{
		 _InOrder(_root);
		 cout << endl;
	}
	void _InOrder(Node* _root)
	{
		if (_root == NULL)
			return;
		_InOrder(_root->_left);
		cout << _root->_key << " ";
		_InOrder(_root->_right);
	}
protected:
	void _RotateL(Node*& parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		//把subRL作为parent的右孩子，parent作为subR的左孩子
		
		parent->_right = subRL;
		if (subRL)
		{
			subRL->_parent = parent;
		}
		subR->_left = parent;
		subR->_parent = parent->_parent;
		parent->_parent = subR;

		parent->_bf = subR->_bf = 0;
		parent = subR;
	}
	void _RotateR(Node*& parent)// /
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		parent->_left = subLR;

		if (subLR)
		{
			subLR->_parent = parent;
		}
		subL->_right = parent;
		subL->_parent = parent->_parent;
		parent->_parent = subL;

		parent->_bf = subL->_bf = 0;
		parent = subL;
	}
	void _RotateLR(Node*& parent)//  <
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		//左单旋
		subL->_right = subLR->_left;
		if (subLR->_left)
			subLR->_left->_parent = subL;
		subLR->_left = subL;
		subLR->_parent = subL->_parent;
		subL->_parent = subLR;
		if (subLR->_bf == 0 || subLR->_bf == -1)
				subL->_bf = 0;
		else                  //bf = 1
			subL->_bf = -1;

		//右单旋
		parent->_left = subLR->_right;
		if (subLR->_right)
			subLR->_right->_parent = parent;
		subLR->_right = parent;
		subLR->_parent = parent->_parent;
		parent->_parent = subLR;
		if (subLR->_bf == -1)
			parent->_bf = 1;
		else                 //bf = 0、1
			parent->_bf = 0;
		//subLR->_bf = 0;
		parent = subLR;
	}
	void _RotateRL(Node*& parent)// >
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		//右单旋
		subR->_left = subRL->_right;
		if (subRL->_right)
			subRL->_right->_parent = subR;
		subRL->_right = subR;
		subRL->_parent = parent;
		subR->_parent = subRL;
		if (subRL->_bf == 0 || subRL->_bf == 1) 
			subR->_bf = 0;
		else
			subR->_bf = 1;
		//左单旋
		parent->_right = subRL->_left;
		if (subRL->_left)
			subRL->_left->_parent = parent;
		subRL->_left = parent;
		subRL->_parent = parent->_parent;
		parent->_parent = subRL;
		if (subRL->_bf == 0 || subRL->_bf == -1)
			subR->_bf = 0;
		else
			subR->_bf = -1;
		//subRL->_bf = 0;
		parent = subRL;
	}
};

void test()
{
	int a[] = { 4,2,6,1,3,5,15,7,16,14 };
	// 50,40,60,10,45,70,5,30,20
	//16, 3, 7, 11, 9, 26, 18, 14, 15
	AVLTree<int, double> t;
	for (int i = 0; i < (sizeof(a) / sizeof(int)); ++i)
	{
		t.Insert(a[i], a[i]);
	}
	t.InOrder();
	t.isBalance();
}