#pragma once

#include <stack>
#include <vector>

#include "State.h"
#include "parser.h"

class Nfa
{
public:
    Nfa(State *start, State *end)
        : in_state(start), out_state(end)
    {
    }

    bool test(std::string str)
    {
        return in_state->test(str);
    }

    State *in_state = nullptr;
    State *out_state = nullptr;
};

class Alphabet
{
public:
    Alphabet(std::string regex)
    {
        for (char token : regex)
        {
            if (isalpha(token) && m_alphabet.find(token) == -1)
            {
                m_alphabet.push_back(token);
            }
        }
    }

    std::string get() const
    {
        return m_alphabet;
    }

    bool validate(std::string word) const
    {
        for (char c : word)
        {
            if (m_alphabet.find(c) == -1)
                return false;
        }

        return true;
    }

protected:
    std::string m_alphabet;
};

class NfaFactory
{
public:
    static Nfa *regex_to_nfa(std::string regex)
    {
        // std::string alphabet = get_alphabet(regex);
        std::stack<Nfa *> fragments_stack;
        for (char token : regex)
        {
            if (token == '+')
            {
                if (fragments_stack.size() >= 2)
                {
                    Nfa *right = fragments_stack.top();
                    fragments_stack.pop();
                    Nfa *left = fragments_stack.top();
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
                    Nfa *result = closure(fragments_stack.top());
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
                    Nfa *right = fragments_stack.top();
                    fragments_stack.pop();
                    Nfa *left = fragments_stack.top();
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
                if (isalpha(token))
                    fragments_stack.push(create_nfa_from_symbol(Parser::charToStr(token)));
                else
                {
                    return nullptr;
                }
            }
        }

        Nfa *top = fragments_stack.top();
        fragments_stack.pop();

        return top;
    }

protected:
    static Nfa *closure(Nfa *fragment)
    {
        State *start = new State(false);
        State *end = new State(true);

        start->add_symbol_transition(EPSILON, end);
        start->add_symbol_transition(EPSILON, fragment->in_state);

        fragment->out_state->m_is_final = false;
        fragment->out_state->add_symbol_transition(EPSILON, end);

        end->add_symbol_transition(EPSILON, fragment->in_state);

        return new Nfa(start, end);
    }

    static Nfa *concat(Nfa *first, std::vector<Nfa *> rest)
    {
        for (auto item : rest)
        {
            first = _concat(first, item);
        }

        return first;
    }

    // or
    static Nfa *disjunction(Nfa *first, std::vector<Nfa *> rest)
    {
        for (auto item : rest)
        {
            first = _disjunction(first, item);
        }

        return first;
    }

    static Nfa *create_nfa_from_symbol(std::string symbol)
    {
        State *in_state = new State(false);
        State *out_state = new State(true);

        in_state->add_symbol_transition(symbol, out_state);

        return new Nfa(in_state, out_state);
    }

    // + ou |
    static Nfa *_disjunction(Nfa *first, Nfa *second)
    {
        State *start = new State(false);
        State *end = new State(true);

        start->add_symbol_transition(EPSILON, first->in_state);
        start->add_symbol_transition(EPSILON, second->in_state);

        first->out_state->m_is_final = false;
        second->out_state->m_is_final = false;

        first->out_state->add_symbol_transition(EPSILON, end);
        second->out_state->add_symbol_transition(EPSILON, end);

        return new Nfa(start, end);
    }

    // .
    static Nfa *_concat(Nfa *first, Nfa *second)
    {
        first->out_state->m_is_final = false;
        second->out_state->m_is_final = true;

        first->out_state->add_symbol_transition(EPSILON, second->in_state);

        return new Nfa(first->in_state, second->out_state);
    }
};
