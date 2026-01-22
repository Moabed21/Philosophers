# Philosophers

# Learning ladder

1) waitpid
2) visual forking
3) intro to process and thread :

Any program is converted to a binary code instructions according to the CPU, we shorthand the binary to hex code stored in the RAM memeory.

Then, the CPU reads and puts them into a queue which called (pipeline) and gets executed by CPU components.

Thread is the basic unit of execution (a set of instructions)

One program can have many threads.

- Multi-threaded applications uses a software called Scheduler, which switches between threads being executed by 
the CPU , the unit of switching is called time slice 

this is the pre-emptive multitasking, because it doesnt rely on any of the threads to give up , just the 
scheduler keeps control of the switching back and forth.

Threads have a priority number which clarifies the turn of each thread to the scheduler.

- Multi Tasking OS => Multi-threaded applications , first systems on a single CPU is a hyper-threading which 
duplicate a part of the pipeline, Unlike a traditional dual-processor configuration that uses two separate 
physical processors, the logical processors in a hyper-threaded core share the execution resources. These 
resources include the execution engine, caches, and system bus interface.

Best solution is multi CPUs

4) What is a Thread? | Threads, Process, Program, Parallelism :

- Single threaded process has only one thread to execute all the sequence of operation.

- Multi threaded process has the joint effort of all threads will result in the exection of the sequence of operations.

- each thread has resources allocated to it like stack or registers and shared resources like heap memory and files.

- the program can have many processes and each process can be handled by one or many threads.

process is the actual execution of a program.

- if the number of threads exceeds the number of actual cores in the CPU , the processor creates an illusion of parallelism,
by slice the time for each thread to be executed

the problem here is if two threads has to access the same resource, one of them will wait the other one.

process with no threads cannot exist.

communication between different threads inside a process is faster than it between different processes.

it's not always a better appproach to use multi threads rather than multi processes , google chrome an example.

5) Interprocess Communication

process an be eiter :

- Independent process : which cannot affect or be affected by the other processes executed in the system.

- Cooperating process :  can affect of be affected, for example any process shares data with other processes .

Inside Cooperating process the interprocess communication is a primary required

Reasons for process cooperation :

- Information sharing.

- Computational speedup.

- Modularity : for example designing a system consists of modules which can work with each other to achieve tasks

- Convenience : to ensure profomance to user who is doing many different tasks.

The interprocess communication (IPC) has two fundamental principle :

- Shared memory : a region of memory is being shared by cooperating processes is established.

Then, processes can exchange information by reading and writing data to the shared region

- Message passing : here the communication takes place by means of messages exchanged between cooperating processes.

Then, they can exchange messages using the kernel (one sends a message to the kernel an it will be routed to the target process).

6) Multitasking vs Multithreading vs Multiprocessing

Multitasking : giving a time slice for each task working on (dont forget the priority) which called pre-emptive multitasking.

Multithreading : having multi threads inside a process.

Multiprocessing : having multi CPU cores inside physical CPU.

7) Introduction to Threads

Thread comprises to :

- thread ID.
- program counter.
- register set.
- stack

It shares with other threads in the same process its code section , data section, and other operating system resources
such as open files and signals.

The traditional process has only a single thread.

If a process has multiple threads it can perform more than one task at a time.

Benefits of multithreading:

- Responsiveness : multithreading allows an app to continue running even if a part of it is blocked or performign heavy load

- Resource Sharing : by default threads in the same process share memory and resources which allow application
to have several threads of activity within the same address space.

- Economy : because of the threads resource sharing on the contrary of processes creation which costly.

- Utilization of multiprocessor architecture : multithreading over a multi-CPU increase concurrency(on the same time execution).

8) What is a semaphore? How do they work? (Example in C)

