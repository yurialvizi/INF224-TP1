#ifndef VIDEO_HH
#define VIDEO_HH

#include "Media.hh"

class Video : public Media
{
private:
    int duration{};
    Video() {}
    Video(string name, string fileName, int duration) : Media(name, fileName), duration(duration) {}

public:
    friend class Manager;
    friend class Movie;
    ~Video() {
        cout << "Video " << Media::getName() << " deleted!" << endl;
    }
    void setDuration(int duration)
    {
        this->duration = duration;
    }

    int getDuration() const
    {
        return duration;
    }

    void display(ostream &s) const override {
        Media::display(s);
        s << "Duration: " << duration << " | ";
    }

    void play() const override {
        string commandLine = "mpv " + Media::getFileName() + " &";
        system(commandLine.data());
    }
};

#endif /* VIDEO_HH */