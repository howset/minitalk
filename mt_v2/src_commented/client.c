/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 17:01:08 by hsetyamu          #+#    #+#             */
/*   Updated: 2024/03/01 21:29:59 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int		g_returned; // global flag to indicate receipt of a return signal
void	alt_handler(int sig, siginfo_t *info, void *ucontext);
void	str_sender(int server_pid, const char *str);
void	c_sender(int server_pid, unsigned char c);

int	main(int argc, char *argv[])
{
	struct sigaction	s_sa;
	int					server_pid;

	if (argc != 3) // control for args
		return (ft_printf("Like this please: ./client [PID] [Message]\n"));
	server_pid = ft_atoi(argv[1]);
	if (kill(server_pid, 0) == -1 || server_pid == 0) // control for invalid PIDs
		return (ft_printf("PID invalid!\n"));
	s_sa.sa_sigaction = &alt_handler; // declare usage of alt_handler instead of sa_handler
	s_sa.sa_flags = SA_SIGINFO; // therefore flags must be activated
	sigemptyset(&(s_sa.sa_mask)); // sa_mask must be initialized, otherwise errors from valgrind
	sigaction(SIGUSR1, &s_sa, NULL); // prepare for returning signals
	sigaction(SIGUSR2, &s_sa, NULL); // not necessary since server only send back SIGUSR1
	str_sender(server_pid, argv[2]); // send string
	str_sender(server_pid, "\n"); // end sent string with a newline to make it look clean
	return (0);
}

void	alt_handler(int sig, siginfo_t *info, void *ucontext) // this is the signal handler for
{ // returning signal from server to providefeedback on the client side and to flip the global flag
	static int	i = 0; // set a static var as a counter

	(void)info; // unused
	(void)ucontext; // unused
	if (sig == SIGUSR1) // on receipt of SIGUSR1
	{
		g_returned = 1; // set the global flag to 1
		ft_printf("\rI sent sent something!! (%d bits)", ++i); // the feedback. Must be pre-increment because otherwise the end would be 1 count too many.
	}
}

void	str_sender(int server_pid, const char *str) // the function that processes the message/str
{ // basically just traverses the str for each char
	while (*str) // calls the character sender in a loop for each char in the str
	{
		c_sender(server_pid, *str); // send one char at a time
		str++;
	}
	c_sender(server_pid, '\0'); // ends the sent str with a null term
}

void	c_sender(int server_pid, unsigned char c) // the character processer
{ // goes through each bit of the char
	int	i;

	i = 7; // start the bitwise right shifting by 7 (down to 0)
	while (i >= 0)
	{
		g_returned = 0; // set the global flag to 0
		if ((c >> i) & 1) // compare the LSB of the right shift by 7(i will decrement in this loop) bitwise to 1 (using &).
			kill(server_pid, SIGUSR1); // (c >> 7 -> 1) --> (1 & 1 -> 1), this would evaluate to TRUE and send SIGUSR1
		else // if not TRUE (c >> 7 -> 0) --> (0 & 1 -> 0), then SIGUSR2
			kill(server_pid, SIGUSR2);
		while (!g_returned) // as long as g_returned is not 1 (set to 0 in this function), wait.
			; // only proceed once server to send signal back to be caught by client signal handler that would flip the flag to 1
		i--; // decrement and proceed with the loop
	}
}