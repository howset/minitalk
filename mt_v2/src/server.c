/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 17:01:04 by hsetyamu          #+#    #+#             */
/*   Updated: 2024/03/03 11:15:58 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	alt_handler(int sig, siginfo_t *info, void *ucontext);

int	main(void)
{
	struct sigaction	s_sa;

	ft_printf("Server PID [%d]\n", getpid());
	ft_printf("I now wait wait wait for signal!\n");
	s_sa.sa_sigaction = &alt_handler;
	s_sa.sa_flags = SA_SIGINFO;
	sigemptyset(&(s_sa.sa_mask));
	sigaction(SIGUSR1, &s_sa, NULL);
	sigaction(SIGUSR2, &s_sa, NULL);
	while (1)
		pause();
	return (0);
}

void	alt_handler(int sig, siginfo_t *info, void *ucontext)
{
	static char	c;
	static int	cnt;

	(void)ucontext;
	if (sig == SIGUSR1)
		c = c | 0x01;
	cnt++;
	if (cnt == 8)
	{
		write(1, &c, 1);
		cnt = 0;
		c = 0;
	}
	c = c << 1;
	kill(info->si_pid, SIGUSR1);
}
