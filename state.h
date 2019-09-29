#pragma once
#include <string>
#include <map>
#include <set>
#include <vector>

std::string gen_random_str(const int len) {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    std::string s;
    for (int i = 0; i < len; ++i) {
        s.push_back(alphanum[rand() % (sizeof(alphanum) - 1)]);
    }

    return s;
}

const std::string EPSILON = "&";

class state 
{
public:
    state(bool is_final)
        : m_is_final(is_final)
    {   
        m_unique_id = gen_random_str(10);
    }

    void add_symbol_transition(std::string symbol, state* final_state)
    {
        m_transitions.insert({ symbol, final_state });
    }

    std::vector<state*> get_symbol_transitions(std::string symbol)
    {
        std::vector<state*> _transitions;
        for (auto item : m_transitions)
        {
            if (item.first == symbol)
                _transitions.push_back(item.second);
        }

        return _transitions;
    }

    bool test(std::string str, std::set<state*> visited = std::set<state*>())
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
            
            for (state* next_state : this->get_symbol_transitions(EPSILON))
            {
                if (next_state->test("", visited))
                    return true;
            }
            return false;
        }

        // abc
        std::string symbol;
        symbol.push_back(str[0]); //a
        std::string rest = str.substr(1, str.length()); //bc

        for (state* next_state : this->get_symbol_transitions(symbol))
        {/*  */
            if (next_state->test(rest))
                return true;
        }

        for (state* next_state : this->get_symbol_transitions(EPSILON))
        {
            if (next_state->test(str, visited))
                return true;
        }

        return false;
    }

    bool operator==(const state& other)
    {
        return (
           this->m_unique_id == other.m_unique_id
        );
    }

    bool m_is_final;
    std::string m_unique_id;
    std::multimap<std::string, state*> m_transitions;
};
