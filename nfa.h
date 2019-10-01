#pragma once

#include <stack>
#include <vector>

#include "state.h"
#include "parser.h"

class nfa
{
public:
    nfa(state* start, state* end)
        : in_state(start)
        , out_state(end)
    {
    }

    bool test(std::string str)
    {
        return in_state->test(str);
    }

    state* in_state = nullptr;
    state* out_state = nullptr;
};

class nfa_factory
{
public:
    static std::string get_alphabet(std::string regex)
    {
        std::string alphabet;
        for (char token : regex)
        {
            if (isalpha(token) && alphabet.find(token) == -1)
            {
                alphabet.push_back(token);
            }
        }

        return alphabet;
    }

    static nfa* regex_to_nfa(std::string regex)
    {
        std::string alphabet = get_alphabet(regex);

        std::cout << alphabet << "\n";

        std::stack<nfa*> fragments_stack;
        for (char token : regex)
        {
            if (token == '+')
            {
                if (fragments_stack.size() >= 2)
                {
                    nfa* right = fragments_stack.top();
                    fragments_stack.pop();
                    nfa* left = fragments_stack.top();
                    fragments_stack.pop();
                    fragments_stack.push(_disjunction(left, right));
                }
                else
                {
                    return nullptr;
                }
                
            }
            else if (token == '*')
            {
                if (fragments_stack.size() >= 1)
                {
                    nfa* result = closure(fragments_stack.top());
                    fragments_stack.pop();
                    fragments_stack.push(result);
                }
                else
                {
                    return nullptr;
                }
                
            }
            else if (token == '.')
            {
                if (fragments_stack.size() >= 2)
                {
                    nfa* right = fragments_stack.top();
                    fragments_stack.pop();
                    nfa* left = fragments_stack.top();
                    fragments_stack.pop();
                    fragments_stack.push(_concat(left, right));
                }
                else
                {
                    return nullptr;
                }
                
            }
            else
            {
                if (token != ' ')
                    fragments_stack.push(create_nfa_from_symbol(Parser::charToStr(token)));
                else
                {
                    return nullptr;
                }
                
            }
        }

        nfa* top = fragments_stack.top();
        fragments_stack.pop();

        return top;
    }

    static nfa* closure(nfa* fragment)
    {
        state* start = new state(false);
        state* end = new state(true);

        start->add_symbol_transition(EPSILON, end);
        start->add_symbol_transition(EPSILON, fragment->in_state);

        fragment->out_state->m_is_final = false;
        fragment->out_state->add_symbol_transition(EPSILON, end);

        end->add_symbol_transition(EPSILON, fragment->in_state);

        return new nfa(start, end);
    }

    static nfa* concat(nfa* first, std::vector<nfa*> rest)
    {
        for (nfa* item : rest)
        {
            first = _concat(first, item);
        }

        return first;
    }

    // or
    static nfa* disjunction(nfa* first, std::vector<nfa*> rest)
    {
        for (nfa* item : rest)
        {
            first = _disjunction(first, item);
        }

        return first;
    }

    static nfa* create_nfa_from_symbol(std::string symbol)
    {
        state* in_state = new state(false);
        state* out_state = new state(true);

        in_state->add_symbol_transition(symbol, out_state);

        return new nfa(in_state, out_state);
    }

private:
    // + ou |
    static nfa* _disjunction(nfa* first, nfa* second)
    {
        state* start = new state(false);
        state* end = new state(true);

        start->add_symbol_transition(EPSILON, first->in_state);
        start->add_symbol_transition(EPSILON, second->in_state);

        first->out_state->m_is_final = false;
        second->out_state->m_is_final = false;

        first->out_state->add_symbol_transition(EPSILON, end);
        second->out_state->add_symbol_transition(EPSILON, end);

        return new nfa(start, end);
    }

    // .
    static nfa* _concat(nfa* first, nfa* second)
    {
        first->out_state->m_is_final = false;
        second->out_state->m_is_final = true;

        first->out_state->add_symbol_transition(EPSILON, second->in_state);

        return new nfa(first->in_state, second->out_state);
    }
};
