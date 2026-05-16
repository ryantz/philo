*This project has been created as part of the 42 curriculum by ryatan.*

# Philosophers

## Description

A simulation of the classic **Dining Philosophers Problem** — a concurrency problem formulated by Edsger Dijkstra in 1965.

One or more philosophers sit around a round table with a bowl of spaghetti in the middle. There are as many forks as philosophers, one between each pair. A philosopher must pick up both their left and right fork to eat. After eating they sleep, then think, then try to eat again. The simulation ends when a philosopher dies of starvation, or when all philosophers have eaten a required number of times.

The goal of the project is to implement this simulation in C using **POSIX threads** and **mutexes**, without any data races or deadlocks.

Key concepts practiced:
- Creating and managing threads with `pthread_create` / `pthread_join`
- Preventing data races with `pthread_mutex_lock` / `pthread_mutex_unlock`
- Avoiding deadlock using consistent fork acquisition ordering
- Precise timing with `gettimeofday` and busy-wait sleep

## Instructions

### Compilation

```bash
make
```

### Usage

```bash
./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep]
./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat]
```

All time values are in **milliseconds**.

| Argument | Description |
|---|---|
| `number_of_philosophers` | Number of philosophers (and forks) at the table |
| `time_to_die` | Time in ms before a philosopher dies if they haven't started eating |
| `time_to_eat` | Time in ms a philosopher spends eating |
| `time_to_sleep` | Time in ms a philosopher spends sleeping |
| `number_of_times_each_philosopher_must_eat` | Optional — simulation stops when all philosophers have eaten this many times |

### Examples

```bash
# 5 philosophers, none should die
./philo 5 800 200 200

# 5 philosophers, simulation stops after each has eaten 7 times
./philo 5 800 200 200 7

# 1 philosopher, should die at ~800ms
./philo 1 800 200 200

# 4 philosophers, one should die
./philo 4 310 200 100
```

### Output format

Each state change is logged as:

```
timestamp_in_ms philosopher_id has taken a fork
timestamp_in_ms philosopher_id is eating
timestamp_in_ms philosopher_id is sleeping
timestamp_in_ms philosopher_id is thinking
timestamp_in_ms philosopher_id died
```

### Makefile rules

| Rule | Description |
|---|---|
| `make` | Compile the project |
| `make clean` | Remove object files |
| `make fclean` | Remove object files and binary |
| `make re` | Recompile from scratch |

## Technical Choices

**Deadlock prevention** — Philosophers with even IDs pick up their left fork first; odd IDs pick up their right fork first. This breaks the circular wait condition. Even-numbered philosophers are also staggered by 1ms at startup to reduce initial contention.

**Precise sleeping** — Instead of relying on `usleep` alone (which can oversleep by several ms), a busy-wait loop checks the current time every 100 microseconds against the target wake time. This keeps timing accurate enough for tight `time_to_die` values.

**Death detection** — A dedicated monitoring thread checks each philosopher's last meal time every 1ms. When a philosopher's starvation time is exceeded, the monitor sets a shared `stop` flag under a mutex and prints the death message atomically under the print mutex to prevent any other output from appearing after death.

**Thread lifecycle** — Philosopher threads are joined after the monitoring thread exits, ensuring clean shutdown without detached threads or resource leaks.

## Resources

### Documentation & References

- [`pthread_mutex_lock` man page](https://man7.org/linux/man-pages/man3/pthread_mutex_lock.3p.html)
- [`gettimeofday` man page](https://man7.org/linux/man-pages/man2/gettimeofday.2.html)

### AI Usage

Claude (Anthropic) was used during this project as a review tool. Specifically:

- **Conceptual explanation** — clarifying why even/odd fork ordering prevents deadlock and how the stagger technique reduces contention
