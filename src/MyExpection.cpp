#include <exception>
#include "MyExpection.h"

MyExpection::MyExpection(const char* msg)
    :message(msg)
{
}

MyExpection::~MyExpection()
{
}

const char *MyExpection::what() const throw()
{
    return message;
}
