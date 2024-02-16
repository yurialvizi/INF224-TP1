#ifndef PHOTO_HH
#define PHOTO_HH

#include "Media.hh"

class Photo : public Media {
   private:
    double latitude{};
    double longitude{};
    Photo() {}
    Photo(string name, string fileName, double lat, double lon)
        : Media(name, fileName), latitude(lat), longitude(lon) {}

   public:
    friend class Manager;
    friend class MediaFactory;
    ~Photo() { cout << "Photo " << Media::getName() << " deleted!" << endl; }

    string classname() const override { return "Photo"; }

    void setLatitude(double lat) { latitude = lat; }

    void setLongitude(double lon) { longitude = lon; }

    double getLatitude() const { return latitude; }

    double getLongitude() const { return longitude; }

    void display(ostream &s) const override {
        Media::display(s);
        s << "Latitude: " << latitude << endl;
        s << "Longitude: " << longitude << endl;
    }

    void play() const override {
        string commandLine = "imagej " + Media::getFileName() + " &";
        system(commandLine.data());
    }

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