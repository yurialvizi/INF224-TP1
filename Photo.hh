#ifndef PHOTO_HH
#define PHOTO_HH

#include "Media.hh"

class Photo : public Media
{
private:
    double latitude{};
    double longitude{};
public:
    Photo() {}
    Photo(string name, string fileName, double lat, double lon) : Media(name, fileName), latitude(lat), longitude(lon) {}

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

    void display(ostream &s) const {
        Media::display(s);
        s << "Latitude: " << latitude << endl;
        s << "Longitude: " << longitude << endl;
    }

    void play() const override {
        string commandLine = "imagej " + Media::getFileName() + " &";
        system(commandLine.data());
    }
};

#endif /* PHOTO_HH */