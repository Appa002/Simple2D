//
// Created by albert on 1/3/18.
//

#ifndef SIMPLE2DENGINE_SINGLETON_H
#define SIMPLE2DENGINE_SINGLETON_H

namespace Simple2D{
    template<class T> class Singleton{
    private:
        static T* instance;
    public:
        static T* get(){
            if(!instance){
                instance = new T;
            }
            return instance;
        }

        static void del(){
            if(instance){
                delete instance;
            }
        }

    };

    template <typename T> T* Simple2D::Singleton<T>::instance = 0;
}

#endif //SIMPLE2DENGINE_SINGLETON_H
