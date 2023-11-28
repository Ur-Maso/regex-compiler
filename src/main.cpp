#include <string>
#include <iostream>
#include <stdexcept>
#include <cstdarg>
#include <map>
#include <queue>
#include <vector>
#include <c_string.h>
#include "type.h"
#include "output.h"
#include "args_parser.h"
int main(int argc, const char** argv) {
    auto args = args::parse(argc, argv);
    // use analyser to check arguments
    args::analyser(args);
    
}