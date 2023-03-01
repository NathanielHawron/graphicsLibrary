#pragma once

#include <filesystem>
#include <fstream>
#include <vector>
#include <string>

namespace graphics{
    template <class sizetype = std::size_t>
    class FileHandle{
    private:
        std::vector<char> bytes;
        uint32_t index;
        char flags;
    public:
        //Flags
        static const uint8_t FLAG_FAILED_TO_READ_FILE = 0b00000001;
        //static const uint8_t FLAG_ = 0b00000010;
        //Constructor/Destructor
        FileHandle(std::size_t bufferSize = 1000);
        FileHandle(std::filesystem::path &path);
        ~FileHandle();
        //Read file into buffer
        void readFile(std::filesystem::path &path);
        //Add data to buffer
        template <class T>
        void addData(const T data);
        template <class T>
        void addData(const T *data);
        void addString(const std::string &string);
        template <class T>
        void addVector(const std::vector<T> &data);
        template <class T>
        void addVector(const T *data, std::size_t size);
        //Get data from buffer
        template <class T>
        T getData();
        template <class T>
        void getData(T *res);
        std::string getString();
        template <class T>
        void getVector(std::vector<T> &res);
        //Write buffer to file
        void writeData(std::filesystem::path &path);
        //Interact with buffer
        std::size_t getSize() const;
        uint32_t getIndex() const;
        void setIndex(uint32_t index);
        void reserve(uint32_t amount);
        //Interact with flags
        bool getFlags(char flags) const;
        void clearFlags();
    };
}

#include "file_handle.cpp"