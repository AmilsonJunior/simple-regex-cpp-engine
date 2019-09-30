#include <string>
#include <iostream>
#include <stack>
#include <map>

namespace parser
{
static std::string insert_concat_operator(std::string regex)
{
	std::string result_str;
	for (int i = 0; i < regex.length(); i++)
	{
		const char token = regex[i];
		result_str.push_back(token);

		if (token == '(' || token == '+')
			continue;

		if (i < regex.length() - 1)
		{
			const char lookahead = regex[i + 1];
			if (lookahead == '*' || lookahead == '+' || lookahead == ')')
				continue;

			result_str.push_back('.');
		}
	}

	return result_str;
}

static std::string charToStr(char c)
{
	std::string str;
	str.push_back(c);
	return str;
}

static std::string to_postfix(std::string regex)
{
	std::string result;
	std::map<std::string, int> operator_precedence;

	operator_precedence.insert({"+", 0});
	operator_precedence.insert({".", 1});
	operator_precedence.insert({"*", 2});

	std::stack<std::string> operator_stack;

	for (char token : regex)
	{
		if (token == '.' || token == '+' || token == '*')
		{
			while (operator_stack.size() &&
				   operator_stack.top() != "(" &&
				   operator_precedence[operator_stack.top()] >= operator_precedence[charToStr(token)])
			{
				result.push_back(operator_stack.top()[0]);
				operator_stack.pop();
			}

			operator_stack.push(charToStr(token));
		}
		else if (token == '(' || token == ')')
		{
			if (token == '(')
			{
				operator_stack.push(charToStr(token));
			}
			else
			{
				while(operator_stack.top() != "(")
				{
					result.push_back(operator_stack.top()[0]);
					operator_stack.pop();
				}
				operator_stack.pop();
			}
		}
		else
		{
			result.push_back(token);
		}
	}

	while (operator_stack.size())
	{
		result.push_back(operator_stack.top()[0]);
		operator_stack.pop();
	}

	return result;
}
} // namespace parser
