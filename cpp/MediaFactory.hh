#ifndef MEDIAFACTORY_HH
#define MEDIAFACTORY_HH

#include <string>

#include "Media.hh"
#include "Photo.hh"
#include "Video.hh"

using namespace std;

/**
 * @class MediaFactory
 * @brief A factory class for creating Media objects.
 */
class MediaFactory {
   public:
    /**
     * @brief Creates a Media object based on the given type.
     * @param type The type of the Media object to create.
     * @return A pointer to the created Media object, or nullptr if the type is
     * invalid.
     */
    static Media* createMedia(const string& type) {
        if (type == "Photo")
            return new Photo();
        else if (type == "Video")
            return new Video();
        else
            return nullptr;
    }
};

#endif /* MEDIAFACTORY_HH */