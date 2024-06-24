/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phil_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asajid <asajid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 17:10:01 by asajid            #+#    #+#             */
/*   Updated: 2023/10/19 13:40:15 by asajid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_greedy_state(t_philo *philo)
{
	pthread_mutex_lock(&philo->phil_mutex->sign_mutex[philo->r_fork]);
	if (philo->value->greedy_state[philo->r_fork] != philo->id)
	{
		pthread_mutex_unlock(&philo->phil_mutex->sign_mutex[philo->r_fork]);
		pthread_mutex_lock(&philo->phil_mutex->sign_mutex[philo->l_fork]);
		if (philo->value->greedy_state[philo->l_fork] != philo->id)
		{
			pthread_mutex_unlock(&philo->phil_mutex->sign_mutex[philo->l_fork]);
			return (0);
		}
		else
			pthread_mutex_unlock(&philo->phil_mutex->sign_mutex[philo->l_fork]);
	}
	else
		pthread_mutex_unlock(&philo->phil_mutex->sign_mutex[philo->r_fork]);
	return (1);
}

int	check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->phil_mutex->last_meal_mutex);
	if ((get_time() - philo->last_eat_time) >= philo->value->time_to_die)
	{
		pthread_mutex_unlock(&philo->phil_mutex->last_meal_mutex);
		pthread_mutex_lock(&philo->phil_mutex->death_mutex);
		if (philo->value->dead_philo == 0)
		{
			philo->value->dead_philo = 1;
			pthread_mutex_unlock(&philo->phil_mutex->death_mutex);
			pthread_mutex_lock(&philo->phil_mutex->print_mutex);
			printf("%lu  philo %d is died\n", get_time()
				- philo->value->starting_time, philo->id + 1);
			pthread_mutex_unlock(&philo->phil_mutex->print_mutex);
			return (1);
		}
		pthread_mutex_unlock(&philo->phil_mutex->death_mutex);
	}
	else
		pthread_mutex_unlock(&philo->phil_mutex->last_meal_mutex);
	return (0);
}

int	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->phil_mutex->fork_mutex[philo->r_fork]);
	if (philo->value->fork_state[philo->r_fork] == -1)
	{
		philo->value->fork_state[philo->r_fork] = 0;
		pthread_mutex_unlock(&philo->phil_mutex->fork_mutex[philo->r_fork]);
		pthread_mutex_lock(&philo->phil_mutex->fork_mutex[philo->l_fork]);
		if (philo->value->fork_state[philo->l_fork] == -1)
		{
			philo->value->fork_state[philo->l_fork] = 0;
			pthread_mutex_unlock(&philo->phil_mutex->fork_mutex[philo->l_fork]);
			pthread_mutex_lock(&philo->phil_mutex->print_mutex);
			printf("%lu philo %d has taken forks\n", get_time()
				- philo->value->starting_time, philo->id + 1);
			pthread_mutex_unlock(&philo->phil_mutex->print_mutex);
			return (0);
		}
		else
		{
			pthread_mutex_unlock(&philo->phil_mutex->fork_mutex[philo->l_fork]);
			pthread_mutex_lock(&philo->phil_mutex->fork_mutex[philo->r_fork]);
			philo->value->fork_state[philo->r_fork] = -1;
		}
	}
	pthread_mutex_unlock(&philo->phil_mutex->fork_mutex[philo->r_fork]);
	return (1);
}

void	*routine(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	if (p->id % 2)
		usleep(15000);
	pthread_mutex_lock(&p->phil_mutex->last_meal_mutex);
	p->last_eat_time = get_time();
	pthread_mutex_unlock(&p->phil_mutex->last_meal_mutex);
	while (1)
	{
		if (check_philo_state(p) || p->value->max_eat_num == p->lunch_eaten)
			return (NULL);
		if (!check_philo_state(p))
		{
			if (check_death(p) == 0 && check_greedy_state(p) == 0
				&& take_forks(p) == 0)
				phil_eat(p);
			usleep(100);
		}
	}
}

int	create_phil_thread(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_num)
	{
		if (pthread_create(&data->philo[i].th, NULL, &routine,
				(void *)&data->philo[i]) != 0)
			return (1);
		i++;
	}
	i = 0;
	while (i < data->philo_num)
	{
		pthread_join(data->philo[i].th, NULL);
		i++;
	}
	return (0);
}
