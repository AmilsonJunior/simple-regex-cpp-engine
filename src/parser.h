#pragma once
#include <string>
#include <iostream>
#include <stack>
#include <map>

using namespace std;

class Parser
{
public:
	static string insert_concat_operator(string regex);
	static string charToStr(char c);
	static string to_postfix(string regex);
};
