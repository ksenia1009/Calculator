#pragma once
#include <string>

using namespace std;
template <class N>
class Note
{
private:
	string Name;
	N Value;
public:
	Note<N>(string str = " ", N val = 0)
	{
		Name = str;
		Value = val;
	}
	N getValue()
	{
		return Value;
	}
	string getName()
	{
		return Name;
	}
	void Set(N val)
	{
		Value = val;
	}
};
