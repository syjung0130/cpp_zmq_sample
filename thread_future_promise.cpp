#include <stdio.h>
#include <iostream>
#include <future>
#include <thread>

using namespace std;

void thread_function(promise<int>* p, int count)
{
    int ret = 0;

    for (int i = 0; i < count; i++)
    {
        ret+=i;
    }
    p->set_value(ret);
}

int main()
{
    promise<int> p;
    /*
    promise와 future를 연결
    promise에서 set_value를 하면 future에서 get으로 받는 것이다.
    */
    future<int> data = p.get_future();

    // 스레드를 실행해서 promise를 전달해주고, 다른 전달인자도 전달함.
    thread _th(thread_function, &p, 10);

    // data.get()을 하면 promise가 set_value할 때까지 기다린다.
    // 내부적으로 data.wait()이 실행된다.
    cout << data.get() << endl;

    // thread를 종료한다.
    _th.join();

    return 0;
}

