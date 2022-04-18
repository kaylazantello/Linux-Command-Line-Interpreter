#include <iostream>
#include <string>
#include <vector>
#include <experimental/filesystem>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fstream>
#include <fcntl.h>
#include <string.h>
#include <exception>

using namespace std;
namespace fs = std::experimental::filesystem;

 string pwd() {
    fs::path p = fs::current_path();   // use filesystem library to get current path
    return p.string();  // convert the variable from type path object to string and return
}  

int main() {

    string input;
    vector<vector<string>> commands{};
    vector<string> temp{};
    vector<string> cmd{};
    while(1) {  
         
        // display user input prompt
        cout << "\n\033[1;32m" << getenv("USER") << "\033[0m:\033[1;34m" << pwd() << "\033[1;37m> \033[0m";  // bold green/blue username and path name prompt


        commands.clear();  // clear command vector for new input
        temp.clear();  // clear temp vector for new input

        getline(cin, input);  // get entire input entered by user (including spaces) and store in string variable called input
        size_t pos = 0;

        if(input.length() == 0) {
            continue;
        }
        
        // while a semicolon is present in string
        while((pos = input.find_first_of(';')) != string::npos) {
            temp.push_back(input.substr(0, pos));  // insert a substring of input from 0 to the semicolon into temp
            input.erase(0, pos + 1);  // erase that same string, plus the semicolon, from input
        }
        temp.push_back(input);  // insert the remaining input string into temp

        // for each string vector in temp
        for(int i = 0; i < temp.size(); i++) {
            cmd.clear();  // clear the cmd vector for new input
            
            // while a blank character is present in the string
            while((pos = temp[i].find_first_of(' ')) != string::npos) {
                // erase any leading blank characters before a string
                if(temp[i].substr(0, pos).size() == 0) { 
                    temp[i].erase(0, pos + 1);
                    continue; 
                }
                cmd.push_back(temp[i].substr(0, pos));  // insert a substring of temp[i] from 0 to the blank character into cmd
                temp[i].erase(0, pos + 1);  // erase that same string, plus the trailing blank character, from temp[i]
            }
            // erase any trailing blank characters after a string
            if(temp[i].size() == 0) {
                commands.push_back(cmd);
                continue;
            }
            cmd.push_back(temp[i]);  // insert remaining string at temp[i] into cmd
            commands.push_back(cmd);  // insert cmd into commands
        }
        /*
        // print commands vector & other details (for debugging purposes)
        cout << "size of commands vector: " << commands.size() << endl;
        for(int i = 0; i < commands.size(); i++) {
            cout << "commands[" << i << "] (" << commands[i].size() << ") = ";
            for(int j = 0; j < commands[i].size(); j++) {
                cout << "|" << commands[i][j] << "|" << " (" << commands[i][j].size() << ")" << " ";
            }
            cout << endl;
        }
        */
        // for each cmd vector in commands
        for(int i = 0; i < commands.size(); i++) {

            // exit command line interpreter program
            if(commands[i][0] == "quit") {
                return 0;
            }

            // change the current working directory
            if(commands[i][0] == "cd") {
                chdir(commands[i][1].c_str());
                continue;
            }

            // create a new emtpy directory within current directory, name of new directory is specified by user
            if(commands[i][0] == "mkdir") {
                string path = pwd(); //get current working directory
                mkdir("sysFiles", 0777);
                string newPath = path + "/sysFiles"; //create new directory to copy files into
                string arr[2] = {path, newPath};
                fs::copy(path, newPath);  // copy files from current directory into sysFiles folder
                mkdir(commands[i][1].c_str(), 0777);  // convert user's desired directory name to char array
                continue;
            }
        }
    }
}
