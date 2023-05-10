/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_creator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 09:34:40 by ndiamant          #+#    #+#             */
/*   Updated: 2023/05/10 11:46:19 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*ft_init_token(void)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->prev = NULL;
	token->next = NULL;
	token->class = NULL;
	token->id = 0;
	return (token);
}

t_token	*ft_create_dollar_token(char *content, int id)
{
	t_token	*token;

	token = ft_init_token();
	token->id = id;
	token->class = ft_init_dollar_token(content, id);
	return (token);
}

t_dollar	*ft_init_dollar_token(char *content, int id)
{
	t_dollar	*dollar;

	dollar = (t_dollar *)malloc(sizeof(t_dollar));
	if (!dollar)
		return (NULL);
	dollar->id = id;
	dollar->content = content;
	dollar->fdin = STDIN_FILENO;
	dollar->fdout = STDOUT_FILENO;
	return (dollar);
}

t_token	*ft_create_redir_token(char *content, int id)
{
	t_token	*token;

	token = ft_init_token();
	token->id = id;
	token->class = ft_init_redir_token(content, id);
	return (token);
}

t_redir	*ft_init_redir_token(char *content, int id)
{
	t_redir	*redir;

	redir = (t_redir *)malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->id = id;
	redir->content = content;
	redir->fdin = STDIN_FILENO;
	redir->fdout = STDOUT_FILENO;
	return (redir);
}

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

void	ft_add_token(t_vars *vars, t_token *to_add)
{
	t_token	*tmp;

	if (!vars->first)
		vars->first = to_add;
	else
	{
		tmp = vars->first;
		while (tmp->next)
			tmp = tmp->next;
		ft_connect_token(tmp, to_add);
	}
}

void	ft_connect_token(t_token *list, t_token *to_add)
{
	list->next = to_add;
	to_add->prev = list;
}

void	ft_print_tokens(t_vars *vars)
{
	t_token	*token;
	t_redir	*redir;
	t_cmd	*cmd;
	t_dollar	*dollar;
	int		i;

	token = vars->first;
	printf("\n\n\n\n");
	while (token)
	{
		if (token->id >= 8 && token->id <= 10)
		{
			cmd = (t_cmd *)token->class;
			printf("%s token content (cmd)(id = %d)\n", cmd->content, token->id);
			i = 0;
			while (cmd->args[i])
			{
				printf("%s ", cmd->args[i]);
				i++;
			}
			printf("(cmd args)\n");
		}
		else if (token->id >= 1 && token->id <= 5)
		{
			redir = (t_redir *)token->class;
			printf("%s token content (redir)(id = %d)\n", redir->content, token->id);
		}
		else if (token->id >= 6 && token->id <= 7)
		{
			dollar = (t_dollar *)token->class;
			printf("%s token content (dollar)(id = %d)\n", dollar->content, token->id);
		}
		token = token->next;
	}
}
