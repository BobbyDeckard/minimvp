/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeulema <imeulema@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 12:54:55 by imeulema          #+#    #+#             */
/*   Updated: 2025/03/28 13:01:45 by imeulema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/mvp.h"

int		count_args_b_pipe(t_token *ptr)
{
	int	count;

	count = 1;
	while (ptr->type != 12)
	{
		count++;
		ptr = ptr->next;
	}
	return (count);
}

int		count_args_a_pipe(t_token *ptr)
{
	int	count;

	count = 1;
	while (ptr->type != 12)
		ptr = ptr->next;
	ptr = ptr->next;
	while (ptr)
	{
		count++;
		ptr = ptr->next;
	}
	return (count);
}

void	get_pipe_args(t_cmd *cmd1, t_cmd *cmd2, t_token **token_list)
{
	t_token	*ptr;
	int		count;
	int		i;

	count = count_args_b_pipe(*token_list);
	cmd1->args = (char **) malloc(count * sizeof(char *));
	if (!cmd1->args)
		exit (1);
	ptr = *token_list;
	i = -1;
	while (++i + 1 < count)
	{
		cmd1->args[i] = ptr->content;
		ptr = ptr->next;
	}
	cmd1->args[i] = NULL;
	count = count_args_a_pipe(*token_list);
	cmd2->args = (char **) malloc(count * sizeof(char *));
	if (!cmd2->args)
		exit (1);
	ptr = ptr->next;
	i = -1;
	while (++i + 1 < count)
	{
		cmd2->args[i] = ptr->content;
		ptr = ptr->next;
	}
}
