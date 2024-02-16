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
    /**
     * @brief Default constructor for Manager class.
     */
    Manager() {}

    /**
     * @brief Destructor for Manager class.
     */
    ~Manager() {}

    /**
     * @brief Creates a new Photo object and adds it to the collection of
     * medias.
     * @param name The name of the photo.
     * @param fileName The file name of the photo.
     * @param lat The latitude of the photo.
     * @param lon The longitude of the photo.
     * @return A pointer to the created Photo object.
     */
    Photo *createPhoto(string name, string fileName, double lat, double lon) {
        Photo *photo = new Photo(name, fileName, lat, lon);
        medias.insert({name, MediaPtr(photo)});
        return photo;
    }

    /**
     * @brief Creates a new Video object and adds it to the collection of
     * medias.
     * @param name The name of the video.
     * @param fileName The file name of the video.
     * @param duration The duration of the video.
     * @return A pointer to the created Video object.
     */
    Video *createVideo(string name, string fileName, int duration) {
        Video *video = new Video(name, fileName, duration);
        medias.insert({name, MediaPtr(video)});
        return video;
    }

    /**
     * @brief Creates a new Movie object and adds it to the collection of
     * medias.
     * @param name The name of the movie.
     * @param fileName The file name of the movie.
     * @param duration The duration of the movie.
     * @param chapters An array of chapter durations.
     * @param chapterCount The number of chapters.
     * @return A pointer to the created Movie object.
     */
    Movie *createMovie(string name, string fileName, int duration,
                       int *chapters, int chapterCount) {
        Movie *movie =
            new Movie(name, fileName, duration, chapters, chapterCount);
        medias.insert({name, MediaPtr(movie)});
        return movie;
    }

    /**
     * @brief Creates a new Group object and adds it to the collection of
     * groups.
     * @param name The name of the group.
     * @param initList The initializer list of media objects to add to the
     * group.
     * @return A pointer to the created Group object.
     */
    Group *createGroup(string name,
                       const initializer_list<MediaPtr> initList = {}) {
        Group *group = new Group(initList, name);
        groups.insert({name, *group});
        return group;
    }

    /**
     * @brief Deletes a media object from the collection of medias.
     * @param name The name of the media object to delete.
     */
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

    /**
     * @brief Deletes a group object from the collection of groups.
     * @param name The name of the group object to delete.
     */
    void deleteGroup(string name) {
        auto it = groups.find(name);
        if (it != groups.end()) {
            groups.erase(it);
        } else {
            cout << "Group " << name << " not found!" << endl;
        }
    }

    /**
     * @brief Finds and displays the details of a group object.
     * @param name The name of the group to find.
     * @param s The output stream to display the details.
     */
    void findGroup(string name, ostream &s) {
        auto it = groups.find(name);
        if (it != groups.end()) {
            it->second.display(s);
        } else {
            s << "Group " << name << " not found!" << endl;
        }
    }

    /**
     * @brief Finds and displays the details of a media object.
     * @param name The name of the media to find.
     * @param s The output stream to display the details.
     */
    void findMedia(string name, ostream &s) {
        auto it = medias.find(name);
        if (it != medias.end()) {
            it->second->display(s);
        } else {
            s << "Media " << name << " not found!" << endl;
        }
    }

    /**
     * @brief Plays a media object.
     * @param name The name of the media to play.
     * @param s The output stream to display the play action.
     */
    void playMedia(string name, ostream &s) {
        auto it = medias.find(name);
        if (it != medias.end()) {
            it->second->play();
        } else {
            s << "Media " << name << " not found!" << endl;
        }
    }

    /**
     * @brief Saves all media objects to a file.
     * @param filename The name of the file to save the media objects.
     * @return True if the save operation is successful, false otherwise.
     */
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

    /**
     * @brief Reads media objects from a file and adds them to the collection.
     * @param filename The name of the file to read the media objects from.
     * @return True if the read operation is successful, false otherwise.
     */
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
            if (file.eof()) break;
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