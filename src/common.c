#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "common.h"

//-------------------------------> COMMAND ARRAY FUNCTION <-------------------------------------//

int commands_array_ctor(CommandsArray* commands_array, size_t commands_count) {
    assert(commands_array);

    commands_array->array = (Command*) calloc(commands_count, sizeof(Command));
    if (!(commands_array->array)) return 1;

    commands_array->commands_capacity = commands_count;
    commands_array->commands_count    = 0;

    return 0;
}

int commands_array_dtor(CommandsArray* commands_array) {
    assert(commands_array);

    for (size_t i = 0; i < commands_array->commands_count; i++) {
        command_dtor(&(commands_array->array[i]));
    }

    commands_array->commands_capacity = 0;
    commands_array->commands_count    = 0;

    free(commands_array->array);
    commands_array->array = NULL;

    return 0;
}

int commands_array_add(CommandsArray* commands_array, char** command, size_t argument_count, CommandsSplitter splitter) {
    assert(commands_array);
    assert(command);

    command_ctor(&(commands_array->array[commands_array->commands_count]), command, argument_count, splitter);

    (commands_array->commands_count)++;

    return 0;
}

void commands_array_dump(const CommandsArray* commands_array) {
    assert(commands_array);

    printf( "COMMAND COUNT: %lu\n"
            "COMMAND CAPACITY: %lu\n"
            "COMMANDS:\n\n", commands_array->commands_count, commands_array->commands_capacity);

    for (size_t i = 0; i < commands_array->commands_count; i++) {
        command_dump(&(commands_array->array[i]));
    }
}

//-----------------------------------> COMMAND FUNCTIONS <------------------------------//

int command_ctor(Command* command, char** command_text, size_t argument_count, CommandsSplitter splitter) {
    assert(command);
    assert(command_text);

    command->argument_count = argument_count;   // initialize command
    command->command        = command_text[0];
    command->splitter       = splitter;

    command->argument_list = (char**) calloc(argument_count + 1, sizeof(char*));
    if (!(command->argument_list)) return 1;

    for (size_t i = 0; i < argument_count; i++) {
        command->argument_list[i] = command_text[i+1];
    }

    // command->argument_list[argument_count] = NULL; // Make null terminated argument array

    return 0;
}

int command_dtor(Command* command) {
    assert(command);

    free(command->argument_list);
    command->argument_count = 0;
    command->command        = NULL;
    command->splitter       = NO_COMMAND_SPLITTER;

    return 0;
}

void command_dump(const Command* command) {
    assert(command);

    printf("COMMAND: %s\n",          command->command);
    printf("ARG COUNT: %lu\n",       command->argument_count);
    printf("COMMAND SPLITTER: %u\n", command->splitter);
    printf("ARGS: ");

    for (size_t i = 0; i < command->argument_count; i++) {
        printf("%s ", command->argument_list[i]);
    }
    printf("\n\n");
}