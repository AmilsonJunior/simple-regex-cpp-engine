#include <iostream>
#include <string>
#include <stack>

#include "State.h"
#include "Nfa.h"

class Program
{
public:
    void run()
    {
        while (true)
        {
            std::string regex, word;
            std::cout << "regex: ";
            std::getline(std::cin, regex);

            if (regex == "-1")
                break;

            while (true)
            {
                std::cout << "[ " << regex << " ] - "
                          << "word: ";
                std::getline(std::cin, word);

                if (word == "-1")
                    break;

                std::string regex_with_operators = Parser::insert_concat_operator(regex);
                std::string post_fixed_regex = Parser::to_postfix(regex_with_operators);
                
                Alphabet alphabet(post_fixed_regex);

                Nfa *nfa_graph = NfaFactory::regex_to_nfa(post_fixed_regex);
                if (!nfa_graph)
                {
                    std::cout << "Invalid Regular Expression. " << regex << " Cannot be represented as NFA.\n";
                    WaitAndClear();
                    break;
                }
                else
                {
                    if (!alphabet.get().size())
                    {
                        std::cout << "Invalid alphabet!\n";
                        WaitAndClear();
                        break;
                    }

                    std::cout << "Alphabet: " << alphabet.get() << std::endl;
                    std::cout << "Valid Regular Expression!\n";
                }

                if (nfa_graph->test(word))
                    std::cout << "\"" << word  << "\"" << " accepted by [ " << regex << " ]\n";
                else
                {
                    std::cout << "\"" << word << "\"" << " not accepted by [ " << regex << " ]\n";
                }

                WaitAndClear();
            }
        }
    }

protected:
    void WaitAndClear()
    {
        std::cin.get();
        system("clear");
    }
};

int main()
{
    Program prog;

    prog.run();

    return 1;
}
