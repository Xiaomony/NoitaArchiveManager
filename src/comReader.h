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
    static const unsigned int listMaxlen = 11;
    struct comLists list [listMaxlen] = {
        {"quit","q",nullptr,"退出\t\t"},
        {"clearScreen","cls",com_cls,"清屏\n\n"},

        {"save","s",com_save,"保存\t\t"},
        {"qsave","qs",com_qsave,"快速保存\t\t"},
        {"rsave","rs",com_rsave,"覆盖式保存(覆盖最新存档)\n\n"},

        {"load","l",com_load,"读取存档\t"},
        {"qload","ql",com_qload,"快速读取(读取最新)\t"},
        {"log","lo",com_log,"查看存档信息\n\n"},

        {"mArchive","ma",com_mArchive,"修改存档信息\t"},
        {"delArch","del",com_delArch,"删除指定存档\t\t"},
        {"qDelete","qd",com_qDelete,"删除最新存档"}
    };

    fileUtils* fu;
protected:
    void com_cls();

    void com_save();
    void com_qsave();
    void com_rsave();

    void com_load();
    void com_qload();
    void com_log();

    void com_mArchive();
    void com_delArch();
    void com_qDelete();
public:
    void loop();
    comReader(fileUtils* fu);
    ~comReader();
};
