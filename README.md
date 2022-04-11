# Linux-Command-Line-Interpreter

## Install and Run
1. Install g++ by entering ```sudo apt install g++``` into your Linux terminal.
2. Install the tree command by entering ```sudo apt install tree```.
3. Download zip file of code, then unzip and save to the desired location.
4. In your Linux terminal, navigate to the chosen directory using the cd command: ```cd filepath```. If you have not yet mounted the file system where the directory resides, use ```cd /mnt/filepath```.
5. Compile the program by entering ```g++ -o start cmdLnInterpreter.cpp -lstdc++fs```.
6. Enter ```./start``` to run the program.

## Commands Implemented
1. quit: exit command line interpreter
2. ls: display a list of the current directory's contents
3. pwd: print path of current directory
4. mkdir: create a new empty directory within current directory
5. rmdir: remove an empty directory within current directory
6. df: display how much space is available on your system
7. free: display how much RAM is available on your system
8. date: print current date
9. cat: create a new file and write to it or print a single file
10. cd: change current working directory
11. rm: removes a single file, multiple files, or a non-empty directory with -r
12. cp: copy files and directories with or without the use of special flags, flags include -i, -v, -p, -f, -r
13. vi: edits an exisiting file
14. mv: rename file or directory
15. tree: displays directory tree from current locations
16. stat: get detailed information about a file or directory
17. find: search for a file in a directory tree

## Additional Notes on Inputting Commands
### Running multiple commands
This command line interpreter allows the user to run multiple commands in a single line by placing a ';' between commands. Commands will be run in the order they were entered. Spaces before or after the semicolon do not affect output.
```
> pwd; mkdir myDir; ls
```
*This will print the path of the current directory, create a new empty directory named 'myDir', then display a list of the current directory's contents*.
### cat
The 'cat' command can be used to print the contents of a single file.
```
> cat myFile.txt
```
*This will display the contents of myFile.txt*.  

It can also be used to create a new file and write to it using the '>' operator. The text entered beneath the command will be written to the file until **CTRL + D** is entered *on a new line*. If the file name passed in already exists in the current directory, that file will be overwritten.
```
> cat > newFile.txt
this is a new file
created with the cat command
^D
```
*This will create a file called 'newFile.txt' which will contain the two lines under the command*.

### vi
the 'vi' command can be used to edit the contents of a single file.
'''
> vi myFile.txt
'''
*This will open up an editor to insert text into myFile.txt*.

Then, you need to press i, type whatever edit you want to make.
To save the edits, press ESC key. Type :wq! filename
Thus you will have successfuly edited a file.

### cp flags
-i: confirms that you are ok overwriting a file  
-v: shows exactly what file is being copied and where it is being copied to  
-p: preserves original privilleges and owner of copied file  
-f: forcing files to be copied regardless of permissions  
-r: forcing directories to copied over recursively  

### find
The 'find' command is used to search for a file in a directory tree. From the directory that is one level above the one you would like search, follow the example below.
```
> find ./directory_name -name filename
```
*This will return the relative path of any file matching that name*  

You can also search for a specific file extension.
```
> find ./directory_name -name *.ext
```

