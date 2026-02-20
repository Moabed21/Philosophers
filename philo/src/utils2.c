/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 22:06:44 by moabed            #+#    #+#             */
/*   Updated: 2026/02/21 00:40:02 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mess_clean(t_pcard *philos, int pnum, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(philos->print_mic);
	pthread_mutex_destroy(philos->store_mutex);
	while (i < pnum)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	free(philos->store_mutex);
	free(philos->print_mic);
	free(philos->is_dead);
	free(forks);
	free(philos);
}

void	smart_sleep(long long time, t_pcard *philo)
{
	long long	start_time;

	start_time = time_calc();
	while (time_calc() - start_time < time)
	{
		pthread_mutex_lock(philo->store_mutex);
		if ((*philo->is_dead) == 1)
		{
			pthread_mutex_unlock(philo->store_mutex);
			break ;
		}
		pthread_mutex_unlock(philo->store_mutex);
		usleep(100);
	}
}

long long	time_calc(void)
{
	struct timeval	time;
	long long		time_in_millisec;

	gettimeofday(&time, NULL);
	time_in_millisec = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (time_in_millisec);
}

void	assign_forks(pthread_mutex_t *forks, t_pcard **philos,
		int philos_number)
{
	int	i;

	i = 0;
	while (i < philos_number)
	{
		(*philos)[i].right_fork = &forks[(i) % philos_number];
		(*philos)[i].left_fork = &forks[(i + 1) % philos_number];
		i++;
	}
}

void	free_fun(t_pcard **ptable, pthread_mutex_t *forks)
{
	if (!forks)
	{
		pthread_mutex_destroy((*ptable)->store_mutex);
		pthread_mutex_destroy((*ptable)->print_mic);
		free((*ptable)->store_mutex);
		free((*ptable)->print_mic);
		free((*ptable)->is_dead);
		free(*ptable);
	}
}
