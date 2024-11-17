/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mewormse <mewormse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 19:51:56 by mewormse          #+#    #+#             */
/*   Updated: 2024/10/26 20:55:58 by mewormse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	exec_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos->num_of_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL, ft_routine,
				&data->philos[i]))
		{
			ft_putstr_fd(THREAD_ERROR, 2);
			return (0);
		}
		i++;
	}
	philo_monitoring(data);
	i = 0;
	while (i < data->philos->num_of_philos)
	{
		if (pthread_join(data->philos[i].thread, NULL))
		{
			ft_putstr_fd(JOIN_ERROR, 2);
			return (0);
		}
		i++;
	}
	return (1);
}

int	init_threads(t_data *data)
{
	int	i;

	pthread_mutex_init(&data->write_lock, NULL);
	pthread_mutex_init(&data->dead_lock, NULL);
	pthread_mutex_init(&data->meal_lock, NULL);
	i = 0;
	while (data->philos[i].num_of_philos)
	{
		data->philos[i].l_fork = ft_calloc(1, sizeof(pthread_mutex_t));
		if (!data->philos[i].l_fork)
		{
			ft_putstr_fd(MALLOC_ERROR, 2);
			return (0);
		}
		pthread_mutex_init(data->philos[i].l_fork, NULL);
		if (i + 1 < data->philos[i].num_of_philos)
			data->philos[i + 1].r_fork = data->philos[i].l_fork;
		data->philos[i].write_lock = &data->write_lock;
		data->philos[i].dead_lock = &data->dead_lock;
		data->philos[i].meal_lock = &data->meal_lock;
		i++;
	}
	if (data->philos[i].num_of_philos != 1)
		data->philos[0].r_fork = data->philos[i - 1].l_fork;
	return (1);
}

t_data	*init_philo(char **argv, int argc)
{
	t_data	*data;

	if (!check_argv(argv, argc))
		return (0);
	data = fill_struct(argv, argc);
	if (!data)
		return (0);
	if (!init_threads(data))
	{
		free_all(data);
		return (0);
	}
	return (data);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc < 5 || argc > 6)
	{
		write(2, "Invalid number of arguments\n", 28);
		return (1);
	}
	data = init_philo(argv, argc);
	if (!data)
		return (1);
	if (!exec_threads(data))
	{
		free_all(data);
		return (1);
	}
	free_all(data);
	return (0);
}
