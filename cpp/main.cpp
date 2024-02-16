//
// main.cpp
// Created on 21/10/2018
//

#define VERSION_STEP_11

#ifdef VERSION_STEP_12

#include <iostream>
#include "Manager.hh"

typedef std::shared_ptr<Media> MediaPtr;

int main(int argc, char const *argv[])
{
    Manager* manager = new Manager();
    // MediaPtr v1(manager->createVideo("Video 1", "media/video.webm", 120));
    // MediaPtr v2(manager->createVideo("Video 2", "media/video.webm", 120));
    // MediaPtr p1(manager->createPhoto("Photo 1", "media/photo.png", 120, 120));
    // MediaPtr p2(manager->createPhoto("Photo 2", "media/photo.png", 120, 120));


    manager->readAllMedia("media.txt");

    return 0;
}



#endif

#ifdef VERSION_STEP_11

#include <iostream>
#include <memory>
#include <sstream>
#include <string>

#include "Manager.hh"
#include "tcpserver.hh"

using namespace std;
typedef std::shared_ptr<Media> MediaPtr;

const int PORT = 3331;
const string SEARCH = "search";
const string PLAY = "play";

int main(int argc, const char* argv[]) {
    Manager* manager = new Manager();
    MediaPtr v1(manager->createVideo("Video 1", "media/video.webm", 120));
    MediaPtr v2(manager->createVideo("Video 2", "media/video.webm", 120));
    MediaPtr p1(manager->createPhoto("Photo 1", "media/photo.png", 120, 120));
    MediaPtr p2(manager->createPhoto("Photo 2", "media/photo.png", 120, 120));

    manager->createGroup("Vacation", {v1, v2, p1, p2});
    manager->createGroup("Photos", {p1, p2});
    manager->createGroup("Videos", {v1, v2});

    auto* server = new TCPServer([&](string const& request, string& response) {
        cout << "request: " << request << endl;

        // first word is the request type
        string requestType = request.substr(0, request.find(" "));
        // second word is the content type (media or group)
        string requestContentType = request.substr(
            request.find(" ") + 1,
            request.find(" ", request.find(" ") + 1) - request.find(" ") - 1);
        // the string between quotes is the content name
        string requestContentName =
            request.substr(request.find("\"") + 1, request.find_last_of("\"") - request.find("\"") - 1);

        ostringstream responseStream;
        if (requestType == SEARCH) {
            if (requestContentType == "media") {
                manager->findMedia(requestContentName, responseStream);
            } else if (requestContentType == "group") {
                manager->findGroup(requestContentName, responseStream);
            } else {
                responseStream << "Invalid content type" << endl;
            }
        } else if (requestType == PLAY) {
            if (requestContentType == "media") {
                manager->playMedia(requestContentName, responseStream);
            } else {
                responseStream << "Invalid content type" << endl;
            }
        } else {
            responseStream << "Invalid request type" << endl;
        }
        response = responseStream.str();

        return true;
});

cout << "Starting Server on port " << PORT << endl;
int status = server->run(PORT);

if (status < 0) {
    cerr << "Could not start Server on port " << PORT << endl;
    return 1;
}

return 0;
}

#endif

#ifdef VERSION_STEP_10

#include <iostream>
#include <vector>

#include "Group.hh"
#include "Manager.hh"
#include "Media.hh"
#include "Movie.hh"
#include "Photo.hh"
#include "Video.hh"

typedef std::shared_ptr<Media> MediaPtr;

int main(int argc, const char* argv[]) {
    Manager* manager = new Manager();
    MediaPtr v1(manager->createVideo("Video 1", "video1.mp4", 120));
    MediaPtr v2(manager->createVideo("Video 2", "video2.mp4", 120));
    MediaPtr p1(manager->createPhoto("Photo 1", "media/photo.png", 120, 120));
    MediaPtr p2(manager->createPhoto("Photo 2", "photo2.jpg", 120, 120));

    manager->createGroup("Vacation", {v1, v2, p1, p2});
    manager->createGroup("Photos", {p1, p2});
    manager->createGroup("Videos", {v1, v2});

    cout << "Searching Vacation: " << endl;
    manager->findGroup("Vacation");
    cout << "Searching photo 1: " << endl;
    manager->findMedia("Photo 1");
    cout << "Deleting photo 2: " << endl;
    manager->deleteMedia("Photo 2");
    manager->findGroup("Vacation");
    manager->findGroup("Photos");
    manager->findMedia("Photo 2");

    return 0;
}

#endif