/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_real.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 18:17:16 by hsetyamu          #+#    #+#             */
/*   Updated: 2024/03/01 15:23:51 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	alt_handler(int sig, siginfo_t *info, void *unused);
void	send_bit(char *s, pid_t pid);
void	connection_terminate(pid_t server_pid);

int	main(int argc, char **argv)
{
	//struct sigaction	s_sa;

	if (argc != 3) //
	{
		ft_printf("Exactly like this please: ./client [PID] [Message]");
		return (1);
	}
	if (!ft_strlen(argv[2])) // if no string to send
		exit(0); // just exit
	//s_sa.sa_flags = SA_SIGINFO; // signify an alt handler
	//s_sa.sa_sigaction = alt_handler;
	//sigaction(SIGUSR1, &s_sa, 0);
	//sigaction(SIGUSR2, &s_sa, 0);
	ft_printf("Sending Bytes   : %d\n", ft_strlen(argv[2]));
	send_bit(argv[2], ft_atoi(argv[1]));
	// while (1)
	// 	pause();
	return (0);
}
// void	alt_handler(int sig, siginfo_t *info, void *ucontext)
// {
// 	static int	recv_bytes = 0;

// 	(void)info;
// 	(void)ucontext;
// 	if (sig == SIGUSR1)
// 	{
// 		ft_printf("\rReceive Back : ", 1); // \r means carriage return, moves the cursor to the beginning of the line, allowing subsequent characters to overwrite existing content on that line.
// 		ft_putnbr_fd(++recv_bytes, 1);
// 	}
// 	send_bit(0, 0);
// }

void	send_bit(char *s, pid_t pid)
{
	static int				i = 8;
	static unsigned char	c;
	static char				*str;
	static pid_t			server_pid;

	if (s)
	{
		str = s;
		server_pid = pid;
		c = *str;
	}
	if (!i)
	{
		i = 8;
		c = *(++str);
		if (!c)
			connection_terminate(server_pid);
	}
	if (c && c >> --i & 0x01)
		kill(server_pid, SIGUSR1);
	else if (c)
		kill(server_pid, SIGUSR2);
}

void	connection_terminate(pid_t server_pid)
{
	int	i;

	i = 8;
	while (i--)
	{
		usleep(50);
		kill(server_pid, SIGUSR2);
	}
	exit(0);
}
