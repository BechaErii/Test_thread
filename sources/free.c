/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mewormse <mewormse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 19:02:36 by mewormse          #+#    #+#             */
/*   Updated: 2024/10/26 20:19:52 by mewormse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos[0].num_of_philos)
	{
		if (data->philos[i].l_fork)
		{
			pthread_mutex_destroy(data->philos[i].l_fork);
			free(data->philos[i].l_fork);
		}
		i++;
	}
	pthread_mutex_destroy(&data->dead_lock);
	pthread_mutex_destroy(&data->meal_lock);
	pthread_mutex_destroy(&data->write_lock);
	free(data->philos);
}

void	free_all(t_data *data)
{
	if (data->philos)
		free_philos(data);
	if (data)
		free(data);
}
