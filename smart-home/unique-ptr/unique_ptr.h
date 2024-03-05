#ifndef SH_UNIQUE_PTR_UNIQUE_PTR_H_
#define SH_UNIQUE_PTR_UNIQUE_PTR_H_

#include <cstddef>
#include <memory>
#include <utility>

namespace antoniaptr {
template<typename T, typename Deleter = std::default_delete<T>>
class unique_ptr {
private:
    T* ptr;
    Deleter deleter;

    void deleter_call() {
        if constexpr (!std::is_same<Deleter, std::nullptr_t>::value) {
            deleter(ptr);
        } else {
            delete ptr;
        }
    }

public:
    explicit unique_ptr(T* p = nullptr, Deleter d = Deleter()) : ptr(p), deleter(d) {}

    ~unique_ptr() {
        deleter_call();
    }

    unique_ptr(unique_ptr&& u) noexcept : ptr(u.ptr), deleter(std::move(u.deleter)) {
        u.ptr = nullptr;
    }

    unique_ptr& operator=(unique_ptr&& u) noexcept {
        if (this != &u) {
            deleter_call();
            ptr = u.ptr;
            deleter = std::move(u.deleter);
            u.ptr = nullptr;
        }
        return *this;
    }

    unique_ptr(const unique_ptr&) = delete;
    unique_ptr& operator=(const unique_ptr&) = delete;

    T& operator*() const { return *ptr; }
    T* operator->() const { return ptr; }
    
    bool operator==(const unique_ptr<T>& other) {
        return ptr == other.ptr;
    }

    bool operator!=(const unique_ptr<T>& other) {
        return ptr == other.ptr;
    }

    T* release() {
        T* temp = ptr;
        ptr = nullptr;
        return temp;
    }

    void reset(T* p = nullptr) {
        deleter_call();
        ptr = p;
    }

    T* get() const { return ptr; }
    Deleter get_deleter() const { return deleter; }

    T& operator[](std::size_t index) const {
        return ptr[index];
    }
};
} // namespace antoniaptr

#endif // SH_UNIQUE_PTR_UNIQUE_PTR_H_