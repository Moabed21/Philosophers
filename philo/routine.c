/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 20:01:33 by moabed            #+#    #+#             */
/*   Updated: 2026/02/14 19:58:52 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *p)
{
	t_pcard		*philo;
	long long	timestamp;

	philo = (t_pcard *)p;
	timestamp = time_calc();
	printf("%lld %d is thinking\n", timestamp, philo->pdetails.pnumber);
	hold_fork(&philo, philo->pdetails.pnumber);
	return (p);
}

void	hold_fork(t_pcard **philo, int p_num)
{
	if (p_num % 2 == 0)
	{
		if (pthread_mutex_lock((*philo)->left_fork) != 0)
		{
		}
	}
	if (p_num % 3 == 0)
	{
		if (pthread_mutex_lock((*philo)->right_fork) != 0)
		{
		}
	}
}
void	routine_start(t_pcard *philos, int pnum)
{
	int	i;

	i = 0;
	while (i < pnum)
	{
		if (pthread_create(&philos[i].thread, NULL, &routine, &philos[i]) != 0)
		{
		}
		i++;
	}
	i = 0;
	while (i < pnum)
	{
		if (pthread_join(philos[i].thread, NULL) != 0)
		{
		}
		i++;
	}
}
// eat operation starts when the two forks (mutexs) are locked

void	eat_operation(t_pcard **philos, pthread_mutex_t **forks)
{
	smart_sleep((*philos)->pdetails.tte,(*philos));
}
