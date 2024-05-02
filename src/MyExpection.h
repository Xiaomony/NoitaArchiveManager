#pragma once

#define msgLog(msg) printf("\033[0;34m%s\033[0m\n",msg)
#define msgSuc(msg) printf("\033[0;32m%s\033[0m\n",msg)
#define msgWrn(msg) printf("\033[0;33m%s\033[0m\n",msg)
#define msgErr(msg) printf("\033[0;31m%s\033[0m\n",msg)

class MyExpection:public std::exception
{
private:
    const char* message;
public:
    MyExpection(const char* msg);
    ~MyExpection();
    const char* what() const throw();
};
