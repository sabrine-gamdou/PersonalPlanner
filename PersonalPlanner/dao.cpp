#include "dao.h"
#include <iostream>

template <typename T>
DAO<T>::~DAO() {
    std::cout << "DAO destructor" << std::endl;
}

template <typename T>
bool DAO<T>::create(T t) {
    std::cout << "DAO creator" << std::endl;
}

template <typename T>
T DAO<T>::read(){
    std::cout << "DAO read" << std::endl;
}

template <typename T>
bool DAO<T>::update(T t){
    std::cout << "DAO update" << std::endl;
}

template <typename T>
bool DAO<T>::delete_(T t){
    std::cout << "DAO delete_" << std::endl;
}
