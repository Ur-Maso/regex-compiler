namespace args {
    struct list {
        bool cpph = false;
        bool is_stdRegex = true;
        std::string namespace_name;
        std::string regex
    };
    list parse(int argc, const char** argv) {
        char c;
        std::cstring<20> flag = "p";
        for (unsigned pos = 0; pos < argc - 1; pos++) {
            std::string param;
            for (unsigned i = 0; (c = argv[pos][i]) != '\0'; i++) {
                if (c == '-') {
                    // flag
                    if (!param.empty())

                    flag = c;
                } else {
                    // argument
                    param += c;
                }
            }

        }
    }
}