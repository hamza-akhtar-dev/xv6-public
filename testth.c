#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

lock_t lock;

void f1(void* arg1, void* arg2) 
{
  lock_acquire(&lock);
  printf(1, "1. this should print %s - args: %d, %d\n", "first", *(int*)arg1, *(int*)arg2);
  sleep(1000);
  lock_release(&lock);
  exit();
}

void f2(void* arg1, void* arg2) 
{
  lock_acquire(&lock);
  printf(1, "2. this should print %s - args: %d, %d\n", "second", *(int*)arg1, *(int*)arg2);
  sleep(100);
  lock_release(&lock);
  exit();
}

void f3(void* arg1, void* arg2)
{
  lock_acquire(&lock);
  printf(1, "3. this should print %s - args: %d, %d\n", "third", *(int*)arg1, *(int*)arg2);
  sleep(10);
  lock_release(&lock);
  exit();
}

int
main(int argc, char *argv[])
{
  lock_init(&lock);
  int arg1;
  int arg2;

  arg1 = 0;
  arg2 = 1;

  printf(1, "Below should be sequential print statements:\n");
  thread_create(&f1, (void *)&arg1, (void *)&arg2);
  thread_create(&f2, (void *)&arg1, (void *)&arg2);
  thread_create(&f3, (void *)&arg1, (void *)&arg2);
  thread_join();
  thread_join();
  thread_join();

  exit();
}