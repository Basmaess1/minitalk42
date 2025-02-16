/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bessabri <bessabri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 11:10:36 by bessabri          #+#    #+#             */
/*   Updated: 2025/02/16 09:49:55 by bessabri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_talk.h"

static int	check_pid(char *str)
{
	int		i;
	pid_t	pid;

	i = 0;
	pid = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
		{
			ft_printf("invalid pid\n");
			exit (1);
		}
		pid = pid * 10 + str[i++] - 48;
	}
	if (kill(pid, 0) == -1)
	{
		ft_printf("Error: Invalid or non-existent PID!\n");
		exit(1);
	}
	return (pid);
}

static void	send_char(int pid, unsigned char c)
{
	int	i;

	i = 8;
	while (i > 0)
	{
		i--;
		if ((c >> i) & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(500);
	}
}

static void	send_string(int pid, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		send_char(pid, str[i]);
		i++;
	}
	send_char(pid, '\0');
}

static void	confirmation_handler(int sig)
{
	if (sig == SIGUSR1)
	{
		write(1, "Message received by server!\n", 28);
	}
}

int	main(int ac, char *av[])
{
	pid_t	pid;

	if (ac != 3)
	{
		write (2, "not enough arguments\n", 21);
		return (1);
	}
	pid = check_pid(av[1]);
	signal(SIGUSR1, confirmation_handler);
	send_string(pid, av[2]);
}
