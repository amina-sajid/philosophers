/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asajid <asajid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 17:16:41 by asajid            #+#    #+#             */
/*   Updated: 2023/10/19 17:10:17 by asajid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_init_philos(t_data *data, t_mutex *mutex)
{
	int	i;

	i = 0;
	while (i < data->philo_num)
	{
		data->philo[i].id = i;
		data->philo[i].r_fork = i;
		data->philo[i].l_fork = ((i + 1) % data->philo_num);
		data->philo[i].lunch_eaten = 0;
		data->philo[i].value = data;
		data->philo[i].phil_mutex = mutex;
		data->philo[i].last_eat_time = 0;
		i++;
	}
}

int	ft_init_mutex(t_data *data, t_mutex *mutex)
{
	int	j;

	if (pthread_mutex_init(&mutex->death_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&mutex->last_meal_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&mutex->print_mutex, NULL) != 0)
		return (1);
	j = 0;
	while (j < data->philo_num)
	{
		if (pthread_mutex_init(&mutex->mutex[j], NULL) != 0)
			return (1);
		if (pthread_mutex_init(&mutex->fork_mutex[j], NULL) != 0)
			return (1);
		if (pthread_mutex_init(&mutex->sign_mutex[j], NULL) != 0)
			return (1);
		j++;
	}
	return (0);
}

int	do_mall(t_mutex *mutex, t_data *data)
{
	mutex->mutex = malloc(data->philo_num * sizeof(pthread_mutex_t));
	if (!mutex->mutex)
		return (1);
	mutex->fork_mutex = malloc(data->philo_num * sizeof(pthread_mutex_t));
	if (!mutex->fork_mutex)
		return (1);
	mutex->sign_mutex = malloc(data->philo_num * sizeof(pthread_mutex_t));
	if (!mutex->sign_mutex)
		return (1);
	return (0);
}

int	init_data_utils(t_data *data, t_mutex *mutex)
{
	data->dead_philo = 0;
	data->starting_time = get_time();
	data->data_mutex = mutex;
	data->philo = malloc((data->philo_num) * sizeof(t_philo));
	if (!data->philo)
		return (1);
	return (0);
}

int	ft_init_data(t_data *data, t_mutex *mutex)
{
	int	i;

	i = 0;
	if (do_mall(mutex, data))
	{
		free (data);
		return (1);
	}
	if (init_array(data))
		return (1);
	while (i < data->philo_num)
	{
		data->fork_state[i] = -1;
		data->greedy_state[i] = -1;
		i++;
	}
	if (ft_init_mutex(data, mutex) == 1)
		return (1);
	if (init_data_utils(data, mutex))
	{
		free_data(data, mutex);
		return (1);
	}
	return (0);
}
