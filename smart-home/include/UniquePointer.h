#ifndef SH_UNIQUEPOINTER_INCLUDE_H_
#define SH_UNIQUEPOINTER_INCLUDE_H_

#include "Deleter.h"

#include <memory>

namespace up {

    template<typename T, typename D = Deleter<T>>
    class UniquePointer {
        public:
            UniquePointer() : ptr_(nullptr) {};
            UniquePointer(T* ptr) : ptr_(ptr) {};
            ~UniquePointer() {
                del_(ptr_);
            };

            UniquePointer(const UniquePointer&) = delete;
            UniquePointer& operator=(const UniquePointer&) = delete;

            UniquePointer(UniquePointer&& other) : ptr_(std::move(other.ptr_)), del_(std::move(other.del_)) {};

            UniquePointer& operator=(UniquePointer&& other) {
                if (this != &other) {
                    del_(ptr_);
                    ptr_ = std::move(other.ptr_);
                    del_ = std::move(other.del_);
                    other.ptr_ = nullptr;
                }
                return *this;
            };

            T* Get() {
                return ptr_;
            };

            D GetDeleter() {
                return del_;
            };

            T* Release() {
                T* temp = ptr_;
                ptr_ = nullptr;
                return temp;
            };

            void Reset(T* p = nullptr) {
                if (p != ptr_) {
                    del_(ptr_);
                    ptr_ = p;
                }
            }

            operator bool () {
                return (ptr_ != nullptr);
            };

            T& operator[](size_t i) {
                return *(ptr_ + i);
            };

            T& operator*() {
                return *ptr_;
            };

            T* operator->() {
                return ptr_;
            };
        private:
            T* ptr_ = nullptr;
            D del_;
    };
} // namespace up

#endif // SH_UNIQUEPOINTER_INCLUDE_H_