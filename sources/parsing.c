/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mewormse <mewormse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 19:04:00 by mewormse          #+#    #+#             */
/*   Updated: 2024/10/27 18:01:31 by mewormse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long int	ft_atoll(const char *nptr)
{
	long long int	i;
	long long int	nbr;
	long long int	negative;

	i = 0;
	nbr = 0;
	negative = 0;
	while ((nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13)))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			negative = 1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		nbr = nbr * 10 + (nptr[i] - 48);
		i++;
	}
	if (negative == 1)
		nbr *= -1;
	return (nbr);
}

int	check_arg(char *args)
{
	int	i;

	i = 0;
	if (!ft_isdigit(args[i]) && (args[i] != '+' && args[i] != '-'))
		return (0);
	if ((args[i] == '+' || args[i] == '-') && !ft_isdigit(args[i + 1]))
		return (0);
	i++;
	while (args[i])
	{
		if (!ft_isdigit(args[i]))
			return (0);
		i++;
	}
	return (1);
}

int	check_argv(char **argv, int argc)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!check_arg(argv[i]))
		{
			ft_putstr_fd(INVALID_ARGUMENT, 2);
			return (0);
		}
		i++;
	}
	return (1);
}
