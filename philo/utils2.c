/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 22:06:44 by moabed            #+#    #+#             */
/*   Updated: 2026/02/16 00:44:20 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	time_calc(void)
{
	struct timeval	time;
	long long		time_in_millisec;

	gettimeofday(&time, NULL);
	time_in_millisec = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (time_in_millisec);
}

void	smart_sleep(long long time, t_pcard *philo)
{
	long long	start_time;

	start_time = time_calc();
	while (time_calc() - start_time < time)
	{
		if (philo->is_philo_dead == 1)
			break ;
		usleep(250);
	}
}

void	mess_clean(t_pcard *philos, int pnum, pthread_mutex_t *forks)
{
	int i;

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