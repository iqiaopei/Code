#include <iostream>
#include <vector>
using namespace std;

//��40�ڸ����ظ����޷���������û�Ź��򡣸�һ���޷�����������ο����ж�һ�����Ƿ�����40�ڸ�����

class BitMap
{
private:
	vector<size_t> _arrays;
	size_t _size;//�Ѵ�����ݸ���
public:
	BitMap()
		:_size(0)
	{}
	BitMap(size_t size)//�����sizeָ�����ܹ�Ҫ�����ݵĸ������������Ŀռ�
		:_size(0)
	{
		_arrays.resize(size >> 5 + 1);//����5λ�൱�ڳ���32��һ��������1λ��һ���ֽ�8λ��һ��int�ĸ��ֽڣ���+1��Ϊ�˱�֤���ܱ�32������ʣ�µ�����Ҳ�ܲ�������
	}
	bool Set(size_t num)//ĳλ��1
	{
		size_t index = num >> 5;//index��num���ڵ������±�(num/32)
		size_t n = num % 32;//n��num�����±��ֽڵĵڼ�λ��num%32��

		if (_arrays[index] & (1 << n))//�����λԭ������1,����Ϊ1����false
		{
			return false;
		}
		else
		{
			_arrays[index] |= (1 << n);//1������������ԭ���ֽڽ��С��򡱲������Ϳ��Խ���λ��1
			++_size;
			return true;
		}
	}
	bool ReSet(size_t num)//ĳλ��1
	{
		size_t index = num >> 5;
		size_t n = num % 32;

		if (!(_arrays[index] & (1 << n)))
		{
			return false;
		}
		else
		{
			_arrays[index] &= (~(1 << n));
			++_size;
			return true;
		}
	}
	bool Test(size_t num)//num�Ƿ����
	{
		size_t index = num << 5;
		size_t n = num % 32;

		return (_arrays[index] & (1 << n));
	}

};
void BitMapTest()
{
	size_t a[40] = {};
	//a[3] = 2;
	BitMap b(10);
	b.Set(2);
	b.Test(2);
}