#include <atomic>
#include <chrono>
#include <functional>
#include <iostream>
#include <thread>

std::atomic_bool runloop = false;

void armTimer()
{
    std::cout << "arm timer" << std::endl;
    runloop.store(true);
}

void disArmTimer()
{
    std::cout << "disarm timer" << std::endl;
    runloop.store(false);
}

template <typename Tp, typename Res, typename CallBkType>
void timer(std::chrono::duration<Tp, Res> const &lTimeOut, CallBkType lCallbk)
{
    while (runloop.load())
    {
        std::this_thread::sleep_for(lTimeOut);
        lCallbk();
    }
}

void foo()
{
    std::cout << "Time:: ";
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(
                     std::chrono::system_clock::now().time_since_epoch())
                     .count()
              << std::endl;
}

int main(void)
{
    using namespace std::chrono_literals;

    std::vector<std::jthread> lvThreadVector;

    armTimer();
    lvThreadVector.emplace_back([]() -> void { timer(10ms, std::bind(foo)); });
    lvThreadVector.emplace_back([]() -> void { timer(1s, disArmTimer); });

    std::cout << "main loop" << std::endl;
    return 0;
}
