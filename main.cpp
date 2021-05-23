#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <string>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <vector>
#include <cstring>


const char *  del = new char(' ');

// prints prompt 
std::string gecommand(bool& b) {
    // prints prompt
    
    // getuid -> returns the real user ID of the calling process
    if (getuid() == 0) {
        // root
        std::cout << "# ";
    } else {
        // non-root user
        std::cout << "$ ";
    }


    std::string command;
    getline(std::cin, command);

    if (command.back() == *("&")) {
        b  = true;
        command.pop_back();
    }

    return command;
}


int main() {
    while(true) {
        // get user's command
        std::string command;
        bool b = false;
        command = gecommand(b);
        std::vector<char *> tokens;
        char *token;
        char* line = const_cast<char*>(command.c_str());
        token = strtok(line, del);
        while (token != NULL) {
            tokens.push_back(token);
            token = strtok(NULL, del);
        }
        if (strcmp(tokens[0],"exit") == 0) {
            return 0;
        }
        // check if the program is a child program 
        pid_t pid = fork(), waitPid;

        if (pid == 0) {
            // check if it is a backgroud command or not
            if (execvp(tokens[0], &tokens[0]) == -1) {
                perror("Error in Child");
            }
            exit(1);

        } else {
            /* 
                execute the given program with arguments by susing 
                execvp or its friends
            */ 
           if(!b) {
                waitPid = waitpid(pid, 0, 0);
            }
        }

        
    }
}