#ifndef SHA_UNIQUEPOINTER_H_
#define SHA_UNIQUEPOINTER_H_

#include <memory>

namespace up {

    template<typename T>
    class UniquePointer {
        public:
            UniquePointer();
            UniquePointer(T*);
            ~UniquePointer();

            UniquePointer(const UniquePointer&) = delete;
            UniquePointer& operator=(const UniquePointer&) = delete;

            UniquePointer(UniquePointer&& other);
            UniquePointer& operator=(UniquePointer&& other);

            T* Get();
            T* Acquire(T*);
            void Release();
            
            T& operator[](size_t);
            T& operator*();
            T* operator->();
        private:
            T* ptr_ = nullptr;
    };
} // namespace UniquePointer

#endif // SHA_UNIQUEPOINTER_H_