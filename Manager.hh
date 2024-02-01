#ifndef MANAGER_HH
#define MANAGER_HH

#include <map>
#include "Media.hh"
#include "Group.hh"
#include "Photo.hh"
#include "Movie.hh"
#include "Video.hh"

using namespace std;

typedef std::shared_ptr<Media> MediaPtr;

class Manager
{
private:
    map<string, MediaPtr> medias{};
    map<string, Group> groups{};
public:
    Manager(){}
    ~Manager(){}

    Photo *createPhoto(string name, string fileName, double lat, double lon) {
        Photo *photo = new Photo(name, fileName, lat, lon);
        medias.insert({name, MediaPtr(photo)});
        return photo;
    }

    Video *createVideo(string name, string fileName, int duration) {
        Video *video = new Video(name, fileName, duration);
        medias.insert({name, MediaPtr(video)});
        return video;
    }

    Movie *createMovie(string name, string fileName, int duration, int *chapters, int chapterCount) {
        Movie *movie = new Movie(name, fileName, duration, chapters, chapterCount);
        medias.insert({name, MediaPtr(movie)});
        return movie;
    }

    Group *createGroup(string name, const initializer_list<MediaPtr> initList = {}) {
        Group *group = new Group(initList, name);
        groups.insert({name, *group});
        return group;
    }

    void deleteMedia(string name) {
        auto it = medias.find(name);        
        if (it != medias.end()) {
            for(auto& group : groups) {
                group.second.remove(it->second);
            }
            medias.erase(it);
        } else {
            cout << "Media " << name << " not found!" << endl;
        }
    }

    void deleteGroup(string name) {
        auto it = groups.find(name);
        if (it != groups.end()) {
            groups.erase(it);
        } else {
            cout << "Group " << name << " not found!" << endl;
        }
    }

    void findGroup(string name) {
        auto it = groups.find(name);
        if (it != groups.end()) {
            it->second.display(cout);
        } else {
            cout << "Group " << name << " not found!" << endl;
        }
    }

    void findMedia(string name) {
        auto it = medias.find(name);
        if (it != medias.end()) {
            it->second->display(cout);
        } else {
            cout << "Media " << name << " not found!" << endl;
        }
    }

    void playMedia(string name) {
        auto it = medias.find(name);
        if (it != medias.end()) {
            it->second->play();
        } else {
            cout << "Media " << name << " not found!" << endl;
        }
    }

};


#endif /* MANAGER_HH */