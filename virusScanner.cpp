/*
Kayla Zantello, Kara Sumpter, Ethan Macalaguim

Project 2: Pager - A Virtual Memory Manager
CST-315: Operating Systems
Dr.Citro
March 9, 2022

This program simulates the paging method of virtual memory by reading in a text file representing logical memory,
generating a page table that maps each page of logical memory to a random frame in physical memory,
then using that page table to place data from logical memory into the correct spot in physical memory.
Finally, the program writes the current state of physical memory to another text file.
*/
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
