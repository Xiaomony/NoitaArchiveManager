#include"comReader.h"

#include"MyExpection.h"
#include<iostream>
#include <windows.h>
#include <ShlObj.h>

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
                {
                    index=i;
                    break;
                }
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
    msgSuc("====================Noita Archive Manager====================\n");
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
        printf("存档名(必填,限32个字,直接回车取消存档):");
        getline(std::cin,name);
        if (!name.size())
            return ;
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
    int index = fu->infos.size()-1;
    if (index>=0)
    {
        std::cout<<"确定要覆盖存档\"["<<index+1<<"]"
        <<fu->infos[index].name<<"\t"<<fu->infos[index].time.toString()
        <<"\"吗(y/n):";
        std::string s;
        getchar();
        getline(std::cin,s);
        if (s!="y")
        {
            msgLog("取消覆盖");
            return ;
        }
        inform t=fu->infos.back();
        t.time=st_time();
        fu->infos.pop_back();
        fu->delArchive(index);
        fu->save(t);
        msgSuc("覆盖成功");
    }
    else
    {
        msgLog("当前无存档,直接保存");
        com_save();
    }
}

void comReader::com_load()
{
    printf("需要读取的存档的序号(0为取消):");
    int index;
    scanf("%d",&index);
    index--;
    if (index>=fu->infos.size()||index<0)
    {
        msgLog("取消读取");
        return ;
    }
    msgWrn("此过程会覆盖Noita中现有的存档,请谨慎操作!");
    std::cout<<"确定要读取存档\"["<<index+1<<"]"
            <<fu->infos[index].name<<"\t"<<fu->infos[index].time.toString()
            <<"\"吗(y/n):";
    std::string s;
    getchar();
    getline(std::cin,s);

    if (s!="y")
    {
        msgLog("取消读取");
        return ;
    }


    try
    {
        fu->loadArchive(index);
        msgSuc("读取成功");
    }
    catch(const std::exception& e)
    {
        throw;
    }
}

void comReader::com_qload()
{
    int index=fu->infos.size()-1;
    if (index<0)
    {
        msgLog("无存档可读取");
        return ;
    }
    msgWrn("此过程会覆盖Noita中现有的存档,请谨慎操作!");
    std::cout<<"确定要读取最新的存档\"["<<index+1<<"]"
            <<fu->infos[index].name<<"\t"<<fu->infos[index].time.toString()
            <<"\"吗(y/n):";
    std::string s;
    getchar();
    getline(std::cin,s);

    if (s!="y")
    {
        msgLog("取消读取");
        return ;
    }

    fu->loadArchive(index);
    msgSuc("读取成功");
}

void comReader::com_log()
{
    auto infos=fu->GetInfos();
    msgWrn("------------------------------------------------------------------------------------");
    printf("\033[0;33m");
    std::cout<<"存档总数："<<infos.size()<<std::endl;

    UINT defaultCodePage = GetACP();
    SetConsoleOutputCP(defaultCodePage);
    
    for (int i=0;i<infos.size();i++)
    {
        auto &it=infos[i];
        std::cout<<i+1<<'\t'<<it.time.toString()<<"\t\t"<<it.name<<"\t\t"<<it.comment<<std::endl;
    }
    SetConsoleOutputCP(CP_UTF8);
    printf("\033[0m");
    msgWrn("------------------------------------------------------------------------------------");
}

void comReader::com_mArchive()
{
    printf("需要修改的存档的序号(0为取消):");
    int index;
    scanf("%d",&index);
    index--;
    if (index>=fu->infos.size()||index<0)
        return ;
    std::string name,comment;
    getchar();
    do{
        printf("新存档名(必填,限32个字,直接回车以保持原本存档名):");
        getline(std::cin,name);
        if (name.size()>32)
            msgErr("超出了32个字");
        else
            break;
    }while(true);
    
    do{
        printf("新存档备注(限1024个字,直接回车以保持原本存档备注):");
        getline(std::cin,comment);
        if (comment.size()>1024)
            msgErr("超出了1024个字");
        else
            break;
    }while(true);
    if (name=="")
        name=fu->infos[index].name;
    if (comment=="")
        comment=fu->infos[index].comment;
    fu->infos[index].change(name,comment);
    msgSuc("修改存档成功");
}

void comReader::com_delArch()
{
    printf("需要删除的存档的序号(0为取消):");
    int index;
    scanf("%d",&index);
    index--;
    if (index>=fu->infos.size()||index<0)
    {
        msgLog("取消删除");
        return ;
    }
    std::cout<<"确定要删除存档\"["<<index+1<<"]"
            <<fu->infos[index].name<<"\t"<<fu->infos[index].time.toString()
            <<"\"吗(y/n):";
    std::string s;
    getchar();
    getline(std::cin,s);

    if (s!="y")
    {
        msgLog("取消删除");
        return ;
    }

    fu->delArchive(index);
    fu->infos.erase(fu->infos.begin()+index);
    msgSuc("删除成功");
}

void comReader::com_qDelete()
{
    if (!fu->infos.size())
    {
        msgErr("无存档");
        return ;
    }
    int index=fu->infos.size()-1;
    std::cout<<"确定要删除存档\"["<<index+1<<"]"
        <<fu->infos[index].name<<"\t"<<fu->infos[index].time.toString()
        <<"\"吗(y/n):";
    std::string s;
    getchar();
    getline(std::cin,s);

    if (s!="y")
    {
        msgLog("取消删除");
        return ;
    }

    fu->delArchive(index);
    fu->infos.erase(fu->infos.begin()+index);
    msgSuc("删除成功");
}

////////////////////////////////////////////////////////////////

comReader::comReader(fileUtils *fu)
    : fu(fu)
{
}

comReader::~comReader()
{
}
