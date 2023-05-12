/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 09:27:44 by ndiamant          #+#    #+#             */
/*   Updated: 2023/05/12 14:50:28 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <bashmaster.h>

void	ft_check_syntax(t_vars *vars)
{	
	if (ft_unclosed_quote_error(vars))
		return ;
	if (ft_pipe_syntax_error(vars))
		return ;
	if (ft_pipe_syntax_error_2(vars))
		return ;
	if (ft_wrong_cmd_error(vars))
		return ;
}

int	ft_pipe_syntax_error(t_vars *vars)
{
	t_token	*token;

	token = vars->first;
	if (token->id == 1)
	{
		printf(RED "No command before pipe\n"RESET);
		return (1);
	}
	while (token)
	{
		if (token->id != 8 && token->id != 9)
		{
			if (token->next)
			{
				token = token->next;
				if (token->id == 1)
				{
					printf(RED "No command before pipe\n"RESET);
					return (1);
				}
			}
		}
		token = token->next;
	}
	return (0);
}

int	ft_pipe_syntax_error_2(t_vars *vars)
{
	t_token	*token;

	token = vars->first;
	while (token)
	{
		if (token->id == 1 && token->next)
		{
			token = token->next;
			if (token->id != 8 && token->id != 9)
			{
				printf(RED "No command after pipe\n"RESET);
				return (1);
			}
		}
		token = token->next;
	}
	token = vars->first;
	while (token->next)
		token = token->next;
	if (token->id == 1)
	{
		printf(RED "No command after pipe\n"RESET);
		return (1);
	}
	return (0);
}

int	ft_unclosed_quote_error(t_vars *vars)
{
	if (vars->quote_error)
	{
		printf(RED "Unclosed quote detected\n" RESET);
		return (1);
	}
	return (0);
}

int	ft_wrong_cmd_error(t_vars *vars)
{
	t_token	*token;

	token = vars->first;
	while (token)
	{
		if (token->id == 10)
		{
			while (token)
			{
				if (token->id == 10)
					printf(RED "Unrecognised command detected : %s\n"RESET, ((t_cmd *)token->class)->content);
				token = token->next;
			}
			return (1);
		}
		token = token->next;
	}
	return (0);
}
