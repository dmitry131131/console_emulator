#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>

typedef enum {
    NO_COMMAND_SPLITTER,         
    AND_COMMAND_SPLITTER,        
    PIPE_COMMAND_SPLITTER,       
    BACKGROUND_COMMAND_SPLITTER
} CommandsSplitter;

typedef struct {
    char*            command;
    size_t           argument_count;
    char**           argument_list;
    CommandsSplitter splitter;
} Command;

typedef struct {
    Command* array;
    size_t         commands_count;
    size_t         commands_capacity;
} CommandsArray;

int commands_array_ctor(CommandsArray* commands_array, size_t commands_count);
int commands_array_dtor(CommandsArray* commands_array);
int commands_array_add(CommandsArray* commands_array, char** command, size_t argument_count, CommandsSplitter splitter);
void commands_array_dump(const CommandsArray* commands_array);

int command_ctor(Command* command, char** command_text, size_t argument_count, CommandsSplitter splitter);
int command_dtor(Command* command);
void command_dump(const Command* command);

#endif