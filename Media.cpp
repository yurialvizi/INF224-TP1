#include "Media.hh"

using namespace std;

Media::Media() {}

Media::Media(const string& name, const string& fileName) : name(name), fileName(fileName) {}

string Media::getName() const {return name;}

void Media::setName(const string& newName) {name = newName;}

string Media::getFileName() const {return fileName;}

void Media::setFileName(const string& newFileName) {fileName = newFileName;}

void Media::display(ostream &s) const {
    s << "Name: " << name << " | ";
    s << "File Name: " << fileName << " | ";
}