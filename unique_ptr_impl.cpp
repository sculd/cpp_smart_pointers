#include <iostream>

template<typename T>
class unique_ptr_impl {
public:
    T* ptr_;

    explicit unique_ptr_impl(T* ptr = nullptr): ptr_(ptr)  {
        if (ptr_) {
            std::cout << "raw ptr ctr: unique_ptr_impl is created with " << *ptr_ << std::endl;
        } else {
            std::cout << "raw ptr ctr: unique_ptr_impl is created with nullptr" << std::endl;
        }
    }

    unique_ptr_impl(const unique_ptr_impl<T>& u) = delete;

    unique_ptr_impl(unique_ptr_impl<T>&& u) noexcept: ptr_(std::move(u.ptr_)) {
        std::cout << "move ctr: unique_ptr_impl is created" << std::endl;
        u.ptr_ = nullptr;
    }

    ~unique_ptr_impl() {
        if (ptr_) {
            std::cout << "unique_ptr_impl with " << *ptr_ << " is destructed" << std::endl;
        } else {
            std::cout << "unique_ptr_impl with nullptr is destructed" << std::endl;
        }
        delete ptr_;
    }

    unique_ptr_impl<T>& operator=(const unique_ptr_impl<T>& u) = delete;

    unique_ptr_impl<T>& operator=(unique_ptr_impl<T>&& u) {
        std::cout << "move =: unique_ptr_impl is assigned." << std::endl;
        if (this == u) return *this;

        delete ptr_;
        ptr_ = u.ptr_;
        u.ptr_ = nullptr;

        return *this;
    }

    T& operator*() {
        return *ptr_;
    }

    T* operator->() {
        return ptr_;
    }

    const T* get() {
        return ptr_;
    }
private:

};
