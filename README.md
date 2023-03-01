# CS503
Operating Systems


## Lab1
The objectives of the first lab assignment are to familiarize you with the steps involved in compiling and running XINU in our lab, and practice basic ABI programming that will be used as a building block in subsequent lab assignments.

## Lab2 

The objectives of this lab are to extend XINU system calls -- which are regular C function calls -- into trapped system calls using x86 hardware support. We will also monitor CPU usage of processes and its dependence on dynamic process behavior.

## Lab3

The objective of this lab is to extend XINU's fixed priority scheduling to dynamic priority scheduling that facilitates fair allocation of CPU cycles to processes. Through monitoring of process behavior we aim to compensate I/O-bound processes that voluntarily relinquish CPU with unspent quantum remaining by improving their responsiveness. That is, from the time an I/O-bound process that blocked becomes ready until when it becomes current is reduced in comparison to CPU-bound processes. The resultant resource consumption profile where CPU-bound processes beget more CPU cycles but incur longer response time relative to I/O-bound processes is the kernel's interpretation of "fairness." In addition to dynamically adjusting process priority to affect fairness, our scheduler needs to be efficient. We will utilize a data structure, called multilevel feedback queue, used UNIX Solaris which is an industrial grade OS to achieve constant overhead scheduling independent of the number of processes in the system. Lastly, TS scheduling employed by commodity operating systems implement heuristic methods that do not guarantee that CPU- bound processes will not starve in an operating environment of over-abundance of I/O-bound processes. We will implement a method for starvation prevention.

## Lab4

The objective of this lab is two-fold. First, support asynchronous event handling via user callback functions. Second, utilize synchronization/coordination primitives to implement a preemptible, reentrant XINU upper half that supports message passing IPC. Both make use of ROP to manipulate the runtime stack and dynamically reroute kernel and user code execution flow.

## Lab5 and Lab6

We will enable paging on the x86 Galieo backends by setting the PG bit of CR0 to 1 to support virtual memory which, in turn, will be combined with demand paging so that pages may be temporarily stored on swap space to conserve main memory. A region of physical main memory will be used to hold pages belonging to the virtual address space of processes. Swap space, referred to as backing store in XINU, is typically implemented as part of the file system of a local disk. In XINU, backing store support is provided as a remote (i.e., networked) disk on a x86 frontend machine in the XINU Lab. Due to network delay swapping pages between Galileo's main memory and remote disk is very slow. In lab5 we will implement backing store as a region of physical main memory. If the region in physical main memory where pages are held becomes full, the backing store is used to accommodate the overflow.

From the kernel's viewpoint, main memory is organized into blocks of fixed size (4 KB) called frames where code and data, including kernel data structures and per-process heap memory, are kept. It is up to paging enabled XINU to manage what is stored in the frames which are containers where the content of pages are stored. From a process viewpoint, the kernel exports an illusion that a process owns the entire 32-bit address space of a Galileo backend. From a programmer's viewpoint, XINU will export system calls that allow a process to perform dynamic memory allocation using a per-process virtual memory heap. The original shared heap maintained as a free list that getmem() and freemem() operated on will be preserved. New system calls will allow memory to be dynamically allocation from per-process virtual memory heaps.


