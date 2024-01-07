For the actual readme.md go to the master branch.

### ABOUT THE PROJECT
Here you have an implementation of a feedback scheduler, created for a university project in the operating systems course.

Team members: 

Nicolò Trebino

Federico Garau

# DOCUMENTATION
## SOLUTION
We decided to implement a feedback scheduler that replaces the original priority-based scheduler. The feedback scheduler that we implemented makes all the threads created with the “thread_create” function with a fixed priority of 2, the only exceptions are for the Main and the Idle threads. The Main has the highest priority (1) and the Idle has the lowest (15), and the queue of their priority works as a FIFO algorithm (notice that it has no sense to create a thread with priority 15 because it won’t be executed because of the Idle thread is an infinite loop), all the other threads will start with a priority of 2 in the queue of priority 2, and after the time quantum, set to 0,5s, they will be moved into the queue of priority 3, and with the “thread_yield_higher()” the thread will yield only if there is another thread with a higher priority (lower number is a higher priority). After reaching the third and last queue of our feedback scheduler (so the queue with priority 4), if there is no higher priority thread, the scheduler will use a Round-Robin algorithm between the threads in the queue with priority 4. For testing, we have created the main.c, located in the: /RIOT_OS/examples/FBTester/main.c.
We created 5 different threads named A, B, C, D, and E with different service times.
With the defined global constant QUANTUM (milliseconds) you can set the time interval between every print of the specified thread.
Here you have some output examples with different values of QUANTUM.

QUANTUM 100
<img src="https://raw.githubusercontent.com/nicolotrebino/RIOT/scheduler_feedback/project_documentation/img1.png" alt="QUANTUM100">


QUANTUM 500
<img src="https://raw.githubusercontent.com/nicolotrebino/RIOT/scheduler_feedback/project_documentation/img2.png" alt="QUANTUM500">

## IMPLEMENTATION CHOICES
We wanted to keep the RIOT OS structure as clean as possible and make our changes only to be a module that you can use or not use, we achieved this using functions already implemented in the operating system, like sched_change_priority() and/or the “#if ” directive to enable some modification only if the module “MODULE_SCHED_FEEDBACK” is used. We added only two important files in the RIOT source code: the sched_feedback.h and the sched_feedback.c, both located in the sys folder (obviously we have also created all the Makefiles to be able to compile and run our application correctly through our new scheduler). In the sched_feedback.h we have defined only the timer used for the new scheduler and the sched_feedback_init, the function used to initialize the feedback scheduler.
In the sched_feedback.c we have implemented the sched_feedback_init and we also implemented three important and different functions:
- sched_feedback_set → which sets the feedback scheduler if it’s necessary
- sched_runq_callback → which checks if the priority of the active thread is the right
priority and it decides what to do based on the priority of the active thread passed as
a parameter.
- sched_feedback_cb → this function is called every tick of the timer (we used the ztimer to implement it) and it decides what to do based on the priority of the active thread.
Some parts of the code are commented for a better understanding of the behavior of the scheduler.

## INSTRUCTION FOR BUILDING, EXECUTING AND TESTING
Building our application is easy. 
A Linux machine is required, so you can proceed in two different ways:
- Codespace*

  Create a codespace into this repository and you will already be ready to follow the steps below.
- Linux machine

  Download or clone this repository on your Linux device and, with the terminal, browse into the repository folder.

You should be in the RIOT/ directory, from here you can follow the following commands step by step:

```console
sudo apt update
```

```console
sudo apt upgrade
```

Install all required packages
```console
sudo apt install git gcc-arm-none-eabi make gcc-multilib libstdc++-arm-none-eabi-newlib openocd gdb-multiarch doxygen wget unzip python3-serial
```

Go into the folder where the application to test the new scheduler is located
```console
cd examples/FBTester
```

Compile and run
```console
make all term
```

## TEST THE DIFFERENCES
<img src="https://raw.githubusercontent.com/nicolotrebino/RIOT/scheduler_feedback/project_documentation/img3.png" height="350" alt="NOFB">

To test the differences with the standard scheduler you can also try to use the standard scheduler already implemented in RIOT with this command instead of the last one:
“NOFB=1 make all term”.
Here on the left side, you can find the output: NOFB = 1 with QUANTUM set to 1000

If you are only interested in the code we added you can check out this commit:

[Scheduler feedback](https://github.com/nicolotrebino/RIOT/commit/58ab5a682f7adce0e7dbcdf462311fb541771afa)

Or check the patch file:

[Patch file](project_documentation/RIOTpatch.patch)


\* A GitHub codespace is a cloud-based development environment that allows you to write, run, and test code directly in the browser or your preferred development environment. It's a virtualized instance of a complete development environment with all the necessary dependencies and configurations.
