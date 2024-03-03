/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 18:35:28 by hsetyamu          #+#    #+#             */
/*   Updated: 2024/03/03 11:30:25 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_BONUS_H
# define MINITALK_BONUS_H
//# define _XOPEN_SOURCE 700 // sigaction&friends, in conjunction with signal.h
//# define _DEFAULT_SOURCE // to avoid implicit declaration of usleep

# include <unistd.h>
//# include <sys/types.h> // pid_t 
# include <signal.h> // SIGUSR1/2 kill sigaction
# include "../lib/src/ft_printf/ft_printf.h"
# include "../lib/src/get_next_line/get_next_line.h"
# include "../lib/src/libft/libft.h"

#endif
