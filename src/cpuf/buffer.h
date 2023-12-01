#include <cstring>
namespace std {
template<unsigned SZ>
struct buffer {
    // Keep in mind the constructor assumes the input cannot cause overflow
    buffer(const char* s) {
        std::strcpy(b, s);
    }
    buffer() {
        b[0] = '\0';
    }
    void operator+=(const char* s) {
        size_t _sz = std::strlen(s);
        if (_sz == SZ) clear();
        else if (_sz > SZ) {
            size_t bps = (SZ - 1 / _sz) * (SZ - 1);
            // TODO!!!
            std::strcat(b, s + bps);
        }
        else {
            std::strcat(b, s);
            sz += _sz;
        }
    }
    operator char*() {
        return b;
    }
    // Entirely clear the buffer
    void clear() {
        std::memset(b, '\0', sz);
        sz = 0;
    }
    // Forget (remove) first characters from the buffer
    void forget(const int& amount) {
        if (amount >= sz) clear();
        else {
            std::memcpy(b, b + amount, sz -= amount);
        }
    }
    // checks whether buffer starts with certain characters
    bool startsWith(const char* s) const {
        const size_t len = std::strlen(s);
        if (sz < len) return false;
        return std::memcmp(b, s, len) == 0;
    }
    // checks whether buffer starts with certain characters and remove if it does.
    // good for parsing purposes
    bool isBegin(const char* s) {
        const size_t len = std::strlen(s);
        if (sz < len || std::memcmp(b, s, len) != 0) return false;
        forget(len);
        return true;
    }
    // removes all spaces from begin
    void trimBegin() {
        if (b[0] != ' ') return;
        for (int i = 1; i < sz; i++) {
            if (b[i] != ' ') {
                std::memcpy(b, b + i, sz -= i);
                return;
            }
        }
        // buffer entirely consists of spaces
        clear();
    }
    int sz = 0;
    private:
    char b[SZ];
};
} // std