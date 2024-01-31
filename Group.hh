#ifndef GROUP_HH
#define GROUP_HH

#include "Media.hh"
#include <list>

using namespace std;

template <typename T>
class Group : public list<T> {
private: 
    string name{};
public: 
    Group() {}
    Group(const initializer_list<T> initList = {}, const string name = {}) : list<T>(initList), name(name) {};
    string getName() const {
        return name;
    }
    void display(ostream& s) const {
        for (const auto& element : *this) {
            element->display(s);
        }
    }
};

#endif /* GROUP_HH */