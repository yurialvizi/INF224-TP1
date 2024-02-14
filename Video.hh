#ifndef VIDEO_HH
#define VIDEO_HH

#include "Media.hh"

class Video : public Media {
   private:
    int duration{};
    Video() {}
    Video(string name, string fileName, int duration)
        : Media(name, fileName), duration(duration) {}

   public:
    friend class Manager;
    friend class Movie;
    friend class MediaFactory;
    ~Video() { cout << "Video " << Media::getName() << " deleted!" << endl; }

    string classname() const override { return "Video"; }

    void setDuration(int duration) { this->duration = duration; }

    int getDuration() const { return duration; }

    void display(ostream &s) const override {
        Media::display(s);
        s << "Duration: " << duration << endl;
    }

    void play() const override {
        string commandLine = "mpv " + Media::getFileName() + " &";
        system(commandLine.data());
    }

    void read(istream &file) override {
        Media::read(file);
        string dur;
        getline(file, dur);
        dur = dur.substr(dur.find(":") + 1);
        duration = stoi(dur);
    }
};

#endif /* VIDEO_HH */