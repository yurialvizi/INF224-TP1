#ifndef PHOTO_HH
#define PHOTO_HH

#include "Media.hh"

/**
 * @class Photo
 * @brief Represents a photo media object.
 *
 * This class inherits from the Media class and adds latitude and longitude
 * attributes to represent the location where the photo was taken.
 */
class Photo : public Media {
   private:
    double latitude{};  /**< The latitude of the photo's location. */
    double longitude{}; /**< The longitude of the photo's location. */

    /**
     * @brief Private constructor.
     */
    Photo() {}

    /**
     * @brief Public constructor.
     * @param name The name of the photo.
     * @param fileName The file name of the photo.
     * @param lat The latitude of the photo's location.
     * @param lon The longitude of the photo's location.
     */
    Photo(string name, string fileName, double lat, double lon)
        : Media(name, fileName), latitude(lat), longitude(lon) {}

   public:
    friend class Manager;
    friend class MediaFactory;

    /**
     * @brief Destructor.
     */
    ~Photo() { cout << "Photo " << Media::getName() << " deleted!" << endl; }

    /**
     * @brief Returns the class name.
     * @return The class name as a string.
     */
    string classname() const override { return "Photo"; }

    /**
     * @brief Sets the latitude of the photo's location.
     * @param lat The latitude value.
     */
    void setLatitude(double lat) { latitude = lat; }

    /**
     * @brief Sets the longitude of the photo's location.
     * @param lon The longitude value.
     */
    void setLongitude(double lon) { longitude = lon; }

    /**
     * @brief Returns the latitude of the photo's location.
     * @return The latitude value.
     */
    double getLatitude() const { return latitude; }

    /**
     * @brief Returns the longitude of the photo's location.
     * @return The longitude value.
     */
    double getLongitude() const { return longitude; }

    /**
     * @brief Displays the photo's information.
     * @param s The output stream to display the information.
     */
    void display(ostream &s) const override {
        Media::display(s);
        s << "Latitude: " << latitude << endl;
        s << "Longitude: " << longitude << endl;
    }

    /**
     * @brief Plays the photo.
     *
     * This function opens the photo file using the "imagej" command.
     */
    void play() const override {
        string commandLine = "imagej " + Media::getFileName() + " &";
        system(commandLine.data());
    }

    /**
     * @brief Reads the photo's information from a file.
     * @param file The input stream to read the information from.
     */
    void read(istream &file) override {
        Media::read(file);
        string lat, lon;
        getline(file, lat);
        getline(file, lon);
        lat = lat.substr(lat.find(":") + 1);
        lon = lon.substr(lon.find(":") + 1);
        latitude = stod(lat);
        longitude = stod(lon);
    }
};

#endif /* PHOTO_HH */