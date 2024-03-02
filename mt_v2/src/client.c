/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 17:01:08 by hsetyamu          #+#    #+#             */
/*   Updated: 2024/03/02 11:18:49 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int		g_returnflag;
void	alt_handler(int sig, siginfo_t *info, void *ucontext);
void	sender(int server_pid, const char *str);

int	main(int argc, char *argv[])
{
	struct sigaction			s_sa;
	int							server_pid;
	static unsigned long int	j = 0;

	if (argc != 3)
		return (ft_printf("Like this please: ./client [PID] [Message]\n"));
	server_pid = ft_atoi(argv[1]);
	if (kill(server_pid, 0) == -1 || server_pid == 0)
		return (ft_printf("PID wrong wrong wrong!\n"));
	s_sa.sa_sigaction = &alt_handler;
	s_sa.sa_flags = SA_SIGINFO;
	sigemptyset(&(s_sa.sa_mask));
	sigaction(SIGUSR1, &s_sa, NULL);
	j = ft_strlen(argv[2]);
	ft_printf("I sent sent sent: %d chars!! (to the server)\n", j + 1);
	sender(server_pid, argv[2]);
	sender(server_pid, "\n");
	return (0);
}

void	alt_handler(int sig, siginfo_t *info, void *ucontext)
{
	(void)info;
	(void)ucontext;
	if (sig == SIGUSR1)
	{
		g_returnflag = 1;
	}
}

void	sender(int server_pid, const char *str)
{
	int				i;
	unsigned char	c;

	while (*str)
	{
		i = 7;
		c = *str;
		while (i >= 0)
		{
			g_returnflag = 0;
			if ((c >> i) & 1)
				kill(server_pid, SIGUSR1);
			else
				kill(server_pid, SIGUSR2);
			while (!g_returnflag)
				;
			i--;
		}
		str++;
	}
}
