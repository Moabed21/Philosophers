/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 04:47:20 by moabed            #+#    #+#             */
/*   Updated: 2026/02/12 14:12:35 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void philo_init(t_args *args, t_pcard *ptable)
{
    t_pcard *ptr;
    int i;

    i = 1;
    ptr = ptable;
    // create the philosophers
    ptable = malloc(sizeof(t_pcard) * args->philos);
    // add the id number to each one
    while (i <= args->philos)
    {
        ptr->pnumber = i;
        ptr++;
        i++;
    }
}
