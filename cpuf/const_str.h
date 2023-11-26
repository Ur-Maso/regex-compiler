namespace std {

template<typename chartype>
struct __const_str {
    const_str(const chartype *&name) : n(const_cast<chartype*>(name)) {}
    const_str(chartype *&name) : n(name) {}
    template <int size>
    const_str(const chartype (*&name)[size]) : n(&name[0]) {}
    template <int size>
    const_str(chartype (*&name)[size]) : n(&name[0]) {}

    void operator=(const chartype *&name) {
        n = const_cast<chartype *>(name);
    }
    void operator=(chartype *&name) {
        n = name;
    }
    template <int size>
    void operator=(const chartype (*&name)[size]) {
        n = &name[0];
    }
    template <int size>
    void operator=(chartype (*&name)[size]) {
        n = &name[0];
    }

    bool operator==(const chartype *&name) {
        return std::strcmp(s, name) == 0;
    }
    bool operator==(chartype *&name) {
        return std::strcmp(s, name) == 0;
    }
    template <int size>
    bool operator==(const chartype (*&name)[size]) {
        return std::strcmp(s, &name[0]) != 0;
    }
    template <int size>
    bool operator==(chartype (*&name)[size]) {
        return std::strcmp(s, &name[0]) != 0;
    }

    bool operator!=(const chartype *&name) {
        return std::strcmp(s, name) != 0;
    }
    bool operator!=(chartype *&name) {
        return std::strcmp(s, name) != 0;
    }
    template <int size>
    bool operator!=(const chartype (*&name)[size]) {
        return std::strcmp(s, &name[0]) != 0;
    }
    template <int size>
    bool operator!=(chartype (*&name)[size]) {
        return std::strcmp(s, &name[0]) != 0;
    }
    bool operator>=(const chartype *&str) {
        return std::strcmp(s, str) == 0 || std::strlen(s) > std::strlen(str);
    }
    bool operator>=(chartype *&str) {
        return std::strcmp(s, str) == 0 || std::strlen(s) > std::strlen(str);
    }
    template <int size>
    bool operator>=(const chartype (*&str)[size]) {
        return std::strcmp(s, str) == 0 || std::strlen(s) > std::strlen(str);
    }
    template <int size>
    bool operator>=(const chartype (*&str)[size]) {
        return std::strcmp(s, str) == 0 || std::strlen(s) > std::strlen(str);
    }
    bool operator<=(const chartype *&str) {
        return std::strcmp(s, str) == 0 || std::strlen(s) < std::strlen(str);
    }
    bool operator<=(chartype *&str) {
        return std::strcmp(s, str) == 0 || std::strlen(s) < std::strlen(str);
    }
    template <int size>
    bool operator<=(const chartype (*&str)[size]) {
        return std::strcmp(s, str) == 0 || std::strlen(s) < std::strlen(str);
    }
    template <int size>
    bool operator<=(const chartype (*&str)[size]) {
        return std::strcmp(s, str) == 0 || std::strlen(s) < std::strlen(str);
    }
    operator char* () {
        return s;
    }
    operator const char*() {
        return s;
    }
  private:
    char* s;
};
using const_str = __const_str<char>;
using const_wstr = __const_str<wchar_t>;
using const_strU16 = __const_str<char16_t>;
using const_strU32 = __const_str<char32_t>;

}