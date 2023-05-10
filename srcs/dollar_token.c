/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 13:08:41 by ndiamant          #+#    #+#             */
/*   Updated: 2023/05/10 13:09:09 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
