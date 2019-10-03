#pragma once

#include <string>
#include <map>
#include <set>
#include <vector>

static std::string gen_random_str(const int len) {
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

class State 
{
public:
    State(bool is_final)
        : m_is_final(is_final)
    {   
        m_unique_id = gen_random_str(10);
    }

    void add_symbol_transition(std::string symbol, State* final_state)
    {
        m_transitions.insert({ symbol, final_state });
    }

    std::vector<State*> get_symbol_transitions(std::string symbol);

    bool match(std::string str, std::set<State*> visited = std::set<State *>());
    bool operator==(const State& other)
    {
        return (
           this->m_unique_id == other.m_unique_id
        );
    }

    bool m_is_final;
    std::string m_unique_id;
    std::multimap<std::string, State*> m_transitions;
};
