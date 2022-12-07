#include <stdio.h>
#include <iostream>
#include <future>//promise, future
#include <thread>//thread

using namespace std;

void thread_function(promise<int>* p, int count)
{
    int ret = 0;

    for (int i = 0; i < count; i++)
    {
        ret += i;
    }

    p->set_value(ret);
}

// javascript에서는 promise.set_value()를 여러번 할 수 있다.
// C++에서는 promise.set_value()를 여러번할 수 없으나,
// shared_future를 사용하면 future.get()의 경우는 여러번 호출할 수 있다.

int main()
{
    promise<int> p;
    //share_future의 경우는 get을 한번만 사용하느 것이 아니고 여러번 사용이 가능하다.
    shared_future<int> data = p.get_future();

    thread _th(thread_function, &p, 10);

    /*
        shared_future를 사용하면
        promise.set_value()는 여러번 못하지만, future.get()은 여러번 할 수 있다.
        data.get()을 하면, promise가 set_value할 때까지 기다린다.
    */
    cout << data.get() << endl;
    cout << data.get() << endl;
    cout << data.get() << endl;
    cout << data.get() << endl;

    _th.join();

    return 0;
}