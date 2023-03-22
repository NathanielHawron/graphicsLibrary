#pragma once

#include <cstdint>

//Constructor/Destructor
template <class sizetype>
graphics::FileHandle<sizetype>::FileHandle(std::size_t bufferSize):
index(0), flags(0), bytes(std::vector<char>())
{
    this->bytes.reserve(bufferSize);
}

template <class sizetype>
graphics::FileHandle<sizetype>::FileHandle(std::filesystem::path &path):
index(0), flags(0){
    std::ifstream file = std::ifstream(path,std::ios::binary);
    if(file.is_open()){
        this->bytes = std::vector<char>(std::istreambuf_iterator<char>(file),std::istreambuf_iterator<char>());
    }else{
        this->flags |= FileHandle::FLAG_FAILED_TO_READ_FILE;
    }
}
template <class sizetype>
graphics::FileHandle<sizetype>::~FileHandle(){}

//Read data from file
template <class sizetype>
void graphics::FileHandle<sizetype>::readFile(std::filesystem::path &path){
    std::ifstream file = std::ifstream(path,std::ios::binary);
    if(file.is_open()){
        std::vector<char> buf = std::vector<char>(std::istreambuf_iterator<char>(file),std::istreambuf_iterator<char>());
        for(uint_fast32_t i=0;i<buf.size();++i){
            this->bytes.push_back(buf.at(i));
        }
    }else{
        this->flags |= FileHandle::FLAG_FAILED_TO_READ_FILE;
    }
    file.close();
}

//Add data to buffer
template <class sizetype> template<class T>
void graphics::FileHandle<sizetype>::addData(const T data){
    const char *p = (char*)&data;
    for(uint_fast32_t i=0;i<sizeof(T);++i){
        this->bytes.push_back(p[i]);
    }
}

template <class sizetype> template<class T>
void graphics::FileHandle<sizetype>::addData(const T *data){
    const char *p = (char*)data;
    for(uint_fast32_t i=0;i<sizeof(T);++i){
        this->bytes.push_back(p[i]);
    }
}
template <class sizetype>
void graphics::FileHandle<sizetype>::addString(const std::string &string){
    this->addData((sizetype)string.size());
    for(uint_fast32_t i=0;i<string.size();++i){
        this->bytes.push_back(string.at(i));
    }
}
template <class sizetype> template<class T>
void graphics::FileHandle<sizetype>::addVector(const std::vector<T> &data){
    this->addData((sizetype)data.size());
    for(uint_fast32_t i=0;i<data.size();++i){
        this->addData(&data.at(i));
    }
}
template <class sizetype> template<class T>
void graphics::FileHandle<sizetype>::addVector(const T *data, std::size_t size){
    this->addData((sizetype)size);
    for(uint_fast32_t i=0;i<size;++i){
        this->addData(data[i]);
    }
}

//Get data from buffer
template <class sizetype> template<class T>
T graphics::FileHandle<sizetype>::getData(){
    T res;
    this->getData(&res);
    return res;
}
template <class sizetype> template<class T>
void graphics::FileHandle<sizetype>::getData(T *res){
    char *p = (char*)res;
    for(uint_fast32_t i=0;i<sizeof(T);++i){
        if(this->index>=this->bytes.size()){
            p[i]=0;
            //@TODO: error
        }else{
            p[i]=this->bytes.at(index);
        }
        ++this->index;
    }
}
template <class sizetype>
std::string graphics::FileHandle<sizetype>::getString(){
    std::string res;
    sizetype size = this->getData<sizetype>();
    for(sizetype i=0;i<size;++i){
        res.push_back(this->getData<char>());
    }
    return res;
}
template <class sizetype> template <class T>
void graphics::FileHandle<sizetype>::getVector(std::vector<T> &res){
    sizetype size = this->getData<sizetype>();
    for(sizetype i=0;i<size;++i){
        res.push_back(this->getData<T>());
    }
}

template <class sizetype>
void graphics::FileHandle<sizetype>::writeData(std::filesystem::path &path){
    if(std::filesystem::exists(path.parent_path())){
        std::ofstream file = std::ofstream(path);
        file.write(this->bytes.data(),this->bytes.size());
        file.close();
    }else{
        //@TODO: error
    }
}

//Interact with buffer
template <class sizetype>
std::size_t graphics::FileHandle<sizetype>::getSize() const{
    return this->bytes.size();
}
template <class sizetype>
uint32_t graphics::FileHandle<sizetype>::getIndex() const{
    return this->index;
}
template <class sizetype>
void graphics::FileHandle<sizetype>::setIndex(uint32_t index){
    this->index = index;
}
template <class sizetype>
void graphics::FileHandle<sizetype>::reserve(uint32_t amount){
    this->bytes.reserve(amount);
}

//Interact with flags
template <class sizetype>
bool graphics::FileHandle<sizetype>::getFlags(char flags) const{
    return (this->flags & flags)!=0;
}
template <class sizetype>
void graphics::FileHandle<sizetype>::clearFlags(){
    this->flags = 0;
}