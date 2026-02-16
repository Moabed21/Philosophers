/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 20:01:33 by moabed            #+#    #+#             */
/*   Updated: 2026/02/16 16:55:55 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	hold_fork_and_eat(t_pcard *philo, int p_num)
{
	if (p_num % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(philo->print_mic);
		printf("%lld %d has taken a fork\n", time_calc(), p_num);
		pthread_mutex_unlock(philo->print_mic);
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->print_mic);
		printf("%lld %d has taken a fork\n", time_calc(), p_num);
		printf("%lld %d is eating\n", time_calc(), p_num);
		pthread_mutex_unlock(philo->print_mic);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->print_mic);
		printf("%lld %d has taken a fork\n", time_calc(), p_num);
		pthread_mutex_unlock(philo->print_mic);
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(philo->print_mic);
		printf("%lld %d has taken a fork\n", time_calc(), p_num);
		printf("%lld %d is eating\n", time_calc(), p_num);
		pthread_mutex_unlock(philo->print_mic);
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
	long long	timestamp;

	timestamp = time_calc();
	smart_sleep(philo->pdetails.tts,philo);
	pthread_mutex_lock(philo->print_mic);
	printf("%lld %d is sleeping\n", timestamp, philo->pdetails.pnumber);
	pthread_mutex_unlock(philo->print_mic);
}
void	*routine(void *p)
{
	t_pcard		*philo;
	long long	timestamp;

	philo = (t_pcard *)p;
	while (1)
	{
		pthread_mutex_lock(philo->print_mic);
		timestamp = time_calc();
		printf("%lld %d is thinking\n", timestamp, philo->pdetails.pnumber);
		pthread_mutex_unlock(philo->print_mic);
		hold_fork_and_eat(philo, philo->pdetails.pnumber);
		philo->pdetails.eatcount--;
		smart_sleep(philo->pdetails.tte, philo);
		put_forks(philo, philo->pdetails.pnumber);
		if(philo->pdetails.eatcount <=0 )
			break;
		philo_sleep(philo);
	}
	return (p);
}

//create two mics (pointers) for the death second for the printing the messages
int	routine_start(t_pcard *philos, int pnum, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < pnum)
	{
		if (pthread_create(&philos[i].thread, NULL, &routine, &philos[i]) != 0)
		{
			mess_clean(philos, pnum, forks);
			return (1);
		}
		i++;
	}
	i = 0;
	while (i < pnum)
	{
		if (pthread_join(philos[i].thread, NULL) != 0)
		{
			mess_clean(philos, pnum, forks);
			return (1);
		}
		i++;
	}
	return (0);
}
// eat operation starts when the two forks (mutexs) are locked
