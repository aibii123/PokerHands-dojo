#pragma once
#include <string>
#include <map>
using namespace std;

class Card
{
public:
    Card(const string&);

    int m_value;
    char m_suit;
    
private:
    static map<char, int> m_map;
};
