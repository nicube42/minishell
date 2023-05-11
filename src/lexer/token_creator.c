/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_creator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 09:34:40 by ndiamant          #+#    #+#             */
/*   Updated: 2023/05/11 12:10:51 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
	t_token		*token;
	t_redir		*redir;
	t_cmd		*cmd;
	t_dollar	*dollar;
	int		i;

	token = vars->first;
	while (token)
	{
		if (token->id >= 8 && token->id <= 10)
		{
			cmd = (t_cmd *)token->class;
			printf("Token content : %s \n 			(cmd)(id = %d)(path = %s)\n", cmd->content, token->id, cmd->path);
			i = 0;
			printf("Cmd args content : ");
			while (cmd->args[i])
			{
				printf("%s ", cmd->args[i]);
				i++;
			}
			printf("\n\n");
		}
		else if (token->id >= 1 && token->id <= 5)
		{
			redir = (t_redir *)token->class;
			printf("Token content : %s \n 			(redir)(id = %d)\n", redir->content, token->id);
		}
		else if (token->id >= 6 && token->id <= 7)
		{
			dollar = (t_dollar *)token->class;
			printf("Token content : %s \n 			(dollar)(id = %d)\n", dollar->content, token->id);
		}
		token = token->next;
	}
}

void	ft_delete_all_tokens(t_vars *vars)
{
	t_token		*token;
	t_cmd		*cmd;
	t_redir		*redir;
	t_dollar	*dollar;
	int			i;

	token = vars->first;
	while (token)
	{
		if (token->id >= 8 && token->id <= 10)
		{
			cmd = (t_cmd *)token->class;
			i = 0;
			free(cmd->content);
			cmd->content = NULL;
			while (cmd->args[i])
			{
				free (cmd->args[i]);
				i++;
			}
			free(cmd);
		}
		else if (token->id >= 1 && token->id <= 5)
		{
			redir = (t_redir *)token->class;
			free (redir);
		}
		else if (token->id >= 6 && token->id <= 7)
		{
			dollar = (t_dollar *)token->class;
			free (dollar);
		}
		if (token->prev)
		{
			free(token->prev);
			token = token->next;
		}
		else
			return ;
	}
}
