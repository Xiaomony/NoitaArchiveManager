#pragma once
#include <filesystem>
#include <vector>
#include <fstream>
#include <cstring>

namespace fs = std::filesystem;

struct st_time
{
    int year, month, day, hour, minute, second;
    st_time(int year, int month, int day,int hour, int minute, int second)
        :year(year),month(month),day(day),hour(hour),minute(minute),second(second) {};
    st_time();
    std::string toString()
        { return std::to_string(year)+'/'+std::to_string(month)+'/'+std::to_string(day)+"  "
                    +std::to_string(hour)+':'+std::to_string(minute)+':'+std::to_string(second); }
};

struct inform
{
    struct st_time time;
    char name[32];
    char comment[1024];
    inform(std::string name,std::string comment)
    {
        strcpy(this->name,name.c_str());
        strcpy(this->comment,comment.c_str());
    };
    inform(){};
    void change(std::string name,std::string comment)
    {
        strcpy(this->name,name.c_str());
        strcpy(this->comment,comment.c_str());
    };
};

class fileUtils
{
friend class comReader;
private:
    void saveLog();
    fs::path datapath, crrpath, infopath; //crrpath:path to the archives
    std::vector <inform> infos;
    std::fstream infofile;
public:
    void save(struct inform info);
    void delArchive(int index);
    void loadArchive(int index);
    double getUsageSpace();
    inline std::vector <inform> GetInfos() const {return infos;}
    fileUtils();
    ~fileUtils();
};