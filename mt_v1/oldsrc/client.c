/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 18:17:16 by hsetyamu          #+#    #+#             */
/*   Updated: 2024/03/01 15:29:16 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <stdio.h>

void	alt_handler(int sig, siginfo_t *info, void *unused);
void	bit_sender(char *str, pid_t pid);
void	connection_terminate(pid_t server_pid);

int	main(int argc, char **argv)
{
	struct sigaction	s_sa = {0}; // avoid uninitialised byte error.
	pid_t			server_pid;

	if (argc != 3) //
	{
		ft_printf("Exactly like this please: ./client [PID] [Message]");
		return (1);
	}
	if (!ft_strlen(argv[2])) // if no string to send
		return (1); // exit but not success
	s_sa.sa_flags = SA_SIGINFO; // mark to use an alt handler
	s_sa.sa_sigaction = alt_handler;
	sigaction(SIGUSR1, &s_sa, 0);
	sigaction(SIGUSR2, &s_sa, 0);
	ft_printf("Sending Bytes   : %d\n", ft_strlen(argv[2]));
	server_pid = ft_atoi(argv[1]);
	bit_sender(argv[2], server_pid);
	while (1)
		pause();
	return (0);
}
void	alt_handler(int sig, siginfo_t *info, void *ucontext)
{
	static int	ret_byte = 0;

	(void)info;
	(void)ucontext;
	if (sig == SIGUSR1)
		ft_printf("\rReceive Back : %d ", ++ret_byte); // \r means carriage return, moves the cursor to the beginning of the line, allowing subsequent characters to overwrite existing content on that line.
	bit_sender(0, 0); // ?send null to null?
}

void	bit_sender(char *str, pid_t pid)
{
	static int				i = 8;
	static char				*s_str;
	static unsigned char	c;
	static pid_t			server_pid;

	if (str)
	{
		s_str = str; // have to do this, otherwise seg fault after incrementing [1]
		c = *s_str; // now c is the character on s_str
		server_pid = pid;
	}
	if (!i)
	{
		i = 8;
		c = *(++s_str);
		if (!c) // if there is no more chars to send then
			connection_terminate(server_pid); // terminate client
	}
	if (c && ((c >> --i) & 0x01)) // [1]  a right shift operation applied to the variable c. --i decrements the value of i by 1 before the shift operation is performed. The >> operator shifts the bits of c to the right by the value of i.
		{ //  checks if the LSB (least significant bit) of the result of the right shift operation applied to c is non-zero (& 0x01 checks if the LSB is 1), and if c itself is non-zero. If both conditions are true, it sends the SIGUSR1 signal to the process identified by server_pid.
		//printf("A\n");
		kill(server_pid, SIGUSR1);
		}
	else if (c)
		{
		//printf("B\n");
		kill(server_pid, SIGUSR2);
		}
}

/* void	bit_sender(char *s, pid_t pid)
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
	while (c)
	{
		if (!i)
		{
			i = 8;
			c = *(++str);
			if (!c)
			{
				connection_terminate(server_pid);
				break ;
			}
		}
		if (c >> (i - 1) & 0x01)
			kill(server_pid, SIGUSR1);
		else
			kill(server_pid, SIGUSR2);
		i--;
	}
}
 */
void	connection_terminate(pid_t server_pid)
{
	int	i;

	i = 8;
	while (i--)
	{
		usleep(50);
		kill(server_pid, SIGUSR2);
	}
	exit (0); //finished normally and terminating client with success
}
