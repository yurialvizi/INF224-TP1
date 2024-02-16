#ifndef GROUP_HH
#define GROUP_HH

#include <list>
#include <memory>

#include "Media.hh"

using namespace std;

typedef std::shared_ptr<Media> MediaPtr;

class Group : public list<MediaPtr> {
   private:
    string name{};
    Group() {}
    Group(const initializer_list<MediaPtr> initList = {},
          const string name = {})
        : list<MediaPtr>(initList), name(name){};

   public:
    friend class Manager;
    string getName() const { return name; }
    void display(ostream& s) const {
        s << "---Group name: " << name << " | ";
        for (const auto& element : *this) {
            element->display(s);
        }
    }
};

#endif /* GROUP_HH */