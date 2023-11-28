namespace args {
    using args_t = map<string, vector<string>>;
    struct analyse_config_t {
        string name;
        unsigned minimum_args = 0;
        unsigned maximum_args = 0;
        vector<string> fixed_args {};
        vector<string> def;
    };
    vector<analyse_config_t> analyse_config {
        {
            .name = "path",
            .minimum_args = 1,
        },
        {
            .name = "util",
            .minimum_args = 1,
            .maximum_args = 1,
            .def { "std::regex" },
        },
        {
            // argument to specify namespace
            .name = "nms",
            .minimum_args = 1,
            .maximum_args = 1,
        }
    };

    args_t parse(const int& argc, const char**& argv) {
        using std::cout, std::endl;
        char c;
        args_t result {
            { "path", {} }
        };
        string flagname = "path";
        for (int pos = 1, offset = 0; pos < argc; pos++) {
            string param;
            bool is_flag = false;
            int i;
            for (i = 0; (c = argv[pos][i]) != '\0'; i++) {
                if (c == '-' && i == 0) {
                    // flag
                    is_flag = true;
                    flagname = "";
                    param = "";
                } else {
                    if (is_flag) {
                        if (!isalpha(c)) ferr("Flag must contain only alphabetic characters", argv, argc, offset + i);
                        else flagname += c;
                    } else {
                        // allow namespace character (::) for util parameter
                        if (!isalnum(c) && c != '_' && !(flagname == "util" && c == ':'))
                            ferr("Parameter must contain only alphanumeric and '_' characters", argv, argc, offset + i);
                        else param += c;
                    }
                }
            }
            offset += i + 1 /* 1 for space */;
            if (flagname == "") ferr("Empty flag", argv, argc, offset);
            if (is_flag) {
                // init the container of argument
                result[flagname] = {};
            } else {
                result[flagname].push_back(param);
            }
        }
        return result;
    }
    // a tool to check arguments
    void analyser(args_t& args) {
        for (const auto& e : args) { // for 1
            const auto& name = e.first;
            const auto& el_args = e.second;
            bool wasConfig = false;
            for (const auto& config : analyse_config) { // for 2
                if (config.name == name) { // if 1
                    wasConfig = true;
                    if (el_args.size() < config.minimum_args) { // if 2
                        err((
                            config.name + " expected at least " + std::to_string(config.minimum_args) + " arguments."
                            ).c_str()
                        );
                    } else if (config.maximum_args > 0 && el_args.size() > config.maximum_args) {
                        string m = config.name + " has got too much arguments. ";
                        if (config.minimum_args == config.maximum_args) {
                            m += "Expected ";
                            m += std::to_string(config.maximum_args);
                        } else {
                            m += std::to_string(config.minimum_args);
                            m += " to ";
                            m += std::to_string(config.maximum_args);
                        }
                        err(m.c_str());
                    } else if (config.fixed_args.size() > 0) {
                        // has fixed arguments
                        for (size_t i = 0; i < args.size(); i++) {
                            const auto el = el_args[i];
                            bool valid = false;
                            for (size_t j = 0; j < config.fixed_args.size(); j++) {
                                if (el == config.fixed_args[j]) {
                                    valid = true;
                                }
                            }
                            if (!valid) {
                                string m = "The argument '";
                                m += el;
                                m += "' is invalid.";
                                err(m.c_str());
                            }
                        }
                    } // if 2
                } // if 1
            } // for 2
            if (!wasConfig) {
                string m = "Flag '";
                m += name;
                m += "' does not exist.";
                err(m.c_str());
            }
        } // for 1
        for (const auto& config : analyse_config) {
            if (config.def.size() > 0 && args.count(config.name) == 0) {
                args[config.name] = config.def;
            }
        }
        // exit
    }
}