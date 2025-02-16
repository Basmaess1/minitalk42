/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bessabri <bessabri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 15:55:41 by bessabri          #+#    #+#             */
/*   Updated: 2025/02/15 16:38:45 by bessabri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_talk.h"

static void	signal_handler(int sig)
{
	static int				i;
	static unsigned char	c;

	if (sig == SIGUSR1)
		c |= 1;
	else if (sig == SIGUSR2)
		c |= 0;
	i++;
	if (i == 8)
	{
		if (c == '\0')
			write (1, "\n", 1);
		else
			write (1, &c, 1);
		i = 0;
		c = 0;
	}
	else
		c = c << 1;
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
	pid_t	pid;

	pid = getpid();
	ft_printf("le numero de pid est :%d\n", pid);
	signal(SIGUSR1, signal_handler);
	signal(SIGUSR2, signal_handler);
	signal(SIGINT, handle_stop);
	while (1)
	{
		pause();
	}
}
