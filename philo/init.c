/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 04:47:20 by moabed            #+#    #+#             */
/*   Updated: 2026/02/17 00:54:53 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

pthread_mutex_t	*philo_init(t_args *args, t_pcard **ptable,
		pthread_mutex_t *print_microphone, int *is_p_dead)
{
	int				i;
	t_pcard			*ptr;
	pthread_mutex_t	*forks;

	i = 0;
	// create the philosophers
	*ptable = malloc(sizeof(t_pcard) * args->philoscount);
	if (!(*ptable))
		return (NULL);
	ptr = (*ptable);
	// init each fork
	forks = forks_init(args->philoscount, ptable);
	if (!forks)
		return (NULL);
	while (++i <= args->philoscount)
	{
		// p takes his number
		ptr->pdetails.pnumber = i;
		// these will be the initial values for all philos at the start
		ptr->pdetails.eatcount = args->eatcount;
		ptr->pdetails.ttd = args->ttd;
		ptr->pdetails.tte = args->tte;
		ptr->pdetails.tts = args->tts;
		ptr->print_mic = print_microphone;
		ptr->is_dead = is_p_dead;
		ptr++;
	}
	assign_forks(forks, ptable, args->philoscount);
	return (forks);
}

void	final_work(t_args *args,t_pcard	*philos,pthread_mutex_t	*forks)
{
	routine_start(philos, args->philoscount, forks);
}

void	hard_work(t_args *args)
{
	int	*is_dead;
	t_pcard			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*print_microphone;

	print_microphone = malloc(sizeof(pthread_mutex_t));
	if (!print_microphone)
		return ;
	is_dead= malloc(sizeof(int));
	if(!is_dead)
	{
		free(print_microphone);
		return ;
	}
	*is_dead = 0;
	if (pthread_mutex_init(print_microphone, NULL) != 0)
	{
		free(is_dead);
		free(print_microphone);
		return ;
	}
	forks = philo_init(args, &philos, print_microphone,is_dead);
	if (!forks)
	{
		pthread_mutex_destroy(print_microphone);
		free(print_microphone);
		free(is_dead);
		return ;
	}
	final_work(args,philos,forks);
}
