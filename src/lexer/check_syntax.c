/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 09:27:44 by ndiamant          #+#    #+#             */
/*   Updated: 2023/05/12 10:31:39 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <bashmaster.h>

void	ft_check_syntax(t_vars *vars)
{
	t_token	*token;

	token = vars->first;
	if (vars->quote_error)
	{
		printf(RED "Unclosed quote detected\n" RESET);
		return ;
	}
	while (token)
	{
		if (token->id == 10)
		{
			printf(RED "Unrecognised command detected : %s\n"RESET, ((t_cmd *)token->class)->content);
			return ;
		}
		/*if (token->id == 1 && token->prev->id != 8 && token->prev->id != 9)
		{
			printf(RED "No command before pipe : %s\n"RESET, ((t_cmd *)token->class)->content);
			return ;
		}*/
		token = token->next;
	}
}
