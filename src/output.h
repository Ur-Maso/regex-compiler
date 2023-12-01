inline const char* stringify(const char* arg) {
    return arg;
}
inline std::string stringify(const std::string& arg) {
    return arg;
}
template<typename T>
inline std::string stringify(T arg) {
    if constexpr (std::is_same_v<T, char>) {
        return string(1, arg);
    } else return std::to_string(arg);
}


template <typename... Args>
[[noreturn]] void err(const Args&... args) {
    std::string mes;
    ((mes += stringify(args)), ...);
    std::cout << "\033[1;31m" << "Error: " << mes << "\033[0m" << std::endl;
    exit(2);
}


[[ noreturn ]] void ferr(const char* mes, const char*& line, const int& errpos) {
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
[[noreturn]] void ferr(const char* mes, const char**& argv, const int& argc, const int& errpos) {
    std::cout << "\033[1;31m"
              << "Error: " << mes << "\033[0m" << '\n';
    for (int i = 1; i < argc; i++) {
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
template <typename... Args>
void warning(const Args&... args) {
    std::string mes;
    ((mes += stringify(args)), ...);
    std::cout << "\033[1;33m" << "Warning: " << mes << "\033[0m" << std::endl;
}
template <typename... Args>
void log(const Args&... args) {
    std::string mes;
    ((mes += stringify(args)), ...);
    std::cout << mes << std::endl;
}
template <typename... Args>
void debug(const Args&... args) {
#ifdef DEBUG
    std::string mes;
    ((mes += stringify(args)), ...);
    std::cout << mes << std::endl;
#endif
}