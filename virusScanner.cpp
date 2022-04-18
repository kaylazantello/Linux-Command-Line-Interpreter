#include <iostream>
#include <string>
#include <experimental/filesystem>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fstream>

using namespace std;
namespace fs = std::experimental::filesystem;

int main() {

    string str;

    // iterate current directory
    for(const fs::directory_entry& dir_entry : fs::recursive_directory_iterator(fs::current_path())) {
        ifstream fin(dir_entry.path().string());  // open each entry using ifstream object
        
        while(fin>>str) {  // while input string can be read in
            if(str == "fs::copy(path,") {  // search for virus signature
                cout << dir_entry.path().string() << " is infected!" << endl;
                fin.close();  // close file
                break;
            }
        }
        fin.close();  // close file
    }

    return 0;
}
