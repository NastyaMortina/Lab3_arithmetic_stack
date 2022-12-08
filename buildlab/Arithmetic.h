#pragma once
#include "Lexema.h"
#include "Operations.h"
#include "Exepcion.h"
class Arithmetic {
    string in;
public:
    Arithmetic(string t = "") 
    {
        in = t;
    }
    Queue<Lexema> parser() {
        //Лексический анализ, выделяем лексемы
        Queue<Lexema>ans;
        int state = 0;
        string tmp = "";
        in += ' ';
        string operation = "(/*+-)^";
        string separator = " /n/t";
        for (int i = 0; i < in.size(); i++) 
        {
            char c = in[i];
            switch (state)
            {
            case 0:
                if (c >= '0' && c <= '9') {
                    tmp = c;
                    state = 1;
                    break;
                }
                else if (count(operation.begin(), operation.end(), c) == 1) 
                {
                    tmp = c;
                    Lexema l(tmp, Operation);
                    ans.push(l);
                    tmp = "";
                    break;
                }
                else if (count(separator.begin(), separator.end(), c) == 1) 
                {
                    state = 0;
                    break;
                }
                else if (c == '.')
                {
                    tmp += c;
                    state = 2;
                    break;
                }
                else
                    throw new Unknow_symbol(c, i + 1);
            case 1:
                if (c >= '0' && c <= '9') 
                {
                    tmp += c;
                    break;
                }
                else if (c == '.') {
                    tmp += c;
                    state = 2;
                    break;
                }
                else if (count(operation.begin(), operation.end(), c) == 1) 
                {
                    Lexema l(tmp, int_number);
                    ans.push(l);
                    tmp = c;
                    Lexema t(tmp, Operation);
                    ans.push(t);
                    state = 0;
                    tmp = "";
                    break;
                }
                else if (count(separator.begin(), separator.end(), c) == 1) 
                {
                    if (tmp == "")break;
                    Lexema l(tmp, int_number);
                    ans.push(l);
                    tmp = "";
                    state = 0;
                    break;
                }
                else 
                {
                    throw new Unknow_symbol(c, i + 1);
                }
            case 2:
                if (c >= '0' && c <= '9') {
                    tmp += c;
                    break;
                }
                else if (count(operation.begin(), operation.end(), c) == 1) 
                {
                    Lexema l(tmp, double_number);
                    ans.push(l);
                    tmp = c;
                    Lexema t(tmp, Operation);
                    ans.push(t);
                    state = 0;
                    tmp = "";
                    break;
                }
                else if (count(separator.begin(), separator.end(), c) == 1) 
                {
                    if (tmp == "")break;
                    Lexema l(tmp, double_number);
                    ans.push(l);
                    tmp = "";
                    state = 0;
                    break;
                }
                else {
                    throw new Unknow_symbol(c, i + 1);
                }
            }
        }
        in.pop_back();
        return ans;
    }

    Queue<Lexema> get_postfix(Queue<Lexema> operands) 
    {
        Queue<Lexema>ans;
        Stack<Lexema>stack;
        while (!operands.is_empty())
        {
            Lexema t = operands.pop();
            if (t.get_type() != Operation) 
            {
                ans.push(t);
            }
            else 
            {
                int priority = get_priority_operation(t.get_string());
                if (priority == -1) 
                {
                    stack.push(t);
                    continue;
                }
                while (!stack.is_empty())
                {
                    Lexema tmp = stack.top();
                    int tmp_priority = get_priority_operation(tmp.get_string());
                    if (priority == -2 && tmp_priority == -1) 
                    {
                        stack.pop();
                        break;
                    }
                    else if (tmp_priority == -1)
                        break;
                    if (tmp_priority >= priority)
                    {
                        ans.push(tmp);
                        stack.pop();
                    }
                    else
                        break;
                }
                if (priority != -2)
                    stack.push(t);
            }
        }
        while (!stack.is_empty()) 
        {
            Lexema tmp = stack.pop();
            int tmp_priority = get_priority_operation(tmp.get_string());
            if (tmp_priority > 0) 
            {
                ans.push(tmp);
            }
        }
        return ans;
    }

    double calculate(Queue<Lexema>t)
    {
        Stack<double>stack;
        Operations* op;
        while (!t.is_empty()) {
            Lexema l = t.pop();
            if (l.get_type() == Operation) 
            {
                double v1 = stack.pop();
                double v2 = stack.pop();
                op = get_operations(l.get_string());
                stack.push(op->calc(v2, v1));
            }
            else 
            {
                double val = stod(l.get_string());
                stack.push(val);
            }
        }
        return stack.pop();
    }

    double getans() 
    {
        Queue<Lexema> lexems = parser();
        cout << lexems << '\n';
        Queue<Lexema> postfix = get_postfix(lexems);
        return calculate(postfix);
    }
};