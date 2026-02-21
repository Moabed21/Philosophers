/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 18:41:00 by moabed            #+#    #+#             */
/*   Updated: 2026/02/21 14:35:48 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
void    *one_routine(void *p)
{
    t_args *args;
    long long start_time;

    args = (t_args *)p;
    start_time = time_calc();

    printf("%lld %d is thinking\n", time_calc() - start_time, 1);
    printf("%lld %d has taken a fork\n", time_calc() - start_time, 1);
    usleep(args->ttd * 1000);
    printf("%lld %d died\n", (long long)args->ttd, 1);
    
    return (NULL);
}

void    one_philo_case(t_args args)
{
    pthread_t thread;

    if (pthread_create(&thread, NULL, one_routine, &args) != 0)
    {
        printf("Error: Failed to create thread\n");
        return;
    }

    if (pthread_join(thread, NULL) != 0)
    {
        printf("Error: Failed to join thread\n");
        return;
    }
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
			one_philo_case(args);
		else
			hard_w1(&args);
	}
	if (ac == 5 && parser(av) == 1)
	{
		main_2(&args, ac, av);
		if (args.philoscount == 1)
			one_philo_case(args);
		else
			hard_w1(&args);
	}
	return (0);
}
