# PeerPulse

A Linux-based peer-liveness monitoring system built with modern C++.

PeerPulse explores how servers monitor the availability of remote peers using heartbeat messages over TCP, with a focus on socket programming, failure detection, and reliable connection management.

## Goals

- Implement TCP client-server communication using Linux sockets.
- Build an application-level heartbeat mechanism.
- Detect peer timeouts and handle disconnections.
- Explore failure detection and recovery strategies.
- Experiment with non-blocking I/O and scalable event-driven networking.

## Tech Stack

- **Language:** C++
- **Platform:** Linux
- **Networking:** TCP/IP sockets
- **Build System:** CMake

## Project Status

Under development.

The initial milestone is to establish TCP communication between two independent C++ programs. Heartbeat monitoring and failure detection will be added incrementally.

## Planned Experiments

- TCP heartbeat vs. TCP keepalive
- TCP vs. UDP heartbeat
- Blocking vs. non-blocking sockets
- `poll()` vs. `epoll()`
- Monitoring multiple peer connections
- Failure detection latency and false positives

## License

License to be decided.