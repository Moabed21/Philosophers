/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 18:41:06 by moabed            #+#    #+#             */
/*   Updated: 2026/02/20 19:40:04 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# define _GNU_SOURCE
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_args
{
	int				pnumber;
	int				philoscount;
	int				ttd;
	int				tte;
	int				tts;
	int				eatcount;
}					t_args;

// each philo must have an id card contains his number , ttd , tte , tts
typedef struct s_pcard
{
	int				*is_dead;
	pthread_mutex_t	*store_mutex;
	pthread_t		thread;
	long long		last_meal;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*print_mic;
	t_args			pdetails;

}					t_pcard;

//-----utils--------
int					ft_atoi(const char *nptr);
int					ft_isdigit(int x);
int					parser(char **args);
void				mutex_destroy(int remaining_forks, pthread_mutex_t **forks);
void safe_print(t_pcard *philo, char *str);
void	ft_usleep(int ms);
//-----utils2-------
void				assign_forks(pthread_mutex_t *forks, t_pcard **philos,
						int philos_number);
long long			time_calc(void);
void				smart_sleep(long long time, t_pcard *philo);
void				mess_clean(t_pcard *philos, int pnum,
						pthread_mutex_t *forks);
void				free_fun(t_pcard **ptable, pthread_mutex_t *forks);
//-----init---------
void				hard_w1(t_args *args);
int					hard_w2(t_pcard **ptable, int p_count);
int					mini_init(t_pcard **ptable, int *is_p_dead,
						pthread_mutex_t *print_microphone, int p_count);
pthread_mutex_t		*philo_init(t_args *args, t_pcard **ptable);
pthread_mutex_t		*forks_init(int number_of_forks, t_pcard **ptable);
//------init2-------
int					store_init(t_pcard **ptable, pthread_mutex_t *store,
						int p_count);

//-----routine------
int					routine_start(t_pcard *philos, int pnum,
						pthread_mutex_t *forks);
#endif
