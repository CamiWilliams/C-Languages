#include "uthread.c" //suppose the uthread library code is in uthread.c

int n_threads = 0;
int myid = 0;
void do_something()
{
  int id;
  id = myid;
  myid++;
  printf("This is ult %d\n", id); //just for demo purpose

  if(n_threads < 5){
    uthread_create(do_something);
    n_threads++;
    printf("ult %d yields \n",id );
    uthread_yield();
    printf("ult %d resumes \n",id);
    uthread_create(do_something);
    n_threads++;
  }

  printf("ult %d starts I/O \n",id);
  uthread_startIO();
  sleep(2); //simulate some long−time I/O operation
  uthread_endIO();
  printf("ult %d returns from I/O \n",id);
  uthread_exit();
}

int main()
{
  int i;
  system_init();
  uthread_create(do_something);
  uthread_exit();
//  sleep(5);
  return 0;
}

/*
 * This is ult 0
 * ult 0 yields
 * This is ult 1
 * ult 1 yields
 * ult 0 resumes
 * ult 0 starts I/O
 * This is ult 2
 * ult 2 yields
 * ult 1 resumes
 * ult 1 starts I/O
 * This is ult 3
 * ult 3 starts I/O
 * This is ult 4
 * ult 4 starts I/O
 * ult 2 resumes
 * ult 2 starts I/O
 * This is ult 5
 * ult 5 starts I/O
 * This is ult 6
 * ult 6 starts I/O
 * ult 0 returns from I/O
 * ult 1 returns from I/O
 * ult 3 returns from I/O
 * ult 4 returns from I/O
 * ult 2 returns from I/O
 * ult 5 returns from I/O
 * ult 6 returns from I/O
 */
