/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mewormse <mewormse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 19:05:54 by mewormse          #+#    #+#             */
/*   Updated: 2024/10/26 19:50:39 by mewormse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	state_message(t_philo *philo, char *message)
{
	size_t	time;

	if (!is_finish(philo))
		return ;
	time = get_current_time() - philo->start_time;
	pthread_mutex_lock(philo->write_lock);
	printf(message, time, philo->id);
	pthread_mutex_unlock(philo->write_lock);
}

void	ft_sleep(size_t overclock)
{
	size_t	start;

	start = get_current_time();
	while (get_current_time() - start < overclock)
		usleep(1);
}
