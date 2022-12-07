#include <stdio.h>
#include <iostream>
#include <future>//promise, future
#include <thread>//thread

using namespace std;

/*
promise와 packed_task의 결과는 같다.
그러나 스레드를 위한 함수의 리턴과 파라미터 타입이 바뀌었다.
packed_task를 이용하면 이전에 작성했던 함수들도 수정없이 병렬 처리가 가능하다는 뜻이다.

그런데, promise와 packaged_task의 최종 보스는 async이다.
async는 promise나 packaged_task, thread 객체까지 전부 생략했다.
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

int main()
{
    // async에 함수명과 파라미터를 설정, 리턴은 future이다.
    shared_future<int> data = async(thread_function, 10);
    // data.get()을 하면 함수가 종료될 때까지 기다린다.
    // 내부적으로 data.wait()이 실행된다.
    cout << data.get() << endl;
    cout << data.get() << endl;
    cout << data.get() << endl;
    cout << data.get() << endl;

    return 0;
}