//
// main.cpp
// Created on 21/10/2018
//

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

/**
 * @brief The main function of the program.
 *
 * This function is the entry point of the program. It creates instances of
 * various media objects, creates groups of media objects, and starts a TCP
 * server to handle client requests. The server listens on a specified port and
 * responds to search and play requests for media objects and groups.
 *
 * @param argc The number of command-line arguments.
 * @param argv An array of command-line arguments.
 * @return An integer representing the exit status of the program.
 */
int main(int argc, const char* argv[]) {
    Manager* manager = new Manager();
    MediaPtr v1(manager->createVideo("Video 1", "media/video.webm", 120));
    MediaPtr v2(manager->createVideo("Video 2", "media/video.webm", 150));
    MediaPtr p1(manager->createPhoto("Photo 1", "media/photo.png", 120, 120));
    MediaPtr p2(manager->createPhoto("Photo 2", "media/photo.png", 40, 60));
    MediaPtr m1(manager->createMovie("Movie 1", "media/video.webm", 120,
                                     new int[2]{60, 120}, 2));
    MediaPtr m2(manager->createMovie("Movie 2", "media/video.webm", 200,
                                     new int[3]{60, 120, 180}, 3));

    manager->createGroup("Vacation", {v1, v2, p1, p2});
    manager->createGroup("Photos", {p1, p2});
    manager->createGroup("Videos", {v1, v2});
    manager->createGroup("Movies", {m1, m2});

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
            request.substr(request.find("\"") + 1,
                           request.find_last_of("\"") - request.find("\"") - 1);

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
