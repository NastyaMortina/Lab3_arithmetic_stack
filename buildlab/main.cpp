#include <iostream>
#include "Arifmetic.h"
#include "Exepcion.h"
using namespace std;
int main() 
{
    string s = "(2+1 * 5";
    Arifmetic a(s);
    try 
    {
        cout << a.getans() << '\n';
    }
    catch (Exepcion* ex) 
    {
        cout << "Error!\n";
        ex->show();
    }
    return 0;
}