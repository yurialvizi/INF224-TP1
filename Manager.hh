#ifndef MANAGER_HH
#define MANAGER_HH

#include <fstream>
#include <iostream>
#include <map>

#include "Group.hh"
#include "Media.hh"
#include "MediaFactory.hh"
#include "Movie.hh"
#include "Photo.hh"
#include "Video.hh"

using namespace std;

typedef std::shared_ptr<Media> MediaPtr;

class Manager {
   private:
    map<string, MediaPtr> medias{};
    map<string, Group> groups{};

   public:
    Manager() {}
    ~Manager() {}

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

    Movie *createMovie(string name, string fileName, int duration,
                       int *chapters, int chapterCount) {
        Movie *movie =
            new Movie(name, fileName, duration, chapters, chapterCount);
        medias.insert({name, MediaPtr(movie)});
        return movie;
    }

    Group *createGroup(string name,
                       const initializer_list<MediaPtr> initList = {}) {
        Group *group = new Group(initList, name);
        groups.insert({name, *group});
        return group;
    }

    void deleteMedia(string name) {
        auto it = medias.find(name);
        if (it != medias.end()) {
            for (auto &group : groups) {
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

    void findGroup(string name, ostream &s) {
        auto it = groups.find(name);
        if (it != groups.end()) {
            it->second.display(s);
        } else {
            cout << "Group " << name << " not found!" << endl;
        }
    }

    void findMedia(string name, ostream &s) {
        auto it = medias.find(name);
        if (it != medias.end()) {
            it->second->display(s);
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

    bool saveAllMedia(string filename) {
        ofstream file(filename);
        if (!file) {
            cerr << "Can't open file " << filename << endl;
            return false;
        }

        for (auto &media : medias) {
            file << media.second->classname() << endl;
            media.second->display(file);
            if (file.fail()) {
                cerr << "Error writing to file " << filename << endl;
                return false;
            }
        }
        file.close();
        return true;
    }

    bool readAllMedia(string filename) {
        cout << "Reading from file " << filename << endl;
        ifstream file(filename);
        if (!file) {
            cerr << "Can't open file " << filename << endl;
            return false;
        }

        while (file) {
            string classname;
            getline(file, classname);
            if(file.eof()) break;
            Media *media = MediaFactory::createMedia(classname);

            if (media == nullptr) {
                cerr << "Invalid media type " << classname << endl;
                return false;
            }

            media->read(file);
            if (file.fail()) {
                cerr << "Error reading from file " << filename << endl;
                return false;
            } else {
                medias.insert({media->getName(), MediaPtr(media)});
            }
        }
        file.close();
        return true;
    }
};

#endif /* MANAGER_HH */