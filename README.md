# Wireless Spectrum Allocation and Interference Monitoring System

## Project Overview

This project simulates a wireless communication system where multiple devices request spectrum (channels and bandwidth) from a central Spectrum Manager. The system dynamically allocates channels and detects interference when multiple devices request the same channel. If interference occurs, the system reallocates a new channel.

---

## Features

* Multi-process simulation using `fork()`
* Inter-process communication using `pipe`
* Shared memory for storing spectrum allocation
* Semaphore for synchronization
* Thread-based device simulation using `pthread`
* Signal handling using `SIGINT` (Ctrl + C)
* File logging using system calls

---

## System Architecture

Devices (Processes) → Pipe → Spectrum Manager → Shared Memory + Semaphore → Channel Allocation → Log File

---

## Technologies Used

* C Programming
* Linux System Calls
* POSIX Threads (pthreads)
* IPC Mechanisms

---

## System Calls Used

* `fork()` → process creation
* `pipe()` → communication
* `shmget(), shmat()` → shared memory
* `semget(), semop()` → semaphore
* `signal()` → signal handling
* `open(), write(), close()` → file handling

---

##  Project Structure

MiniProject/
│
├── sourcefile/
│   ├── main.c
│   ├── device.c
│   ├── semaphore.c
│   ├── log.c
│   ├── signal.c
│
├── includefile/
│   ├── device.h
│   ├── semaphore.h
│   ├── log.h
│   ├── mysignal.h
│
├── Makefile
└── README.md

---

##  How to Compile

make all

---

## How to Run

make run

---

##  Sample Output

Device 1 → BW=5 MHz, Signal=70 dBm
Manager: Channel 1 given

Device 2 → BW=10 MHz, Signal=60 dBm
Manager: Interference on Channel 1 between Device 1 and Device 2
Manager: Channel 2 reallocated

---

## Signal Handling

Press **Ctrl + C** to stop the system gracefully using SIGINT.

---

##  Log File

The system generates a file:
log.txt

which stores final channel allocation results.

---

##  Learning Outcomes

* Understanding Linux system calls
* Process and thread management
* Inter-process communication (IPC)
* Synchronization using semaphore
* Handling concurrency issues

---

##  Author

Avishkar More

