/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mewormse <mewormse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 19:05:27 by mewormse          #+#    #+#             */
/*   Updated: 2024/10/26 19:50:32 by mewormse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleeping(t_philo *philo)
{
	if (philo->num_of_philos == 1)
		return ;
	if (philo->time_to_die <= philo->time_to_sleep)
		return ;
	state_message(philo, SLEEPING_MESSAGE);
	ft_sleep(philo->time_to_sleep);
}

void	take_forks(t_philo *philo)
{
	if (philo->id == 1)
	{
		pthread_mutex_lock(philo->l_fork);
		state_message(philo, FORK_MESSAGE);
		pthread_mutex_lock(philo->r_fork);
		state_message(philo, FORK_MESSAGE);
	}
	else
	{
		pthread_mutex_lock(philo->r_fork);
		state_message(philo, FORK_MESSAGE);
		pthread_mutex_lock(philo->l_fork);
	}
	state_message(philo, FORK_MESSAGE);
}

void	eating(t_philo *philo)
{
	if (philo->num_of_philos == 1)
	{
		state_message(philo, FORK_MESSAGE);
		ft_sleep(philo->time_to_die + 1);
		is_finish(philo);
		return ;
	}
	take_forks(philo);
	state_message(philo, EATING_MESSAGE);
	pthread_mutex_lock(philo->meal_lock);
	philo->meals_eaten++;
	philo->last_meal = get_current_time();
	pthread_mutex_unlock(philo->meal_lock);
	ft_sleep(philo->time_to_eat);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

int	is_finish(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead == 1)
	{
		pthread_mutex_unlock(philo->dead_lock);
		return (0);
	}
	pthread_mutex_unlock(philo->dead_lock);
	return (1);
}

void	*ft_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->id % 2 == 0)
		ft_sleep(10);
	while (is_finish(philo))
	{
		if (is_finish(philo) == 0)
			return (NULL);
		if (is_finish(philo) != 0)
			eating(philo);
		sleeping(philo);
		if (is_finish(philo) != 0)
			state_message(philo, THINKING_MESSAGE);
	}
	return (NULL);
}
