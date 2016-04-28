enum Color
{
	RED,
	BLACK,
};
template <class K, class V>
struct RBTreeNode
{
	K _key;
	V _value;

	RBTreeNode<K, V>* _left;
	RBTreeNode<K, V>* _right;
	RBTreeNode<K, V>* _parent;
	Color _col;

	RBTreeNode(const K& key, const V& value,Color col = RED)
		:_key(key)
		, _value(value)
		, _left(NULL)
		, _right(NULL)
		, _parent(NULL)
		, _col(col)
	{}
};
template <class K, class V>

class RBTree
{
	typedef RBTreeNode Node;
protected:
	Node* _root;
public:
	RBTree()
		:_root(NULL)
	{}
	~RBTree()
	{}
public:
	bool Insert(const K& key, const V& value)
	{
		if (_root == NULL)
		{
			_root = new Node(key, value, BLACK);
			return true;
		}
		
		Node* cur = _root;
		Node* parent = NULL;
		//1.构造二叉搜索树
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
				return false;
		}
		cur = new Node(key, value, RED);
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
		//调整结点--颜色规则
		while (cur!=_root && parent->_col==RED)
		{
			Node* grandfather = parent->_parent;

			
			if (parent == grandfather->_left)
			{
				Node* uncle = grandfather->_right;

				//case1 --> cur为红，p为红，g为黑，u存在且为红
				if (uncle && uncle->_col = RED)
				{
					parent->_col = uncle->_col = BLACK;
					grandfather->_col = RED;
					grandfather = cur;
					parent = cur->_parent;
				}
				else// case2/case3 --> u不存在或u为黑
				{
					if (cur == parent->_right)
					{
						_RotateL(parent);
					}
					grandfather->_col = RED;
					parent->_col = BLACK;
					_RotateR(grandfather);
				}
			}
			else
			{

			}
		}
		_root = BLACK;
	}
public:
	void InOrder()
	{
		_Inorder(_root);
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
	void _RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		parent->_right = subRL;
		if (subRL)
			subRL->_parent = parent;
		subR->_left = parent;
		subR->_parent = parent->_parent;
		parent->_parent = subR;


	}
	void _RotateR(Node* parent)
	{

	}
};