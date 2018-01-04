//
// Created by albert on 1/3/18.
//

#ifndef SIMPLE2DENGINE_SINGLETON_H
#define SIMPLE2DENGINE_SINGLETON_H

namespace Simple2D{
    template<class T> class Singleton{
    private:
        T* instance = 0;
    public:
        T* get(){
            if(!instance){
                instance = new T;
            }
            return instance;
        }

        void del(){
            if(instance){
                delete instance;
            }
        }

    };
}

#endif //SIMPLE2DENGINE_SINGLETON_H
