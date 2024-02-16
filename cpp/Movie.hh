/**
 * @file Movie.hh
 * @brief Defines the Movie class, a subclass of Video.
 */

#ifndef MOVIE_HH
#define MOVIE_HH

#include "Video.hh"

/**
 * @class Movie
 * @brief Represents a movie, inheriting from the Video class.
 */
class Movie : public Video {
   private:
    int *chapters{};        /**< Array of chapter numbers */
    int numberOfChapters{}; /**< Number of chapters in the movie */

    /**
     * @brief Default constructor for the Movie class.
     */
    Movie(){};

    /**
     * @brief Parameterized constructor for the Movie class.
     * @param name The name of the movie.
     * @param fileName The file name of the movie.
     * @param duration The duration of the movie.
     * @param chapters Array of chapter numbers.
     * @param numberOfChapters Number of chapters in the movie.
     */
    Movie(string name, string fileName, int duration, int *chapters,
          int numberOfChapters)
        : Video(name, fileName, duration),
          chapters(chapters),
          numberOfChapters(numberOfChapters){};

   public:
    friend class Manager;

    /**
     * @brief Sets the chapters of the movie.
     * @param chapters Array of chapter numbers.
     * @param numberOfChapters Number of chapters in the movie.
     */
    void setChapters(int *chapters, int numberOfChapters) {
        int *oldChapters = this->chapters;
        delete[] oldChapters;
        this->numberOfChapters = numberOfChapters;

        this->chapters = new int[numberOfChapters];
        copy(chapters, chapters + numberOfChapters, this->chapters);
    }

    /**
     * @brief Gets a copy of the chapters array.
     * @return A copy of the chapters array.
     */
    int *getChapters() const {
        int *copyChapters = new int[numberOfChapters];
        copy(chapters, chapters + numberOfChapters, copyChapters);
        return copyChapters;
    }

    /**
     * @brief Gets the number of chapters in the movie.
     * @return The number of chapters in the movie.
     */
    int getNumberOfChapters() const { return numberOfChapters; }

    /**
     * @brief Displays information about the movie.
     * @param s The output stream to display the information.
     */
    void display(ostream &s) const override {
        Video::display(s);
        s << "Chapters: "
          << " ";
        for (int i = 0; i < getNumberOfChapters(); i++) {
            s << chapters[i] << " ";
        }
        s << endl;
    }
};

#endif /* MOVIE_HH */