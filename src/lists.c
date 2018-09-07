/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opavliuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 18:54:23 by opavliuk          #+#    #+#             */
/*   Updated: 2018/09/05 18:54:24 by opavliuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ls.h"

void	free_lists(t_dir *list)
{
	t_info *tmp;

	while (list)
	{
		while (list->head)
		{
			tmp = list->head;
			free(list->head->name_file);
			list->head = list->head->next;
			free(tmp);
		}
		free(list->name);
		list = list->next;
	}
}

t_dir	*new_dir(t_dir **dir, const char *name)
{
	t_dir *new;

	new = *dir;
	if (!(*dir))
	{
		*dir = (t_dir *)malloc(sizeof(t_dir));
		ft_bzero(*dir, sizeof(t_dir));
		(*dir)->name = ft_strdup(name);
		return (*dir);
	}
	else
	{
		while (new->next)
			new = new->next;
		new->next = (t_dir *)malloc(sizeof(t_dir));
		ft_bzero(new->next, sizeof(t_dir));
		new->next->name = ft_strdup(name);
		return (new->next);
	}
}

t_info	*new_file(t_info **head)
{
	t_info *new;

	new = *head;
	if (!(*head))
	{
		*head = (t_info *)malloc(sizeof(t_info));
		ft_bzero(*head, sizeof(t_info));
		return (*head);
	}
	else
	{
		while (new->next)
			new = new->next;
		new->next = (t_info *)malloc(sizeof(t_info));
		ft_bzero(new->next, sizeof(t_info));
		return (new->next);
	}
}
