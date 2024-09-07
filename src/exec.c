#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "exec.h"

#define MAX_PATH_LEN 1024

static int execute(Command* command);

// TODO support running many commands
int execute_commands(CommandsArray* commands_array) {
    assert(commands_array);

    const pid_t child_pid = fork();

    if (child_pid < 0) { assert(0); }  // fork error

    if (child_pid) {
        int status = 0;
        waitpid(child_pid, &status, 0);
        printf("Exit status: %d\n", status);
    }
    else {
        // execl("/bin/ls", "ls", NULL); // this is the code the child runs 
        execute(&(commands_array->array[0]));
    }

    return 0;
}

static int execute(Command* command) {
    assert(command);

    char path[MAX_PATH_LEN] = {'/', 'b', 'i', 'n', '/'};

    strcat(path, command->command);

    char** args = (char**) calloc(command->argument_count + 1, sizeof(char*));
    assert(args);

    args[0] = command->command;
    for (size_t i = 0; i < command->argument_count; i++) {
        args[i + 1] = command->argument_list[i];
    }

    execv(path, args);

    free(args);

    return 0;
}