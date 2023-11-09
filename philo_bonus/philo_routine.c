/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaruso <ecaruso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:34:55 by ecaruso           #+#    #+#             */
/*   Updated: 2023/11/09 14:46:15 by ecaruso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	eat(t_philo *philo)
{
	sem_wait(philo->env->sem_eat);
	message(philo, FORK);
	sem_wait(philo->env->sem_eat);
	message(philo, FORK);
	philo->time_left = get_time();
	philo->is_eating = 1;
	message(philo, EAT);
	my_usleep(philo->env->time_to_eat);
	philo->eat_count++;
	philo->is_eating = 0;
	sem_post(philo->env->sem_eat);
	sem_post(philo->env->sem_eat);
}

void	*supervisor(void *data)
{
	t_philo	*philo;

	philo = (t_philo *) data;
	philo->time_left = get_time();
	while ((get_time() - philo->time_left) < (u_int64_t) philo->env->time_to_die
		&& (philo->env->max_eat == -1
			|| philo->eat_count < philo->env->max_eat))
		usleep(100);
	if (philo->eat_count >= philo->env->max_eat && philo->env->max_eat != -1)
	{
		philo->is_alive = 0;
	}
	else
	{
		sem_wait(philo->env->sem_dead);
		message(philo, DIE);
		philo->is_alive = 0;
		exit(2);
		sem_post(philo->env->sem_dead);
	}
	return ((void *) 0);
}

void	routine(t_philo *philo)
{
	while (philo->is_alive)
	{
		eat(philo);
		message(philo, SLEEP);
		my_usleep(philo->env->time_to_sleep);
		message(philo, THINK);
	}
}

int	play(t_env *env, int philo_id)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		env->philo.id = philo_id;
		if (env->philo.id % 2 != 0 && env->number_of_philosophers > 1)
			my_usleep(10);
		pthread_create(&env->philo.supervisor, NULL, &supervisor, &env->philo);
		pthread_detach(env->philo.supervisor);
		routine(&env->philo);
		exit(2);
	}
	else
		env->pid[200] = pid;
	return (0);
}
