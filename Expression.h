#pragma once
#include "RPN.h"
#include <cmath>
class Expression
{
private:
	RPN pol;
public:
	Expression(string str = " ");
	Expression(const Expression& ex);
	~Expression();
	Expression& operator=(const Expression& ex);
	double getValue();
	string toString();
	int getCountTable();
	Note<double> operator[](int k);
	void setValue(string _name, double val);
};

Expression::Expression(string str)
{ 
	try {
		pol = RPN(str);
	}
	catch (string s) {
		throw "Invalid input: " + s;
	}
}

Expression::Expression(const Expression& ex)
{
	try {
                pol = RPN(ex.pol);
        }
        catch (string s) {
                throw "Invalid input: " + s;
        }
}

Expression::~Expression()
{
}

Expression& Expression::operator=(const Expression& ex)
{
	pol = ex.pol;
	return *this;
}

int Expression::getCountTable()
{
	return pol.getTable().getCount();
}

Note<double> Expression::operator[](int k)
{
	return pol.getTable()[k];
}

void Expression::setValue(string _name, double val)
{
	if (pol.getTable().Search(_name).getName() != " ")
	{
		pol.getTable().Add(Note<double>(_name, val));
	}
}

double Expression::getValue()
{
	double left, right;
	Stack<double> st(20);
	for (int i = 0; i < pol.getCount(); i++)
	{
		if (pol[i] == "+")
		{
			right = st.Pop();
			left = st.Pop();
			st.Push(left + right);
		}
		else
		{
			if (pol[i] == "-")
			{
				right = st.Pop();
				left = st.Pop();
				st.Push(left - right);
			}
			else
			{
				if (pol[i] == "*")
				{
					right = st.Pop();
					left = st.Pop();
					st.Push(left * right);
				}
				else
				{
					if (pol[i] == "/")
					{
						right = st.Pop();
						left = st.Pop();
						st.Push(left / right);
					}
					else
					{
						if (pol[i] == "^")
						{
							right = st.Pop();
							left = st.Pop();
							st.Push(pow(left, right));
						} 
						else
						{
							st.Push(pol.getTable().Search(pol[i]).getValue());
						}
					}
				}
			}
		}
	}
	return std::round(st.Pop() * 100) / 100;
}
