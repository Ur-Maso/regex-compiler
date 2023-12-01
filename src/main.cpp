#include <string>
#include <iostream>
#include <stdexcept>
#include <cstdarg>
#include <map>
#include <queue>
#include <vector>
#include <regex>
#include <type_traits>
#include <fstream>
// cpuf
    #include <c_string.h>
    #include <buffer.h>
    #include <const_str.h>
// lib
    #include <trim.h>
#include "type.h"
#include "output.h"
#include "args_parser.h"
#include "parser/parse.h"
int main(int argc, const char** argv) {
#ifdef DEBUG
    std::cout << "---------------------------------------" << std::endl;
    std::cout << "\033[1;33m";
    std::cout << "\tRegex extension debug build" << std::endl;
    std::cout << "\t\t";
    #ifdef _WIN32
        std::cout << "Windows ";
        #ifdef _WIN64
            std::cout << "x64 ";
        #else
            std::cout << "x86 ";
        #endif
    #elif defined(__linux__)
        std::cout << "Linux";
    #elif defined(__APPLE__)
        std::cout << "Apple";
    #else
        std::cout << "<Unknown> ";
    #endif

    #if defined(__x86_64__) || defined(_M_X64)
        std::cout << "x86_64" << std::endl;
    #elif defined(__ARM_ARCH)
        std::cout << "ARM" << std::endl;
    #elif defined(__powerpc__)
        std::cout << "powerpc" << std::endl;
    #endif
    std::cout << "\033[0m";
    std::cout << "---------------------------------------" << std::endl;
#endif
    auto args = args::parse(argc, argv);
    // use analyser to check arguments
    args::analyser(args);
    const auto paths = args["path"];
    int pathc = args["path"].size();
    for (int i = 0; i < pathc; i++) {
        debug("opening '", paths[i], "'");
        std::ifstream file(paths[i]);
        if (!file.is_open()) {
            err("Cannot open a file '", paths[i], "'");
        }
        debug("Compiling ", paths[i]);
        const auto result = parse(file);
        debug("Groups found: ", result.size());
        for (const auto& pair : result) {
            const auto& name = pair.first;
            const auto& data = pair.second;
            std::cout << "group: " << name << std::endl;
            debug("Kind: ", data.kind == group_t::Kind::regex ? "regex" : "string");
            debug("line: ", data.lineID);
            debug("openC: ", data.openC);
            for (const auto& var_pair : data.vars) {
                std::cout << "\t" << var_pair.first << ": " << var_pair.second << std::endl;
            }
            debug("value: ", data.value);
        }
    }
}