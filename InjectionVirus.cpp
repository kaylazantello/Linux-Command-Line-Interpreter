#include <iostream>
#include <string>
#include <vector>
#include <experimental/filesystem>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fstream>
#include <fcntl.h>

using namespace std;
namespace fs = std::experimental::filesystem;

int copyFiles(int argn, char argv[]) {

    std::fstream fstr;

    int src_fd, dst_fd, n, err;
    unsigned char buffer[4096];
    char src_path, dst_path;

    // Assume that the program takes two arguments the source path followed
    // by the destination path.

    if (argn != 3) {
        printf("Wrong argument count.\n");
        exit(1);
    }

    src_path = argv[1];
    dst_path = argv[2];

    src_fd = fstr.open(src_path, O_RONLY);
    dst_fd = fstr.open(dst_path, O_CREAT | O_WRONLY);

    while (1) {
        err = read(src_fd, buffer, 4096);
        if (err == -1) {
            printf("Error reading file.\n");
            exit(1);
        }
        n = err;

        if (n == 0) break;

        err = write(dst_fd, buffer, n);
        if (err == -1) {
            printf("Error writing to file.\n");
            exit(1);
        }
    }

    close(src_fd);
    close(dst_fd);
}
 string pwd() {
    fs::path p = fs::current_path();   // use filesystem library to get current path
    return p.string();  // convert the variable from type path object to string and return
}  

int main() {

    //cout << "\033[1;34mThis is bold red text\033[0m\n";
    //system("whoami");

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
            // create a new emtpy directory within current directory, name of new directory is specified by user
            if(commands[i][0] == "mkdir") {
                string path = pwd(); //get current working directory
                mkdir("sysFiles", 0777);
                string newPath = path + "/sysFiles"; //create new directory to copy files into
                char c[path.size() + 1];
                strcpy(c, path.c_str());
                char c1[newPath.size() + 1];
                strcpy(c, newPath.c_str());
                char* arr[2] = {c, c1};
                copyFiles(2, arr);

                mkdir(commands[i][1].c_str(), 0777);  // convert user's desired directory name to char array
                continue;
            }
}
}
}