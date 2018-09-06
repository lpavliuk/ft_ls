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

void	free_list(t_info *head)
{
	while (head)
	{
		free(head->name);
		head = head->next;
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
