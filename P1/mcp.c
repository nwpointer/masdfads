#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdbool.h>
#include "./substring.c"
#include <sys/stat.h>
#include <proc/readproc.h>

volatile sig_atomic_t print_flag = false;

void runChildProcess(char **tokens, int numtokens){

    int sig;

    sigset_t sigset;
    sigemptyset(&sigset);
    sigaddset(&sigset, SIGUSR1);
    sigprocmask(SIG_BLOCK, &sigset, NULL);

    int result = sigwait(&sigset, &sig);
    
    char * const t[1] = {"foo"};
    execvp(tokens[0], t);

    printf("Unknown command\n");
    exit(0);
}

void handle_alarm( int sig ) {
    print_flag = true;
}


int main(int argc, char *argv[]){
	if(argc < 2){
                return 0;
    }
    FILE *instructions;
	instructions = fopen(argv[1], "r");
    if(instructions == NULL)
        return 1;

    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    char **tokens;
    size_t numtokens;

    int status;

    pid_t pid[1024];
    int pStatus[1024];
    int p=0;
    int returnStatus;

	while((read = getline(&line, &len, instructions)) != -1){
		tokens = strsplit(line, ", \t\n", &numtokens);
        p++;
		pid[p] = fork();
        pStatus[p] = 1;
		if (pid[p]) {
            continue;
		} else if (pid[p] == 0) {   
            // child
            runChildProcess(tokens, numtokens);
		} else {
		    printf("fork error\n");
		    exit(1);
		}
		if (tokens != NULL) free(tokens);
    }

    

    // PROCTAB* proc = openproc(PROC_FILLMEM | PROC_FILLSTAT | PROC_FILLSTATUS);
    // proc_t proc_info;
    // memset(&proc_info, 0, sizeof(proc_info));
    // while (readproc(proc, &proc_info) != NULL) {
    //     if(proc_info.ppid == parrent){
    //         printf("%20s:\t%5ld\t%5lld\t%5lld\n",
    //                proc_info.cmd, proc_info.resident,
    //                proc_info.utime, proc_info.stime);
    //     }
    // }

    // signal( SIGALRM, handle_alarm ); // Install handler first,
    // alarm( 1 ); // before scheduling it to be called.

    // int z=0;
    // int current;
    // int next;

    // while (z<10) {
    //     if ( print_flag ) {
    //         current = ((z)%p)+1;
    //         next = (((z)+1)%p)+1;
    //         printf( "%d,%d\n", current, next);
    //         // 
    //         if(z<=2){
    //             printf("init\n");
    //             kill(pid[current],SIGUSR1);
    //             // sleep(1);
    //             kill(pid[current],SIGSTOP);
    //         }else{
    //             kill(pid[current],SIGSTOP);
    //             // sleep(1);
    //             kill(pid[next],SIGCONT);
    //         }

    //         // 
    //         print_flag = false;
    //         alarm( 2 );
    //         z++;
    //     }
    // }
    // for(int i=1; i<=p;i++){
    //     kill(pid[i],SIGKILL);
    // }

    pid_t poll = fork();

    if(poll == 0){
        signal( SIGALRM, handle_alarm ); // Install handler first,
        alarm( 1 ); // before scheduling it to be called.

        int z=0;
        int current;
        int next;
        int done = 0;
        pid_t parrent = getppid();
        char * pname = argv[0];



        PROCTAB* proc;
        proc_t proc_info;
        char str[80];
        

        
        while (!done) {
            if ( print_flag ) {
                current = ((z)%p)+1;
                next = (((z)+1)%p)+1;
                // 
                if(z<p){
                    printf("init %d\n", current);
                    kill(pid[current],SIGUSR1);
                    kill(pid[current],SIGSTOP);
                }else{
                    printf( "ending %d, starting %d\n", current, next);
                    kill(pid[current],SIGSTOP);
                    kill(pid[next],SIGCONT);
                }
                // 
                print_flag = false;
                alarm( 2 );
                z++;


                // check process status to continue or kill while loop
                int s = 0;
                printf("S: %d \n", s);
                for(int i=1; i<=p;i++){
                    printf("%d\n", kill(pid[i], 0));
                    s+= kill(pid[i],0);
                    if(s==-p){
                        printf("Done\n");
                        // break;
                        // kill(getpid(), SIGKILL);
                        done = 1;
                        // return(0);
                    }
                }

                // print process information
                proc = openproc(PROC_FILLMEM | PROC_FILLSTAT | PROC_FILLSTATUS);
                memset(&proc_info, 0, sizeof(proc_info));
                while (readproc(proc, &proc_info) != NULL) {
                    strcpy(str, "./");
                    strcat(str,proc_info.cmd);
                    if(strcmp(str, pname) == 0){
                        printf("CMD | PPID | CPU TIME |  PROCESS STATUS\n");
                        printf("%5s:\t%5ld\t%5lld\t%5lld %d\n",
                               proc_info.cmd,
                               proc_info.ppid,
                               proc_info.utime,
                               proc_info.state
                               );
                    }
                }
                closeproc(proc);
            }
        }
        // clean up
        for(int i=1; i<=p;i++){
            kill(pid[i],SIGKILL);
        }

        fclose(instructions);
        if(line){
            free(line);
        }  

        return(0);
    }else{
        printf("initializing processes\n");
        // waitpid(pid[3],)
        //return(0);
        /* Establish handler. */
        // wait(0);
        // wait(0);
        // wait(0);
        // while(1){

        // }
        // int returnStatus; 
        // int z=0;   
        // while(z<12){
        //     if ( print_flag ) {
        //         printf("%d\n", kill(pid[1], 0));
        //         z++;
        //     }
            
        // }
        // waitpid(0, &returnStatus, 0);
        // kill(poll,SIGKILL);
        // while(1){
        //     for(int i=1; i<=p;i++){
        //         printf("%d", kill(pid[i], 0));
        //     }
        // }

        // for(int i=1; i<=p;i++){
        //     kill(pid[i],SIGUSR1);
        //     kill(pid[i],SIGSTOP);
        // }
        // kill(pid[2],SIGUSR1);
        // sleep(1);
        // kill(pid[2],SIGSTOP);
        // kill(pid[3],SIGUSR1);
        // sleep(1);
        // kill(pid[3],SIGSTOP);

        // for (int i = 0; i < 5; ++i)
        // {
        //     // kill(pid[i],SIGUSR1);
        //     // sleep(1);
        //     // kill(pid[i],SIGSTOP);
        //     // waitpid(pid[i], &returnStatus, 0);
        // }
        // waitpid(poll, &returnStatus, 0);
        // wait(1);
        
        // for(int i=1; i<=p;i++){
        //     waitpid(pid[i], &returnStatus, 0);
        // }
        // kill(poll,SIGKILL);
    }


    // for(int i=1; i<=p;i++){
    //     kill(pid[i],SIGUSR1);
    //     // kill(pid[i],SIGSTOP);
    //     // kill(pid[i],SIGCONT);
           
    //     waitpid(pid[i], &returnStatus, 0);  // Parent process waits here for child to terminate.

    //     if (returnStatus == 0)  // Verify child process terminated without error.  
    //     {
    //       printf("no error\n");
    //     }

    //     if (returnStatus == 1)      
    //     {
    //       printf("error\n");
    //     }
    // }

    


    // int z =1;
    // while(pStatus[1] || pStatus[2] || pStatus[3]) {
    //     if ( print_flag ) {
    //         if(z<=p){
    //             printf("%d\n",z);
    //             pStatus[z] = 0;
    //             // kill(pid[z],SIGUSR1);
    //             // kill(pid[z],SIGSTOP);
    //             // waitpid(pid[z], &returnStatus, 0);
    //         }

    //         print_flag = false;
    //         alarm( 2 );
    //         z++;
    //     }   
    // }

    // for(int i=0; i<=p;i++){
    //    int returnStatus;    
    //    waitpid(pid[i], &returnStatus, 0);  // Parent process waits here for child to terminate.

    //    if (returnStatus == 0)  // Verify child process terminated without error.  
    //    {
    //       printf("no error\n");
    //    }

    //    if (returnStatus == 1)      
    //    {
    //       printf("error\n");
    //    }
    // }
    

 //    printf("done\n");


   
   
 //    // free(pid);
 //    // free(pStatus);
    //kill(poll,SIGKILL);
    exit(0);

}
