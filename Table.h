#pragma once
#include "Note.h"
#include <string>

template <class M>
class Table
{
private:
	Note<M>* mem;
	int size;
	int count;
public:
	int getCount()
	{
		return count;
	}
	Table<M>(int _size = 0)
	{
		size = _size;
		count = 0;
		Note<M> m;
		mem = new Note<M>[size];
		for (int i = 0; i < size; i++)
		{
			mem[i] = m;
		}
	}
	Table<M>(const Table<M>& tb)
	{
		size = tb.size;
		count = tb.count;
		mem = new Note<M>[size];
		for (int i = 0; i < size; i++)
		{
			mem[i] = tb.mem[i];
		}
	}
	~Table<M>()
	{
		delete[] mem;
	}
	Table<M> operator=(const Table<M>& tb)
	{
		if (size != tb.size)
		{
			if (size != 0)
			{
				delete[] mem;
			}
			size = tb.size;
			count = tb.count;
			mem = new Note<M>[size];
		}
		for (int i = 0; i < size; i++)
		{
			mem[i] = tb.mem[i];
		}
		return *this;
	}
	Note<M> Search(string _name)
	{
		int l = -1;
		Note<M> tmp;
		for (int i = 0; (i < count) && (l == -1); ++i)
		{
			if (_name == mem[i].getName())
			{
				l = i;
				tmp = mem[i];
			}
		}
		return tmp;
	}
	void Add(Note<M> tmp)
	{
		int l = -1;
		for (int i = 0; (i < count) && (l == -1); ++i)
		{
			if (tmp.getName() == mem[i].getName())
			{
				l = i;
			}
		}
		if (l == -1)
		{
			mem[count++] = tmp;
		}
		else
		{
			mem[l] = tmp;
		}
	}
	void Delete(string _name)
	{
		int l = -1;
		for (int i = 0; (i < count) && (l == -1); i++)
		{
			if (_name == mem[i].getName())
			{
				l = i;
			}
		}
		if (l >= 0)
		{
			mem[l] = mem[--count];
		}
	}
	Note<M> operator[](int k)
	{
		Note<M> tmp;
		if ((k >= 0) && (k < count))
		{
			return mem[k];
		}
		else
		{
			return tmp;
		}
	}
	int isFull()
	{
		if (count == size)
		{
			return 1;
		}
		return 0;
	}
	int isEmpty()
	{
		if (count == 0)
		{
			return 1;
		}
		return 0;
	}
};
