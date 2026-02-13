/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 22:06:44 by moabed            #+#    #+#             */
/*   Updated: 2026/02/14 01:37:37 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void print_stamp(long long timestamp, int pnumber, int status)
{
    if (status == 0)
    {
        printf("%lld %d died\n", timestamp, pnumber);
    }
    else if (status == 1)
    {
        printf("%lld %d is thinking\n", timestamp, pnumber);
    }
    else if (status == 2)
    {
        printf("%lld %d is sleeping\n", timestamp, pnumber);
    }
    else if (status == 3)
    {
        printf("%lld %d is eating\n", timestamp, pnumber);
    }
    else if (status == 4)
    {
        printf("%lld %d has taken a fork\n", timestamp, pnumber);
    }
}
long long time_calc()
{
    struct timeval time;
    long long time_in_millisec;

    gettimeofday(&time, NULL);
    time_in_millisec = (time.tv_sec * 1000) + (time.tv_usec / 1000);
    return (time_in_millisec);
}

void smart_sleep(long long time)
{
    long long start_time;

    start_time = time_calc();
    while (time_calc() - start_time >= time)
    {
        usleep(250);
    }
}