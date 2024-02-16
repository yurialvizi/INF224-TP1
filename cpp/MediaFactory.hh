#ifndef MEDIAFACTORY_HH
#define MEDIAFACTORY_HH

#include <string>

#include "Media.hh"
#include "Photo.hh"
#include "Video.hh"

using namespace std;

class MediaFactory {
   public:
    static Media* createMedia(const std::string& type) {
        if (type == "Photo")
            return new Photo();
        else if (type == "Video")
            return new Video();
        else
            return nullptr;
    }
};

#endif /* MEDIAFACTORY_HH */