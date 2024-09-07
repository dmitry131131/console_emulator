#include "console.h"
#include "parser.h"

int main(int argc, char* argv[]) {

    CommandsArray commands_array = {};

    parse_commands(argc, (argv+1), &commands_array);

    commands_array_dtor(&commands_array);

    return 0;
}