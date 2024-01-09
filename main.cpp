//
// main.cpp
// Created on 21/10/2018
//

#include <iostream>
#include "Media.hh"
#include "Photo.hh"
#include "Video.hh"
#include <vector>

using namespace std;

int main(int argc, const char* argv[])
{
    vector<Media*> mediaList;

    for (int i = 0; i < 6; i++) {
        
        if (i%2 == 0)
        {
            string name = "photo " + to_string(i);
            Photo *media = new Photo(name, "media/photo.png", i, 2*i);
            mediaList.push_back(media);
        }
        else
        {
            string name = "video " + to_string(i);
            Video *media = new Video(name, "media/video.webm", i);
            mediaList.push_back(media);
        }
    }
    

    for (int i = 0; i < 6; i++)
    {
        if (i%3 == 0)
        {
            mediaList[i]->play();
        } else {
            mediaList[i]->display(cout);
        }
        
    }
    
    return 0;
}
