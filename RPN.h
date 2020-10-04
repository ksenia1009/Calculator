#pragma once
#include "Table.h"
#include "Stack.h"
#include <iostream>
#include <string>
#include <cstdio>

using namespace std;
class RPN
{
private:
	string str;
	string* pol;
	int size;
	int count;
	Table<double> tabval;
	Table<int> tabprior;
	Stack<Note<int> > stackoper;
	void MakeTabPrior();
	void StrToLecs(string str, const string& delimiters, int& k, string w[]);
	void WorkLeft();
	void WorkRight();
	void WorkOperand(string tmp);
	void WorkOperation(Note<int> tmp);
	void WorkEndStr();
	void MakeRPN();
public:
	int getCount();
	string operator[](int k);
	Table<double>& getTable();
	RPN(string _str = " ");
	RPN(const RPN& p);
	~RPN();
	RPN& operator=(const RPN& p);
};

void RPN::MakeTabPrior()
{
	tabprior = Table<int>(5);
	tabprior.Add(Note<int>("+", 1));
	tabprior.Add(Note<int>("-", 1));
	tabprior.Add(Note<int>("*", 2));
	tabprior.Add(Note<int>("/", 2));
	tabprior.Add(Note<int>("^", 3));
}

RPN::RPN(string _str)
{
	str = _str;
	if (str.find('-') == 0)
		str.insert(0, "0");
	size = str.length();
	pol = new string[size];
	MakeTabPrior();
	stackoper = Stack<Note<int> >((size/2)+1);
	tabval = Table<double>((size / 2) + 1);
	try {
		MakeRPN();
	}
	catch (string s) {
		throw s;
	}
}

RPN::~RPN()
{
	delete[] pol;
}

RPN::RPN(const RPN& p)
{
	str = p.str;
	size = p.size;
	pol = new string[size];
	count = p.count;
	for (int i = 0; i < count; i++)
	{
		pol[i] = p.pol[i];
	}
	tabval = p.tabval;
	tabprior = p.tabprior;
	stackoper = p.stackoper;
}

Table<double>& RPN::getTable()
{
	return tabval;
}

RPN& RPN::operator=(const RPN& p)
{
	if (size != p.size)
	{
		if (size != 0)
		{
			delete[] pol;
		}
		size = p.size;
		pol = new string[size];
	}
	str = p.str;
	count = p.count;
	for (int i = 0; i < size; i++)
	{
		pol[i] = p.pol[i];
	}
	tabval = p.tabval;
	tabprior = p.tabprior;
	stackoper = p.stackoper;
	return *this;
}

void RPN::StrToLecs(string str, const string& delimiters, int& k, string w[])
{
	string tmp = str + " ";
	k = 0;
	for (int i = 0; i < tmp.length(); i++)
	{
		if (delimiters.find(tmp[i]) == string::npos)
		{
			w[k].push_back(tmp[i]);
		}
		else
		{
			if (tmp[i] == ' ')
			{
				if (!w[k].empty())
				{
					w[++k] = "";
				}
			}
			else
			{
				if (!w[k].empty())
				{
					k++;
				}
				w[k] = tmp[i];
				w[++k] = "";
			}
		}
	}

}

void RPN::WorkLeft()
{
	Note<int> _tmp("(", 0);
	stackoper.Push(_tmp);
}

void RPN::WorkRight()
{
	while (stackoper.Top().getName() != "(")
	{
		pol[count++] = stackoper.Pop().getName();
	}
	stackoper.Pop();
}

void RPN::WorkOperand(string tmp)
{
	if ((tmp >= "0") && (tmp <= "9"))
	{
		if (tmp.find(",") != string::npos)
			tmp.replace(tmp.find(","), 1, ".");
		tabval.Add(Note<double>(tmp, stod(tmp)));
	}
	else
		throw tmp;
	pol[count++] = tmp;
}

void RPN::WorkOperation(Note<int> tmp)
{
	while ((!stackoper.isEmpty()) && (stackoper.Top().getValue() >= tmp.getValue()))
	{
		pol[count++] = stackoper.Pop().getName();
	}
	stackoper.Push(tmp);
}

void RPN::WorkEndStr()
{
	while (!(stackoper.isEmpty()))
	{
		pol[count++] = stackoper.Pop().getName();
	}
}

int RPN::getCount()
{
	return count;
}

string RPN::operator[](int k)
{
	if ((k >= 0) && (k <= count))
		return pol[k];
	else return " ";
}

void RPN::MakeRPN()
{
	int t = str.length();
	int newSize = t + 1;
	string* arrLecs = new string[newSize];
	int countLecs = 0;
	string razd = "+-*/^() ";
	StrToLecs(str, razd, countLecs, arrLecs);
	count = 0;
	for (int i = 0; i < countLecs; i++)
	{
		if (arrLecs[i] == "(")
		{
			WorkLeft();
		}
		else
		{
			if (arrLecs[i] == ")")
			{
				WorkRight();
			}
			else
			{
				Note<int> tmp = tabprior.Search(arrLecs[i]);
				if (tmp.getName() == " ")
				{
					WorkOperand(arrLecs[i]);
				}
				else
				{
					WorkOperation(tmp);
				}
			}
		}
	}
	WorkEndStr();
	delete[] arrLecs;
}
