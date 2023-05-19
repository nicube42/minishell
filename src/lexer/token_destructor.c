/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_destructor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 10:10:35 by ndiamant          #+#    #+#             */
/*   Updated: 2023/05/19 10:18:51 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_destroy_dollar(t_token *token)
{
	t_dollar	*dollar;

	dollar = (t_dollar *)token->class;
	dollar->content = 0;
	dollar ->id = 0;
	free (dollar);
	dollar = 0;
}

void	ft_destroy_redir(t_token *token)
{
	t_redir		*redir;

	redir = (t_redir *)token->class;
	redir->content = 0;
	redir->id = 0;
	free (redir);
	redir = 0;
}

void	ft_destroy_cmd(t_token *token)
{
	t_cmd	*cmd;
	int		i;

	cmd = (t_cmd *)token->class;
	i = 0;
	free(cmd->content);
	cmd->content = NULL;
	free(cmd->path);
	while (cmd->args[i])
	{
		free (cmd->args[i]);
		cmd->args[i] = NULL;
		i++;
	}
	free(cmd);
}

void	ft_delete_all_tokens(t_vars *vars)
{
	t_token		*token;

	token = vars->first;
	while (token)
	{
		if (token->id >= 8 && token->id <= 10)
			ft_destroy_cmd(token);
		else if (token->id >= 1 && token->id <= 5)
			ft_destroy_redir(token);
		else if (token->id >= 6 && token->id <= 7)
			ft_destroy_dollar(token);
		token->id = 0;
		token->class = 0;
		token = token->next;
	}
}
