/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 13:07:34 by ndiamant          #+#    #+#             */
/*   Updated: 2023/05/14 19:33:44 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_token	*ft_create_cmd_token(char *content, int id, char **args, t_vars *vars)
{
	t_token	*token;

	token = ft_init_token();
	token->id = id;
	token->class = ft_init_cmd_token(content, id, args, vars);
	return (token);
}

t_cmd	*ft_init_cmd_token(char *content, int id, char **args, t_vars *vars)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->id = id;
	cmd->content = content;
	cmd->args = args;
	cmd->path = vars->tmp_path;
	cmd->fdin = STDIN_FILENO;
	cmd->fdout = STDOUT_FILENO;
	return (cmd);
}
