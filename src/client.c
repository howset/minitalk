/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 18:17:16 by hsetyamu          #+#    #+#             */
/*   Updated: 2024/02/28 18:44:28 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_bit(int pid, char *msg);
void	handler(int signo, siginfo_t *siginfo, void *ucontext);
void	bit_by_bit(int pid, int bit);

int	main(int argc, char **argv)
{
	if (argc == 3)
		send_bit(ft_atoi(argv[1]), argv[2]); // to do, put atoi in send_bit
	else
		return(ft_printf("Only 3 args accepted.\n"));
	return (0);
}

void	send_bit(int pid, char *msg)
{
	struct sigaction	stc_sa;
	siginfo_t			siginfo;
	int					i;

	stc_sa.sa_flags = SA_SIGINFO;
	stc_sa.sa_sigaction = &handler;
	sigemptyset(&stc_sa.sa_mask);
	sigaction(SIGUSR1, &stc_sa, 0);
	siginfo.si_pid = pid;
	i = 0;
	while (msg[i] != '\0')
	{
		bit_by_bit(pid, msg[i++]);
	}
	//ft_printf("===Message received===\n"); //confirmation like this?? 
}

void	handler(int sig, siginfo_t *info, void *ucontext)
{
	(void)ucontext;
	(void)info;
	(void)sig;
}

void	bit_by_bit(int pid, int bit)
{
	int	counter;

	counter = 0;
	while (counter <= 7)
	{
		if ((bit >> counter) & 1)
		{
			if (kill(pid, SIGUSR1) == -1)
				ft_printf("Error signal\n");
		}
		else
		{
			if (kill(pid, SIGUSR2) == -1)
				ft_printf("Error signal\n");
		}
		counter++;
		usleep(100);
	}
}
