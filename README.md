# Operating-System-Scheduler-with-Memory-Allocation

This repository provides an implementation for a process scheduler with memory allocation using different scheduling algorithms. The scheduler performs two main functions:

1. When receiving a signal from the process generator, it forks the process and adds it to the ready queue.
2. It chooses which process will be allocated the CPU. This happens inside `scheduling_SJF`, `scheduling_RR`, or `scheduling_HPF` according to the scheduling algorithm chosen by the user.

The implemented scheduling algorithms are:

- Shortest Job First (SJF)
- Round Robin (RR)
- Highest Priority First (HPF)

<!-- This repository also includes memory allocation functionality, which can be enabled by setting a flag in the `scheduler.c` file.

To use this scheduler, simply compile the `scheduler.c` file and run the resulting executable. The program will prompt the user to select a scheduling algorithm and provide input for the process generator. Once the scheduler is running, it will output information about the processes being executed and their state.

Please refer to the `README.md` file in the repository for more information on compiling and running the program, and for details on the implementation of each scheduling algorithm.-->
