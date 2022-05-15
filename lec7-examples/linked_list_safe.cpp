#include <stdio.h>

#include <list>
#include <thread>
#include <optional>

struct list
{
private:
  std::list<int> list;
  std::mutex mutex; // ! mutex is in the scope of the struct

public:
  void append_to_list(int value)
  {
    std::unique_lock<std::mutex> lock(mutex); // acquire the lock
    list.push_back(value);
  } // release the lock automatically once we reach the end of lifetime

  std::optional<int> remove_from_list(int position)
  {
    std::unique_lock<std::mutex> lock(mutex); // acquire the lock
    std::list<int>::iterator iter = list.begin();
    while (position > 0 && iter != list.end())
    {
      iter++;
      position--;
    }
    if (position != 0 || iter == list.end())
    {
      return {}; // nothing to return
    }
    int value = *iter;
    list.erase(iter);
    return value;
  } // release the lock automatically

  std::list<int>::iterator begin() { return list.begin(); }
  std::list<int>::iterator end() { return list.end(); }
};

int main()
{
  auto l = list{};
  l.append_to_list('a');
  l.append_to_list('b');
  l.append_to_list('c');
  l.append_to_list('d');

  auto t1 = std::thread([l_ptr = &l]
                        { l_ptr->remove_from_list(1); });
  auto t2 = std::thread([l_ptr = &l]
                        { l_ptr->remove_from_list(1); });

  t1.join();
  t2.join();

  for (auto iter = l.begin(); iter != l.end(); iter++)
  {
    printf("%c", *iter);
    if (std::next(iter) != l.end())
    {
      printf(" -> ");
    }
  }
  printf("\n");
}
