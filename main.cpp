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

class B {
public:
    int value_;
    B(int value): value_(value) {
        std::cout << "B(" << value_ << ") is created" << std::endl;
    }
};

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
    shared_ptr_impl<A> sa1(new A(1));
    std::cout << "sa1.use_count(): " << sa1.use_count() << std::endl;
    shared_ptr_impl<A> sa2(sa1);
    std::cout << "sa1.use_count(): " << sa1.use_count() << std::endl;
    std::cout << "sa2.use_count(): " << sa2.use_count() << std::endl;

    shared_ptr_impl<A> saa1(new A(2));
    std::cout << "saa1.use_count(): " << saa1.use_count() << std::endl;
    shared_ptr_impl<A> saa2;
    saa2 = saa1;
    std::cout << "saa1.use_count(): " << saa1.use_count() << std::endl;
    std::cout << "meaningless duplicated assignment" << std::endl;
    saa2 = saa1;
    std::cout << "saa1.use_count(): " << saa1.use_count() << std::endl;
    std::cout << "assignment with another sa" << std::endl;
    saa2 = sa1;
    std::cout << "saa1.use_count(): " << saa1.use_count() << std::endl;
    std::cout << "sa1.use_count(): " << sa1.use_count() << std::endl;
    saa2 = saa2;
    std::cout << "saa1.use_count(): " << saa1.use_count() << std::endl;
    saa2 = saa2;
    std::cout << "saa1.use_count(): " << saa1.use_count() << std::endl;

    return 0;
}
