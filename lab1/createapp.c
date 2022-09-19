#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int createapp(char *cmd, char **argv)
{
    int pid = fork();
    //Child
    if (pid==0)
    {
        nice(10);
        // sleep(10);
        execvp(cmd, argv);
        // comes here only if execvp fails
        exit(1);
    }
    //Parent
    else
    {
        int status;
        // blocking call (non blocking approach is explained in the pdf)
        waitpid(pid, &status, 0);

        if ( WIFEXITED(status) )
        {
            int exit_status = WEXITSTATUS(status);       
            // printf("Exit status of the child was %d\n", exit_status);
            if(exit_status==1)
            {
                return -1;
            }
        }
        
    }
    return pid;
}

int main()
{
    char* command = "ls";
    char* argument_list[] = {"ls", "-l", NULL};
    int i = createapp(command, argument_list);
    printf("\npid: %d\n", i);

}