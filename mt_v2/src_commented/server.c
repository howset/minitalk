/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 17:01:04 by hsetyamu          #+#    #+#             */
/*   Updated: 2024/03/01 23:01:18 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	alt_handler(int sig, siginfo_t *info, void *ucontext);

int	main(void)
{
	struct sigaction	s_sa = {0};

	ft_printf("Server PID [%d]\n",getpid()); // print PID to term
	ft_printf("I now wait wait wait for signal!\n");
	s_sa.sa_sigaction = &alt_handler; // declare usage of alt_handler instead of sa_handler
	s_sa.sa_flags = SA_SIGINFO; // therefore flags must be activated
	sigemptyset(&(s_sa.sa_mask)); // sa_mask must be initialized, otherwise errors from valgrind
	sigaction(SIGUSR1, &s_sa, NULL); // prepare for incoming signals
	sigaction(SIGUSR2, &s_sa, NULL); // prepare for incoming signals
	while (1) // now we wait for signal from client
		pause();
	return (0);
}

void	alt_handler(int sig, siginfo_t *info, void *ucontext)
{
	static char	c; // for the character
	static int	i; // just a counter. both static to keep content during repeated calls.

	(void)ucontext; // unused
	if (sig == SIGUSR1) // if SIGUSR1
		c = c | 1; //assign the LSB of c to 1 (will definitely be 1) 
	i++; // increment the counter. If SIGUSR2, just increment without setting any bit of c to 1 (stays 0)
	if (i == 8) // until 8 (one char is 8 bits)
	{
		write(1, &c, 1); // write c
		i = 0; // set counter back to 0
		c = 0; // set c back to 0
	}
	c = c << 1; // shift left 1 bit for next iteration
	if (kill(info->si_pid, SIGUSR1) == -1) // control seq that serves also to send SIGUSR1 back to client
		exit(ft_printf("Error sending signal\n"));
}
