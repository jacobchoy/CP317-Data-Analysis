#ifndef FILEREADER_H
#define FILEREADER_H

#include <fstream>
#include <string>
#include <map>
#include "student.h"

class FileReader{
    private:
        std::string fileName;
        std::ifstream inputFile;

    public:
        FileReader();
        FileReader(const std::string& filename);

        ~FileReader() = default;

        std::string getFileName() const;
        std::ifstream& getFile();

        void setFileName(const std::string& name);
        void setFile (const std::string& filename);

        bool readNameFile (std::map<std::string, Student>& students);
        bool readCourseFile(std::map<std::string, Student>& students);
};

#endif