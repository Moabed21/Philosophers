# 🛠️ Philosophers : The "Lite" Version

## 1. The Core Difference: Buildings vs. Roommates
**Concept:** How code lives in memory.

### The Process = The House 🏠
* **What is it?** A standalone program running in memory.
* **Isolation:** Fully independent. If one house burns down, the neighbor is safe.
* **Cost:** Expensive to build (heavy system resources).
* **Privacy:** Has its own private kitchen (Memory) and keys (Permissions).

### The Thread = The Roommates 👯
* **What is it?** A worker living *inside* the Process.
* **Sharing:** They share the kitchen (Heap), living room (Global Vars), and bathroom (Files).
* **Risk:** If one roommate sets the kitchen on fire (Segfault), the **whole house** burns down.

---

## 2. The CPU: The Juggler 🤹
**Concept:** How one CPU runs many things.

* **The Illusion:** It looks like 10 apps are running at once.
* **The Reality:** The CPU is juggling. It runs App A for 0.001 seconds, then App B, then App A again.
* **Context Switch:** The moment the CPU freezes App A to switch to App B. This "pause" costs energy (overhead).
* **Scheduler:** The "Boss" who decides whose turn it is next.

> **Rule of Thumb:**
> * **Concurrency:** One juggler handling 3 balls (Time-slicing).
> * **Parallelism:** Three jugglers, each with 1 ball (Multi-Core).

---

## 3. Creating Life: `fork()` 🧬
**Concept:** Making new processes in C.

When you run `fork()`, you don't start from scratch. You **clone**.

* **Parent:** The original.
* **Child:** A perfect duplicate (same code, same variables at that moment).
* **The Split:**
    * If `fork()` returns `0` → You are now in the **Child** timeline.
    * If `fork()` returns `PID` → You are in the **Parent** timeline.

> **⚠️ Danger Zone: Zombies**
> If the Child finishes but the Parent is too busy to check on it (`waitpid`), the Child becomes a **Zombie**—dead, but still taking up space in the RAM.

---

## 4. Communication: How to Talk 🗣️
**Concept:** IPC (Inter-Process Communication).

Since Processes (Houses) are separate, they need special tools to talk.

| Method | The Analogy | Speed | Safety |
| :--- | :--- | :--- | :--- |
| **Pipe** | A pneumatic tube. You put data in one end, it pops out the other. | Slower | High (Safe) |
| **Shared Memory** | A whiteboard in the hallway. Anyone can write on it. | Instant | Low (Race Conditions) |

---

## 5. Synchronization: The Bathroom Key 🔑
**Concept:** Avoiding conflicts (Race Conditions).

**The Problem:** Two threads try to update the same variable at the exact same time. The data gets corrupted.

**The Solution:** The **Semaphore**.
Think of it as the key to a single-toilet bathroom.

1.  **`wait()` (Lock):**
    * Is the key on the hook?
    * **Yes:** Take key, enter, lock door.
    * **No:** Wait outside (Sleep) until it's free.
2.  **`post()` (Unlock):**
    * Exit, put key back on hook.
    * The next person waiting grabs it.

> **Atomic:** This means grabbing the key happens in **one instant motion**. You can't be interrupted while reaching for it.

# Unix Threads in c

1) Short introduction to threads

first include the pthread.h library

pthread_t is used to define a thread 

## pthread_create()
a function is used to create a new thread, takes four parameters:

- a pointer to the thread
- thread attribute
- the routine which thread meant to work on
- argument that is passed to the routine

int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
    void *(*start_routine)(void*), void *arg);

If successful, pthread_create() returns zero. Otherwise, an error number is returned to indicate the error.

## pthread_join()
a function used to prevent the main process to finish execute without the thread finish its job
(like wait() in the processes) but for threads , takes two parameters:

- the thread to be be waited for
- the thread return value (or the routine function return value).

If successful, pthread_join() returns zero. Otherwise, an error number is returned to indicate the error.

You shouldn't create and join the same thread in the same loop iteration because the program will run sequentially not con currently

## Race conditions

Data race occures whe threads tries to access shared resources simultaneously(ath the same time)

## What is a mutex

its the solution to pervent Data race in programming method:

pthread_mutex_t : to create the semaphore 
pthread_mutex_lock : to lock it 
pthread_mutex_unlock : to unlock it
pthread_mutex_init : to initialize it
pthread_mutex_destroy : to destroy it

## Gettimeofday()

to use it include the < sys/time.h > then define a variable from struct of type timeval , to print the current time in microsec :

     struct timeval current_time;
    gettimeofday(&current_time, NULL);
    printf("current time is : %ld", current_time.tv_usec);
