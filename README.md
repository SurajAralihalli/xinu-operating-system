# XINU Operating System

## Lab1

This Git repo contains my lab assignment for Lab1, which aimed to familiarize me with the steps involved in compiling and running XINU in our lab. In this lab, I gained experience with basic ABI programming and learned how to use it as a building block for subsequent lab assignments.

## Lab2

This Git repo contains my lab assignment for Lab2, which focused on extending XINU system calls into trapped system calls using x86 hardware support. In this lab, I also learned how to monitor CPU usage of processes and their dependence on dynamic process behavior.

## Lab3

This Git repo contains my lab assignment for Lab3, which aimed to extend XINU's fixed priority scheduling to dynamic priority scheduling. The objective of this lab was to facilitate fair allocation of CPU cycles to processes through monitoring of process behavior. I learned how to compensate I/O-bound processes that voluntarily relinquish CPU with unspent quantum remaining by improving their responsiveness. In addition, I gained knowledge of utilizing a data structure called multilevel feedback queue, used UNIX Solaris, which is an industrial-grade OS to achieve constant overhead scheduling independent of the number of processes in the system. Lastly, I learned how to implement a method for starvation prevention to ensure that CPU-bound processes do not starve in an operating environment of over-abundance of I/O-bound processes.

## Lab4

This Git repo contains my lab assignment for Lab4, which had two-fold objectives. First, it aimed to support asynchronous event handling via user callback functions. Second, I learned how to utilize synchronization/coordination primitives to implement a preemptible, reentrant XINU upper half that supports message passing IPC. In this lab, I also learned how to use ROP to manipulate the runtime stack and dynamically reroute kernel and user code execution flow.

## Lab5 and Lab6

This Git repo contains my lab assignments for Lab5 and Lab6, which aimed to enable paging on the x86 Galileo backends by setting the PG bit of CR0 to 1 to support virtual memory. In these labs, I learned how to implement demand paging so that pages may be temporarily stored on swap space to conserve main memory. I also learned how to manage what is stored in the frames, which are containers where the content of pages is stored. From a process viewpoint, I learned how to export an illusion that a process owns the entire 32-bit address space of a Galileo backend. From a programmer's viewpoint, I learned how to export system calls that allow a process to perform dynamic memory allocation using a per-process virtual memory heap. The original shared heap maintained as a free list that getmem() and freemem() operated on was also preserved, and new system calls were introduced to allow memory to be dynamically allocated from per-process virtual memory heaps.


