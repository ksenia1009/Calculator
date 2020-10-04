#pragma once
template <class T>
class Stack
{
private:
	T* mem;
	int size;
	int last;
public:
	Stack<T>(int _size = 20)
	{
		last = 0;
		size = _size;
		mem = new T[size];
	}
	Stack<T>(const Stack<T>& st)
	{
		last = st.last;
		size = st.size;
		mem = new T[size];
		for (int i = 0; i < size; i++)
		{
			mem[i] = st.mem[i];
		}
	}
	~Stack<T>()
	{
		delete[] mem;
	}
	Stack<T>& operator=(const Stack<T>& st)
	{
		if (size != st.size)
		{
			if (size != 0)
			{
				delete[] mem;
			}
			size = st.size;
			mem = new T[size];
		}
		for (int i = 0; i < size; i++)
		{
			mem[i] = st.mem[i];
		}
		last = st.last;
		return *this;
	}
	void Push(T tmp)
	{
		if (last < size)
		{
			mem[last++] = tmp;
		}
	}
	T Top()
	{
		return mem[last - 1];
	}
	T Pop()
	{
		return mem[--last];
	}
	int isEmpty()
	{
		return last == 0;
	}
	int isFull()
	{
		return last == size;
	}
};
