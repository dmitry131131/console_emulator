#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "parser.h"

const size_t INITIAL_CAPACITY = 5;

typedef struct {
    size_t argc;
    char** argv;
    size_t capacity;
} CommandLine;

static int command_line_ctor(CommandLine* cmd, size_t capacity);
static int command_line_dtor(CommandLine* cmd);
static int command_line_dump(CommandLine* cmd);
static int read_command(CommandLine* cmd, char* line);

int console() {

    CommandLine cmd = {};
    command_line_ctor(&cmd, INITIAL_CAPACITY);

    char* line = NULL;
    size_t n = 0;

    getline(&line, &n, stdin);

    read_command(&cmd, line);

    CommandsArray commands_array = {};
    parse_commands(cmd.argc, cmd.argv, &commands_array);

    commands_array_dump(&commands_array);

    commands_array_dtor(&commands_array);

    // command_line_dump(&cmd);

    command_line_dtor(&cmd);
    free(line);
    
    return 0;
}

static int command_line_ctor(CommandLine* cmd, size_t capacity) {
    assert(cmd);

    cmd->capacity = capacity;

    cmd->argv = (char**) calloc(capacity, sizeof(char*));
    cmd->argc = 0;

    return 0;
}

static int command_line_dtor(CommandLine* cmd) {
    assert(cmd);
    
    free(cmd->argv);
    cmd->argc     = 0;
    cmd->capacity = 0;

    return 0;
}

static int command_line_dump(CommandLine* cmd) {
    assert(cmd);

    printf( "CAPACITY: %lu\n"
            "ARGC: %lu\n"
            "ARGV: ", cmd->capacity, cmd->argc);

    for (size_t i = 0; i < cmd->argc; i++) {
        printf("%s ", cmd->argv[0]);
    }   
    putchar('\n');

    return 0;
}

static int read_command(CommandLine* cmd, char* line) {
    assert(cmd);

    //printf("%s\n", line);

    char* current_token = strtok(line, " ");;

    for (size_t i = 0;; i++) {
        cmd->argv[i] = current_token;
        (cmd->argc)++;

        current_token = strtok(NULL, " ");
        if (!current_token) break;

        if (cmd->argc >= cmd->capacity - 1) {
            cmd->argv = (char**) realloc(cmd->argv, cmd->capacity * sizeof(char*) * 2);
            assert(cmd->argv);
            
            cmd->capacity *= 2;
        }
    }

    return 0;
}