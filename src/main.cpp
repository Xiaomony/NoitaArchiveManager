#include <filesystem>
#include <cstdio>
#include <windows.h>
#include <ShlObj.h>
#include <string>
#include <exception>
#include <iostream>

#include "fileUtils.h"
#include "MyExpection.h"
#include "comReader.h"

fileUtils* fu;
comReader* cr;

void init();
void loop();

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    try
    {
        init();
        loop();
    }
    catch(const MyExpection& e)
    {
        msgErr(e.what());
    }
    delete fu;
    delete cr;
    system("pause");
    return 0;
}

void init()
{
    fu=new fileUtils();
    cr=new comReader(fu);
}

void loop()
{
    cr->loop();
}
