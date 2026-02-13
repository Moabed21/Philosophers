/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 04:47:20 by moabed            #+#    #+#             */
/*   Updated: 2026/02/13 11:26:06 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t *forks_init(int number_of_forks, t_pcard **ptable)
{
    pthread_mutex_t *forks;
    int i;

    i = 0;
    forks = malloc(sizeof(pthread_mutex_t) * number_of_forks);
    if (!forks)
    {
        free(ptable);
        return (NULL);
    }
    while (i < number_of_forks)
    {
        if (pthread_mutex_init(&forks[i], NULL) == -1)
        {
            free(*ptable);
            return (NULL);
        }
        i++;
    }
    return (forks);
}

pthread_mutex_t *philo_init(t_args *args, t_pcard **ptable)
{
    t_pcard *ptr;
    pthread_mutex_t *forks;
    int i;

    i = 0;
    // create the philosophers
    *ptable = malloc(sizeof(t_pcard) * args->philoscount);
    if (!*ptable)
        return (NULL);
    ptr = (*ptable);
    // add the id number to each one
    forks = forks_init(args->philoscount, ptable);
    if (!forks)
    {
        free(*ptable);
        return (NULL);
    }
    while (++i <= args->philoscount)
    {
        // p takes his number
        ptr->pdetails.pnumber = i;
        // these will be the initial values for all philos at the start
        ptr->pdetails.eatcount = args->eatcount;
        ptr->pdetails.ttd = args->ttd;
        ptr->pdetails.tte = args->tte;
        ptr->pdetails.tts = args->tts;
        ptr++;
    }
    return (forks);
}
