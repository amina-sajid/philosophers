/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asajid <asajid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 17:12:28 by asajid            #+#    #+#             */
/*   Updated: 2023/10/19 17:03:56 by asajid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_parse_data(t_data *data, int ac, char **av)
{
	if (ac == 5 || ac == 6)
	{
		data->philo_num = ft_atoi(av[1]);
		data->time_to_die = ft_atoi(av[2]);
		data->time_to_eat = ft_atoi(av[3]);
		data->time_to_sleep = ft_atoi(av[4]);
		if (av[5])
			data->max_eat_num = ft_atoi(av[5]);
		else
			data->max_eat_num = -1;
		data->dead_philo = 0;
	}
}

int	check_data(int ac, char **av, t_data **data, t_mutex *m)
{
	*data = (t_data *)ft_calloc(1, sizeof(t_data));
	if (!*data)
	{
		return (1);
	}
	ft_parse_data(*data, ac, av);
	if (check_overflow(*data) != 0)
	{
		printf("Invalid arguments");
		free(*data);
		return (1);
	}
	if (ft_init_data(*data, m))
	{
		printf("entrinf ft_init_data\n");
		return (1);
	}
	ft_init_philos(*data, m);
	return (0);
}

void	free_mut(t_mutex *m)
{
	if (m->mutex)
		free(m->mutex);
	if (m->fork_mutex)
		free(m->fork_mutex);
	if (m->sign_mutex)
		free(m->sign_mutex);
	else
		return ;
}

int	main(int ac, char **av)
{
	t_data	*data;
	t_mutex	m;

	if (check_error(ac, av) != 0)
	{
		printf("Error: Invalid Inputs\n");
		return (1);
	}
	if (check_data(ac, av, &data, &m))
		return (1);
	if (create_phil_thread(data) == 1)
	{
		free_data(data, &m);
		return (1);
	}
	free_data(data, &m);
	return (0);
}
