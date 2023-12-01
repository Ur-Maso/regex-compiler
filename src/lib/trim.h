std::string trim(const std::string& str) {
    std::string s;
    for (std::size_t i = 0, size = str.size(); i < size; i++) {
        int c = str[i];
        if (c != ' ') s += c;
    }
    return s;
}