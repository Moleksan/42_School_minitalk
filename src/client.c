/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moleksan <moleksan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:12:53 by moleksan          #+#    #+#             */
/*   Updated: 2024/08/14 14:41:35 by moleksan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_confirmation_flag = 0;

void	response_handler(int signum)
{
	static int	counter = 0;

	g_confirmation_flag = 1;
	counter++;
	if (counter == 8)
	{
		ft_printf("Character received by server.\n");
		counter = 0;
	}
	(void)signum;
}

void	send_bit(int pid, int bit)
{
	int	signal;

	if (bit == 1)
		signal = SIGUSR1;
	else
		signal = SIGUSR2;
	if (kill(pid, signal) == -1)
	{
		ft_putstr_fd("Error sending signal", 2);
		exit(EXIT_FAILURE);
	}
	while (!g_confirmation_flag)
		;
	g_confirmation_flag = 0;
}

void	send_character(int pid, unsigned char character)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		send_bit(pid, (character >> i) & 1);
		usleep(400);
		i--;
	}
}

void	send_message(int pid, const char *message)
{
	while (*message)
		send_character(pid, *message++);
	send_character(pid, '\0');
}

int	main(int argc, char **argv)
{
	pid_t	target_pid;

	if (argc != 3)
	{
		ft_putstr_fd("Usage: ./client [PID] [string]\n", 2);
		exit(EXIT_FAILURE);
	}
	target_pid = ft_atoi(argv[1]);
	if (target_pid <= 0)
	{
		ft_putstr_fd("Invalid PID\n", 2);
		exit(EXIT_FAILURE);
	}
	signal(SIGUSR2, response_handler);
	send_message(target_pid, argv[2]);
	return (0);
}
