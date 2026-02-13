/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 18:41:06 by moabed            #+#    #+#             */
/*   Updated: 2026/02/13 16:36:11 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
typedef struct s_args
{
	int pnumber;
	int philoscount;
	int ttd;
	int tte;
	int tts;
	int eatcount;
} t_args;

// each philo must have an id card contains his number , ttd , tte , tts
typedef struct s_pcard
{
	pthread_t *thread;
	pthread_mutex_t *right_fork;
	pthread_mutex_t *left_fork;
	t_args pdetails;

} t_pcard;

//-----utils--------
int ft_atoi(const char *nptr);
int ft_isdigit(int x);
int parser(char **args);
void mutex_destroy(int remaining_forks, pthread_mutex_t **forks);
//------------------
//-----init---------
void philo_init(t_args *args, t_pcard **ptable);
pthread_mutex_t *forks_init(int number_of_forks, t_pcard **ptable);
#endif
