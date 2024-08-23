#include <iostream>

template <typename T>
class shared_ptr_impl {
    T* ptr_;
public:
    static int count_;

    shared_ptr_impl(T* ptr) {
        ptr_ = ptr;
    }
};


int shared_ptr_impl<T>::count_{ 0 };
