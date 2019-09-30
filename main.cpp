#include <iostream>
#include <string>
#include <stack>

#include "state.h"
#include "nfa.h"
#include "parser.h"

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

            std::string regex_with_operators = parser::insert_concat_operator(regex);
            std::cout << regex_with_operators << "\n";
            std::cout << parser::to_postfix(regex_with_operators) << "\n";
        }
    }

protected: // nfa = fragment = |> (state) --> a (state)
    nfa* to_nfa(std::string regex)
    {
       
       return nullptr;
    }

    // nfa* to_nfa(std::string regex)
    // {
    //     // if (regex == "")
    //     //     return create_nfa_from_epsilon();
        
    //     std::stack<nfa*> _stack;

    //     for (char token : regex) 
    //     {
    //         if (token == '*') 
    //         {
    //             nfa* _closure = closure(_stack.top());
    //             _stack.pop();
    //             _stack.push(_closure);
    //         }
    //         else if (token == '+')
    //         {
    //             if (_stack.size() >= 2)
    //             {
    //                 nfa* right = _stack.top();
    //                 _stack.pop();
    //                 nfa* left = _stack.top();
    //                 _stack.pop();
    //                 _stack.push(disjunction(left, right));
    //             }
    //             else
    //             {
    //                 std::cout << "error: cannot apply + over stack size < 2\n";
    //             }
    //         }
    //         else
    //         {
    //             _stack.push(create_nfa_from_symbol(std::to_string(token)));
    //         }
    //     }

    //     nfa* top = _stack.top();
    //     _stack.pop();
        
    //     return top;
    // }
};

int main () 
{
    program prog;
    
    prog.run();

    return 1;
}
