/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bessabri <bessabri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 11:10:48 by bessabri          #+#    #+#             */
/*   Updated: 2025/02/15 17:06:44 by bessabri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_talk.h"

static void	process_byte(unsigned char *c, int *i, pid_t *client_pid)
{
	if (*c == '\0')
	{
		write(1, "\n", 1);
		kill(*client_pid, SIGUSR1);
	}
	else
		write(1, c, 1);
	*i = 0;
	*c = 0;
}

static void	signal_handler(int sig, siginfo_t *info, void *content)
{
	static int				i;
	static unsigned char	c;
	static pid_t			client_pid;

	if (client_pid == 0 || client_pid != info->si_pid)
	{
		client_pid = info->si_pid;
		i = 0;
		c = 0;
	}
	if (sig == SIGUSR1)
		c |= 1;
	else if (sig == SIGUSR2)
		c |= 0;
	i++;
	if (i == 8)
	{
		process_byte(&c, &i, &client_pid);
	}
	else
		c <<= 1;
	(void) content;
}

static void	handle_stop(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr("\n.......shut down.......\n");
		exit(0);
	}
}

int	main(void)
{
	struct sigaction		sa;
	pid_t					pid;

	sa.sa_sigaction = signal_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
	{
		write (2, "error\n", 6);
		return (1);
	}
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		write (2, "error\n", 6);
		return (1);
	}
	signal(SIGINT, handle_stop);
	pid = getpid();
	ft_printf("le numero de pid est : %d\n", pid);
	while (1)
	{
		pause();
	}
}
