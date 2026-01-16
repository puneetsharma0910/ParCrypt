# Parallel File Encryptor (C++)

A high-performance parallel file encryption tool built in C++ to explore operating system fundamentals, concurrency models, and low-level I/O behavior under real workloads.

This project compares process-based and thread-based parallelism while ensuring correctness, safety, and predictable performance across thousands of files.

---

## Problem Statement

Encrypting large numbers of files sequentially underutilizes modern multi-core systems and leads to poor throughput.

This project investigates:
- How processes vs threads behave under heavy file I/O workloads
- When mmap outperforms traditional read/write system calls
- How to guarantee data correctness with concurrent workers
- What failure modes appear during parallel execution

---

## Key Features

- Parallel encryption engine using:
  - fork()-based worker processes
  - Thread-pool–based worker model
- Memory-mapped file I/O (mmap) to reduce redundant disk reads
- Shared memory IPC for fast coordination between workers
- Semaphore and mutex synchronization to prevent race conditions
- Deterministic encryption/decryption with data integrity guarantees
- Benchmarking harness for performance and correctness analysis

---

## Tech Stack

- Language: C++  
- OS Concepts: fork, mmap, shared memory, semaphores, mutexes  
- Tools: gdb, make  
- Testing: Python-based load generator

---  

## Architecture Overview

### Concurrency Models

**Process Model**
- Workers created using fork()
- Shared memory for task coordination
- Strong isolation with higher memory overhead

**Thread Model**
- Fixed-size thread pool
- Shared address space
- Lower overhead with increased synchronization complexity

### File I/O Strategy

- Files mapped into memory using mmap
- Workers operate directly on memory regions
- Eliminates repeated read/write system calls
- Improves throughput for batch workloads

---

## Synchronization & Correctness

- Semaphores control access to shared task queues
- Mutexes protect critical sections during file writes
- Explicit cleanup of shared memory and mapped regions

Concurrency issues were debugged using:
- gdb
- Syscall-level inspection
- Controlled fault injection

---

## Benchmarking & Load Testing

A Python script generates thousands of random files to simulate real workloads.

Measured metrics:
- Throughput (files/sec)
- Per-file latency
- CPU utilization
- Memory overhead
- Failure behavior under contention

Benchmarks compare:
- Process-based vs thread-based execution
- mmap vs traditional file I/O

---

## Build & Run

### Build
make

### Encrypt Files
./encryptor encrypt ./input ./output

### Decrypt Files
./encryptor decrypt ./output ./restored

### Generate Load
python3 generate_files.py --count 5000 --size 1MB

---

## Design Tradeoffs

| Decision | Benefit | Cost |
|--------|--------|------|
| fork() processes | Strong isolation | Higher memory usage |
| Threads | Lower overhead | Complex synchronization |
| mmap I/O | High throughput | Careful lifetime management |
| Shared memory | Fast IPC | Manual cleanup required |

---

## Failure Handling

- Partial writes detected and rolled back  
- Workers exit safely on encryption errors  
- Shared memory cleaned up on abnormal termination  
- Input validation prevents corrupted outputs  

---

## What This Project Demonstrates

- Practical operating systems knowledge  
- Correct use of concurrency primitives  
- Debugging real-world parallel execution bugs  
- Measuring and reasoning about system performance  
- Designing for correctness over raw speed  

---

## Future Improvements

- Configurable worker pool sizing  
- AES-NI acceleration  
- Checksum verification for encrypted outputs  
- Extended benchmarks on network file systems  

---





