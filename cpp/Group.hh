#ifndef GROUP_HH
#define GROUP_HH

#include <list>
#include <memory>

#include "Media.hh"

using namespace std;

typedef std::shared_ptr<Media> MediaPtr;

/**
 * @class Group
 * @brief Represents a group of Media objects.
 *
 * This class inherits from std::list<MediaPtr> and provides additional
 * functionality for managing a group of Media objects. It stores a name for the
 * group and allows displaying the group's contents.
 */
class Group : public list<MediaPtr> {
   private:
    string name{}; /**< The name of the group. */

    /**
     * @brief Default constructor.
     *
     * Constructs an empty Group object.
     */
    Group() {}

    /**
     * @brief Constructor with initializer list and name.
     *
     * Constructs a Group object with the specified initializer list of MediaPtr
     * objects and a name for the group.
     *
     * @param initList The initializer list of MediaPtr objects.
     * @param name The name of the group.
     */
    Group(const initializer_list<MediaPtr> initList = {},
          const string name = {})
        : list<MediaPtr>(initList), name(name){};

   public:
    friend class Manager;

    /**
     * @brief Get the name of the group.
     *
     * @return The name of the group.
     */
    string getName() const { return name; }

    /**
     * @brief Display the group's contents.
     *
     * Prints the name of the group and then calls the display() function for
     * each Media object in the group, followed by a separator line.
     *
     * @param s The output stream to write the group's contents to.
     */
    void display(ostream& s) const {
        s << "---Group name: " << name << endl;
        for (const auto& element : *this) {
            element->display(s);
            s << "-------------------" << endl;
        }
    }
};

#endif /* GROUP_HH */