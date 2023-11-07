/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaruso <ecaruso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:34:55 by ecaruso           #+#    #+#             */
/*   Updated: 2023/11/07 19:54:37 by ecaruso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	eat(t_philo *philo)
{
	sem_wait(philo->env->sem_lock);
	message(philo, FORK);
	sem_wait(philo->env->sem_lock);
	message(philo, FORK);
	philo->is_eating = 1;
	philo->time_left += philo->env->time_to_die;
	message(philo, EAT);
	my_usleep(philo->env->time_to_eat);
	philo->eat_count++;
	philo->is_eating = 0;
	sem_post(philo->env->sem_lock);
	sem_post(philo->env->sem_lock);
}

void	die_all(t_env *env)
{
	env->philo.is_alive = 0;
	sem_close(env->sem_lock);
	sem_close(env->sem_dead);
	sem_close(env->sem_eat);
}

void	*supervisor(void *data)
{
	t_philo	*philo;

	philo = (t_philo *) data;
	while (get_time() < philo->time_left && (philo->env->max_eat == -1
			|| philo->eat_count < philo->env->max_eat))
		;
	if (philo->eat_count >= philo->env->max_eat && philo->env->max_eat > 0)
	{
		philo->is_alive = 0;
		exit(2);
	}
	else
	{
		sem_wait(philo->env->sem_dead);
		die_all(philo->env);
		message(philo, DIE);
		exit(2);
		sem_post(philo->env->sem_dead);
	}
	return ((void *) 0);
}

void	routine(t_philo philo)
{
	philo.time_left = philo.env->time_to_die + get_time();
	if (philo.id % 2 != 0 && philo.env->number_of_philosophers > 1)
		my_usleep(10);
	pthread_create(&philo.supervisor, NULL, &supervisor, &philo);
	pthread_detach(philo.supervisor);
	while (philo.is_alive)
	{
		if (philo.env->number_of_philosophers == 1)
			case_one(philo.env);
		else
		{
			eat(&philo);
			sem_wait(philo.env->sem_eat);
			message(&philo, SLEEP);
			my_usleep(philo.env->time_to_sleep);
			message(&philo, THINK);
			sem_post(philo.env->sem_eat);
		}
	}
}

int	play(t_env *env, int philo_id)
{
	pid_t	pid;
	
	pid = fork();
	if(pid == 0)
	{
		env->philo.id = philo_id;
		routine(env->philo);
		exit(0);
	}
	else
		env->pid[200] = pid;
	return (0);
}
