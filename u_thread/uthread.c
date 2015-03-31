#define _XOPEN_SOURCE 600
#define _GNU_SOURCE

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <sched.h>
#include <ucontext.h> // getcontext(ucp)   : initializes the structure pointed at by ucp
                      //                     to the currently active context.
                      // setcontext(ucp)   : restores the user context pointed at by ucp
                      // makecontext(ucp, func) : modifies the context pointed to by ucp
                      // swapcontext(oucp, ucp) : saves the current context in the structure
                      //                  pointed to by oucp, and then activates the
                      //                  context pointed to by ucp.
                      // allow user-level context switching between multiple
                      // threads of control within a process.
                      // http://man7.org/linux/man-pages/man2/setcontext.2.html

/*
 * Author: Cami Williams
 * Mem leak: valgrind --leak-check=full --show-reachable=yes --track-origins=yes !!valgrind --leak-check=full --show-reachable=yes --track-origins=yes ./uthread_tests
 */

// Thread represents a Node of the ready queue
struct thread {
  struct thread* next;
  struct thread* prev;

  ucontext_t* context;
  int type; //0 if kernel, 1 if IO
};

// Determines if sys_init has been called, 0 if no, 1 if yes
int initialized = 0;
// Keeps the size of the ready queue
int rq_size;
// Keeps how many running threads there are (max 1)
int num_running_threads;
// Keeps how many io threads there are
int num_io_threads;
// Points to the head of the ready queue
struct thread* HEAD;
// Points to the tail of the ready queue
struct thread* TAIL;
// Describes the calling thread properties
struct thread* CALLING_THREAD;

// Semaphore for actions
sem_t mutex;

/* Adds a thread to the ready queue. Since it is FCFS, it will add to the end */
void add(struct thread* t);
/* Removes and returns thread from the ready queue. Since it is FCFS, it will remove and return the first element */
struct thread* removeThread();
/* Performs the setcontext operations */
int doSetContext(void* arg);
/* Initializes the thread for the ready queue */
struct thread* initializeThread();

/*
 * This function has to be called before any other uthread library function.
 * Initializes the uthread system. Should maintain data structure of a ready
 * queue, number of currently running kernel threads (should not exceed 1), and
 * the number of processes that are currently waiting for the I/O operation
 */
void system_init() {
  if(initialized == 1) {
    fprintf(stderr, "Error, system has been initialized already \n");
    exit(EXIT_FAILURE);
  } else {
    sem_init(&mutex, 0, 1);

    sem_wait(&mutex);
      initialized = 1;
      num_running_threads = 0;
      rq_size = 0;
      num_io_threads = 0;
      HEAD = NULL;
      TAIL = NULL;
      CALLING_THREAD = initializeThread();
      CALLING_THREAD->type = 0;
    sem_post(&mutex);
  }
}

/*
 * The calling thread requests to create a user-level thread that runs the
 * func. The context of function should be properly created and stored on the
 * ready queue for execution. The function returns 0 on success and -1 otherwise
 */
int uthread_create(void (*func)()) {
  sem_wait(&mutex);
    if(initialized == 0) {
      fprintf(stderr, "Error, system needs to be initialized \n");
      sem_post(&mutex);
      return -1;
    }
  sem_post(&mutex);

  //http://linux.die.net/man/3/makecontext
  struct thread* t = initializeThread();
  makecontext(t->context, func, 0);

  sem_wait(&mutex);
    if(num_running_threads == 0) {
      num_running_threads++;
      CALLING_THREAD = t;
      sem_post(&mutex);

      clone(doSetContext, malloc(16384), CLONE_VM, t->context);
      free(t);
    } else {
      add(t);
      sem_post(&mutex);
    }

  return 0;
}

/*
 * The calling thread calls this function before it requests for I/O operations
 * (scanf, printf, read, write, etc.) We assume that when this function is
 * called, the state of the calling thread transits from running state to
 * waiting state and will not run on CPU actively. Therefore, it will create
 * a new kernel thread and schedule the first thread in the ready queue to run
 * (assuming the scheduling algorithm used is FCFS). This calling user-level
 * thread will remain associated with its current kernel thread, initiating I/O
 * and then waiting for it to complete. This function returns 0 on success and
 * -1 otherwise
 */
int uthread_startIO() {
  sem_wait(&mutex);
    if(initialized == 0) {
      fprintf(stderr, "Error, system needs to be initialized \n");
      sem_post(&mutex);
      return -1;
    }
    struct thread* temp = removeThread();
    temp->type = 1;
  sem_post(&mutex);

  if(temp != NULL) {
    sem_wait(&mutex);
      num_io_threads++;
    sem_post(&mutex);

    clone(doSetContext, malloc(16384), CLONE_VM, temp->context);
    free(temp);
  }
  return 0;
}

/*
 * The function should be called right after it finishes I/O operations. We
 * assume that when this function is called, the state of the caling process is
 * switched from the waiting state to the ready state. It should save the
 * context of current thread and put it in the ready queue. Note that the kernel
 * thread it is currently associated with needs to be terminated after this
 * function is called, because its kernel thread is only for initiating I/O and
 * waiting for the I/O to be completed. This function returns 0 on success and
 * -1 otherwise
 */
int uthread_endIO() {
  sem_wait(&mutex);
    if(initialized == 0) {
      fprintf(stderr, "Error, system needs to be initialized \n");
      sem_post(&mutex);
      return -1;
    }
  sem_post(&mutex);

  struct thread* t = initializeThread();
  t->type = 1;

  sem_wait(&mutex);
    add(t);
    num_io_threads--;
  sem_post(&mutex);

  return 0;
}

/*
 * The calling thread requests to yield the kernel thread to another process. It
 * should save the context of current running thread and load the first one on
 * the ready queue (assuming the scheduling algorithm used is FCFS). The
 * function returns 0 on success and -1 otherwise.
 */
int uthread_yield() {
  sem_wait(&mutex);
    if(initialized == 0) {
      fprintf(stderr, "Error, system needs to be initialized \n");
      sem_post(&mutex);
      return -1;
    }
    struct thread* nextWaiting = removeThread();
    struct thread* currRun = CALLING_THREAD;

  sem_post(&mutex);

  if(nextWaiting != NULL) {
    swapcontext(currRun->context, nextWaiting->context);
    sem_wait(&mutex);
      CALLING_THREAD = nextWaiting;
    sem_post(&mutex);
    free(nextWaiting);
  }
  return 0;
}

/*
 * This function is called when the calling user-level thread ends its
 * execution. It should schedule the first user-level thread in the ready
 * queue for running.
 */
void uthread_exit() {
  sem_wait(&mutex);
    if(initialized == 0) {
      fprintf(stderr, "Error, system needs to be initialized \n");
      sem_post(&mutex);
      exit(EXIT_FAILURE);
    }

    num_running_threads--;
    struct thread* temp = removeThread();
  sem_post(&mutex);

  if(temp == NULL) {
    exit(EXIT_SUCCESS);
  }

  sem_wait(&mutex);
    if(CALLING_THREAD->type == 1) {
      num_io_threads--;
      num_running_threads++;
    }
    CALLING_THREAD = temp;
  sem_post(&mutex);

  setcontext(temp->context);
//  clone(doSetContext, (void *)malloc(16384), CLONE_VM, temp->context);
  free(temp);
}


//------------------------ HELPER FUNCTIONS ------------------------//

int doSetContext(void* arg) {
  ucontext_t* con = (ucontext_t*) arg;

  // printf("------------------------\n");
  // printf("Num Running Threads %d \n" , num_running_threads);
  // printf("Num IO Threads %d \n" , num_io_threads);
  // printf("RQ Size %d \n" , rq_size);
  // printf("------------------------\n");

  setcontext(con);
}

struct thread* initializeThread() {
  ucontext_t *ucp;
  ucp = (ucontext_t*)malloc(sizeof(ucontext_t));
  getcontext(ucp);

  struct thread* temp = (struct thread*)malloc(sizeof(struct thread));
  temp->context = ucp;
  temp->context->uc_stack.ss_sp = malloc(16384);
  temp->context->uc_stack.ss_size = 16384;
  temp->next = NULL;
  temp->prev = NULL;

  return temp;
}

void add(struct thread* t) {
  if(t == NULL) {
    fprintf(stderr, "Error, thread is NULL \n");
    exit(EXIT_FAILURE);
  } else {
    if(HEAD == NULL) HEAD = t;
    else {
      TAIL->next = t;
      t->next = NULL;
      t->prev = TAIL;
    }
    TAIL = t;
    rq_size++;
  }
}

struct thread* removeThread() {
  if (HEAD == NULL) {
    return NULL;
  } else {
      struct thread* t;
      t = HEAD;
      HEAD = HEAD->next;
      rq_size--;
      return t;
  }
}
