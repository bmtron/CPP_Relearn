#include <iostream>
#include "filescan.h"
#include "helpers.h"
#include <string>
#include <vector>

using namespace std;

int main()
{
    FileScan fScan;
    bool keepScanning = true;
    while(keepScanning) {
        vector<string> driveMap = fScan.listDrives();
        printf("Logical drives in use:\n");
        for (vector<string>::iterator it = driveMap.begin(); it != driveMap.end(); ++it)
        {
            cout << to_string(it - driveMap.begin() + 1) + ": " + *it << endl;
        }
        cout << "Please select a drive to scan" << endl;
        uint32_t userChoice;
        cin >> userChoice;
        string selectedDrive;

        if (userChoice > driveMap.size()) {
            cout << "Please make a valid selection." << endl;
            cin >> userChoice;
        }
        else
        {
            selectedDrive = driveMap[userChoice - 1];
        }
        cout << "You have selected drive" + selectedDrive + " to scan. Preparing scan now..." << endl;
        vector<string> dirMap = fScan.listDirectories(selectedDrive);

        for(vector<string>::iterator it = dirMap.begin(); it != dirMap.end(); ++it)
        {
            cout << *it << endl;
        }
        string user_input_keep_scanning;
        cout << "Would you like to scan again? y/n" << endl;
        cin >> user_input_keep_scanning;

        if (user_input_keep_scanning == "n") {
            keepScanning = false;
        }
    }
    return 0;
}
