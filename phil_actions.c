/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phil_actions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asajid <asajid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 17:11:20 by asajid            #+#    #+#             */
/*   Updated: 2023/10/19 17:10:36 by asajid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	phil_sleep(t_philo *philo)
{
	if (check_philo_state(philo))
		return ;
	pthread_mutex_lock(&philo->phil_mutex->print_mutex);
	printf("%lu  philo %d is sleeping\n", (get_time()
			- philo->value->starting_time), philo->id + 1);
	pthread_mutex_unlock(&philo->phil_mutex->print_mutex);
	ft_usleep(philo->value->time_to_sleep);
	if (check_philo_state(philo))
		return ;
	pthread_mutex_lock(&philo->phil_mutex->print_mutex);
	printf("%lu  philo %d  is thinking\n", (get_time()
			- philo->value->starting_time), philo->id + 1);
	pthread_mutex_unlock(&philo->phil_mutex->print_mutex);
}

void	drop_forks(t_philo *phil)
{
	pthread_mutex_lock(&phil->phil_mutex->fork_mutex[phil->r_fork]);
	phil->value->fork_state[phil->r_fork] = -1;
	pthread_mutex_unlock(&phil->phil_mutex->fork_mutex[phil->r_fork]);
	pthread_mutex_lock(&phil->phil_mutex->fork_mutex[phil->l_fork]);
	phil->value->fork_state[phil->l_fork] = -1;
	pthread_mutex_unlock(&phil->phil_mutex->fork_mutex[phil->l_fork]);
}

void	phil_eat(t_philo *phil)
{
	if (check_philo_state(phil))
		return ;
	pthread_mutex_lock(&phil->phil_mutex->last_meal_mutex);
	phil->last_eat_time = get_time();
	pthread_mutex_unlock(&phil->phil_mutex->last_meal_mutex);
	pthread_mutex_lock(&phil->phil_mutex->print_mutex);
	printf("%lu philo %d is eating\n", (get_time()
			- phil->value->starting_time), phil->id + 1);
	pthread_mutex_unlock(&phil->phil_mutex->print_mutex);
	pthread_mutex_lock(&phil->phil_mutex->sign_mutex[phil->r_fork]);
	phil->value->greedy_state[phil->r_fork] = phil->id;
	pthread_mutex_unlock(&phil->phil_mutex->sign_mutex[phil->r_fork]);
	pthread_mutex_lock(&phil->phil_mutex->sign_mutex[phil->l_fork]);
	phil->value->greedy_state[phil->l_fork] = phil->id;
	pthread_mutex_unlock(&phil->phil_mutex->sign_mutex[phil->l_fork]);
	ft_usleep(phil->value->time_to_eat);
	phil->lunch_eaten++;
	drop_forks(phil);
	phil_sleep(phil);
}

int	init_array(t_data *data)
{
	data->fork_state = malloc(data->philo_num * sizeof(int));
	if (!data->fork_state)
		return (1);
	data->greedy_state = malloc(data->philo_num * sizeof(int));
	if (!data->greedy_state)
		return (1);
	return (0);
}
