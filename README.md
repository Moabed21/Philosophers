# 🛠️ Philosophers : The "Lite" Version

> A simplified implementation of the classic **Dining Philosophers Problem** using **Unix threads in C**.  
> This project explores 🧵 threads, 🔒 synchronization, ⏱️ timing, and 🧠 memory concepts in a practical and visual way.

---

# 📚 Table of Contents

- [🏠 Processes vs Threads](#-processes-vs-threads)
- [🤹 The CPU & Scheduling](#-the-cpu--scheduling)
- [🧬 Creating Life with `fork()`](#-creating-life-with-fork)
- [🗣️ Inter-Process Communication (IPC)](#-inter-process-communication-ipc)
- [🔑 Synchronization & Semaphores](#-synchronization--semaphores)
- [🧵 Unix Threads in C (`pthread`)](#-unix-threads-in-c-pthread)
- [⚠️ Race Conditions](#️-race-conditions)
- [🔒 Mutexes](#-mutexes)
- [⏱️ Time Handling with `gettimeofday()`](#️-time-handling-with-gettimeofday)

---

# 🏠 Processes vs Threads

## 1️⃣ The Core Difference: Buildings vs. Roommates

### 🏠 The Process = The House

- **What is it?** A standalone program running in memory.
- **Isolation:** Fully independent. If one house burns down, the neighbor is safe.
- **Cost:** Expensive to build (heavy system resources).
- **Privacy:** Has its own private kitchen (Memory) and keys (Permissions).

---

### 👯 The Thread = The Roommates

- **What is it?** A worker living *inside* the Process.
- **Sharing:** Share the kitchen (Heap), living room (Global Variables), and bathroom (Files).
- **Risk:** If one roommate causes a segfault 💥, the **whole house crashes**.

---

# 🤹 The CPU & Scheduling

## How One CPU Runs Many Tasks

- **The Illusion:** It looks like 10 apps are running at once.
- **Reality:** The CPU is juggling.
  - Runs App A for 0.001 seconds
  - Switches to App B
  - Then back to App A

### 🔄 Context Switch

The moment the CPU pauses one task to run another.

⚠️ Context switching costs time and energy (overhead).

### 👔 The Scheduler

The operating system's "Boss" that decides:
- Who runs next
- For how long
- With what priority

---

### 📌 Rule of Thumb

| Concept | Analogy |
|----------|----------|
| **Concurrency** | One juggler handling 3 balls (time-slicing) |
| **Parallelism** | Three jugglers, each with 1 ball (multi-core CPU) |

---

# 🧬 Creating Life with `fork()`

When using `fork()`, you **clone** the current process.

- 👨 Parent → The original
- 👶 Child → The duplicate

Both continue execution from the same point.

### Return Values:

- `0` → You're in the **Child**
- `PID` → You're in the **Parent**
- `-1` → Error occurred

---

### ⚠️ Danger Zone: Zombies 🧟

If a child process finishes but the parent does not call `wait()` or `waitpid()`:

- The child becomes a **Zombie process**
- It is dead, but still occupies system resources

---

# 🗣️ Inter-Process Communication (IPC)

Processes are isolated, so they need special tools to communicate.

| Method | Analogy | Speed | Safety |
|--------|----------|--------|--------|
| **Pipe** | Pneumatic tube 📦 | Slower | High |
| **Shared Memory** | Shared whiteboard 📝 | Very Fast | Risky (Race conditions) |

---

# 🔑 Synchronization & Semaphores

## The Problem: Race Conditions 🏎️

Two threads try to modify the same variable at the same time.

Result?
- Corrupted data
- Unexpected behavior
- Crashes

---

## The Solution: Semaphore 🔑

Think of it as a **single-bathroom key**.

### `wait()` (Lock)

- Is key available?
  - Yes → Take it and enter.
  - No → Wait outside.

### `post()` (Unlock)

- Leave bathroom.
- Put key back.
- Next waiting thread enters.

---

### 🧠 What Does "Atomic" Mean?

An atomic operation:
- Happens in one indivisible step
- Cannot be interrupted
- Guarantees consistency

---

# 🧵 Unix Threads in C (`pthread`)

To use threads in C:

```c
#include <pthread.h>
```

---

## 🔹 `pthread_t`

Used to define a thread:

```c
pthread_t thread;
```

---

## 🔹 `pthread_create()`

Creates a new thread.

### Prototype:

```c
int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
                   void *(*start_routine)(void*), void *arg);
```

### Parameters:

- Pointer to thread
- Thread attributes
- Function the thread will execute
- Argument passed to the function

### Return Value:

- `0` → Success
- Non-zero → Error code

---

## 🔹 `pthread_join()`

Waits for a thread to finish.

### Prototype:

```c
int pthread_join(pthread_t thread, void **retval);
```

### Parameters:

- Thread to wait for
- Pointer to return value

### Important ⚠️

Do NOT create and join the same thread inside the same loop iteration.

❌ That makes your program run sequentially  
✅ Create all threads first, then join them

---

# ⚠️ Race Conditions

A **data race** occurs when:

- Two or more threads
- Access shared memory
- At the same time
- And at least one modifies it

Result → Undefined behavior.

---

# 🔒 Mutexes

A **mutex** (Mutual Exclusion) prevents race conditions.

### Functions:

- `pthread_mutex_t` → Declare mutex
- `pthread_mutex_init()` → Initialize
- `pthread_mutex_lock()` → Lock
- `pthread_mutex_unlock()` → Unlock
- `pthread_mutex_destroy()` → Destroy

### Example:

```c
pthread_mutex_t lock;

pthread_mutex_init(&lock, NULL);
pthread_mutex_lock(&lock);

/* Critical Section */

pthread_mutex_unlock(&lock);
pthread_mutex_destroy(&lock);
```

---

# ⏱️ Time Handling with `gettimeofday()`

Include:

```c
#include <sys/time.h>
```

### Example:

```c
struct timeval current_time;

gettimeofday(&current_time, NULL);
printf("Current time (microseconds): %ld\n", current_time.tv_usec);
```

- `tv_sec` → Seconds
- `tv_usec` → Microseconds

Useful for:
- Measuring philosopher eating time 🍝
- Death timing ⏳
- Logging events

---

# 🎯 Project Goal

This project demonstrates:

- 🧠 Thread lifecycle management
- 🔒 Proper synchronization
- ⏱️ Time-based simulation
- 🚫 Avoiding deadlocks
- 🚦 Preventing race conditions

It is a simplified ("Lite") version of the **Dining Philosophers** problem designed to strengthen understanding of:

- Concurrency
- Parallelism
- System-level programming
- Resource sharing
- CPU scheduling

---

# 🚀 Final Thoughts

Understanding threads and synchronization is fundamental for:

- Operating Systems
- High-performance servers
- Real-time systems
- Game engines
- Embedded systems

This project builds strong foundations in **concurrent programming in C** — one of the most powerful and challenging areas in systems development.

Happy coding! 👨‍💻🔥