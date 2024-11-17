/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mewormse <mewormse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 19:59:37 by mewormse          #+#    #+#             */
/*   Updated: 2024/10/27 18:14:44 by mewormse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long int	get_current_time(void)
{
	struct timeval			tv;
	size_t					time;

	if (gettimeofday(&tv, NULL) == -1)
	{
		ft_putstr_fd(TIME_ERROR, 2);
		return (0);
	}
	time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return ((long long int)time);
}

int	check_nums(t_data *data, int argc)
{
	if (data->philos->num_of_philos < 1 || data->philos->time_to_die < 1
		|| data->philos->time_to_eat < 1 || data->philos->time_to_sleep < 1)
		return (0);
	if ((argc == 6 && data->philos->meals_required < 0)
		|| (argc == 6 && data->philos->meals_required > INT_MAX))
		return (0);
	if (data->philos->num_of_philos > INT_MAX
		|| data->philos->time_to_die > INT_MAX
		|| data->philos->time_to_eat > INT_MAX
		|| data->philos->time_to_sleep > INT_MAX)
		return (0);
	return (1);
}

int	fill_infos(char **argv, int argc, t_data *data)
{
	long long int	i;

	i = 0;
	while (i < ft_atoll(argv[1]))
	{
		data->philos[i].id = i + 1;
		data->philos[i].dead = &data->dead;
		data->philos[i].start_time = data->philos[0].start_time;
		data->philos[i].num_of_philos = ft_atoll(argv[1]);
		data->philos[i].time_to_die = ft_atoll(argv[2]);
		data->philos[i].time_to_eat = ft_atoll(argv[3]);
		data->philos[i].time_to_sleep = ft_atoll(argv[4]);
		data->philos[i].last_meal = data->philos->start_time;
		if (argc == 6)
			data->philos[i].meals_required = (int )ft_atoll(argv[5]);
		else
			data->philos[i].meals_required = -1;
		i++;
	}
	if (!check_nums(data, argc))
	{
		ft_putstr_fd(INVALID_ARGUMENT, 2);
		return (0);
	}
	return (1);
}

t_philo	*alloc_struct(char **argv)
{
	t_philo	*philos;

	if (ft_atoll(argv[1]) < 1)
	{
		ft_putstr_fd(INVALID_ARGUMENT, 2);
		return (0);
	}
	philos = ft_calloc(ft_atoll(argv[1]) + 1, sizeof(t_philo));
	if (!philos)
	{
		ft_putstr_fd(MALLOC_ERROR, 2);
		return (0);
	}
	return (philos);
}

t_data	*fill_struct(char **argv, int argc)
{
	t_data	*data;
	int		i;

	i = 1;
	data = ft_calloc(1, sizeof(t_data));
	if (!data)
	{
		ft_putstr_fd(MALLOC_ERROR, 2);
		return (0);
	}
	data->philos = alloc_struct(argv);
	if (!data->philos)
	{
		free(data);
		return (0);
	}
	data->philos[0].start_time = get_current_time();
	if (!data->philos[0].start_time || !fill_infos(argv, argc, data))
	{
		free_all(data);
		return (0);
	}
	return (data);
}
