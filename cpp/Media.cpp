/**
 * @file Media.cpp
 * @brief Implementation file for the Media class.
 */

#include "Media.hh"

#include <iostream>
#include <string>

using namespace std;

/**
 * @brief Default constructor for the Media class.
 */
Media::Media() {}

/**
 * @brief Parameterized constructor for the Media class.
 * @param name The name of the media.
 * @param fileName The file name of the media.
 */
Media::Media(const string& name, const string& fileName)
    : name(name), fileName(fileName) {}

/**
 * @brief Get the name of the media.
 * @return The name of the media.
 */
string Media::getName() const { return name; }

/**
 * @brief Set the name of the media.
 * @param newName The new name of the media.
 */
void Media::setName(const string& newName) { name = newName; }

/**
 * @brief Get the file name of the media.
 * @return The file name of the media.
 */
string Media::getFileName() const { return fileName; }

/**
 * @brief Set the file name of the media.
 * @param newFileName The new file name of the media.
 */
void Media::setFileName(const string& newFileName) { fileName = newFileName; }

/**
 * @brief Display the media information.
 * @param s The output stream to display the information.
 */
void Media::display(ostream& s) const {
    s << "Name: " << name << endl;
    s << "File Name: " << fileName << endl;
}

/**
 * @brief Read the media information from a file.
 * @param file The input stream to read the information from.
 */
void Media::read(istream& file) {
    string name, filename;
    getline(file, name);
    setName(name);
    getline(file, fileName);
    setFileName(fileName);
}