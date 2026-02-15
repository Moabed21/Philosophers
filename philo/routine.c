/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 20:01:33 by moabed            #+#    #+#             */
/*   Updated: 2026/02/15 23:50:36 by moabed           ###   ########.fr       */
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
void	*routine(void *p)
{
	int			i;
	t_pcard		*philo;
	long long	timestamp;

	philo = (t_pcard *)p;
	pthread_mutex_lock(philo->print_mic);
	timestamp = time_calc();
	printf("%lld %d is thinking\n", timestamp, philo->pdetails.pnumber);
	pthread_mutex_unlock(philo->print_mic);
	while (1)
	{
		hold_fork_and_eat(philo, philo->pdetails.pnumber);
	}
	return (p);
}
void	mess_clean(t_pcard *philos, int pnum, pthread_mutex_t *forks)
{
	int	i;

	//allocated elements are : print_mic , forks, philosophers
	i = 0;
	//first target to be freed : print_mic
	pthread_mutex_destroy(philos->print_mic);
	free(philos->print_mic);
	//then, the forks starting form the right
	while (i < pnum)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	free(forks);
	//finally, the table godfather :)
	free(philos);
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
