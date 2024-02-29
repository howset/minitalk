/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 18:17:21 by hsetyamu          #+#    #+#             */
/*   Updated: 2024/02/28 18:38:39 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	sigusr_handler(int signo, siginfo_t *siginfo, void *ucontext);

int	main(void)
{
	struct sigaction	stc_sa; // declare a struct for sigaction named stc_sa

	stc_sa.sa_flags = SA_SIGINFO; // specify flags as SA_SIGINFO to use alternate signal handler
	stc_sa.sa_sigaction = &sigusr_handler; // alternate signal handler
	sigemptyset(&stc_sa.sa_mask); // Must be initialized by sigemptyset.
	sigaddset(&stc_sa.sa_mask, SIGUSR1); // SIGUSR1 will be blocked while the signal handler is executing.
	sigaddset(&stc_sa.sa_mask, SIGUSR2); // as well, SIGUSR2.
	if ((sigaction(SIGUSR1, &stc_sa, NULL)) == -1)  // control seq if error
		ft_printf("Error sigaction\n");
	if ((sigaction(SIGUSR2, &stc_sa, NULL)) == -1)
		ft_printf("Error sigaction\n");
	ft_printf("Server work work and now wait wait\n"); // print message
	ft_printf("PID is: %d\n", getpid());
	while (1) // now wait until there is signal. break out by SIGINT
		pause();
	return (0);
}

void	sigusr_handler(int sig, siginfo_t *info, void *ucontext)
{
	static unsigned char		lett = 0;
	static int					i = 0; // counter

	(void)ucontext; // unused
	if (sig == SIGUSR1)
		lett |= (1 << i);
	i++;
	if (i == 8)
	{
		ft_putchar_fd(lett, 1);
		i = 0;
		lett = 0;
		if (kill(info->si_pid, SIGUSR1) == -1)
			ft_printf("Error signal");
	}
}
