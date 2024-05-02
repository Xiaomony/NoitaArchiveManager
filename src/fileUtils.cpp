#include <string>
#include <windows.h>
#include <ShlObj.h>

#include "fileUtils.h"
#include "MyExpection.h"

fileUtils::fileUtils()
{
    char path[MAX_PATH];
    if (!SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_LOCAL_APPDATA, NULL, 0, path)))
        throw MyExpection("无法找到系统AppData文件夹");
    datapath.assign(path);
    if (!fs::exists(datapath))
        throw MyExpection("无法找到系统AppData文件夹");
    datapath=datapath.parent_path().append("LocalLow\\Nolla_Games_Noita");
    if (!fs::exists(datapath))
        throw MyExpection("无法找到Noita存档文件夹  请检查Noita是否安装");
    crrpath=fs::current_path();
    crrpath.append("Archive");
    fs::create_directory(crrpath);
}

fileUtils::~fileUtils()
{
}
