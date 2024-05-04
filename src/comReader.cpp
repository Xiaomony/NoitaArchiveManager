#include"comReader.h"

#include"MyExpection.h"
#include<iostream>
#include<windows.h>
#include<ShlObj.h>

void comReader::loop()
{
    com_cls();
    std::string command;
    int index;
    do
    {
        index=-1;
        printf(">>>");
        //std::cin>>command;
        getline(std::cin, command);
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

void comReader::print_log(int start, int end)
{
    auto infos=fu->GetInfos();
    msgWrn("------------------------------------------------------------------------------------");
    printf("\033[0;33m");
    std::cout<<"存档总数："<<infos.size()<<"\n";

    UINT defaultCodePage = GetACP();
    SetConsoleOutputCP(defaultCodePage);
    
    start = std::max(0,start);
    end = std::min((int)(infos.size())-1,end);
    for (int i=start;i<=end;i++)
    {
        auto &it=infos[i];
        std::cout<<i+1<<'\t'<<it.time.toString()<<"\t\t"<<it.name<<"\t\t"<<it.comment<<std::endl;
    }
    SetConsoleOutputCP(CP_UTF8);
    printf("\033[0m");
    msgWrn("------------------------------------------------------------------------------------");
}

void comReader::com_help()
{
    msgWrn("---------------------------------------------------------------");
    msgWrn("gitHub主页:https://github.com/Xiaomony/NoitaArchiveManager.git");
    msgWrn("1.本程序运行时会在程序所在目录下建立一个Archive文件夹用于存储日志文件和保存的存档,请勿删除(若删除,则相当于恢复程序第一次运行的状态)");
    msgWrn("2.建议将程序放在磁盘中的某个文件夹下,再发送到桌面快捷方式使用(避免程序在桌面创建Archive文件夹后被误删)");
    msgWrn("3.请在Noita主界面有\"继续\"这一选项时读取存档,若没有则请先\"新游戏\"后再关闭游戏读档,重新打开后再点击\"继续\"");
    msgWrn("4.建议关闭Steam云存档");
    msgWrn("5.请在Noita正常保存、关闭后再进行存档");
    msgWrn("  (游戏进行中存档的话保存的是Noita的自动存档,可能是几分钟前的存档,并非保存时的存档)");
    msgWrn("6.游戏进行中请勿读取存档");
    msgWrn("7.随着游戏的进行,每次存档所用的时间和占用的空间也会不断增大,请耐心等待");
    // msgWrn("");
    msgWrn("---------------------------------------------------------------");
}

void comReader::com_cls()
{
    system("cls");
    msgSuc("====================Noita Archive Manager====================");
    msgSuc("==================初次使用请使用help或h查看帮助==================\n");
    printf("\033[0;34m");
    msgLog("输入操作：(数字/编号/括号内简写)");
    for (int i=0;i<listMaxlen;i++)
    {
        auto &it=list[i];
        printf("%d.%s(%s)\t%s",i+1,it.command.c_str(),it.simplified.c_str(),it.introduce.c_str());
    }
    printf("\033[0m");
}

void comReader::com_save()
{
    std::string name,comment;
    //getchar();
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
        std::cout<<"确定要覆盖存档\"["<<index+1<<"]";

        UINT defaultCodePage = GetACP();
        SetConsoleOutputCP(defaultCodePage);
        std::cout<<fu->infos[index].name<<"\t";
        SetConsoleOutputCP(CP_UTF8);
        
        std::cout<<fu->infos[index].time.toString()<<"\"吗(y/n):";

        std::string s;
        //getchar();
        getline(std::cin,s);
        if (s!="y")
        {
            msgLog("取消覆盖");
            return ;
        }
        inform t=fu->infos.back();
        t.time=st_time();
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
    if (!fu->infos.size())
    {
        msgErr("无存档可读取");
        return;
    }
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
    std::cout<<"确定要读取存档\"["<<index+1<<"]";

    UINT defaultCodePage = GetACP();
    SetConsoleOutputCP(defaultCodePage);
    std::cout<<fu->infos[index].name<<"\t";
    SetConsoleOutputCP(CP_UTF8);
    
    std::cout<<fu->infos[index].time.toString()<<"\"吗(y/n):";
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
        msgErr("无存档可读取");
        return ;
    }
    msgWrn("此过程会覆盖Noita中现有的存档,请谨慎操作!");
    std::cout<<"确定要读取最新的存档\"["<<index+1<<"]";

    UINT defaultCodePage = GetACP();
    SetConsoleOutputCP(defaultCodePage);
    std::cout<<fu->infos[index].name<<"\t";
    SetConsoleOutputCP(CP_UTF8);

    std::cout<<fu->infos[index].time.toString()<<"\"吗(y/n):";

    std::string s;
    //getchar();
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
    print_log(0,fu->infos.size()-1);
}

void comReader::com_slog()
{
    print_log(fu->infos.size()-7,fu->infos.size()-1);
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
    fu->saveLog();
    msgSuc("修改存档成功");
}

void comReader::com_delArch()
{
    if (!fu->infos.size())
    {
        msgErr("无存档");
        return ;
    }
    printf("需要删除的存档的序号(0为取消):");
    int index;
    scanf("%d",&index);
    index--;
    if (index>=fu->infos.size()||index<0)
    {
        msgLog("取消删除");
        return ;
    }
    std::cout<<"确定要删除存档\"["<<index+1<<"]";

    UINT defaultCodePage = GetACP();
    SetConsoleOutputCP(defaultCodePage);
    std::cout<<fu->infos[index].name<<"\t";
    SetConsoleOutputCP(CP_UTF8);
    
    std::cout<<fu->infos[index].time.toString()<<"\"吗(y/n):";
    std::string s;
    getchar();
    getline(std::cin,s);

    if (s!="y")
    {
        msgLog("取消删除");
        return ;
    }

    fu->delArchive(index);
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
    std::cout<<"确定要删除存档\"["<<index+1<<"]";

    UINT defaultCodePage = GetACP();
    SetConsoleOutputCP(defaultCodePage);
    std::cout<<fu->infos[index].name<<"\t";
    SetConsoleOutputCP(CP_UTF8);
    
    std::cout<<fu->infos[index].time.toString()<<"\"吗(y/n):";
    std::string s;
    //getchar();
    getline(std::cin,s);

    if (s!="y")
    {
        msgLog("取消删除");
        return ;
    }

    fu->delArchive(index);
    msgSuc("删除成功");
}

void comReader::com_usage()
{
    printf("占用空间:%.2fMB\n",fu->getUsageSpace());
}

////////////////////////////////////////////////////////////////

comReader::comReader(fileUtils *fu)
    : fu(fu)
{
}

comReader::~comReader()
{
}
