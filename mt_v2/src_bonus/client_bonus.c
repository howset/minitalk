/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 17:01:08 by hsetyamu          #+#    #+#             */
/*   Updated: 2024/03/01 21:27:35 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

int		g_returned;
void	alt_handler(int sig, siginfo_t *info, void *ucontext);
void	str_sender(int server_pid, const char *str);
void	c_sender(int server_pid, unsigned char c);

int	main(int argc, char *argv[])
{
	struct sigaction	s_sa;
	int					server_pid;

	if (argc != 3)
		return (ft_printf("Like this please: ./client [PID] [Message]\n"));
	server_pid = ft_atoi(argv[1]);
	if (kill(server_pid, 0) == -1 || server_pid == 0)
		return (ft_printf("PID invalid!\n"));
	s_sa.sa_sigaction = &alt_handler;
	s_sa.sa_flags = SA_SIGINFO;
	sigemptyset(&(s_sa.sa_mask));
	sigaction(SIGUSR1, &s_sa, NULL);
	str_sender(server_pid, argv[2]);
	str_sender(server_pid, "\n");
	return (0);
}

void	alt_handler(int sig, siginfo_t *info, void *ucontext)
{
	static int	i = 0;

	(void)info;
	(void)ucontext;
	if (sig == SIGUSR1)
	{
		g_returned = 1;
		ft_printf("\rI sent sent something!! (%d bits)", ++i);
	}
}

void	str_sender(int server_pid, const char *str)
{
	while (*str)
	{
		c_sender(server_pid, *str);
		str++;
	}
	c_sender(server_pid, '\0');
}

void	c_sender(int server_pid, unsigned char c)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		g_returned = 0;
		if ((c >> i) & 1)
			kill(server_pid, SIGUSR1);
		else
			kill(server_pid, SIGUSR2);
		while (!g_returned)
			;
		i--;
	}
}
