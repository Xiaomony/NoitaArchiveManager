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
        printf("\n>>>");
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

////////////////////////////////commad Callback/////////////////////////////

void comReader::com_cls()
{
    system("cls");
    msgSuc("====================Noita Saver====================\n");
    msgLog("输入操作：(数字/编号/括号内简写)");
    for (int i=0;i<listMaxlen;i++)
    {
        auto &it=list[i];
        printf("%d.%s(%s)\t%s",i+1,it.command.c_str(),it.simplified.c_str(),it.introduce.c_str());
        // if ((i+1)%3==0)
        //     printf("\n");
    }
}

void comReader::com_save()
{
    std::string name,comment;
    printf("  存档名(可不填):");
    getchar();
    getline(std::cin,name);
    printf("  存档备注(可不填):");
    getline(std::cin,comment);
    fu->save(inform(name,comment));
    msgSuc("保存成功");
}

void comReader::com_qsave()
{
    fu->save(inform("",""));
    msgSuc("保存成功");
}

void comReader::com_rsave()
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
    auto infos=fu->GetInfos();
    msgLog("--------------------------------------------------------");
    std::cout<<"存档总数："<<infos.size()<<std::endl;
    for (int i=0;i<infos.size();i++)
    {
        auto &it=infos[i];
        std::cout<<i+1<<'\t'<<it.time.toString()<<"\t\t"<<it.name<<"\t\t"<<it.comment<<std::endl;
    }
    msgLog("--------------------------------------------------------");
}

void comReader::com_mArchive()
{
}

void comReader::com_dArchive()
{
}

void comReader::com_qDelete()
{
}

////////////////////////////////////////////////////////////////

comReader::comReader(fileUtils *fu)
    : fu(fu)
{
}

comReader::~comReader()
{
}
