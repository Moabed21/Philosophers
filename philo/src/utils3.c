/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 21:07:50 by moabed            #+#    #+#             */
/*   Updated: 2026/02/20 23:54:21 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	hold_fork_and_eat(t_pcard *philo, int p_num)
{
	if (p_num % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		safe_print(philo, "has taken fork");
		pthread_mutex_lock(philo->left_fork);
		safe_print(philo, "has taken fork");
		safe_print(philo, "is eating");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		safe_print(philo, "has taken fork");
		pthread_mutex_lock(philo->right_fork);
		safe_print(philo, "has taken fork");
		safe_print(philo, "is eating");
	}
}

void	put_forks(t_pcard *philo, int p_num)
{
	if (p_num % 2 == 0)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
}

void	philo_sleep(t_pcard *philo)
{
	pthread_mutex_lock(philo->store_mutex);
	if (*(philo->is_dead) == 1)
	{
		pthread_mutex_unlock(philo->store_mutex);
		return ;
	}
	pthread_mutex_unlock(philo->store_mutex);
	safe_print(philo, "is sleeping");
	smart_sleep(philo->pdetails.tts, philo);
}
