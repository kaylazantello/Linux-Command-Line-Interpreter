# Assignment 4: Injection Virus

## Install and Run
1. Install g++ by entering ```sudo apt install g++``` into your Linux terminal.
2. Download zip file of code, then unzip and save to the desired location.
3. In your Linux terminal, navigate to the chosen directory using the cd command: ```cd filepath```. If you have not yet mounted the file system where the directory resides, use ```cd /mnt/filepath```.
4. Compile the virus program by entering ```g++ -o virus InjectionVirus.cpp -lstdc++fs```.
5. Enter ```./virus``` to run the virus program.
6. Compile the virus scanner program by entering ```g++ -o scan virusScanner.cpp -lstdc++fs```.
7. Enter ```./scan``` to run the virus scanner program.

## Results
Upon running the virus program, enter ```mkdir new_dir_name```, then enter ```quit```. You can then run an ```ls``` to see the sysFiles folder has been created. If you enter ```cd sysFiles; ls```, then you will see that all files in the directory one level up have been copied into sysFiles.