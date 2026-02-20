/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 06:49:00 by moabed            #+#    #+#             */
/*   Updated: 2026/02/20 21:05:35 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	store_init(t_pcard **ptable, pthread_mutex_t *store, int p_count)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(store, NULL) != 0)
	{
		free(store);
		free(*ptable);
		return (1);
	}
	while (i < p_count)
	{
		(*ptable)[i].store_mutex = store;
		i++;
	}
	return (0);
}

pthread_mutex_t	*forks_init(int number_of_forks, t_pcard **ptable)
{
	pthread_mutex_t	*forks;
	int				i;

	i = 0;
	forks = malloc(sizeof(pthread_mutex_t) * number_of_forks);
	if (!forks)
	{
		free(*ptable);
		return (NULL);
	}
	while (i < number_of_forks)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
		{
			mutex_destroy(i, &forks);
			free(*ptable);
			return (NULL);
		}
		i++;
	}
	return (forks);
}
