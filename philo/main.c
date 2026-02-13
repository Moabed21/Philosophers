/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 18:41:00 by moabed            #+#    #+#             */
/*   Updated: 2026/02/13 15:11:24 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// dont forget the makefile flags
// protect each function , malloc , mutex , etc
void	timecalc(void)
{
	struct timeval	time;
	long long		time_in_millisec;

	gettimeofday(&time, NULL);
	time_in_millisec = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	printf("current time : %ld \n", time_in_millisec);
}

void	hardwork(t_args *args)
{
	t_pcard			*philos;
	pthread_mutex_t	*forks;

	timecalc();
	forks = philo_init(args, &philos);
	if (!forks)
		return ;
}

int	main(int ac, char **av)
{
	t_args	args;

	if (ac == 6 && parser(av) == 1)
	{
		args.philoscount = ft_atoi(av[1]);
		args.ttd = ft_atoi(av[2]);
		args.tte = ft_atoi(av[3]);
		args.tts = ft_atoi(av[4]);
		args.eatcount = ft_atoi(av[5]);
		hardwork(&args);
	}
}
