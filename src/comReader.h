#pragma once
#include<string>
#include"fileUtils.h"
class comReader;

typedef void (comReader::*comCallBack)();
struct comLists
{
    std::string command,simplified,introduce;
    comCallBack clBack;
    comLists(std::string command,std::string simplified,comCallBack clBack,std::string introduce)
        :command(command),simplified(simplified),clBack(clBack),introduce(introduce)
        {};
};

class comReader
{
private:
    static const unsigned int listMaxlen = 7;
    struct comLists list [listMaxlen] = {
        {"quit","q",nullptr,"退出"},
        {"clearScreen","cls",com_cls,"清屏"},
        {"save","s",com_save,"保存"},
        {"qsave","qs",com_qsave,"快速保存"},
        {"load","l",com_load,"读取存档"},
        {"qload","ql",com_qload,"快速读取(读取最新)"},
        {"log","lo",com_log,"输出存档信息"}
    };

    fileUtils* fu;
protected:
    void com_cls();
    void com_save();
    void com_qsave();
    void com_load();
    void com_qload();
    void com_log();
public:
    void loop();
    comReader(fileUtils* fu);
    ~comReader();
};
