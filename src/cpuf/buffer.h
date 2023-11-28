#include <cstring>
namespace std {
template<unsigned SZ>
struct buffer {
    // Keep in mind the constructor assumes the input cannot cause overflow
    buffer(const char* s) {
        std::strcpy(b, s);
    }
    void operator+=(const char* s) {
        size_t sz = std::strlen(s);
        if (sz == SZ) clear();
        else if (sz > SZ) 
            std::strcpy(b, s + SZ * (sz / SZ));
            sz = std::strlen(b);
        else 
            std::strcat(b, s);
    }
    char operator[](const unsigned short& id) {
        return b[id];
    }
    // Entirely clear the buffer
    void clear() {
        std::memset(b, '\0', sz);
    }
    // Forget (remove) first characters from the buffer
    void forget(unsigned short& amount) {
        if (amount >= sz)
            clear();
            return;
        memcpy(b, b + amount, sz - amount);
    }
    
    unsigned sz = 0;
    private:
    char b[SZ] = "";
};
} // std