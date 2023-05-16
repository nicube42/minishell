/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 09:27:44 by ndiamant          #+#    #+#             */
/*   Updated: 2023/05/16 19:27:11 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <bashmaster.h>

int	ft_check_syntax(t_vars *vars)
{	
	if (ft_unclosed_quote_error(vars))
		return (0);
	if (ft_pipe_syntax_error(vars))
		return (0);
	if (ft_pipe_syntax_error_2(vars))
		return (0);
	if (ft_wrong_cmd_error(vars))
		return (0);
	return (1);
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
	if (vars->dquote || vars->quote)
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
					printf(RED "Unrecognised command : %s\n"RESET, ((t_cmd *)token->class)->content);
				token = token->next;
			}
			return (1);
		}
		token = token->next;
	}
	return (0);
}
