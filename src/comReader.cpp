#include"comReader.h"

#include"MyExpection.h"
#include<iostream>

void comReader::loop()
{
    com_cls();
    std::string command;
    int index=0;
    do
    {
        std::cin>>command;
        try
        {
            index=std::stoi(command);
        }
        catch(const std::invalid_argument)
        {
            for (int i=0;i<listMaxlen;i++)
            {
                auto &it=list[i];
                if (command==it.command||command==it.simplified)
                    index=i;
            }
        }
        catch(const std::out_of_range)
        {
            continue;
        }
        if (!index)
            break;
        ((*this).*(list[index].clBack))();
    } while (true);
    
}

//////////commad Callback////////////

void comReader::com_cls()
{
    system("cls");
    msgSuc("====================Noita Saver====================\n");
    msgLog("输入操作：(数字/编号/括号内简写)");
    for (int i=0;i<listMaxlen;i++)
    {
        auto &it=list[i];
        printf("%d.%s(%s)\t%s\t",i+1,it.command.c_str(),it.simplified.c_str(),it.introduce.c_str());
        if ((i+1)%3==0)
            printf("\n");
    }
    printf("\n>>>");
}

void comReader::com_save()
{
}

void comReader::com_qsave()
{
}

void comReader::com_load()
{
}

void comReader::com_qload()
{
}

void comReader::com_log()
{
}

////////////////////////////////

comReader::comReader(fileUtils *fu)
    : fu(fu)
{
}

comReader::~comReader()
{
}
