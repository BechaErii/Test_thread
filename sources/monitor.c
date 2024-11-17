/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mewormse <mewormse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 19:03:21 by mewormse          #+#    #+#             */
/*   Updated: 2024/10/26 20:19:52 by mewormse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_if_all_eat(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&data->meal_lock);
	if (data->philos[0].meals_required == -1)
	{
		pthread_mutex_unlock(&data->meal_lock);
		return (1);
	}
	while (i < data->philos[0].num_of_philos)
	{
		if (data->philos[i].meals_eaten < data->philos[0].meals_required)
		{
			pthread_mutex_unlock(&data->meal_lock);
			return (1);
		}
		i++;
	}
	pthread_mutex_unlock(&data->meal_lock);
	pthread_mutex_lock(&data->dead_lock);
	data->dead = 1;
	pthread_mutex_unlock(&data->dead_lock);
	return (0);
}

int	check_if_someone_died(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos[0].num_of_philos)
	{
		pthread_mutex_lock(&data->meal_lock);
		if (get_current_time() - data->philos[i].last_meal
			> data->philos[i].time_to_die)
		{
			pthread_mutex_lock(&data->dead_lock);
			data->dead = 1;
			pthread_mutex_unlock(&data->dead_lock);
			pthread_mutex_lock(&data->write_lock);
			printf(DEAD_MESSAGE, get_current_time()
				- data->philos[0].start_time, data->philos[i].id);
			pthread_mutex_unlock(&data->write_lock);
			pthread_mutex_unlock(&data->meal_lock);
			return (0);
		}
		pthread_mutex_unlock(&data->meal_lock);
		i++;
	}
	return (1);
}

void	philo_monitoring(t_data *data)
{
	while (1)
	{
		if (!check_if_all_eat(data) || !check_if_someone_died(data))
			break ;
		usleep(10);
	}
	return ;
}
