/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 18:40:54 by moabed            #+#    #+#             */
/*   Updated: 2026/02/20 23:56:46 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *nptr)
{
	int	x;
	int	sign;

	sign = 1;
	x = 0;
	while (*nptr == ' ' || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign *= -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		x *= 10;
		x = x + (*nptr - '0');
		nptr++;
	}
	if (!(*nptr >= '0' && *nptr <= '9'))
		return (x * sign);
	return (x * sign);
}

int	ft_isdigit(int x)
{
	if (x >= 48 && x <= 57)
		return (1);
	else
		return (0);
}

int	parser(char **args)
{
	int	i;
	int	j;
	int	count;

	i = 1;
	while (args[i])
	{
		count = 0;
		j = 0;
		while (args[i][j])
		{
			if (!ft_isdigit(args[i][j]) && args[i][j] <= 48)
				count++;
			j++;
		}
		if (count >= 1)
		{
			write(2, "bad inputs\n", 12);
			return (0);
		}
		i++;
	}
	return (1);
}

void	mutex_destroy(int remaining_forks, pthread_mutex_t **forks)
{
	int	i;

	i = 0;
	while (i < remaining_forks)
	{
		pthread_mutex_destroy(&(*forks)[i]);
		i++;
	}
	free(*forks);
}

void	safe_print(t_pcard *philo, char *str)
{
	pthread_mutex_lock(philo->store_mutex);
	if (*philo->is_dead)
	{
		pthread_mutex_unlock(philo->store_mutex);
		return ;
	}
	pthread_mutex_unlock(philo->store_mutex);
	pthread_mutex_lock(philo->print_mic);
	printf("%lld %d %s\n", time_calc(), philo->pdetails.pnumber, str);
	pthread_mutex_unlock(philo->print_mic);
}
