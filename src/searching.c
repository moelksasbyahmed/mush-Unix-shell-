#include "../headers/searching.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <errno.h>
#include <signal.h>
#include <fcntl.h>
pid_t current_child_pid = -1;
int execute_command(char **args) {
    if (strchr(args[0], '/') != NULL) {
        if (access(args[0], X_OK) == 0) {
            pid_t pid = fork();
            if (pid == 0) {
                signal(SIGINT, SIG_DFL);
                execv(args[0], args);
                perror("execv failed");
                exit(EXIT_FAILURE);
            } else if (pid > 0) {
                
                int status;
                
                waitpid(pid, &status, 0);
                current_child_pid=pid;
                return WIFEXITED(status) && WEXITSTATUS(status) == 0;
            } else {
                perror("fork failed");
                return 0;
            }
        } else {
            printf("Not an executable file: %s\n", args[0]);
            return 0;
        }
    } else {
        const char *paths[] = {"/bin", "/usr/bin", "/usr/local/bin",};
        char full_path[256];
        bool found = false;
        char true_path[256];    
        for (int j = 0; j < sizeof(paths)/sizeof(paths[0]); j++) {
            snprintf(full_path, sizeof(full_path), "%s/%s", paths[j], args[0]);
            if (access(full_path, X_OK) == 0) {
                found = true;
                break;
            }
        }

        if (!found) {
            printf("Command not found: %s\n", args[0]);
            return 0;
        }

        pid_t pid = fork();
        if (pid == 0) {
            execv(full_path, args);
            perror("execv failed");
            exit(EXIT_FAILURE);
        } else if (pid > 0) {
            int status;
            waitpid(pid, &status, 0);
            return WIFEXITED(status) && WEXITSTATUS(status) == 0;
        } else {
            perror("fork failed");
            return 0;
        }
    }
}

void search_excutable(char **args) {
    bool redirecting = false;
    bool should_execute = true;
    bool last_command_success = true;

    for (int i = 0; args[i] != NULL; ) {
        if ( args[i]!=NULL&&strcmp(args[i], "exit") == 0) {
            free(args);
            exit(0);
        }
        if(args[i]!=NULL&&strcmp(args[i], "cd") == 0){
            if (args[i + 1] != NULL) {
                if (chdir(args[i + 1]) != 0) {
                    perror("cd failed");
                }
            } else {
                fprintf(stderr, "cd: missing argument\n");
            }
            i += 2;
            continue;
        }
        for (int i = 0; args[i] != NULL; i++) {
            if (strcmp(args[i], ">") == 0) {
                redirecting = true;
        
               
                args[i] = NULL;
        
                
                int fd = open(args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (fd < 0) {
                    perror("open failed");
                    return;
                }
                int saved_stdout = dup(STDOUT_FILENO);
                if (saved_stdout < 0) {
                    perror("dup failed");
                    close(fd);
                    return;
                }

            
                dup2(fd, STDOUT_FILENO);
        
               
                execute_command(args);
                close(fd);
                if (dup2(saved_stdout, STDOUT_FILENO) < 0) {
                    perror("restoring stdout failed");
                }
                close(saved_stdout); 
            
               
                return; 
            } 
        }
        if (args[i]!=NULL&&strcmp(args[i], "&&") == 0) {
            should_execute = last_command_success;
            i++;
            continue;
        } else if (args[i]!=NULL&&strcmp(args[i], "||") == 0) {
            should_execute = !last_command_success;
            i++;
            continue;
        }

       
        int cmd_end = i;
        while (args[cmd_end] != NULL &&
               strcmp(args[cmd_end], "&&") != 0 &&
               strcmp(args[cmd_end], "||") != 0) {
            cmd_end++;
        }

       
        char *next_op = args[cmd_end];
        args[cmd_end] = NULL;

        
        if (should_execute&&!redirecting) {
            last_command_success = execute_command(args + i);
        }

        
        args[cmd_end] = next_op;
        i = cmd_end;
        should_execute = true;
    }
}
