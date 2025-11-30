#ifndef IO_HPP
#define IO_HPP
#include<fstream>
#include<iostream>
#include<string>
using namespace std;

class IO{
    public:
    IO(const string &file_path);
    ~IO();

    fstream getfilestream();

    private:
    fstream file_stream;


};



#endif
