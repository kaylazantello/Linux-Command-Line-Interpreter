/*********************************************************
Project 1: Improved UNIX/Linux Command Line Interpreter
Ethan Macalaguim and Kayla Zantello and Kara Burkholder
CST-315: Operating Systems
February 20, 2022
Commands implemented:
quit
ls
pwd
mkdir
rmdir
df
free
date
cat
cd 

1.Create and rename directories - DONE
2.Delete directories, with special handling of non-empty directories (e.g. special flag to delete command) -DONE
3.Create, rename, edit, and delete files -ALMOST DONE
4.When a file is created, a special flag will indicate the amount of data (bytes) to (randomly) generate for it (in order to eliminate the need to open and edit each file) -DONE
5.Move files across directories 
6.Duplicate files -ETHAN
7.Duplicate directories - ETHAN
8.Search for a file in a directory tree - DONE
9.Display a directory tree given a starting node - DONE
10.Get basic information about a file - DONE
11.Get detailed information about a file (e.g. using a special flag) -DONE
12.Get basic information about a directory - DONE
13.Get detailed information about a directory (e.g. using a flag) - DONE

Execute multiple commandds by entering a ; between commands
************************************************************/
#include <iostream>
#include <string>
#include <vector>
#include <experimental/filesystem>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
//#include <filesystem>
#include <fstream>

using namespace std;
namespace fs = std::experimental::filesystem;
//namespace nfs = std::filesystem;

// returns path of current directory as a string
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
        //cout << "\n> ";  // simple prompt
        //cout << "\n" << pwd() << "> ";  // path name prompt
        //cout << "\n\033[1;34m" << pwd() << "\033[0m> ";  // bold blue path name prompt

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

            // print path of current directory
            if(commands[i][0] == "pwd") {
                cout << pwd() << endl;
                continue;
            }

            // display list of the current directory's contents
            if(commands[i][0] == "ls") {
                for(int j = 0; j < commands[i].size() - 1; j++) {  // append any flags to the command string
                    commands[i][0] = commands[i][0] + " " + commands[i][j+1];
                }
                system(commands[i][0].c_str());  // convert command from string to char array, then use system() to execute command
                continue;
            }

            // removes a single file, multiple files, or a non-empty directory with -r
            if(commands[i][0] == "rm") {
                string p1 = commands[i][0];
                if(commands[i][1] == "-r") {
                    string p2 = " " + string("-r") + " " + commands[i][2];
                    p1.append(p2);
                }
                else{
                    for(int j=1;j<commands[i].size();j++) {
                        string p2 = " " + commands[i][j];
                        p1.append(p2);
                    }
                }

                system(p1.c_str());
                continue;
            }

            // copying files and directories with or without the use of special flags
            if(commands[i][0] == "cp") {
                string p1 = commands[i][0];

                // Copying of directories specifically (base case)
                if(fs::is_directory(commands[i][1])) {
                    string p2 = " " + commands[i][1] + " " + commands [i][2];
                    p1.append(p2);
                }
                else {
                    // copying everything else (and a directory special case)
                    //printf("it is not a directory");

                    // copying a file to a new directory
                    if(fs::is_directory(commands[i][2])) {
                        string p2 = " " + commands[i][1] + " " + commands[i][2];
                        p1.append(p2);
                    }

                    // determining whether or not the command has a flag
                    else if(commands[i].size() < 4) {
                        string p2 = " " + commands[i][1] + " " + commands[i][2];
                        p1.append(p2);
                    }

                    // copying based on special flags
                    // confirms that you are ok overwriting a file
                    else if(commands[i][1] == "-i") {
                        string p2 = " " + commands[i][1] + " " + commands[i][2] + " " + commands[i][3];
                        p1.append(p2);
                    }

                    // preserves original privilleges and owner of copied file
                    else if(commands[i][1] == "-p") {
                        string p2 = " " + commands[i][1] + " " + commands[i][2] + " " + commands[i][3];
                        p1.append(p2);
                    }

                    // Shows exactly what file is being copied and where it is being copied to
                    else if(commands[i][1] == "-v") {
                        string p2 = " " + commands[i][1] + " " + commands[i][2] + " " + commands[i][3];
                        p1.append(p2);
                    }

                    // forcing files to be copied regardless of permissions
                    else if(commands[i][1] == "-f") {
                        string p2 = " " + commands[i][1] + " " + commands[i][2] + " " + commands[i][3];
                        p1.append(p2);                        
                    }

                    // forcing directories to copied over recursively
                    else if(commands[i][1] == "-r") {
                        string p2 = " " + commands[i][1] + " " + commands[i][2] + " " + commands[i][3];
                        p1.append(p2);
                    }
                    
                    // takes into account copying more than one file at a time
                    else if(commands[i].size() > 3) {
                        for(int j=1;j<commands[i].size();j++) {
                            if(fs::is_directory(commands[i][j])) {
                                string p2 = " " + commands[i][j];
                                p1.append(p2);
                                break;
                            }
                            else {
                                string p2 = " " + commands[i][j];
                                p1.append(p2);
                            }
                        }
                    }                   

                }
                system(p1.c_str());
                continue;
            }

            // print the current date
            if(commands[i][0] == "date") {
                system(commands[i][0].c_str());
                continue;
            }

            // create a new emtpy directory within current directory, name of new directory is specified by user
            if(commands[i][0] == "mkdir") {
                mkdir(commands[i][1].c_str(), 0777);  // convert user's desired directory name to char array
                continue;
            }

            // remove an empty directory specified by user
            if(commands[i][0] == "rmdir") {
                // construct path string of directory to delete by adding directory name to the end of the current path
                string dirPath = pwd().append("/");
                dirPath.append(commands[i][1]);

                // convert path from string to char array, if rmdir() returns 0, then removal was successful
                if(rmdir(dirPath.c_str()) == 0) {
                    continue;
                }
                else {
                    cout << "rmdir: failed to remove \'" << commands[i][1] << "\'" << endl;  // notify user if unsuccessful
                    continue;
                }
            }

            // change the current working directory
            if(commands[i][0] == "cd") {
                chdir(commands[i][1].c_str());
                continue;
            }

            // concatenate and print files
            if(commands[i][0] == "cat") {
                if(commands[i][1] == ">") {
                    string newCommand = commands[i][0] + " > " + commands[i][2];
                    system(newCommand.c_str());
                    // PLACE CODE ON RANDOMLY GENERATING FILE BYTE SIZE HERE
                    fs::resize_file(commands[i][2], (rand()%100)+5);
                    continue;
                }
                else {
                    string newCommand2 = commands[i][0] + " " + commands[i][1];
                    system(newCommand2.c_str());
                    continue;
                }
            }

            // editing a file
            if(commands[i][0] == "vi") {
                string newCommand = commands[i][0] + " " + commands[i][2];
                system(newCommand.c_str());
                continue;
            }

            // display storage usage
            if(commands[i][0] == "df") {
                system(commands[i][0].c_str());
                continue;
            }

            // display RAM availability
            if(commands[i][0] == "free") {
                system(commands[i][0].c_str());
                continue;
            }

            // run short term process scheduler
            if(commands[i][0] == "./scheduler") {
                system(commands[i][0].c_str());
                continue;
            }

            // rename a file or directory
            if(commands[i][0] == "mv") {
                fs::rename(commands[i][1], commands[i][2]);  // arg 1 is old name, arg 2 is new name
                continue;
            }

            // display directory tree
            if(commands[i][0] == "tree") {
                system(commands[i][0].c_str());
                continue;
            }

            // get detailed information about a file or directory
            if(commands[i][0] == "stat") {
                string statCommand = commands[i][0] + " " + commands[i][1];
                system(statCommand.c_str());
                continue;
            }
            
            // search for a file in a directory tree
            if(commands[i][0] == "find") {
                for(int j = 0; j < commands[i].size() - 1; j++) {  // append the additional input to command string
                    commands[i][0] = commands[i][0] + " " + commands[i][j+1];
                }
                
                system(commands[i][0].c_str());
                continue;
            }

            //if(commands[i].size() == 0) {
            //if(commands[i][0] == " " || "") {
                //continue;
            //}
            
        }
    
    }
    return 0;
}