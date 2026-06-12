*This project has been created as part of the 42 curriculum by faiello.*

# Dining Philosophers

## Description

This project implements the classic Dining Philosophers concurrency problem using POSIX threads and mutexes in C. The goal is to simulate philosophers who alternate between thinking, eating, and sleeping while sharing forks. The implementation focuses on avoiding deadlock and starvation while respecting the 42 coding norms.

## Instructions

### Compilation

From the project root:

```bash
make
```

### Execution

Run the program with the following arguments:

```bash
./philo num_philosophers time_to_die time_to_eat time_to_sleep [num_meals]
```

- `num_philosophers`: number of philosophers and forks
- `time_to_die`: maximum time in milliseconds without eating
- `time_to_eat`: time in milliseconds to eat
- `time_to_sleep`: time in milliseconds to sleep
- `num_meals` (optional): number of meals each philosopher must eat before exiting

### Makefile targets

```bash
make        # build the executable
make clean  # remove object files
make fclean # remove object files and executable
make re     # clean and rebuild
```

## Resources

- "Dining Philosophers Problem" - classic concurrency problem in operating systems
- POSIX threads documentation - `pthread_create`, `pthread_mutex_lock`, `pthread_mutex_unlock`
- 42 Network and Norminette coding standard references

### AI usage

AI assistance was used to:
- organize and refine the README content
- ensure the project documentation and instructions are clear
- confirm compliance with the requested README structure

No core project logic or implementation was rewritten by AI; only the documentation was improved.

## Project structure

- `main.c` - program entry, argument validation, thread creation and joining
- `utils.c` - timing, printing, and shared state utilities
- `init.c` - initialization and cleanup of data structures and mutexes
- `fork.c` - fork acquisition and release functions
- `philo.c` - philosopher routine and main behavior loop
- `philo_cycle.c` - philosopher cycle actions separated for norm compliance
- `philo_forks.c` - fork-taking helper functions
- `monitor.c` - death monitoring and stopping conditions
- `philosophers.h` - shared types and function prototypes
- `Makefile` - build rules

## Example usage

```bash
./philo 5 800 200 200
./philo 5 800 200 200 7
./philo 1 800 200 200
```

## Notes

- The implementation avoids deadlock by alternating fork acquisition order for even and odd philosophers.
- Output is protected by a print mutex to avoid interleaved messages.
- A death flag is shared safely using mutex protection.

## Norminette check

Run:

```bash
norminette *.c *.h
```

The README is now in English and follows the required structure for 42 projects.

