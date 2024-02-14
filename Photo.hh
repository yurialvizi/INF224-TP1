#ifndef PHOTO_HH
#define PHOTO_HH

#include "Media.hh"

class Photo : public Media
{
private:
    double latitude{};
    double longitude{};
    Photo() {}
    Photo(string name, string fileName, double lat, double lon) : Media(name, fileName), latitude(lat), longitude(lon) {}
public:
    friend class Manager;
    ~Photo() {
        cout << "Photo " << Media::getName() << " deleted!" << endl;
    }

    void setLatitude(double lat) {
        latitude = lat;
    }

    void setLongitude(double lon) {
        longitude = lon;
    }

    double getLatitude() const {
        return latitude;
    }

    double getLongitude() const {
        return longitude;
    }

    void display(ostream &s) const override {
        Media::display(s);
        s << "Latitude: " << latitude << " | ";
        s << "Longitude: " << longitude << " | ";
    }

    void play() const override {
        string commandLine = "imagej " + Media::getFileName() + " &";
        system(commandLine.data());
    }
};

#endif /* PHOTO_HH */