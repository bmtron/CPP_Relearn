#ifndef FILESCAN_H
#define FILESCAN_H
#include <string>
#include <vector>
#include <filesystem>
class FileScan
{
public:
    FileScan();
    std::vector<std::string> listDrives();
    std::vector<std::string> listDirectories(std::string mainPath);
    uintmax_t getDirectorySize(std::filesystem::directory_entry);
    std::string scan();
};

#endif // FILESCAN_H
