/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 18:41:00 by moabed            #+#    #+#             */
/*   Updated: 2026/02/20 16:45:40 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// dont forget the makefile flags
// protect each function , malloc , mutex , etc

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
		hard_w1(&args);
	}
	if (ac == 5 && parser(av) == 1)
	{
		args.philoscount = ft_atoi(av[1]);
		args.ttd = ft_atoi(av[2]);
		args.tte = ft_atoi(av[3]);
		args.tts = ft_atoi(av[4]);
		args.eatcount = 0;
		hard_w1(&args);
	}
	return (0);
}
