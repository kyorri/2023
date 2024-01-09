#include "UniquePointer.h"

#include <iostream>

namespace up {

    template<typename T>
    UniquePointer<T>::UniquePointer() : ptr_(nullptr) {};

    template<typename T>
    UniquePointer<T>::UniquePointer(T* ptr) {
        this->acquire(ptr);
    };

    template<typename T>
    UniquePointer<T>::~UniquePointer() {
        this->release();
    };

    template<typename T>
    UniquePointer<T>::UniquePointer(UniquePointer&& other) {
        
    };

    template<typename T>
    UniquePointer<T>& UniquePointer<T>::operator=(UniquePointer<T>&& other) {

    };

    template<typename T>
    T* UniquePointer<T>::Get() {
        return ptr_;
    };

    template<typename T>
    T* UniquePointer<T>::Acquire(T* ptr) {
        if (ptr_ != nullptr) {
            std::cerr << "This pointer is already acquired." << std::endl;
        }
        else {
            ptr_ = ptr;
        }
    };

    template<typename T>
    void UniquePointer<T>::Release() {
        delete ptr_;
        ptr_ = nullptr;
    };

    template<typename T>
    T& UniquePointer<T>::operator*() {
        return *ptr_;
    };
    
    template<typename T>
    T& UniquePointer<T>::operator[](size_t i) {
        return *(ptr_ + (i * sizeof(T)));
    };

    template<typename T>
    T* UniquePointer<T>::operator->() {
        return ptr_;
    };

} // namespace UniquePointer
