/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 18:41:00 by moabed            #+#    #+#             */
/*   Updated: 2026/02/14 01:26:41 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// dont forget the makefile flags
// protect each function , malloc , mutex , etc

void hardwork(t_args *args)
{
	t_pcard *philos;
	pthread_mutex_t *forks;

	time_calc();
	forks = philo_init(args, &philos);
	if (!forks)
		return;
	printf("init succeed\n");
}

int main(int ac, char **av)
{
	t_args args;

	if (ac == 6 && parser(av) == 1)
	{
		args.philoscount = ft_atoi(av[1]);
		args.ttd = ft_atoi(av[2]);
		args.tte = ft_atoi(av[3]);
		args.tts = ft_atoi(av[4]);
		args.eatcount = ft_atoi(av[5]);
		hardwork(&args);
	}
	return (0);
}
