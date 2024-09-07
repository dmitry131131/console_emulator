#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "parser.h"

const char* AND_COMMAND_TOKEN  = "&&";
const char* PIPE_COMMAND_TOKEN = "|";

typedef struct {
    size_t start;
    size_t end;
} Pair;

typedef struct {
    Pair*   array;
    size_t  capacity;
    size_t  current_pointer;
} StartPositionArray;

static StartPositionArray start_position_array_ctor(size_t capacity);
static int start_position_array_dtor(StartPositionArray* array);

// TODO make full version with many commands support
int parse_commands(size_t argc, char* argv[], CommandsArray* commands_array) {
    assert(argv);
    assert(commands_array);
    
    if (argc < 1) return 0;

    StartPositionArray command_start_positions = start_position_array_ctor(argc);

    command_start_positions.array[command_start_positions.current_pointer].start = 0;  
    
    for (size_t i = 0; i < argc; i++) {
        if (!strcmp(argv[i], AND_COMMAND_TOKEN)) {
            command_start_positions.array[command_start_positions.current_pointer].end = i - 1;
     
            command_start_positions.current_pointer++;
            command_start_positions.array[command_start_positions.current_pointer].start = i + 1;
        }
    }
    command_start_positions.array[command_start_positions.current_pointer].end = argc - 1;
    command_start_positions.current_pointer++;

    if (commands_array_ctor(commands_array, command_start_positions.current_pointer)) {
        assert(0);  // TODO add normal handling of commands array ctor error
    }

    for (size_t i = 0; i < command_start_positions.current_pointer; i++) {
        commands_array_add( commands_array,
                            argv + command_start_positions.array[i].start, 
                            command_start_positions.array[i].end - command_start_positions.array[i].start);
    }

    start_position_array_dtor(&command_start_positions);

    return 0;
}

static StartPositionArray start_position_array_ctor(size_t capacity) {
    StartPositionArray array = {};
    
    array.array = (Pair*) calloc(capacity, sizeof(Pair));
    assert(array.array);

    array.capacity        = capacity;
    array.current_pointer = 0;

    return array;
}

static int start_position_array_dtor(StartPositionArray* array) {
    assert(array);

    free(array->array);
    array->capacity = 0;

    return 0;
}   