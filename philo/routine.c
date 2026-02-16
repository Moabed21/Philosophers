/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 20:01:33 by moabed            #+#    #+#             */
/*   Updated: 2026/02/17 01:21:34 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	hold_fork_and_eat(t_pcard *philo, int p_num)
{
	philo->last_meal = time_calc();
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
	pthread_mutex_lock(philo->print_mic);
	printf("%lld %d is sleeping\n", time_calc(), philo->pdetails.pnumber);
	pthread_mutex_unlock(philo->print_mic);
	smart_sleep(philo->pdetails.tts, philo);
}
void	*routine(void *p)
{
	t_pcard		*philo;
	

	philo = (t_pcard *)p;
	while (1)
	{
		pthread_mutex_lock(philo->print_mic);
		printf("%lld %d is thinking\n", time_calc(), philo->pdetails.pnumber);
		pthread_mutex_unlock(philo->print_mic);
		hold_fork_and_eat(philo, philo->pdetails.pnumber);
		philo->pdetails.eatcount--;
		smart_sleep(philo->pdetails.tte, philo);
		put_forks(philo, philo->pdetails.pnumber);
		if((*philo->is_dead) == 1 || philo->pdetails.eatcount <= 0)
			break;
		philo_sleep(philo);
	}
	return (p);
}

void	master_of_masters(t_pcard **philos, int pnum)
{
	int			i;
	long long	difference;

	i = 0;
	while (i < pnum)
	{
		difference = time_calc() - (*philos)[i].last_meal;
		if (difference >= (*philos)[i].pdetails.ttd)
		{
			pthread_mutex_lock((*philos)->print_mic);
			printf("%lld %d has died\n", time_calc(),
					(*philos)[i].pdetails.pnumber);
			pthread_mutex_unlock((*philos)->print_mic);
			(*(*philos)[i].is_dead) = 1;
			break;
		}
		i++;
		if(i >= pnum)
			i = 0;
	}
	return ;
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
	master_of_masters(&philos, pnum);
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
