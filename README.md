# minish
## Usage:

- Makefile : build executable by "make all".  
- minish.c : single c file that implements basic mini shell (minish). 


1) Run "make" command after extracting files.  
2) It will compile 'minish.c' and generate executable file 'minish'.  
3) "./minish"  will launch the program and give prompt as follows, prompt will display current woking directory as well.

  - **minish:/home/csvb/os/hw1>>** 

##  minish is simple shell program which imitates basic shell functions as follows:

### 1. Run any command with single, multiple or no arguments

sh:/home/csvb/os/hw1/nisarg_hw1>>ls -l 
total 44  
-rw-rw-r-- 1 csvb csvb   102 Sep 20 00:56 Makefile  
-rwxrwxr-x 1 csvb csvb 13920 Sep 20 01:16 minish  
-rw-rw-r-- 1 csvb csvb  9121 Sep 20 01:16 minish.c  
-rw-rw-r-- 1 csvb csvb  8088 Sep 20 01:16 minish.o  
-rwxr-x--- 1 csvb csvb   275 Sep 20 00:56 myscript  
Exited, status=0  
minish: /home/csvb/os/hw1/nisarg_hw1>> 

### 2. Put any command or script in background by appending '&': 

minish:/home/csvb/os/hw1/nisarg_hw1>>sleep 10 &  
minish:/home/csvb/os/hw1/nisarg_hw1>>  

### 3. List backgrounded processes with "listjobs" command 

minish:/home/csvb/os/hw1/nisarg_hw1>>listjobs   
  List of backgrounded processes : 

| Name  |  PID | Status |
| -----| ------ |------ |
| sh | 19932  |FINISHED  |
| sleep | 19936  |RUNNING  |

minish:/home/csvb/os/hw1/nisarg_hw1>>

### 4. Put any backgrounded process in foreground by "fg" command :

minish:/home/csvb/os/hw1/nisarg_hw1>>sleep 30 & 
minish:/home/csvb/os/hw1/nisarg_hw1>>listjobs   
  List of backgrounded processes :  

| Name  |  PID | Status |
| -----| ------ |------ |
| sh | 19932  |FINISHED  |
| sleep | 19936  |FINISHED  |
| sh | 19937  |FINISHED  |
| sleep | 19953  |RUNNING  |

minish:/home/csvb/os/hw1/nisarg_hw1>>fg 19953  

### 5. Terminate current process by pressing "ctrl + c". 

minish:/home/csvb/os/hw1/nisarg_hw1>>sh myscript 1 2 3 
Displaying Arguments at an interval of 5 Seconds  
^C:Process 19962 Terminated:Killed by signal 2  
minish:/home/csvb/os/hw1/nisarg_hw1>>  

### 6. Change directory by "cd" or get current directory by "pwd"  

minish:/home/csvb/os/hw1>>pwd  
Current Working Directory : /home/csvb/os/hw1 
minish:/home/csvb/os/hw1>>cd ..  
Directory Changed to /home/csvb/os  
minish:/home/csvb/os>>cd ..  
Directory Changed to /home/csvb 
minish:/home/csvb>>cd os/hw1 
Directory Changed to os/hw1 
minish:/home/csvb/os/hw1>>pwd  
Current Working Directory : /home/csvb/os/hw1 
minish:/home/csvb/os/hw1>> 


### 7. Exit the shell by issuing "exit" command. 
It will first wait for any of its child processes to finish (to avoid orphan processes) and then terminate. 

minish:/home/csvb/os/hw1>>exit 

Waiting for any processes to finish...  
Done  
Good Bye !!   

csvb@CS550-npatel49:/os/hw1/nisarg_hw1$  



##      Thats All Folks !!    
