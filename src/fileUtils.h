#pragma once
#include <filesystem>

namespace fs=std::filesystem;

class fileUtils
{
private:
    fs::path datapath,crrpath;
public:
    fileUtils();
    ~fileUtils();
};