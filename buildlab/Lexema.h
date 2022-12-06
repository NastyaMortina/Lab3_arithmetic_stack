#pragma once
#include<string>
#include<iostream>
#include<algorithm>
#include <vector>
#include "Queue.h"
#include "Stack.h"
#include <map>
using namespace std;

enum TypeElement 
{
    none,
    Operation,
    int_number,
    double_number
};
int get_priority_operation(string c) 
{
    if (c == "(")
        return -1;
    if (c == ")")
        return -2;
    if (c == "^")
        return 3;
    if (c == "*" || c == "/")
        return 2;
    if (c == "+" || c == "-")
        return 1;
    return 0;
}
class Lexema
{
    TypeElement type;
    string s;
    int pos;
public:
    Lexema(string _s = "", TypeElement _type = none, int index = -1) 
    {
        type = _type;
        s = _s;
        pos = index;
    }
    string get_string() 
    {
        return s;
    }
    TypeElement get_type() 
    {
        return type;
    }
    int get_pos() 
    {
        return pos;
    }
    friend ostream& operator << (ostream& out, Lexema& p) 
    {
        out << "{" << p.s << ", ";
        if (p.type == Operation) 
        {
            out << "operation";
        }
        else if (p.type == int_number) 
        {
            out << "int number";
        }
        else if (p.type == double_number) 
        {
            out << "double number";
        }
        else 
        {
            out << "None";
        }
        out << "}";
        out << "\n";
        return out;
    }
};


