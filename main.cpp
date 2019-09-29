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

            // WIP

            // std::vector<nfa*> list = {
            //     create_nfa_from_symbol("b"),
            //     create_nfa_from_symbol("c")
            // };

            // nfa* res = orMultiple(create_nfa_from_symbol("a"), list);
            // std::cout << res->test("a") << std::endl; // true
            // std::cout << res->test("b") << std::endl; // true
            // std::cout << res->test("c") << std::endl; // true
            // std::cout << res->test("d") << std::endl; // false
            // std::cout << res->test("abc") << std::endl; // false

            nfa* res = nfa_factory::closure(nfa_factory::create_nfa_from_symbol("a"));
            std::cout << res->test("") << std::endl; // true
            std::cout << res->test("a") << std::endl; // true
            std::cout << res->test("aa") << std::endl; // true
            std::cout << res->test("aaa") << std::endl; // true
            std::cout << res->test("ab") << std::endl; // false
            std::cout << res->test("accb") << std::endl; // false
        }
    }

protected: // nfa = |> (state) --> a (state)
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
