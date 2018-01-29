//
// Created by albert on 1/3/18.
//


#ifndef SIMPLE2DENGINE_EXTERNALCODELOADINGWRAPPER_H
#define SIMPLE2DENGINE_EXTERNALCODELOADINGWRAPPER_H


#ifdef WIN32
    #include <Windows.h>
#else
    #include <dlfcn.h>
#endif

#include <string>

namespace Simple2D::ExternalCode{

    class Handle{
    public:

        Handle() = default;
        ~Handle() = default;

#ifdef WIN32
        HINSTANCE handle;
#else
        void* handle;
#endif

#ifdef WIN32
    HINSTANCE get(){
        return handle;
    };
#else
    void* get(){
        return handle;
    };
#endif
    };

    inline Handle open (std::string&& path){
#ifdef WIN32
        Handle h;
        h.handle = LoadLibrary(path.c_str());
#else
        Handle h;
        h.handle = dlopen(path.c_str(), RTLD_NOW | RTLD_GLOBAL);
#endif
        return h;
    }

    inline Handle open (std::string& path){
#ifdef WIN32
        Handle h;
        h.handle = LoadLibrary(path.c_str());
#else
        Handle h;
        h.handle = dlopen(path.c_str(), RTLD_NOW | RTLD_GLOBAL);
#endif
        return h;
    }

    inline void* find(Handle handle, std::string&& name){
#ifdef WIN32
        return GetProcAdress(handle.handle, name.c_str());
#else
        return dlsym(handle.handle, name.c_str());
#endif
    }

    inline void* find(Handle handle, std::string& name){
#ifdef WIN32
        return GetProcAdress(handle.handle, name.c_str());
#else
        return dlsym(handle.handle, name.c_str());
#endif
    }

    inline int close(Handle handle){
#ifdef WIN32
        return FreeLibrary(handle.handle);
#else
        return dlclose(handle.handle);
#endif

    }


}

#endif //SIMPLE2DENGINE_EXTERNALCODELOADINGWRAPPER_H
