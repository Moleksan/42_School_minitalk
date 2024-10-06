/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moleksan <moleksan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:35:08 by moleksan          #+#    #+#             */
/*   Updated: 2024/08/06 12:35:33 by moleksan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include "libft.h"
# include "ft_printf.h"

// client
void	send_bit(int pid, int bit);
void	send_character(int pid, unsigned char character);
void	send_message(int pid, const char *message);
void	response_handler(int signum);

// server
void	signal_handler(int signal, siginfo_t *siginfo, void *ucontext);

#endif
