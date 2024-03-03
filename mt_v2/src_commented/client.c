/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 17:01:08 by hsetyamu          #+#    #+#             */
/*   Updated: 2024/03/03 11:06:37 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int		g_returnflag; // global flag to indicate receipt of a return signal
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
		g_returnflag = 1; // set the global flag to 1
		ft_printf("\rI sent sent something!! (%d bits)", ++i); // the feedback. Must pre-increment because otherwise the end would be 1 count too many.
	}
}

void	sender(int server_pid, const char *str) // the function that processes the message/str
{ // basically just traverses the str for each char, then traverses each bit and kills it to server
	int				i; // bitcounter for countdown, to send from first bit to last
	unsigned char	c; // to hold each char of *str

	while (*str) // send one char at a time
	{
		i = 7; // to countdown 8 bits
		c = *str;
		while (i >= 0) // loop over the bits of c
		{
			g_returnflag = 0; // set the flag to 0, this means to wait for feedback/signal from server
			if ((c >> i) & 0x01) // shift bits by 7 (on first loop), to set the very end bit of the order as the first --> explain in slides
				kill(server_pid, SIGUSR1); // (c >> 7 -> 1) --> (1 & 1 -> 1), this would evaluate to TRUE and send SIGUSR1
			else // if not TRUE (c >> 7 -> 0) --> (0 & 1 -> 0), then SIGUSR2
				kill(server_pid, SIGUSR2);
			while (!g_returnflag) // as long as flag is not 1 (set to 0 in this function), wait.
				; // only proceed once server to send signal back to be caught by client signal handler that would flip the flag to 1
			i--; // decrement and proceed with the loop
		}
		str++; // next char please
	}
}
