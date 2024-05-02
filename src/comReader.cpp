#include"comReader.h"

#include"MyExpection.h"
#include<iostream>


void comReader::loop()
{
    com_cls();
    std::string command;
    int index;
    do
    {
        index=-1;
        printf("\n>>>");
        std::cin>>command;
        try
        {
            index=std::stoi(command)-1;
            if (index>=listMaxlen||index<0)
                index=-1;
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
        if (!index)
            break;
        if (index!=-1)
            ((*this).*(list[index].clBack))();
    } while (true);
    
}

////////////////////////////////commad Callback/////////////////////////////

void comReader::com_cls()
{
    system("cls");
    msgSuc("====================Noita Saver====================\n");
    printf("\033[0;34m");
    msgLog("输入操作：(数字/编号/括号内简写)");
    for (int i=0;i<listMaxlen;i++)
    {
        auto &it=list[i];
        printf("%d.%s(%s)\t%s",i+1,it.command.c_str(),it.simplified.c_str(),it.introduce.c_str());
        // if ((i+1)%3==0)
        //     printf("\n");
    }
    printf("\033[0m");
}

void comReader::com_save()
{
    std::string name,comment;
    getchar();
    do{
        printf("存档名(可不填,限32个字):");
        getline(std::cin,name);
        if (name.size()>32)
            msgErr("超出了32个字");
        else
            break;
    }while(true);
    
    do{
    printf("存档备注(可不填,限1024个字):");
    getline(std::cin,comment);
        if (comment.size()>1024)
            msgErr("超出了1024个字");
        else
            break;
    }while(true);

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
    msgWrn("------------------------------------------------------------------------------------");
    printf("\033[0;33m");
    std::cout<<"存档总数："<<infos.size()<<std::endl;
    for (int i=0;i<infos.size();i++)
    {
        auto &it=infos[i];
        std::cout<<i+1<<'\t'<<it.time.toString()<<"\t\t"<<it.name<<"\t\t"<<it.comment<<std::endl;
    }
    printf("\033[0m");
    msgWrn("------------------------------------------------------------------------------------");
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
