#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class Media {
private:
    string name{};
    string fileName{};

public:
    Media();
    Media(const string& name, const string& fileName) : name{name}, fileName{fileName} {}
    
    ~Media() {}

    string getName() const {return name;}

    void setName(const string& newName) {name = newName;}

    string getFileName() const {return fileName;}

    void setFileName(const string& newFileName) {fileName = newFileName;}

    void display(ostream &s) {}
};
