## chrono

计时库 since C++ 11

### 统计程序运行时间

```c++
#include <iostream>
#include <chrono>

using namespace std;
using namespace chrono;
int main() {
    auto start = system_clock::now();

    // Some computation here

    auto end = system_clock::now();
    duration<double, ratio<1, 1000>> elapsed = end-start;
    cout << "elapsed time: " << elapsed.count() << "ms\n";
}
```

### 打印当前时间

```c++
#include <iostream>
#include <chrono>
#include <ctime>    

using namespace std;
using namespace chrono;
int main() {
    auto end = system_clock::now();
    time_t end_time = system_clock::to_time_t(end);
    cout << "finished computation at " << ctime(&end_time);
}
```

### 获得当前时间作为随机数种子

```c++
mt19937 rand(chrono::system_clock::now().time_since_epoch().count());
unsigned int random1 = rand();
unsigned int random2 = rand();
unsigned int random3 = rand();
printf("%d\n%d\n%d\n", random1, random2, random3);
```