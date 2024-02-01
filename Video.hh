#ifndef VIDEO_HH
#define VIDEO_HH

#include "Media.hh"

class Video : public Media
{
private:
    int duration{};

public:
    Video() {}
    Video(string name, string fileName, int duration) : Media(name, fileName), duration(duration) {}
    ~Video() {
        cout << "Video " << Media::getFileName() << " deleted!" << endl;
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
        s << "Duration: " << duration << endl;
    }

    void play() const override {
        string commandLine = "mpv " + Media::getFileName() + " &";
        system(commandLine.data());
    }
};

#endif /* VIDEO_HH */