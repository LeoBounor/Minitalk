/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbounor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 12:56:45 by lbounor           #+#    #+#             */
/*   Updated: 2022/05/20 12:56:47 by lbounor          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

size_t	g_writed = 0;

void	signalsender(char *tosend, int pid)
{
	size_t	i;

	i = 0;
	while (tosend[i])
	{
		if (tosend[i] == '0')
			kill(pid, SIGUSR1);
		else if (tosend[i] == '1')
			kill(pid, SIGUSR2);
		usleep(150);
		i++;
	}
}

void	chartobyte(int c, char *str)
{
	int	i;

	i = 7;
	str[8] = '\0';
	while (i >= 0)
	{
		if (c % 2 > 0)
			str[i--] = '1';
		else
			str[i--] = '0';
		c /= 2;
	}
}

void	callback_handler(int signum)
{
	if (signum == SIGUSR1)
		g_writed++;
}

int	string_sender(char *tosend, int pid)
{
	size_t	i;
	char	bytedchar[9];

	i = 0;
	signal(SIGUSR1, callback_handler);
	while (tosend[i])
	{
		chartobyte(tosend[i++], bytedchar);
		signalsender(bytedchar, pid);
	}
	return (i);
}

int	main(int argc, char **argv)
{
	if (argc != 3)
	{
		ft_putstr_fd(
			" \\ BAD ARGUMENT // usage : ./client (SERVER_PID) (MESSAGE)", 1);
		return (0);
	}
	string_sender(argv[2], ft_atoi(argv[1]));
	ft_putnbr_fd(g_writed * 100 / ft_strlen(argv[2]), 1);
	ft_putstr_fd(" % received", 1);
	return (0);
}
