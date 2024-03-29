#include <iostream>
#include <string>
#include <stack>
#include <unordered_map>
#include <sstream>
#include <cctype>
#include <cmath>
#include <functional>
#include <iomanip>

std::unordered_map<std::string, double> vars;
std::unordered_map<std::string, std::function<double(double)>> funcs =
{
	{"exp", exp},
	{"log", log},
	{"log2", log2},
	{"log10", log10},
	{"sqrt", sqrt},
	{"cbrt", cbrt},
	{"sin", sin},
	{"cos", cos},
	{"tan", tan},
	{"asin", asin},
	{"acos", acos},
	{"atan", atan}
};

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
				return;
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
				return;
			}
			s.push(op2 % op1);
		}
		else if (isalpha(ch))
		{
			ss.putback(ch);
			std::string iStr;
			ss >> iStr;
			if (iStr == "let")
			{
				std::string val;
				ss >> iStr >> ch >> val;
				vars[iStr] = atof(val.c_str());
				return;
			}
			else if (iStr == "pow")
			{
				if (s.size() < 2)
				{
					std::cerr << "Function \"pow\" needs two arguments" << std::endl;
					return;
				}
				double a = s.top(); s.pop();
				double b = s.top(); s.pop();
				s.push(pow(b, a));
			}
			else if (auto entity = funcs.find(iStr); entity != funcs.end())
			{
				if (s.size() == 0)
				{
					std::cout << "Function " << std::get<0>(*entity) << " needs argument" << std::endl;
					return;
				}

				auto func = std::get<1>(*entity);
				double a = s.top(); s.pop();
				s.push(func(a));
			}
			else
			{
				if (vars.count(iStr) != 1)
				{
					std::cerr << "Undefined identifier" << std::endl;
					return;
				}

				s.push(vars[iStr]);
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
		std::cout << std::setprecision(11) << std::fixed << "= " << (!s.empty() ? s.top() : 0) << std::endl;
}

int main()
{
	std::cout << "Enter expression to calculate or 'q' to quit:" << std::endl;

	vars["PI"]  = 3.14159265359;
	vars["E"]   = 2.71828182845;
	vars["PHI"] = 1.61803398874; // golden ration

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
