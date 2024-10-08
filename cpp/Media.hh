#ifndef MEDIA_HH
#define MEDIA_HH

#include <stdio.h>

#include <iostream>
#include <string>

using namespace std;

class Media {
   private:
    string name{};
    string fileName{};

   public:
    Media();
    Media(const string& name, const string& fileName);

    ~Media() {}

    virtual string classname() const = 0;

    /**
     * @brief Retorna o nome da mídia.
     * @return O nome da mídia.
     */
    string getName() const;

    void setName(const string& newName);

    string getFileName() const;

    void setFileName(const string& newFileName);

    virtual void display(ostream& s) const;

    virtual void play() const = 0;

    virtual void read(istream& file) = 0;
};
#endif /* MEDIA_HH */