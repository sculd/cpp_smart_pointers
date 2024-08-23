#include <iostream>
#include <memory>
#include "unique_ptr_impl.cpp"
#include "shared_ptr_impl.cpp"

class A {
    public:
    int value_;
    int *data_;

    A(int value): value_(value) {
        std::cout << "A(" << value_ << ") is created" << std::endl;
        data_ = new int[100];
    }

    A(A&& a): value_(a.value_), data_(std::move(a.data_)) {
        std::cout << "move ctr from A(" << a.value_ << ")" << std::endl;
    }

    A& operator=(A&& a) {
        std::cout << "moved = from A(" << a.value_ << ")" << std::endl;
        value_ = a.value_;
        data_ = a.data_;

        a.value_ = 0;
        a.data_ = nullptr;
        return *this;
    }

    void some() { std::cout << "some(" << value_ << ")" << std::endl; }

    ~A() {
        std::cout << "A(" << value_ << ") is deleted" << std::endl;
        delete[] data_;
    }
};

std::ostream& operator<<(std::ostream& os, const A& a)
{
    os << "A(" << a.value_ << ")";
    return os;
}

void thrower() {
  // 예외를 발생시킴!
  throw 1;
}

void do_something() {
  unique_ptr_impl<A> pa(new A(1));
  std::cout << "pa : ";
  pa->some();

  // pb 에 소유권을 이전.
  unique_ptr_impl<A> pb = std::move(pa);
  std::cout << "pb : ";
  pb->some();
}

int main(int argc, char **argv) {
    do_something();

    unique_ptr_impl<A> ua;

    shared_ptr_impl<A> sa(new A(2));
    std::cout << sa.count_ << std::endl;

    return 0;
}
