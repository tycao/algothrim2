#pragma once

#include <iostream>
#include <map>

using namespace std;

class Part
{
    friend void add_part(const string&, int, const string&);
public:
    Part(const string &n) : name(n){}
    void describe(void);
    int count_howmany(const Part *p);
    int myCount(map<Part*, int>& myMap, const Part *p, int num);

private:
    string name;
    map<Part*, int> subparts;
};

class NameContainer
{
public:
    NameContainer(void) {}
    Part* loopup(const string &name)
    {
        if (this->name_map.find(name) == this->name_map.end())
        {
            Part* part = new Part(name);
            name_map.insert(pair<std::string, Part*>(name, part));
            return part;
        }
        else
            return (name_map.find(name))->second;
    }
    ~NameContainer()
    {
        for (map<std::string, Part*>::iterator i = name_map.begin(); i != name_map.end(); ++i)
            delete i->second;
    }
private:
    map<std::string, Part*> name_map;
};

NameContainer partContainer;
//列出part的名字，及其所有subparts与其对应的数量
//并使用游标处理subparts
void Part::describe(void)
{
    cout << "part " << this->name << " subparts are : " << endl;
    if (subparts.empty())
    {
        cout << "There is no subparts!!!" << endl;
        return;
    }
    for (map<Part*, int>::iterator it = this->subparts.begin(); it != this->subparts.end(); ++it)
        cout << it->second << " " << it->first->name << endl;
}
int Part::count_howmany(const Part *p)
{
    return myCount(this->subparts, p, 1);
}
int Part::myCount(map<Part*, int>& myMap, const Part *p, int num)
{
    if (myMap.empty()) return 0;
    for (std::map<Part*, int>::iterator it = myMap.begin(); it != myMap.end(); ++it)
    {
        num = num * (it->second);
        if (it->first->name == p->name) return num;
        else if (myCount(it->first->subparts, p, num) == 0) num = num / (it->second);
        else return myCount(it->first->subparts, p, num);
    }
}

//全局函数
void add_part(const string& x, int q, const string &y)
{
    Part* px = partContainer.loopup(x);
    Part* py = partContainer.loopup(y);
    px->subparts.insert(make_pair(py, q));
}
