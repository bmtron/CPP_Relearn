#include "filescan.h"
#include <windows.h>
#include <direct.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include "helpers.h"

namespace fs = std::filesystem;

FileScan::FileScan()
{
}

std::string FileScan::scan()
{
    return "";
}

std::vector<std::string> FileScan::listDrives()
{
    TCHAR szDrive[ ] = _T(" A:");
    std::vector<std::string> driveMap;
    DWORD uDriveMask = GetLogicalDrives();

    //printf("The bitmask of the logical drives is hex: %0lX\n", uDriveMask);
    //printf("The bitmask of the logical drives in decimal: %lu\n", uDriveMask);
    if (uDriveMask == 0)
    {
        printf("\nGetLogicalDrives() failed with failure code: %lu\n", GetLastError());
    }
    else
    {
        //printf("\nThis machine has the following logical drives:\n");
        while(uDriveMask)
        {
            if (uDriveMask & 1)
            {
                //printf("%s\n", szDrive);
                std::string tempDrive = szDrive;
                driveMap.push_back(tempDrive);
            }
            ++szDrive[1];
            uDriveMask >>= 1;
        }
       // printf("\n");
    }
    return driveMap;
}

std::vector<std::string> FileScan::listDirectories(std::string mainPath) {
    std::vector<std::string> dMap;
    Helpers helper;
    const fs::path drivePath = fs::path(helper.trim(mainPath) + "\\");
    for (const auto& entry : fs::directory_iterator(drivePath)) {
        const auto filenameStr = entry.path().filename().string();
        if (entry.is_directory() && filenameStr != "System Volume Information" && filenameStr != "$Recycle.Bin") {
            size_t dirSize = 0;
            try {
                for(fs::recursive_directory_iterator it(entry.path()); it != fs::recursive_directory_iterator(); ++it)
                {
                    if (!fs::is_directory(*it))
                    {
                        dirSize += fs::file_size(*it);
                    }
                }
                dMap.push_back("dir: " + filenameStr + " size: " + std::to_string(dirSize / pow(1024, 3)) + " GB");
            } catch (const std::exception& e) {
                std::cerr << e.what() << std::endl;
            }
        }
        else if (entry.is_regular_file()) {

            dMap.push_back("file: " + filenameStr + " size: " + std::to_string(entry.file_size() / pow(1024, 3)) + " GB");
        }
    }


    return dMap;
}

uintmax_t FileScan::getDirectorySize(std::filesystem::directory_entry entry) {
    const fs::path dirPath = fs::path(entry.path());
    uintmax_t fileSize = 0;
    for (const auto& fileEntry : fs::directory_iterator(dirPath)) {
        if (fileEntry.is_directory()) {
            fileSize += getDirectorySize(fileEntry);
        }
        else if (fileEntry.is_regular_file()) {
            fileSize += fileEntry.file_size();
        }
        else {
            return fileSize;
        }
    }
    return fileSize;
}
