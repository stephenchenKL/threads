#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <chrono>         // std::chrono::seconds
#include <mutex>          // std::mutex
#include <syncstream>
#include <atomic>

std::mutex mtx;           // mutex for critical section
int counter = 0;
std::atomic<int> atomic_counter = 0;
const int ITERATIONS = 10;
const int SLEEP_MS = 1000;

void increase_atomic(int iterations) {
    std::thread::id this_id = std::this_thread::get_id();
    while (iterations-- > 0){
        std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_MS));
        std::osyncstream(std::cout) << "thread " << this_id << " \n";
        ++atomic_counter;
    }
}

void increase_without_lockguard(int iterations) {
    std::thread::id this_id = std::this_thread::get_id();
    while (iterations-- > 0){
        std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_MS));
        //std::osyncstream(std::cout) << "increase_without_lockguard thread " << this_id << " \n";
        ++counter;
    }
}

void increase_with_lockguard(int iterations) {
    std::thread::id this_id = std::this_thread::get_id();
    std::lock_guard<std::mutex> lck(mtx);
    while (iterations-- > 0){
        std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_MS));
        std::osyncstream(std::cout) << "increase_with_lockguard thread " << this_id << " \n";
        ++counter;
    }
}

int main ()
{
    auto test = [](std::string_view fun_name, auto fun)
    {
        counter = 0;
        std::cout << fun_name << ":\nbefore, counter: " << counter << '\n';
        auto start = std::chrono::high_resolution_clock::now();
        std::thread t1(fun, ITERATIONS);
        std::thread t2(fun, ITERATIONS);
        t1.join();
        t2.join();
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        std::cout << "after, counter: " << counter << ", duration: " << duration.count() << "\n\n";
    };

    test("increase_with_lockguard", increase_with_lockguard);
    test("increase_without_lockguard", increase_without_lockguard);

    std::cout << "before, atomic_counter: " << atomic_counter << '\n';
    auto start = std::chrono::high_resolution_clock::now();
    std::thread t1(increase_atomic, ITERATIONS);
    std::thread t2(increase_atomic, ITERATIONS);
    t1.join();
    t2.join();
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "after, counter: " << atomic_counter <<  ", duration: " << duration.count() << "\n\n";

  return 0;
}