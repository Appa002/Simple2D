//
// Created by albert on 2/9/18.
//

#ifndef SIMPLE2D_BEHAVIOR_H
#define SIMPLE2D_BEHAVIOR_H

#include <SDL2/SDL.h>
#include "types.h"

namespace Simple2D {

    struct Attribute{
        void* content;
        std::string name;
        size_t typeHash;
        Attribute() : content(nullptr), typeHash(0), name(""){}
        template <class T> Attribute* set(std::string& name ,T* content) {
            this->name = name;
            this->content = content;
            this->typeHash = typeid(T).hash_code();
            return this;
        }
    };

    class Behavior {
    private:
        std::vector<Attribute*> attributes;
    protected:
        template <class T> int addAttribute(std::string& name, T* content){
            for(auto attr : attributes){
                if(attr->name == name)
                    return -1;
            }
            attributes.push_back((new Attribute())->set<T>(name, content));
            return 0;
        }
        template <class T> int addAttribute(std::string&& name, T* content){
            for(auto attr : attributes){
                if(attr->name == name)
                    return -1;
            }
            attributes.push_back((new Attribute())->set<T>(name, content));
            return 0;
        }


    public:
        size_t amountOfAttributes(){return attributes.size();}

        template <class T> int deleteAttribute(std::string& name){
            for(auto attrib : attributes){
                if(attrib->name == name){
                    if(attrib->typeHash != typeid(T).hash_code())
                        throw std::runtime_error("Deleting attribute \"" + name + "\" with incorrect type\"" + std::string(typeid(T).name()) + "\"");

                    delete reinterpret_cast<T*>(attrib->content);
                    return 0;
                }
            }
            return -1;
        }
        template <class T> int deleteAttribute(std::string&& name){
            size_t i = 0;
            for(auto attrib : attributes){
                if(attrib->name == name){
                    if(attrib->typeHash != typeid(T).hash_code())
                        throw std::runtime_error("Deleting attribute \"" + name + "\" with incorrect type\"" + std::string(typeid(T).name()) + "\"");

                    attributes.erase(attributes.begin() + i);
                    delete reinterpret_cast<T*>(attrib->content);
                    return 0;
                }
                i++;
            }
            return -1;
        }

        template <class T> T getAttribute(std::string& name){
            for(auto attr : attributes){
                if(attr->name == name){
                    if(attr->typeHash == typeid(T).hash_code())
                        throw std::runtime_error("Querying for attribute \"" + name + "\" with incorrect type << \"" + std::string(typeid(T).name()) + "\"");
                    return *reinterpret_cast<T*>(attr->content);
                }
            }
        }
        template <class T> T getAttribute(std::string&& name){
            for(auto attr : attributes){
                if(attr->name == name){
                    if(attr->typeHash != typeid(T).hash_code())
                        throw std::runtime_error("Querying for attribute \"" + name + "\" with incorrect type\"" + std::string(typeid(T).name()) + "\"");
                    return *reinterpret_cast<T*>(attr->content);
                }
            }
        }

        template <class T> int setAttribute(std::string& name, T value){
            for(auto attr : attributes){
                if(attr->name == name){
                    *(reinterpret_cast<T*>(attr->content)) = value;
                    return 0;
                }
            }
            return -1;
        }
        template <class T> int setAttribute(std::string&& name, T value){
            for(auto attr : attributes){
                if(attr->name == name){
                    *(reinterpret_cast<T*>(attr->content)) = value;
                    return 0;
                }
            }
            return -1;
        }

        bool existAttribute(std::string& name){
            for(auto attr : attributes){
                if(attr->name == name)
                    return true;
            }
            return false;
        }
        bool existAttribute(std::string&& name){
            for(auto attr : attributes){
                if(attr->name == name)
                    return true;
            }
            return false;
        }

        virtual void init() = 0;
        virtual void update() = 0;
        virtual void setup() = 0;
        virtual void onRemoval() {};
        virtual void onEvent(SDL_Event& e) {};
        virtual void fixedUpdate(){};
    };
}

#endif //SIMPLE2D_BEHAVIOR_H
