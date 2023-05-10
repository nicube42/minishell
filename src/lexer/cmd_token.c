/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasdiamantis <nicolasdiamantis@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 13:07:34 by ndiamant          #+#    #+#             */
/*   Updated: 2023/05/10 19:07:59 by nicolasdiam      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_token	*ft_create_cmd_token(char *content, int id, char **args)
{
	t_token	*token;

	token = ft_init_token();
	token->id = id;
	token->class = ft_init_cmd_token(content, id, args);
	return (token);
}

t_cmd	*ft_init_cmd_token(char *content, int id, char **args)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->id = id;
	cmd->content = content;
	cmd->args = args;
	cmd->fdin = STDIN_FILENO;
	cmd->fdout = STDOUT_FILENO;
	return (cmd);
}
