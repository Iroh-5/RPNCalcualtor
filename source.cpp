#include <iostream>
#include <string>
#include <stack>
#include <unordered_map>
#include <sstream>
#include <cctype>
#include <cmath>

std::unordered_map<std::string, double> vars;

void calculate(std::stringstream& ss)
{
	std::stack<double> s;
	char ch;
	while (ss >> ch)
	{
		if (ch == '+')
		{
			double op1 = s.top(); s.pop();
			double op2 = s.top(); s.pop();
			s.push(op1 + op2);
		}
		else if (ch == '-')
		{
			double op1 = s.top(); s.pop();
			double op2 = s.top(); s.pop();
			s.push(op2 - op1);
		}
		else if (ch == '*')
		{
			double op1 = s.top(); s.pop();
			double op2 = s.top(); s.pop();
			s.push(op1 * op2);
		}
		else if (ch == '/')
		{
			double op1 = s.top(); s.pop();
			double op2 = s.top(); s.pop();
			if (op1 == 0)
			{
				std::cerr << "Division by zero" << std::endl;
				std::terminate();
			}
			s.push(op2 / op1);
		}
		else if (ch == '%')
		{
			int op1 = static_cast<int>(s.top()); s.pop();
			int op2 = static_cast<int>(s.top()); s.pop();
			if (op1 == 0)
			{
				std::cerr << "Division by zero" << std::endl;
				std::terminate();
			}
			s.push(op2 % op1);
		}
		else if (isalpha(ch))
		{
			ss.putback(ch);
			std::string iStr;
			ss >> iStr;
			if (iStr.compare("let") == 0)
			{
				std::string val;
				ss >> iStr >> ch >> val;
				vars[iStr] = atof(val.c_str());
				return;
			}
			else
			{
				if (vars.count(iStr) != 1)
				{
					std::cerr << "Undefined identifier" << std::endl;
					std::terminate();
				}
				else
				{
					s.push(vars[iStr]);
				}
			}
		}
		else
		{
			ss.putback(ch);
			double val;
			ss >> val;
			s.push(val);
		}
	}

	if (s.size() > 1)
		std::cout << "Invalid syntax" << std::endl;
	else
		std::cout << "= " << (!s.empty() ? s.top() : 0) << std::endl;
}

int main()
{
	std::cout << "Enter expression to calculate or 'q' to quit" << std::endl;

	vars["PI"] = 3.14159265359;
	vars["E"]  = 2.7182818284;

	while (true)
	{
		char ch;
		std::string input;
		std::cout << "> ";
		getline(std::cin, input);
		std::stringstream ss(input);

		ss >> ch;
		if (ch != 'q')
		{
			ss.putback(ch);
			calculate(ss);
		}
		else
		{
			break;
		}
	}

	return 0;
}
