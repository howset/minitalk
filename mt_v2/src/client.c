/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 17:01:08 by hsetyamu          #+#    #+#             */
/*   Updated: 2024/03/01 17:40:29 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_bit_received;
void	send_string(int pid, const char *str);
void	send_char(int pid, unsigned char c);
void	send_bit(int pid, int bit);
void	alt_handler(int sig, siginfo_t *info, void *ucontext);

int	main(int argc, char *argv[])
{
	struct sigaction	s_sa;
	int					server_pid;

	if (argc != 3)
		return(ft_printf("Exactly like this please: ./client [PID] [Message]\n"));
	server_pid = ft_atoi(argv[1]);
	if (kill(server_pid, 0) == -1 || server_pid == 0)
		return(ft_printf("PID invalid!\n"));
	s_sa.sa_sigaction = &alt_handler;
	s_sa.sa_flags = SA_SIGINFO;
	send_string(server_pid, argv[2]);
	send_string(server_pid, "\n");
	ft_printf("String sent\n");
	return (0);
}

void	send_string(int pid, const char *str)
{
	while (*str)
		send_char(pid, *str++);
	send_char(pid, '\0');
}

void	send_char(int pid, unsigned char c)
{
	int	i;

	for (i = 7; i >= 0; i--)
	{
		g_bit_received = 0;
		send_bit(pid, (c >> i) & 1);
		while (!g_bit_received)
			;
	}
}

void	send_bit(int pid, int bit)
{
	int	signal;

	if (bit == 1)
		signal = SIGUSR1;
	else
		signal = SIGUSR2;
	if (kill(pid, signal) == -1)
		exit(ft_printf("Error sending signal\n"));
}

void	alt_handler(int sig, siginfo_t *info, void *ucontext)
{
	(void)info;
	(void)ucontext;
	if (sig == SIGUSR1)
		g_bit_received = 1;
}
