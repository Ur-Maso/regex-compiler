#pragma once

#ifndef CPUF_CONST_STR
#define CPUF_CONST_STR

namespace std {

template<typename chartype>
struct __const_str {
    __const_str(const chartype *s) : n(const_cast<chartype*>(s)) {}
    __const_str(const __const_str<chartype>& s) : n(const_cast<chartype*>(s)) {}
    /*
        Does not handle strings that are not \0-terminated;
        if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126).
    */
    void operator=(const chartype *s) {
        n = const_cast<chartype *>(s);
    }
    void operator=(const __const_str<chartype> s) {
        n = const_cast<chartype *>(&s);
    }
    bool operator==(const chartype *s) {
        return std::strcmp(n, s) == 0;
    }
    bool operator==(const __const_str<chartype> s) {
        return std::strcmp(n, &s) == 0;
    }
    bool operator!=(const chartype *s) {
        return std::strcmp(n, s) != 0;
    }
    bool operator!=(const __const_str<chartype> s) {
        return std::strcmp(n, &s) != 0;
    }
    bool operator>(const chartype *s) {
        return std::strlen(n) > std::strlen(s);
    }
    bool operator>(const __const_str<chartype> s) {
        return std::strlen(n) > std::strlen(&s);
    }
    bool operator<(const chartype *s) {
        return std::strlen(n) < std::strlen(s);
    }
    bool operator<(const __const_str<chartype> s) {
        return std::strlen(n) < std::strlen(&s);
    }
    bool operator>=(const chartype *s) {
        return std::strlen(n) > std::strlen(s) || std::strcmp(n, s) == 0;
    }
    bool operator>=(const __const_str<chartype> s) {
        return std::strlen(n) > std::strlen(&s) || std::strcmp(n, &s) == 0;
    }
    bool operator<=(const chartype *s) {
        return std::strlen(n) < std::strlen(s) || std::strcmp(n, s) == 0;
    }
    bool operator<=(const __const_str<chartype> s) {
        return std::strlen(n) < std::strlen(&s) || std::strcmp(n, &s) == 0;
    }

#ifdef CPUF_C_STRING
    // some additional operators for std::cstring

    template<unsigned S>
    void operator=(const std::__cstring<chartype, S> s) {
        n = const_cast<chartype *>(&s);
    }
    template<unsigned S>
    bool operator==(const std::__cstring<chartype, S> s) {
        return std::strcmp(n, &s) == 0;
    }
    template<unsigned S>
    bool operator!=(const std::__cstring<chartype, S> s) {
        return std::strcmp(n, &s) != 0;
    }
    template<unsigned S>
    bool operator>(const std::__cstring<chartype, S> s) {
        return std::strlen(n) > std::strlen(&s);
    }
    template<unsigned S>
    bool operator<(const std::__cstring<chartype, S> s) {
        return std::strlen(n) < std::strlen(&s);
    }
    template<unsigned S>
    bool operator>=(const std::__cstring<chartype, S> s) {
        return std::strlen(n) > std::strlen(&s) || std::strcmp(n, &s) == 0;
    }
    template<unsigned S>
    bool operator<=(const std::__cstring<chartype, S> s) {
        return std::strlen(n) < std::strlen(&s) || std::strcmp(n, &s) == 0;
    }
#endif
    template <typename Stream>
    Stream& operator>>(Stream& stream) {
        stream >> n;
        return stream;
    }
    template <typename Stream>
    Stream& operator<<(Stream& stream) {
        stream << n;
        return stream;
    }
    operator char*() { return n ; }

    /*  strchr
        Find certain character in the string and return pointer onto it. null pointer if not found
    */
    inline const chartype *find(const unsigned &character) const
    {
        return std::strchr(n, character);
    }
    /*  strstr
        Find string and return pointer onto it. null pointer if not found
    */
    inline const chartype *find(const chartype *string) const {
        return std::strstr(n, string);
    }
#ifdef CPUF_C_STRING
    template <unsigned S>
    inline const chartype *find(const std::__cstring<chartype, S> &string) const {
        return std::strstr(n, &string);
    }
#endif
    inline const chartype *find(const __const_str<chartype> &string) const {
        return std::strstr(n, &string);
    }
    size_t size() {
        return std::strlen(n);
    }
  private:
    char* n;
};
using const_str = __const_str<char>;
using const_wstr = __const_str<wchar_t>;
using const_strU16 = __const_str<char16_t>;
using const_strU32 = __const_str<char32_t>;

} // namespace std

#endif // CPUF_C_STR