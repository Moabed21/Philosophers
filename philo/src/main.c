/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 18:41:00 by moabed            #+#    #+#             */
/*   Updated: 2026/02/21 00:39:41 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	one_philo_case(int philo)
{
	printf("%lld %d %s\n", time_calc(), philo,"is thinking");
	printf("%lld %d %s\n", time_calc(), philo,"has taken a fork");
}
void	main_2(t_args *args, int ac, char **av)
{
	if (ac == 6)
	{
		args->philoscount = ft_atoi(av[1]);
		args->ttd = ft_atoi(av[2]);
		args->tte = ft_atoi(av[3]);
		args->tts = ft_atoi(av[4]);
		args->eatcount = ft_atoi(av[5]);
	}
	if (ac == 5)
	{
		args->philoscount = ft_atoi(av[1]);
		args->ttd = ft_atoi(av[2]);
		args->tte = ft_atoi(av[3]);
		args->tts = ft_atoi(av[4]);
		args->eatcount = 0;
	}
}

int	main(int ac, char **av)
{
	t_args	args;

	if (ac == 6 && parser(av) == 1)
	{
		main_2(&args, ac, av);
		if (args.philoscount == 1)
			one_philo_case(args.philoscount);
		else
			hard_w1(&args);
	}
	if (ac == 5 && parser(av) == 1)
	{
		main_2(&args, ac, av);
		if (args.philoscount == 1)
			one_philo_case(args.philoscount);
		else
			hard_w1(&args);
	}
	return (0);
}
