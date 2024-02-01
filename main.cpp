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

using namespace std;
typedef std::shared_ptr<Media> MediaPtr;

int main(int argc, const char* argv[])
{
    MediaPtr v1(new Video("Video 1", "video1.mp4", 120));
    MediaPtr v2(new Video("Video 2", "video2.mp4", 120));
    MediaPtr p1(new Photo("Photo 1", "photo1.jpg", 120, 120));
    MediaPtr p2(new Photo("Photo 2", "photo2.jpg", 120, 120));

    // Video v1("Video 1", "video1.mp4", 120);
    // Video v2("Video 2", "video2.mp4", 120);
    // Photo p1("Photo 1", "photo1.jpg", 120, 120);
    // Photo p2("Photo 2", "photo2.jpg", 120, 120);

    
    Group* vacation = new Group({v1, v2, p1, p2}, "Vacation");
    Group* photos = new Group({p1, p2}, "Photos");
    Group* videos = new Group({v1, v2}, "Videos");
    // Group<Media*> photos({&p1, &p2}, "Photos");
    // Group<Media*> videos({&v1, &v2}, "Videos");


    cout << "Group name: " << vacation->getName() << endl;
    cout << "Group name: " << photos->getName() << endl;
    cout << "Group name: " << videos->getName() << endl;
    // cout << "Group name: " << photos.getName() << endl;
    // cout << "Group name: " << videos.getName() << endl;

    cout << "Displaying groups: " << endl;
    vacation->display(cout);
    cout << "Pop front: " << endl;
    vacation->pop_front();
    vacation->display(cout);
    cout << "Pop back: " << endl;
    vacation->pop_back();
    vacation->display(cout);
    delete vacation;
    photos->display(cout);
    videos->display(cout);
    photos->pop_front();
    videos->pop_back();

    
    // photos.display(cout);
    // videos.display(cout);

    return 0;
}
