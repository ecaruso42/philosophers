/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaruso <ecaruso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 16:41:41 by ecaruso           #+#    #+#             */
/*   Updated: 2023/10/17 19:51:13 by ecaruso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	check_input(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (ft_atoi(argv[i]) <= 0)
			return (0);
		i++;
	}
	return (1);
}

int	init(t_env *env, int argc, char **argv)
{
	env->number_of_philosophers = ft_atoi(argv[1]);
	env->time_to_die = ft_atoi(argv[2]);
	env->time_to_eat = ft_atoi(argv[3]);
	env->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		env->max_eat = ft_atoi(argv[5]);
	else
		env->max_eat = -1;
	env->table = (t_philo *)malloc(sizeof(t_philo)
			* env->number_of_philosophers);
	printf("%d%d", env->number_of_philosophers, env->time_to_sleep);
	free(env->table);
	return (1);
}
