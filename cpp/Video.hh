#ifndef VIDEO_HH
#define VIDEO_HH

#include "Media.hh"

/**
 * @class Video
 * @brief Represents a video media object.
 *
 * This class inherits from the Media class and adds additional functionality
 * specific to video media.
 */
class Video : public Media {
   private:
    int duration{}; /**< The duration of the video in seconds. */

    /**
     * @brief Default constructor for the Video class.
     */
    Video() {}

    /**
     * @brief Parameterized constructor for the Video class.
     * @param name The name of the video.
     * @param fileName The file name of the video.
     * @param duration The duration of the video in seconds.
     */
    Video(string name, string fileName, int duration)
        : Media(name, fileName), duration(duration) {}

   public:
    friend class Manager;
    friend class Movie;
    friend class MediaFactory;

    /**
     * @brief Destructor for the Video class.
     *
     * Prints a message indicating that the video has been deleted.
     */
    ~Video() { cout << "Video " << Media::getName() << " deleted!" << endl; }

    /**
     * @brief Returns the class name of the Video object.
     * @return The class name "Video".
     */
    string classname() const override { return "Video"; }

    /**
     * @brief Sets the duration of the video.
     * @param duration The duration of the video in seconds.
     */
    void setDuration(int duration) { this->duration = duration; }

    /**
     * @brief Gets the duration of the video.
     * @return The duration of the video in seconds.
     */
    int getDuration() const { return duration; }

    /**
     * @brief Displays information about the video.
     * @param s The output stream to display the information.
     */
    void display(ostream &s) const override {
        Media::display(s);
        s << "Duration: " << duration << endl;
    }

    /**
     * @brief Plays the video using the mpv player.
     */
    void play() const override {
        string commandLine = "mpv " + Media::getFileName() + " &";
        system(commandLine.data());
    }

    /**
     * @brief Reads the video information from a file stream.
     * @param file The input file stream to read from.
     */
    void read(istream &file) override {
        Media::read(file);
        string dur;
        getline(file, dur);
        dur = dur.substr(dur.find(":") + 1);
        duration = stoi(dur);
    }
};

#endif /* VIDEO_HH */