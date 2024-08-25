#include <iostream>

template <typename T>
class shared_ptr_impl {
private:
    T* ptr_ = nullptr;
    int* count_ = nullptr;

    void release_resource_if_zero_count() {
        if (ptr_ == nullptr) {
            return;
        }
        if (*count_ > 0) {
            return;
        }
        std::cout << "releasing the resources for " << *ptr_ << std::endl;
        delete ptr_;
        delete count_;
    }
public:
    static int cls_count_;

    explicit shared_ptr_impl(T* ptr = nullptr): ptr_(ptr) {
        if (ptr_) {
            std::cout << "raw ptr ctr: shared_ptr_impl is created with " << *ptr_ << std::endl;
            count_ = new int(1);
        } else {
            std::cout << "raw ptr ctr: shared_ptr_impl is created with nullptr" << std::endl;
        }
    }

    shared_ptr_impl(const shared_ptr_impl<T>& o): ptr_(o.ptr_), count_(o.count_) {
        std::cout << "copy ctr: shared_ptr_impl is created" << std::endl;
        *count_ += 1;
    }

    shared_ptr_impl& operator = (const shared_ptr_impl<T>& o) {
        std::cout << "copy assignment: shared_ptr_impl with " << *o.ptr_ << std::endl;
        if (this->ptr_ == o.ptr_) {
            return *this;
        }
        if (ptr_) {
            *count_ -= 1;
            std::cout << "count_ for currentn ptr " << *ptr_ << " reduced to " << *count_ << std::endl;
            release_resource_if_zero_count();
        }
        ptr_ = o.ptr_;
        count_ = o.count_;
        *count_ += 1;
        std::cout << "count_ for currentn ptr " << *ptr_ << " increases to " << *count_ << std::endl;

        return *this;
    }

    ~shared_ptr_impl() {
        if (ptr_) {
            std::cout << "shared_ptr_impl with " << *ptr_ << " is destructed" << std::endl;
        } else {
            std::cout << "shared_ptr_impl with nullptr is destructed" << std::endl;
        }
        *count_ -= 1;
        std::cout << "count_" << *count_ << std::endl;
        release_resource_if_zero_count();
    }

    int use_count() {
        return *count_;
    }

    T* operator -> () {
        return ptr_;
    }
};

template <typename T>
int shared_ptr_impl<T>::cls_count_{ 0 };
