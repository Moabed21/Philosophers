/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 04:47:20 by moabed            #+#    #+#             */
/*   Updated: 2026/02/20 23:55:27 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t	*philo_init(t_args *args, t_pcard **ptable)
{
	int				i;
	t_pcard			*ptr;
	pthread_mutex_t	*forks;

	i = 0;
	ptr = (*ptable);
	forks = forks_init(args->philoscount, ptable);
	if (!forks)
		return (NULL);
	while (++i <= args->philoscount)
	{
		ptr->pdetails.pnumber = i;
		ptr->pdetails.eatcount = args->eatcount;
		ptr->pdetails.ttd = args->ttd;
		ptr->pdetails.tte = args->tte;
		ptr->pdetails.tts = args->tts;
		ptr->last_meal = time_calc();
		ptr++;
	}
	assign_forks(forks, ptable, args->philoscount);
	return (forks);
}

int	mini_init(t_pcard **ptable, int *is_p_dead,
		pthread_mutex_t *print_microphone, int p_count)
{
	int		i;
	t_pcard	*ptr;

	ptr = (*ptable);
	i = 0;
	if (pthread_mutex_init(print_microphone, NULL) != 0)
	{
		pthread_mutex_destroy((*ptable)->store_mutex);
		free((*ptable)->store_mutex);
		free(is_p_dead);
		free(*ptable);
		free(print_microphone);
		return (1);
	}
	while (i < p_count)
	{
		ptr->print_mic = print_microphone;
		ptr->is_dead = is_p_dead;
		ptr++;
		i++;
	}
	*((*ptable)->is_dead) = 0;
	return (0);
}

int	hard_w2(t_pcard **ptable, int p_count)
{
	int				*is_dead;
	pthread_mutex_t	*print_microphone;

	print_microphone = malloc(sizeof(pthread_mutex_t));
	if (!print_microphone)
	{
		pthread_mutex_destroy((*ptable)->store_mutex);
		free((*ptable)->store_mutex);
		free(*ptable);
		return (1);
	}
	is_dead = malloc(sizeof(int));
	if (!is_dead)
	{
		pthread_mutex_destroy((*ptable)->store_mutex);
		free((*ptable)->store_mutex);
		free(*ptable);
		free(print_microphone);
		return (1);
	}
	if (mini_init(ptable, is_dead, print_microphone, p_count) == 1)
		return (1);
	return (0);
}

void	hard_w1(t_args *args)
{
	t_pcard			*ptable;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*store;

	ptable = malloc(sizeof(t_pcard) * args->philoscount);
	if (!ptable)
		return ;
	store = malloc(sizeof(pthread_mutex_t));
	if (!store)
	{
		free(ptable);
		return ;
	}
	if (store_init(&ptable, store, args->philoscount) == 1)
		return ;
	if (hard_w2(&ptable, args->philoscount) == 1)
		return ;
	forks = philo_init(args, &ptable);
	if (!forks)
	{
		free_fun(&ptable, forks);
		return ;
	}
	routine_start(ptable, args->philoscount, forks);
}
