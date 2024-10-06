/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moleksan <moleksan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 11:42:51 by moleksan          #+#    #+#             */
/*   Updated: 2024/08/12 17:09:18 by moleksan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	signal_handler(int signal, siginfo_t *siginfo, void *ucontext)
{
	static unsigned char	current_char = 0;
	static int				bit_counter = 0;
	static pid_t			sender_pid = 0;

	(void)ucontext;
	if (sender_pid != siginfo->si_pid)
	{
		bit_counter = 0;
		current_char = 0;
	}
	sender_pid = siginfo->si_pid;
	current_char <<= 1;
	if (signal == SIGUSR1)
		current_char |= 1;
	bit_counter++;
	if (bit_counter == 8)
	{
		write(1, &current_char, 1);
		bit_counter = 0;
		current_char = 0;
	}
	kill(sender_pid, SIGUSR2);
}

int	main(void)
{
	struct sigaction	action;

	ft_printf("PID: %d\n", getpid());
	action.sa_sigaction = &signal_handler;
	action.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGUSR2, &action, NULL);
	while (1)
		pause ();
	return (0);
}
