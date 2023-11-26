namespace args {
    map<string, string> parse(int argc, const char** argv) {
        char c;
        map<string, string> result {};

        string flagname = "path";
        for (unsigned pos = 0; pos < argc - 1; pos++) {
            string param;
            bool is_flag = false;
            int i = 0;
            for (; (c = argv[pos][i]) != '\0'; i++) {
                if (c == '-') {
                    if (i != 0)
                        ferr("Parameter cannot")
                    // flag
                    is_flag = true;
                    flagname.clear();
                    param.clear();
                } else {
                    if (is_flag)
                        if (!isalpha(c))
                            ferr("Flag must contain only alpha characters", argv, argc, i);
                    else
                        if (!isalnum(c))
                            ferr("Parameter must contain only alphanumeric characters", argv, argc, i);
                }
                // argument
                if (is_flag) flagname += c;
                else         param += c;
            }
            if (flagname == "") {
                ferr("Empty flag", argv, argc, i);
            }
        }
    }
}