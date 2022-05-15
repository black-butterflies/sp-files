#include <stdio.h>
#include <thread>

int main()
{
  auto t = std::thread([]
                       { printf("Hello World from a cpp thread!\n"); });

  // if you don't join your threads, the threads will terminate at some point but it is non-deterministic
  // the destructor of t will be called once main is done -> it terminates the program brutally

  t.join();
}
