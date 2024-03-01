# Minitalk

## Signals
- Sources [[1]](https://en.wikipedia.org/wiki/Signal_(IPC)) [[2]](https://www.youtube.com/watch?v=Hu2CYemkgYw) [[3]](https://www.youtube.com/watch?v=VwS3dx3uyiQ)
- Standardized messages that are sent to a running program (or process) to trigger specific behavior.
- Sent in form of a pulse/frequency of electricity in order to notify a process/program of an event that occurred.
- When signals are sent, the operating system interrupts/pauses the running processes to deliver the signal.
- There are defaults actions that are taken/performed according to what kind of signal that are sent (defined in signal.h), e.g.: (Some of these are similar, with different nuances)

| Signal 	| Shortcut			| Catchable | Notes  |
|---		|---				|---		|---|
| SIGINT 	| <kbd>Ctrl+C</kbd> | yes  		| Terminal interrupt (The contolling terminal instructs the process to terminate gracefully). SIGTERM is very similar (?).  |
| SIGTSTP 	| <kbd>Ctrl+Z</kbd> | yes  		| Terminal stop (The contolling terminal instructs the process to suspend execution and move it to the background)  |
| SIGCONT 	| <kbd>fg</kbd>  	| yes  		| Resume execution (<kbd>bg</kbd> to send back to background)  |
| SIGQUIT 	| <kbd>Ctrl+\\</kbd>| yes  		| Quit the process (The contolling terminal instructs the process to quit and perform a core dump).  |
| SIGSTOP 	|   				| no  		| Stop executing (Handled by the kernel not OS.)  |
| SIGKILL 	|   				| no  		| Terminate immediately (Handled by the kernel not OS.). The receiving process cannot perform any clean-up upon receiving this signal.  |
- Some of the response to these signals can be modified by a custom handler. This handler can be defined in either `signal()` or `sigaction()` system call.
- We can **NOT** create our own signals. The response to a (standardised) signal & the meaning of it, however, can be changed.

## `sigaction()`

- Sources [[1]](https://en.wikipedia.org/wiki/Sigaction) [[2]](https://pubs.opengroup.org/onlinepubs/9699919799/functions/sigaction.html) [[3]](https://man7.org/linux/man-pages/man2/signal.2.html) [[4]](https://www.youtube.com/watch?v=_1TuZUbCnX0) [[5]](https://www.youtube.com/watch?v=VwS3dx3uyiQ)
- Avoid the use of `signal()` and use `sigaction()` instead.
- In `<signal.h>` 
```
# define _XOPEN_SOURCE 700
# include <signal.h>
```
- The structure according to POSIX standard should contain at least the following fields:
```c
struct sigaction {
	void         (*sa_handler)(int);      //address of signal handler 
	sigset_t     sa_mask;                 //additional signals to block
	int          sa_flags;                //signal options
	void         (*sa_sigaction)(int, siginfo_t *, void*); //alternate signal handler
};
```
### sa_handler
- The `sa_handler` member specifies the address of a function to be called when the process receives the signal. The signal number is passed as an integer argument to this function.
- Only one signal handler must be specified, either `sa_handler` or `sa_sigaction`. If it is desired to use `sa_sigaction`, `SA_SIGINFO` flag must be set. 

### sa_mask
- The `sa_mask` member specifies additional signals to be blocked during the execution of signal handler. 
- Must be initialized with `sigemptyset(3)`. 
- Specify here the signals that would be blocked during the execution of the handler function.
- The signals are held in place until the handler function is done executing, then it will be delivered.
- Multiple signals of the same type are/may be combined.
- Maybe better imagined as delaying a signal instead of blocking.

### sa_flags
- The `sa_flags` member specifies some additional flags. 
- Setting the flag `SA_SIGINFO` tells the kernel to call the alternate signal handler (`sa_sigaction`) instead of the default (`sa_handler`)

### sa_sigaction
- `sa_sigaction` is an alternate signal handler with different set of parameters. 
- The `int` parameter is the signal number.
- The `siginfo_t` struct pointer will contain info such as which process sent the signal once `sa_sigaction` is invoked.
- The `void*` pointer allows to pass in a context (obsolete, non-POSIX construct to manage user threads.). Just use NULL. 

## `kill()`
- Sources[[1]](https://www.csl.mtu.edu/cs4411.ck/www/NOTES/signal/raise.html) [[2]](https://www.csl.mtu.edu/cs4411.ck/www/NOTES/signal/kill.html)
- A general command used to send a signal to a process in UNIX. (aside from `raise()`)
- A termination signal is the default (SIGTERM).
- `pid_t pid = getpid();` (`#include <sys/types.h>`)
- `int kill(pid_t pid, int sig);` (`#include <signal.h>`)

## `sleep()` and `pause()`
- `sleep()` -> do nothing, cant respond to signals
- `pause()` -> do nothing, but can catch signals.

## Bitwise operators
- Source [[1]](https://www.geeksforgeeks.org/bitwise-operators-in-c-cpp/)

## RTFM
- signal(7)
- sigaction
- kill
- usleep
- pause

## Flow
- Due to reccommendation in the internet, use `sigaction()` instead of `signal()`.
- Can only use `kill()` to send signals hence the use of alternate signal handler in sigaction because `SA_SIGINFO` can then contain `si_pid` and `si_uid`.

## Valgrind shortcut to copy-paste
```
cc -Wall -Werror -Wextra -g -I./src ./src/server.c ./lib/libft.a -o server && valgrind --tool=memcheck -q --leak-check=full --show-leak-kinds=all -s --track-origins=yes ./server | cat -e
```

```
cc -Wall -Werror -Wextra -g -I./src ./src/client.c ./lib/libft.a -o client && valgrind --tool=memcheck -q --leak-check=full --show-leak-kinds=all -s --track-origins=yes ./client 116193 "test"| cat -e
```

## Content
```
Minitalk
├── lib
│   ├── src
│   │   ├── ft_printf
│   │   │   ├── ft_printf_c.c
│   │   │   ├── ft_printf_di.c
│   │   │   ├── ft_printf_hex.c
│   │   │   ├── ft_printf_p.c
│   │   │   ├── ft_printf_s.c
│   │   │   ├── ft_printf_u.c
│   │   │   ├── ft_printf.c
│   │   │   └── ft_printf.h
│   │   ├── get_next_line
│   │   │   ├── get_next_line_bonus.c
│   │   │   ├── get_next_line_bonus.h
│   │   │   ├── get_next_line_utils_bonus.c
│   │   │   ├── get_next_line_utils.c
│   │   │   ├── get_next_line.c
│   │   │   └── get_next_line.h
│   │   └── libft
│   │       ├── ft_atoi.c
│   │       ├── ft_[everything else].c
│   │       └── libft.h
│   └── Makefile
├── src
│   ├── client.c
│   ├── minitalk.h
│   └── server.c
└── Makefile
```
