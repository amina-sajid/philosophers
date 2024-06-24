/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asajid <asajid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 17:14:00 by asajid            #+#    #+#             */
/*   Updated: 2023/10/19 17:12:27 by asajid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo	t_philo;
typedef struct s_data	t_data;

typedef struct s_mutex
{
	pthread_mutex_t		*mutex;

	pthread_mutex_t		death_mutex;
	pthread_mutex_t		last_meal_mutex;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		*sign_mutex;
	pthread_mutex_t		*fork_mutex;

}						t_mutex;

typedef struct s_philo
{
	int					id;

	int					r_fork;
	int					l_fork;
	int					time_to_die;
	int					lunch_eaten;
	size_t				last_eat_time;
	pthread_t			th;
	t_mutex				*phil_mutex;

	t_data				*value;

}						t_philo;

typedef struct s_data
{
	int					philo_num;
	size_t				time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					max_eat_num;
	size_t				starting_time;
	int					dead_philo;

	int					*greedy_state;
	int					*fork_state;

	t_philo				*philo;
	t_mutex				*data_mutex;

}						t_data;

int						check_error(int ac, char **av);
int						check_overflow(t_data *data);
void					ft_init_philos(t_data *data, t_mutex *mutex);
int						create_phil_thread(t_data *data);
int						ft_destroy_mutex(t_data *data);
int						ft_init_data(t_data *data, t_mutex *mutex);
void					ft_print(t_data *data, int i);
void					phil_eat(t_philo *phil);
long					get_time(void);
void					phil_think(t_philo *philo);
void					phil_sleep(t_philo *philo);
int						ft_atoi(const char *str);
void					*ft_calloc(size_t count, size_t size);
void					free_mut(t_mutex *m);
void					free_data(t_data *data, t_mutex *mutex);
int						check_philo_state(t_philo *philo);
int						ft_usleep(useconds_t time);
int						init_array(t_data *data);

#endif
