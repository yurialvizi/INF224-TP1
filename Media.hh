#ifndef MEDIA_HH
#define MEDIA_HH

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
    Media(const string& name, const string& fileName);
    
    ~Media() {}

    string getName() const;

    void setName(const string& newName);

    string getFileName() const;

    void setFileName(const string& newFileName);

    void display(ostream &s) const;

    virtual void play() const = 0;
};
#endif /* MEDIA_HH */