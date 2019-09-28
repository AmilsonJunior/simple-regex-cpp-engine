#pragma once
#include <string>
#include <map>

class state 
{
public:
    state(bool is_final)
        : m_is_final(is_final)
    {
    }

    void add_symbol_transition(std::string symbol, state* final_state)
    {
        transitions.insert({ symbol, final_state })
    }

    bool m_is_final;
    std::map<std::string, state*> transitions;
};
