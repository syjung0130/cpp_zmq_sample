#include <stdio.h>
#include <iostream>
#include <future>//promise, future
#include <thread>//thread

using namespace std;

/*
promise와 future를 사용하기 위해서 결국 함수에 parameter로 promise를 설정해야한다.
기존에 있는 함수를 수정할 수 없는 상황에서 비동기를 사용하려고 한다면 promise를 사용할 수 없다.
이 때, packed_task를 사용하면 된다.
*/

int thread_function(int count)
{
    int ret = 0;

    for (int i = 0; i < count; i++)
    {
        ret += i;
    }

    return ret;
}

/*
promise와 packaged_task의 결과는 같다.
그러나 스레드를 위한 함수의 리턴과 파라미터 타입이 바뀌었다.
packaged_task를 이용하면 이전에 작성된 함수들도 수정없이 병렬 처리가 가능하다는 뜻이다.
*/
int main()
{
    packaged_task<int(int)> task(thread_function);
    shared_future<int> data = task.get_future();
    thread _th(move(task), 10);

    cout << data.get() << endl;
    cout << data.get() << endl;
    cout << data.get() << endl;
    cout << data.get() << endl;

    _th.join();

    return 0;
}