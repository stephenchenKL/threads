#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <chrono>         // std::chrono::seconds
#include <mutex>          // std::mutex
#include <syncstream>
#include <string_view>

std::mutex mtx;           // mutex for critical section
int counter = 0;

void increase_without_lockguard(int iterations) {
    while (iterations-- > 0)
        ++counter;
}

void increase_with_lockguard(int iterations) {
    std::lock_guard<std::mutex> lck(mtx);
    while (iterations-- > 0)
        ++counter;
}

int main ()
{
    auto test = [](std::string_view fun_name, auto fun)
    {
        counter = 0;
        std::cout << fun_name << ":\nbefore, counter: " << counter << '\n';
        
        std::thread t1(fun, 1'000'000);
        std::thread t2(fun, 1'000'000);
        
        t1.join();
        t2.join();
        std::cout << "after, counter: " << counter << "\n\n";
    };

    test("increase_with_lockguard", increase_with_lockguard);
    test("increase_without_lockguard", increase_without_lockguard);

  return 0;
}