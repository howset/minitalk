/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 18:17:21 by hsetyamu          #+#    #+#             */
/*   Updated: 2024/02/29 22:55:57 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	alt_handler(int sig, siginfo_t *info, void *unused);

int	main(void)
{
	struct sigaction	s_sa = {.sa_sigaction = alt_handler}; // avoid uninitialised byte error. replaces all of the current code plus does the proper initialization (if one or more struct members are explicitly initialized, the others will be initialized to 0).

	ft_printf("Server PID [%d]\n",getpid()); // show getpid()
	ft_printf("I now wait wait for signal!\n");
	s_sa.sa_flags = SA_SIGINFO; // mark to use an alt handler
	s_sa.sa_sigaction = alt_handler;
	sigaction(SIGUSR1, &s_sa, NULL); // when SIGUSR1 comes, do the alt handler
	sigaction(SIGUSR2, &s_sa, NULL); // when SIGUSR2 comes, the same as above
	while (1) // now wait
		pause(); 
	return (0);
}

void	alt_handler(int sig, siginfo_t *info, void *ucontext)
{
	static unsigned char	c = 0; // or maybe c = 0x00 (?)
	static int				i = 0;
	static pid_t			client_pid = 0;

	(void)ucontext;
	if (!client_pid) // set client_pid from SA_SIGINFO (the struct from sa_flags)
		client_pid = info->si_pid;
	c |= (sig == SIGUSR1); // set c as 1 if sig == SIGUSR1. bitwise OR assignment operator
	if (++i == 8)
	{
		i = 0;
		if (c == 0)
		{
			client_pid = 0;
			return ;
		}
		ft_putchar_fd(c, 1);
		c = 0;
		//ft_printf(" A\n");
		kill(client_pid, SIGUSR1); // feedback?
	}
	else
	{
		c <<= 1; // bitwise left shift operation
		//ft_printf(" B\n");
		kill(client_pid, SIGUSR2); // feedback?
	}
}
