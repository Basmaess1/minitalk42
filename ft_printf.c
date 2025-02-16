/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bessabri <bessabri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 12:01:48 by bessabri          #+#    #+#             */
/*   Updated: 2025/02/15 09:44:07 by bessabri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_talk.h"

void	ft_putchar(int c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	if (!str)
	{
		ft_putstr("(null)");
	}
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
}

void	ft_putnbr(int n)
{
	if (n == -2147483648)
		write (1, "-2147483648", 11);
	else if (n < 0)
	{
		ft_putchar('-');
		n = -n;
		ft_putnbr(n);
	}
	else if (n > 9)
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
	else
		ft_putchar(n + 48);
}

void	ft_format(char specifier, va_list args)
{
	if (specifier == '%')
		write(1, "%", 1);
	else if (specifier == 'c')
		ft_putchar(va_arg(args, int));
	else if (specifier == 's')
		ft_putstr(va_arg(args, char *));
	else if (specifier == 'd' || specifier == 'i')
		ft_putnbr(va_arg(args, int));
}

void	ft_printf(const char *format, ...)
{
	va_list		ptr;
	int			i;

	i = 0;
	if (!format)
		return ;
	va_start(ptr, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			ft_format(format[i], ptr);
		}
		else
			write(1, &format[i], 1);
		i++;
	}
	va_end(ptr);
}
