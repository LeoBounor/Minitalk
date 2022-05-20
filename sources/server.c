/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbounor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 12:56:24 by lbounor           #+#    #+#             */
/*   Updated: 2022/05/20 12:56:26 by lbounor          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

void	bytetochar(char *bytedchar)
{
	size_t	i;
	int		o;
	int		power;
	int		res;

	i = 0;
	res = 0;
	while (bytedchar[i])
	{
		o = 7 - i;
		power = 1;
		while (o-- > 0)
			power = power * 2;
		res += (bytedchar[i++] - '0') * power;
	}
	ft_putchar_fd(res, 1);
}

void	sighandler(int signum, siginfo_t *siginfo)
{
	static char		bytedchar[8];
	static int		count = 0;

	if (signum == SIGUSR1)
		bytedchar[count++] = '0';
	else if (signum == SIGUSR2)
		bytedchar[count++] = '1';
	if (count == 8)
	{
		count = 0;
		bytetochar(bytedchar);
		kill(siginfo->si_pid, SIGUSR1);
	}
}

int	main(void)
{
	struct sigaction	signal;

	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
	signal.sa_handler = (void *)sighandler;
	signal.sa_flags = SA_SIGINFO;
	while (1)
	{
		sigaction(SIGUSR1, &signal, NULL);
		sigaction(SIGUSR2, &signal, NULL);
		pause();
	}
}
