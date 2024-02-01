//
// main.cpp
// Created on 21/10/2018
//

#include <iostream>
#include "Media.hh"
#include "Photo.hh"
#include "Video.hh"
#include "Movie.hh"
#include "Group.hh"
#include <vector>
#include "Manager.hh"

typedef std::shared_ptr<Media> MediaPtr;

int main(int argc, const char* argv[])
{
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
