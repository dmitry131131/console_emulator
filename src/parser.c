#include <stdio.h>
#include <assert.h>

#include "parser.h"

// TODO make full version with many commands support
int parse_commands(int argc, char* argv[], CommandsArray* commands_array) {
    assert(argv);
    assert(commands_array);

    assert(argc >= 2);  // TODO Make normal handling of few args error

    if (commands_array_ctor(commands_array, (size_t) argc)) {
        assert(0);  // TODO add normal handling of commands array ctor error
    }

    commands_array_add(commands_array, argv, (size_t) (argc - 2));

    commands_array_dump(commands_array);

    return 0;
}