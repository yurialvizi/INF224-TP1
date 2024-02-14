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
            return nullptr; // or throw an exception based on your error handling
    }
};

#endif /* MEDIAFACTORY_HH */