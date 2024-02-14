#ifndef MOVIE_HH
#define MOVIE_HH

#include "Video.hh"

class Movie : public Video
{
private:
    int *chapters{};
    int numberOfChapters{};
    Movie() {};
    Movie(string name, string fileName, int duration, int *chapters, int  numberOfChapters) : Video(name, fileName, duration), chapters(chapters), numberOfChapters(numberOfChapters){};

public:
    friend class Manager;
    
    void setChapters(int *chapters, int numberOfChapters)
    {
        int *oldChapters = this->chapters;
        delete[] oldChapters;
        this->numberOfChapters = numberOfChapters;

        this->chapters = new int[numberOfChapters];
        copy(chapters, chapters + numberOfChapters, this->chapters);
    }

    int *getChapters() const
    {
        int *copyChapters = new int[numberOfChapters];
        copy(chapters, chapters + numberOfChapters, copyChapters);
        return copyChapters;
    }

    int getNumberOfChapters() const
    {
        return numberOfChapters;
    }

    void display(ostream &s) const override
    {
        Video::display(s);
        s << "Chapters: " << " ";
        for (int i = 0; i < getNumberOfChapters(); i++)
        {
            s << chapters[i] << " | ";
        }
    }

};

#endif /* MOVIE_HH */