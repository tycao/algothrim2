#include <iostream>
#include <fstream>
using namespace std;

#include "parts.h"

void load(char* filename)
{
    ifstream in(filename);
    string part, subpart;
    int quantity;
    if (!in) return;
    while (in)
    {
        in >> part >> quantity >> subpart;
        add_part(part, quantity, subpart);
    }
}
void whatis(const string &x)
{
    Part* xp = partContainer.loopup(x);
    cout << endl;
    xp->describe();
}
void howmany(const string& x, const string& y)
{
    Part* xp = partContainer.loopup(x);
    Part* yp = partContainer.loopup(y);
    cout << endl << y << " has " << yp->count_howmany(xp) << " " << x << endl;
}
void process(char* filename)
{
    ifstream in(filename);
    string query, x, y;
    if (!in) return;
    while (in)
    {
        in >> query >> x;
        if (query == "howmany") in >> y;
        if (query == "howmany") howmany(x, y);
        else if (query == "whatis") whatis(x);
        else { cerr << "Error!!!Can not query " << query << endl; return; }
    }
}
int main()
{
    load("d:\\a.txt");
    process("d:\\b.txt");
    return 0;
}
