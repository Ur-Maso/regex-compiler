#pragma once

#ifndef CPUF_C_STRING
#define CPUF_C_STRING

#include <cstring>
#include <cctype>

namespace std {

template <typename chartype, unsigned SIZE>
struct __cstring {
  private:
    chartype s[SIZE];
#ifdef CPUF_C_STRING_DEBUG
#include <stdexcept>
    const char* errs[6] = {
        "constructor",
        "=",
        "+=",
        "access by operator []", /* 21 */
        "copy_n",
        "cut (start pos)"
    };
    [[noreturn]] void error(const unsigned char &n) {
        char mes[35 + 21 + 1 /* \0 */] = "cstring overflow error. At operation: "; /* 35 */
        std::strcat(mes, errs[n]);
        throw std::overflow_error(mes);
    }
    void _set(chartype *&newstr, unsigned char& op_n) {
        if (std::strlen(newstr) >= SIZE) error(op_n);
        std::strcpy(s, newstr);
    }
#else
    void _set(chartype *&newstr) {
        std::strcpy(s, newstr);
    }
#endif

  public:
    __cstring() {
       s[0] = '\0';
    }
    template <unsigned S>
    __cstring(const chartype (&string)[S])
    {  
#ifndef CPUF_C_STRING_DEBUG
       _set(&string[0]);
#else
       _set(&string[0], 0);
#endif
    }
    template <unsigned S>
    __cstring(const __cstring<chartype, S> &string)
    {
#ifndef CPUF_C_STRING_DEBUG
       _set(&string);
#else
       _set(&string, 0);
#endif
    }
    __cstring(const chartype *&string)
    {
#ifndef CPUF_C_STRING_DEBUG
       _set(string);
#else
       _set(string, 0);
#endif
    }
    __cstring(const chartype &character)
    {
        s[0] = character;
        s[1] = '\0';
    }
    __cstring(chartype &character)
    {
        s[0] = character;
        s[1] = '\0';
    }
    template <unsigned S>
    auto &operator=(const chartype (&string)[S])
    {
#ifndef CPUF_C_STRING_DEBUG
       _set(&string[0]);
#else
       _set(&string[0], 1);
#endif
        return *this;
    }
    template <unsigned S>
    auto &operator=(const __cstring<chartype, S> &string)
    {
#ifndef CPUF_C_STRING_DEBUG
       _set(&string);
#else
       _set(&string, 1);
#endif
        return *this;
    }
    auto &operator=(const chartype *&string)
    {
#ifndef CPUF_C_STRING_DEBUG
       _set(string);
#else
       _set(string, 1);
#endif
        return *this;
    }
    auto &operator=(const chartype &character)
    {
        s[0] = character;
        s[1] = '\0';
        return *this;
    }
    template <unsigned S>
    auto &operator+=(const chartype (&string)[S])
    {
#ifdef CPUF_C_STRING_DEBUG
        if (S + std::strlen(s) >= SIZE) error(2);
#endif
        std::strcat(s, string);
        return *this;
    }
    template <unsigned S>
    auto &operator+=(const __cstring<chartype, S> &string)
    {
#ifdef CPUF_C_STRING_DEBUG
        if (string.size() + std::strlen(s) >= SIZE)
            error(2);
#endif
        std::strcat(s, &string);
        return *this;
    }
    auto &operator+=(const chartype *&string)
    {
#ifdef CPUF_C_STRING_DEBUG
        if (std::strlen(s) + std::strlen(string) >= SIZE)
            error(2);
#endif
        std::strcat(s, string);
        return *this;
    }
    auto &operator+=(const chartype &c)
    {
        auto add_id = std::strlen(s);
        if (add_id != 0) add_id++;
#ifdef CPUF_C_STRING_DEBUG
        if (add_id >= SIZE) error(2);
#endif
        s[add_id] = c;
        s[add_id + 1] = '\0';
        return *this;
    }
    template <unsigned S>
    bool operator==(const chartype (&string)[S]) const
    {
        return std::strcmp(s, string) == 0;
    }
    template <unsigned S>
    bool operator==(const __cstring<chartype, S> &string) const
    {
        return std::strcmp(s, &string) == 0;
    }
    bool operator==(const chartype *&string) const
    {
        return std::strcmp(s, string) == 0;
    }
    bool operator==(const chartype &c) const
    {
        return s[0] == c && s[1] == '\0';
    }
    bool operator==(const size_t &size) const
    {
        return std::strlen(s) == size;
    }
    template <unsigned S>
    bool operator!=(const chartype (&string)[S]) const
    {
        return std::strcmp(s, string) != 0;
    }
    template <unsigned S>
    bool operator!=(const __cstring<chartype, S> &string) const
    {
        return std::strcmp(s, &string) != 0;
    }
    bool operator!=(const chartype *&string) const
    {
        return std::strcmp(s, string) != 0;
    }
    bool operator!=(const chartype &c) const
    {
        return !(s[0] == c && s[1] == '\0');
    }
    bool operator!=(const size_t &size) const
    {
        return std::strlen(s) != size;
    }
    template <unsigned S>
    inline bool operator>(const chartype (&string)[S]) const
    {
        return std::strlen(s) > std::strlen(string);
    }
    template <unsigned S>
    inline bool operator>(const __cstring<chartype, S> &string) const
    {
        return std::strlen(s) > string.size();
    }
    inline bool operator>(const chartype *&string) const
    {
        return std::strlen(s) > std::strlen(string);
    }
    inline bool operator>(const chartype &c) const
    {
        return s[1] != '\0';
    }
    inline bool operator>(const unsigned &size) const
    {
        return std::strlen(s) > size;
    }
    template <unsigned S>
    inline bool operator<(const chartype (&string)[S]) const
    {
        return std::strlen(s) < std::strlen(string);
    }
    template <unsigned S>
    inline bool operator<(const __cstring<chartype, S> &string) const
    {
        return std::strlen(s) < string.size();
    }
    inline bool operator<(const chartype *&string) const
    {
        return std::strlen(s) < std::strlen(string);
    }
    inline bool operator<(const chartype &c) const
    {
        return s[0] == '\0';
    }
    template <unsigned S>
    inline bool operator>=(const chartype (&string)[S]) const
    {
        return std::strlen(s) > std::strlen(string) ||
               std::strcmp(s, string) == 0;
    }
    template <unsigned S>
    inline bool operator>=(const __cstring<chartype, S> &string) const
    {
        return std::strlen(s) > string.size() ||
               std::strcmp(s, &string) == 0;
    }
    inline bool operator>=(const chartype *&string) const
    {
        return std::strlen(s) > std::strlen(string) ||
               std::strcmp(s, string) == 0;
    }
    inline bool operator>=(const chartype &c) const
    {
        return s[1] != '\0' || s[0] == c;
    }
    inline bool operator>=(const unsigned &size) const
    {
        return std::strlen(s) >= size;
    }
    template <unsigned S>
    inline bool operator<=(const chartype (&string)[S]) const
    {
        return std::strlen(s) < std::strlen(string) ||
               std::strcmp(s, string) == 0;
    }
    template <unsigned S>
    inline bool operator<=(const __cstring<chartype, S> &string) const
    {
        return std::strlen(s) < string.size() ||
               std::strcmp(s, &string) == 0;
    }
    inline bool operator<=(const chartype *&string) const
    {
        return std::strlen(s) < std::strlen(string) ||
               std::strcmp(s, string) == 0;
    }
    inline bool operator<=(const chartype &c) const
    {
        return s[0] == '\0' || s[0] == c;
    }
    template <typename T>
    inline T &operator<<(T &stream)
    {
        stream << s;
        return stream;
    }
#ifdef _GLIBCXX_ISTREAM
    std::istream& operator>>(std::istream& stream) {
        unsigned i = 0;
        while (
            std::cin.get(s[i])
                &&
            !isspace(s[i])
                &&
            i < SIZE - 1
        ) i++;
        s[i] = '\0';
        return stream;
    }
#endif
    template <typename T>
    inline T &operator>>(T &stream)
    {
        stream >> s;
        return stream;
    }
    inline chartype operator[](const unsigned id) {
        #ifdef CPUF_C_STRING_DEBUG 
            if (id > SIZE) error(3);
        #endif
        return s[id];
    }
    inline chartype *operator&() const
    {
        return const_cast<chartype*>(&s[0]);
    }
    inline chartype (&operator*())[SIZE]
    {
        return s;
    }
    /*
       strncpy implementation.
       Copies specified characters amount from input string to the current. Unlike native strncpy, it's a safer way. The null terminate character is put automatically.
       string - the string which characters must be copied
       n - the amount of characters to copy.
    */
    template <unsigned S>
    void copy_n(const chartype (&string)[S], unsigned &n) const
    {
#ifdef CPUF_C_STRING_DEBUG
        if (n >= SIZE) error(4); 
#endif
        std::strncpy(s, string, n);
        s[n + 1] = '\0';
    }
    template <unsigned S>
    void copy_n(const __cstring<chartype, S> &string, unsigned &n) const
    {
#ifdef CPUF_C_STRING_DEBUG
        if (n >= SIZE) error(4);
#endif
        std::strncpy(s, &string, n);
        s[n + 1] = '\0';
    }
    void copy_n(const chartype *&string, unsigned &n) const
    {
#ifdef CPUF_C_STRING_DEBUG
        if (n > SIZE || n > std::strlen(string) || n < 0) error(3);
#endif
        std::strncpy(s, string, n);
        s[n + 1] = '\0';
    }
    /* strchr
        Find certain character in the string and return pounsigneder onto it. null pounsigneder if not found
    */
    inline const chartype *find(const unsigned &character) const
    {
        return std::strchr(s, character);
    }
    /* strstr
        Find string and return pounsigneder onto it. null pounsigneder if not found
    */
    template <unsigned S>
    inline const chartype *find(const chartype (&string)[S]) const
    {
        return std::strstr(s, &string);
    }
    template <unsigned S>
    inline const chartype *find(const __cstring<chartype, S> &string) const
    {
        return std::strstr(s, &string);
    }
    inline const chartype *find(const chartype *&string) const
    {
        return std::strstr(s, string);
    }
    // Cut the string from begin
    inline auto& cut_begin(const unsigned &chars_amount)
    {
        strcpy(s, s + chars_amount);
        return *this;
    }
    // Cut the string from end
    auto& cut_end(const unsigned &chars_amount)
    {
        const unsigned size = std::strlen(s);
        for (unsigned i = size - chars_amount; i < size; ++i)
        {
            s[i] = '\0';
        }
        return *this;
    }
    /*
        Cut the string from start onto specified characters amount. The start position and the last characters are cutted too.
        "abcde" --> cut(1, 2) --> "ae"
        
        If the start equals last character position string remains unchanged
    */
    inline auto& cut(const unsigned& start, const unsigned& end)
    {
        return fcut(start, start + end);
    }
     /*
        Cut the string from start to end. The start position and the last characters are cutted too.
        "abcde" --> cut(1, 2) --> "ade"
        
        If the start equals last character position string remains unchanged
    */
    auto& fcut(const unsigned& start, const unsigned& end)
    {
        const unsigned size = std::strlen(s);
#ifdef CPUF_C_STRING_DEBUG
        if (start > size || start > end) error(5);
#endif
        if (end > size) strcpy(s + start, s + size + 1);
        else            strcpy(s + start, s + end + 1);
        return *this;
    }
    unsigned indexOf(const chartype &c) {
        chartype* r = std::strchr(s, c);
        if (r == NULL) {
           return -1;
        }
        return &s - r;
    }
    template<unsigned S>
    unsigned indexOf(const chartype (&string)[S]) {
        chartype* r = std::strstr(s, string);
        if (r == NULL) {
           return -1;
        }
        return &s - r;
    }
    template<unsigned S>
    unsigned indexOf(const __cstring<chartype, S>& string) {
        chartype* r = std::strstr(s, &string);
        if (r == NULL) {
           return -1;
        }
        return &s - r;
    }
    template<unsigned S>
    unsigned indexOf(const chartype*& string) {
        chartype* r = std::strstr(s, string);
        if (r == NULL) {
           return -1;
        }
        return &s - r;
    }
    inline auto size() const { 
        return std::strlen(s); 
    }
    constexpr auto fsize() const {
        return SIZE;
    }
};


 template<unsigned size>
 using cstring = __cstring<char, size>;
 template<unsigned size>
 using cwstring = __cstring<wchar_t, size>;

 template<unsigned size>
 using cstringU16 = __cstring<char16_t, size>;
 template<unsigned size>
 using cstringU32 = __cstring<char32_t, size>;
} // namespace std


#endif  // CPUF_C_STRING
