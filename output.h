[[noreturn]] void err(const char* mes) {
    std::cout << "\033[1;31m" << "Error: " << mes << "\033[0m" << std::endl;
}
[[noreturn]] void ferr(const char* mes, const char*& line, const int& errpos) {
    std::cout << "\033[1;31m"
              << "Error: " << mes << "\033[0m" << '\n'
              << line << '\n';
    for (int i = 0; i < errpos; i++) {
        std::cout << ' ';
    }
    std::cout << '^' << std::endl;
    exit(2);
}
// specifically for argv
[[noreturn]] void ferr(const char* mes, const char**& argv, int argc, const int& errpos) {
    std::cout << "\033[1;31m"
              << "Error: " << mes << "\033[0m" << '\n';
    argc--;
    for (int i = 0; i < argc; i++) {
        std::cout << argv[i] << ' ';
    }
    std::cout << '\n';
    for (int i = 0; i < errpos; i++) {
        std::cout << ' ';
    }
    std::cout << '^' << std::endl;
    exit(2);
}
[[noreturn]] void ferr(const char*& mes, const char*& line, const int& bpos, const int& epos) {
    std::cout << "\033[1;31m"
              << "Error: " << mes << "\033[0m" << '\n'
              << line << '\n';
    for (int i = 0; i < bpos; i++) {
        std::cout << ' ';
    }
    for (int j = 0; j <= epos; j++) {
        std::cout << '^';
    }
    std::cout << std::endl;
    exit(2);
}
template <typename T, typename ...Args>
void debug(const T arg, Args... args) {
#ifdef DEBUG
    debug(arg);
    debug(...args);
#endif
};
void debug(const bool arg) {
#ifdef DEBUG
    std::cout << "\033[1;33m" << arg << "\033[0m" << std::endl;
#endif
}
void debug(const int arg) {
#ifdef DEBUG
    std::cout << "\033[1;31m" << arg << "\033[0m" << std::endl;
#endif
}
void debug(const std::string arg) {
#ifdef DEBUG
    std::cout << arg << std::endl;
#endif
}
template <typename T, typename ...Args>
void out(const T arg, Args... args) {
    debug(arg);
    debug(...args);
};
void out(const bool arg) {
    std::cout << "\033[1;33m" << arg << "\033[0m" << std::endl;
}
void out(const int arg) {
    std::cout << "\033[1;31m" << arg << "\033[0m" << std::endl;
}
void out(const std::string arg) {
    std::cout << arg << std::endl;
}