# Philosophers

# Learning ladder

1) waitpid
2) visual forking
3) intro to process and thread :

Any program is converted to a binary code instructions according to the CPU, we shorthand the binary to hex code stored in the RAM memeory.

Then, the CPU reads and puts them into a queue which called (pipeline) and gets executed by CPU components.

Thread is the unit of execution (a set of instructions)

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