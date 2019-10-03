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

    bool match(std::string str)
    {
        return in_state->match(str);
    }

    State *in_state = nullptr;
    State *out_state = nullptr;
};

class Alphabet
{
public:
    Alphabet(std::string regex);

    std::string get() const
    {
        return m_alphabet;
    }

    bool validate(std::string word) const;

protected:
    std::string m_alphabet;
};

class NfaFactory
{
public:
    static Nfa *regex_to_nfa(std::string regex);

protected:
    static Nfa *create_nfa_from_symbol(std::string symbol);
    // *
    static Nfa *closure(Nfa *fragment);
    // +
    static Nfa *disjunction(Nfa *first, Nfa *second);
    // .
    static Nfa *concat(Nfa *first, Nfa *second);
};
