#include <string>
#include <windows.h>
#include <ShlObj.h>

#include "comReader.h"
#include "fileUtils.h"
#include "MyExpection.h"

st_time::st_time()
{
        auto now = std::chrono::system_clock::now();
        auto time = std::chrono::system_clock::to_time_t(now);
        auto lt = std::localtime(&time);

        year = lt->tm_year + 1900;
        month = lt->tm_mon + 1; // 月份从0开始计算，所以需要加上1
        day = lt->tm_mday;
        hour = lt->tm_hour;
        minute = lt->tm_min;
        second = lt->tm_sec;
}
////////////////////////////////////////

void fileUtils::save(inform info)
{
    fs::path newArchpath = crrpath;
    newArchpath.append("archive"+std::to_string(infos.size()));
    fs::create_directories(newArchpath);
    fs::copy(datapath,newArchpath,fs::copy_options::recursive);
    infos.push_back(info);
}

void fileUtils::delArchive(int index)
{
    fs::path p=crrpath;
    p.append("Archive"+std::to_string(index));
    try {
        fs::remove_all(p);
        fs::path old;
        while(index<infos.size()-1)
        {
            old=crrpath;
            old.append("Archive"+std::to_string(index+1));
            fs::rename(old,p);
            p=old;
            index++;
        }
    } catch (const std::filesystem::filesystem_error& e) {
        throw MyExpection("未能删除存档");
    }
}

///////////////////////////////////////
fileUtils::fileUtils()
{
    char path[MAX_PATH];
    if (!SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_LOCAL_APPDATA, NULL, 0, path)))
        throw MyExpection("无法找到系统AppData文件夹");
    datapath.assign(path);
    if (!fs::exists(datapath))
        throw MyExpection("无法找到系统AppData文件夹");
    datapath=datapath.parent_path().append("LocalLow\\Nolla_Games_Noita\\save00");
    if (!fs::exists(datapath))
        throw MyExpection("无法找到Noita存档文件夹  请检查Noita是否安装");
    crrpath=fs::current_path();
    crrpath.append("Archive");
    fs::create_directory(crrpath);

    infopath=crrpath;
    infopath.append("information.log");
    if (!fs::exists(infopath))
    {
        std::fstream f(infopath,std::ios::out);
        if (!f.is_open())
            throw MyExpection("创建日志文件失败");
        f.close();
    }
    else{
        infofile.open(infopath,std::ios::in|std::ios::binary);
        if (!infofile.is_open())
            throw MyExpection("打开日志文件失败");

        infofile.seekg(0, std::ios::end);
        size_t file_size = infofile.tellg();
        if (file_size)
        {
            infofile.seekg(0,std::ios::beg);
            infos=std::vector <inform> (file_size/sizeof(inform));
            try
            {
                infofile.read(reinterpret_cast<char*>(infos.data()),file_size);
            }
            catch(const std::exception& e)
            {
                throw MyExpection("读取日志文件失败(Archive文件夹下的information.log损坏)");
            }
        }
        infofile.close();
    }
}

fileUtils::~fileUtils()
{
    infofile.open(infopath,std::ios::out|std::ios::binary);
    infofile.write(reinterpret_cast<char*>(infos.data()),sizeof(inform)*infos.size());
    infofile.close();
}
