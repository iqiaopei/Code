#include <iostream>
#include <vector>
using namespace std;

//给40亿个不重复的无符号整数，没排过序。给一个无符号整数，如何快速判断一个数是否在这40亿个数中

class BitMap
{
private:
	vector<size_t> _arrays;
	size_t _size;//已存的数据个数
public:
	BitMap()
		:_size(0)
	{}
	BitMap(size_t size)//这里的size指的是总共要存数据的个数，即开多大的空间
		:_size(0)
	{
		_arrays.resize(size >> 5 + 1);//右移5位相当于除以32（一个数字是1位，一个字节8位，一个int四个字节）。+1是为了保证不能被32整除的剩下的整数也能参与运算
	}
	bool Set(size_t num)//某位置1
	{
		size_t index = num >> 5;//index是num所在的数组下标(num/32)
		size_t n = num % 32;//n是num所在下标字节的第几位（num%32）

		if (_arrays[index] & (1 << n))//如果该位原本就是1,则结果为1返回false
		{
			return false;
		}
		else
		{
			_arrays[index] |= (1 << n);//1进行左移再与原来字节进行“或”操作，就可以将该位置1
			++_size;
			return true;
		}
	}
	bool ReSet(size_t num)//某位置1
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
	bool Test(size_t num)//num是否存在
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