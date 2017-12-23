#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <libgen.h>
#include <sys/types.h>
#include <signal.h>

#define BUFFER_LENGTH 1024
void handleSignal(int signal) {}
int main()
{

  char input[BUFFER_LENGTH];
  char *command[50];        //command entered by user
  char *bin_path = "/bin/"; //path to bin
  char path[20];            //full file path
  int command_count;        //argument count
  int background;           //Background Command flag
  int no_command = 0;       //No Command entered flag
  pid_t child_pid, fg_pid, fg_pid1, w;
  int status;
  int bg_process[25];
  char bg_process_name[25][100]; //Background Process array
  int bg_count = 0;
  char current_directory[1024];
  char *dir_parts[50];
  int dir_count;
  signal(SIGINT, handleSignal); //catch signal sent by ctrl+c
 while (1)
  {

    for (int k = 0; k < bg_count; k++)
    {
      w = waitpid(bg_process[k], &status, WNOHANG);
    }

    //get current working directory
    getcwd(current_directory, sizeof(current_directory));

    // printf("------------------\n Minish Started \n ------------------\n");
    //print shell prompt
    printf("minish:~%s>>", current_directory);
    no_command = 0;
    background = 0;

    //Get input from user via stdin
    if (fgets(input, BUFFER_LENGTH, stdin) != NULL)
    {
      if (input[0] == '\n') //no Command is entered
      {
        no_command = 1;
      }
      int len = strlen(input);
      if (len > 0 && input[len - 1] == '\n') //remove \n characer that fgets append
      {                                      // and replace it with NULL
        input[--len] = '\0';
      }
    }
 //tokenize full command into space seperated strings
    char *token;
    token = strtok(input, " ");
    int i = 0;
    while (token)
    {
      command[i] = token;
      token = strtok(NULL, " ");
      i++;
    }
    command[i] = NULL; //assigned null value to last token
    command_count = i;

    //inbuilt commands which will not run by fork exec mechanism
    if (no_command == 0)
    {
      //listjobs command
      if (strcmp(command[0], "listjobs") == 0)
      {
        no_command = 1;
        printf("List of backgrounded processes :\n");
        printf("------------------------------------------\n");
        printf("Name\t\tPID\t\tStatus\t\t\n");
        printf("------------------------------------------\n");
        int w_status;
        char process_status[20] = "Default";
        for (int k = 0; k < bg_count; k++)
        {
          w = waitpid(bg_process[k], &w_status, WNOHANG);
          int s = kill(bg_process[k], 0);
          if (s == 0)
  strcpy(process_status, "RUNNING");
          else
            strcpy(process_status, "FINISHED");
          printf("%s\t\t%d\t\t%s\t\t\n", bg_process_name[k], bg_process[k], process_status);
        }
        printf("------------------------------------------\n");
      }

      //fg command
      if (strcmp(command[0], "fg") == 0)
      {
        no_command = 1;
        fg_pid = atoi(command[1]);
        fg_pid1 = waitpid(fg_pid, &status, 0);
        if (fg_pid1 == -1)
          perror("waitpid");
        //int temp_status = kill(fg_pid1, SIGCONT);
      }

      //cd command
      if (strcmp(command[0], "cd") == 0)
      {
        no_command = 1;

        if (strcmp(command[1], "..") == 0)
        {
          char *dirc, *dname;
          if (getcwd(current_directory, sizeof(current_directory)) != NULL)
          {
			dirc = strdup(current_directory);
            dname = dirname(dirc);
            int chdir_rtrn = chdir(dname);
            if (chdir_rtrn == 0)
              printf("Directory Changed to %s \n", dname);
            else
              perror("chdir");
          }
          else
          {
            perror("getcwd");
          }
        }

        if (strncmp(command[1], "/", 1) != 0 && strcmp(command[1], "..") != 0)
        {
          if (getcwd(current_directory, sizeof(current_directory)) != NULL)
          {
            strcpy(current_directory, "/");
            strcpy(current_directory, command[1]);
            int chdir_rtrn = chdir(current_directory);
            if (chdir_rtrn == 0)
              printf("Directory Changed to %s\n", current_directory);
            else
              perror("chdir");
          }
          else
			  {
            perror("getcwd");
          }
        }

        if (strncmp(command[1], "/", 1) == 0 && strcmp(command[1], "..") != 0)
        {
          if (getcwd(current_directory, sizeof(current_directory)) != NULL)
          {
            strcat(current_directory, command[1]);
            int chdir_rtrn = chdir(current_directory);
            if (chdir_rtrn == 0)
              printf("Directory Changed to %s/n", current_directory);
            else
              perror("error");
          }
          else
          {
            perror("getcwd");
          }
        }
      }
	  
	    //pwd command
      if (strcmp(command[0], "pwd") == 0)
      {
        no_command = 1;

        if (getcwd(current_directory, sizeof(current_directory)) != NULL)
          printf("Current Working Directory : %s\n", current_directory);
        else
          perror("getcwd");
      }

      //exit command
      if (strcmp(command[0], "exit") == 0)
      {
        no_command = 1;
        printf("Waiting for any processes to finish...\n");
        fg_pid1 = wait(NULL);
        if (fg_pid1 == -1)
          perror("waitpid");
        printf("Done\n");
        printf("Good Bye !!\n");
        return EXIT_SUCCESS;
      }
    }
 //Normal commands which will run by fork exec mechanism
    if (no_command == 0) //Start forking and execution if command is entered
    {
      if (strcmp(command[i - 1], "&") == 0)
      {
        command[i - 1] = NULL;
        background = 1;
      }
      strcpy(path, bin_path);   //prefix command with /bin
      strcat(path, command[0]); //add program to path
      for (i = 0; i < strlen(path); i++)
      {
        if (path[i] == '\n') //replace any newline character with null
          path[i] = '\0';
      }

      child_pid = fork();

      //Error in fork
      if (child_pid < 0)
        perror("fork error");

      //Child Process
      if (child_pid == 0)
      {
        int exec_value = execvp(path, command);
        if (exec_value == -1)
        {
 perror("execlp");
          exit(EXIT_FAILURE);
        }
      }

      //Parent Process
      else
      {
        // command is entered in normal mode
        if (background == 0)
        {
          w = waitpid(child_pid, &status, WUNTRACED);
          if (w == -1)
          {
            perror("waitpid");
            exit(EXIT_FAILURE);
          }
          if (WIFEXITED(status))
          {
            printf("Exited, status=%d\n", WEXITSTATUS(status));
          }
          else if (WIFSIGNALED(status))
          {
            printf("Killed by signal %d\n", WTERMSIG(status));
          }
          else if (WIFSTOPPED(status))
          {
            printf("Stopped by signal %d\n", WSTOPSIG(status));
          }
 else if (WIFCONTINUED(status))
          {
            printf("Continued\n");
          }
        }
      }

      // command is entered in background mode;
      if (background == 1)
      {
        w = waitpid(child_pid, &status, WNOHANG);
        if (w == -1)
        {
          perror("waitpid");
          exit(EXIT_FAILURE);
        }
        //add process to backgground process array
        bg_process[bg_count] = child_pid;
        strcpy(bg_process_name[bg_count], command[0]);
        bg_count++;
      }
    }
  }
}


