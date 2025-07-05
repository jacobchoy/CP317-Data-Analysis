#ifndef FILEWRITER_H
#define FILEWRITER_H

#include <fstream>
#include <string>
#include <map>
#include "student.h"

class FileWriter{
    private:
        std::string fileName;
        std::ofstream outputFile;

    public:
        FileWriter();
        FileWriter(const std::string& filename);

        ~FileWriter() = default;

        std::string getFileName() const;
        std::ofstream& getFile();

        void setFileName(const std::string& name);
        void setFile(const std::string& filename);

        bool writeOutputFile(const std::map<std::string, Student>& students);
};

#endif