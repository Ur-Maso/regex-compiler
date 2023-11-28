#include <stdexcept>
#include <string>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <dlfcn.h>
#endif
namespace std {
    class dlib_err : public std::exception {
    public:
        enum class Kind {
            loadlib, loadfun, load
        };
        dlib_err(const char*& e, Kind k) {
            kind = k;
            m += e;
        }

        dlib_err(const std::string& e, Kind k) {
            kind = k;
            m += e;
        }

        virtual const char* what() const noexcept override {
            return m.c_str();
        }
        Kind kind;
    private:
        std::string m = "Dll load error: ";
    };
}

class dlib {
    public:
    dlib(const std::string& path) {
        loadlib(path);
    }
    dlib() {
        handler = nullptr;
    }
    ~dlib() {
        if (handler != nullptr) {
#ifdef _WIN32
            FreeLibrary(handler);
#else
            dlclose(handler);
#endif
       }
    }
    /*
        Free the dynamic library. 
        It doesn't check if the library is loaded.
    */
    void free() {
#ifdef _WIN32
        FreeLibrary(handler);
#else
        dlclose(handler);
#endif
        handler = nullptr;
    }
    void loadlib(std::string path) {
#ifdef _WIN32
        path += ".dll";
        handler = LoadLibraryA(path.c_str());
#else
        path += ".so";
        handler = dlopen(path.c_str(), RTLD_NOW | RTLD_GLOBAL);
#endif
        if (handler == nullptr) {
            path.insert(0, "cannot open '");
            path += '\'';
            throw std::dlib_err(path, std::dlib_err::Kind::loadlib);
        }
    }
    // Load the function. The first template parameter is return type and other are parameter types. If no template specified function considered void in return and without parameters
    template<typename ReturnT = void, typename... Params>
    ReturnT(*loadfun(std::string name))(Params...) {
        auto p = reinterpret_cast<ReturnT(*)(Params...)>(
#ifdef _WIN32
            GetProcAddress
#else
            dlsym
#endif
                (handler, name.c_str())
        );
        if (p == nullptr) {
            name.insert(0, "cannot load function '");
            name += "'";
            throw std::dlib_err(name, std::dlib_err::Kind::loadfun);
        }
        return p;
    }
    // Load something from library with your own type
    template<typename T>
    T load(std::string name) {
        T p = reinterpret_cast<T>(
#ifdef _WIN32
            GetProcAddress
#else
            dlsym
#endif
                (handler, name.c_str())
        );
        if (p == nullptr) {
            name.insert(0, "cannot load '");
            name += "'";
            throw std::dlib_err(name, std::dlib_err::Kind::load);
        }
        return p;
    }
    bool isLoaded() {
        return handler != nullptr;
    }
    bool isfree() {
        return handler == nullptr;
    }
    private:
#ifdef _WIN32
        HMODULE handler;
#else
        void* handler;
#endif
};
