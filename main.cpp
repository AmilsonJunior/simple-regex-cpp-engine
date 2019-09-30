#include <iostream>
#include <string>
#include <stack>

#include "state.h"
#include "nfa.h"

class program 
{
public:
    void run()
    {
        while(true)
        {
            std::string regex, word;
            std::cout << "regex: ";
            std::getline(std::cin, regex);

            if (regex == "-1")
                break;

            std::cout << "word: ";
            std::getline(std::cin, word);

            std::string regex_with_operators = Parser::insert_concat_operator(regex);
            std::cout << regex_with_operators << "\n";
            std::string post_fixed_regex = Parser::to_postfix(regex_with_operators);
            std::cout << post_fixed_regex << "\n";

            nfa* nfa_graph = nfa_factory::regex_to_nfa(post_fixed_regex);
            if (nfa_graph->test(word))
                std::cout << "valid\n";
            else
            {
                std::cout << "invalid\n";
            }
        }
    }
};

int main () 
{
    program prog;
    
    prog.run();

    return 1;
}
