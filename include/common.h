#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>

typedef struct {
    char*  command;
    size_t argument_count;
    char** argument_list;
} Command;

typedef struct {
    Command* array;
    size_t         commands_count;
    size_t         commands_capacity;
} CommandsArray;

int commands_array_ctor(CommandsArray* commands_array, size_t commands_count);
int commands_array_dtor(CommandsArray* commands_array);
int commands_array_add(CommandsArray* commands_array, char** command, size_t argument_count);
void commands_array_dump(const CommandsArray* commands_array);

int command_ctor(Command* command, char** command_text, size_t argument_count);
int command_dtor(Command* command);
void command_dump(const Command* command);

#endif