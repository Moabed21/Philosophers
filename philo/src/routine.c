/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 20:01:33 by moabed            #+#    #+#             */
/*   Updated: 2026/02/20 23:54:40 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	routine_continue(t_pcard **philo, char *msg)
{
	safe_print(*philo, msg);
	hold_fork_and_eat((*philo), (*philo)->pdetails.pnumber);
	pthread_mutex_lock((*philo)->store_mutex);
	(*philo)->last_meal = time_calc();
	pthread_mutex_unlock((*philo)->store_mutex);
	smart_sleep((*philo)->pdetails.tte, (*philo));
	put_forks((*philo), (*philo)->pdetails.pnumber);
	pthread_mutex_lock((*philo)->store_mutex);
	(*philo)->pdetails.eatcount--;
	if ((*philo)->pdetails.eatcount == 0)
	{
		pthread_mutex_unlock((*philo)->store_mutex);
		return (1);
	}
	pthread_mutex_unlock((*philo)->store_mutex);
	return (0);
}

void	*routine(void *p)
{
	t_pcard	*philo;

	philo = (t_pcard *)p;
	if (philo->pdetails.pnumber % 2 == 0)
		usleep(1500);
	while (1)
	{
		pthread_mutex_lock(philo->store_mutex);
		if (*philo->is_dead == 1)
		{
			pthread_mutex_unlock(philo->store_mutex);
			break ;
		}
		pthread_mutex_unlock(philo->store_mutex);
		if (routine_continue(&philo, "is thinking"))
			break ;
		philo_sleep(philo);
		usleep(500);
	}
	return (p);
}

int	if_all_have_eaten(t_pcard *philos, int p_count)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (i < p_count)
	{
		pthread_mutex_lock(philos[i].store_mutex);
		if (philos[i].pdetails.eatcount == 0)
			count++;
		pthread_mutex_unlock(philos[i].store_mutex);
		i++;
	}
	if (count == p_count)
		return (1);
	return (0);
}

void	master_of_masters(t_pcard *philos, int p_count)
{
	int			i;
	long long	diff;

	while (1)
	{
		i = 0;
		while (i < p_count)
		{
			pthread_mutex_lock(philos[i].store_mutex);
			diff = time_calc() - philos[i].last_meal;
			pthread_mutex_unlock(philos[i].store_mutex);
			if (diff >= philos[i].pdetails.ttd)
			{
				safe_print(&philos[i], "has died");
				pthread_mutex_lock(philos[i].store_mutex);
				*philos[i].is_dead = 1;
				pthread_mutex_unlock(philos[i].store_mutex);
				return ;
			}
			i++;
		}
		if (if_all_have_eaten(philos, p_count))
			return ;
		usleep(1000);
	}
}

int	routine_start(t_pcard *philos, int p_count, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < p_count)
	{
		if (pthread_create(&philos[i].thread, NULL, &routine, &philos[i]) != 0)
		{
			mess_clean(philos, p_count, forks);
			return (1);
		}
		i++;
	}
	i = 0;
	master_of_masters(philos, p_count);
	while (i < p_count)
	{
		if (pthread_join(philos[i].thread, NULL) != 0)
		{
			mess_clean(philos, p_count, forks);
			return (1);
		}
		i++;
	}
	mess_clean(philos, p_count, forks);
	return (0);
}
