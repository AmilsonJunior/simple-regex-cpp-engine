#include "State.h"

std::vector<State *> State::get_symbol_transitions(std::string symbol)
{
    std::vector<State *> _transitions;
    for (auto item : m_transitions)
    {
        if (item.first == symbol)
            _transitions.push_back(item.second);
    }

    return _transitions;
}

bool State::match(std::string str, std::set<State *> visited)
{
    if (visited.find(this) != visited.end())
    {
        return false;
    }

    visited.insert(this);

    if (str.length() == 0)
    {
        if (this->m_is_final)
            return true;

        for (State *next_state : this->get_symbol_transitions(EPSILON))
        {
            if (next_state->match("", visited))
                return true;
        }
        return false;
    }

    // abc
    std::string symbol;
    symbol.push_back(str[0]);                       //a
    std::string rest = str.substr(1, str.length()); //bc (pode ser vazio)

    for (State *next_state : this->get_symbol_transitions(symbol))
    {
        if (next_state->match(rest))
            return true;
    }

    for (State *next_state : this->get_symbol_transitions(EPSILON))
    {
        if (next_state->match(str, visited))
            return true;
    }

    return false;
}