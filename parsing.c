/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 08:59:14 by ndiamant          #+#    #+#             */
/*   Updated: 2023/05/09 11:52:48 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_parsing(char *line)
{
	int		i;
	int		j;
	int		k;
	int		quote;
	int		dquote;
	char	**tmp;

	j = 0;
	k = 0;
	tmp = malloc(sizeof(char *) * (ft_token_qty(line) + 2));
	tmp[k] = malloc(sizeof(char) * (ft_token_len(line, 0) + 1));
	if (!tmp)
		exit(1);
	quote = 0;
	dquote = 0;
	i = 0;
	while (line[i])
	{
		if (ft_is_quote(line[i]) == 1)
			quote = !quote;
		if (ft_is_quote(line[i]) == 2)
			dquote = !dquote;
		if (ft_is_blank(line[i]) && !quote && !dquote)
		{
			k++;
			tmp[k] = malloc(sizeof(char) * (ft_token_len(line, 0) + 1));
			j = 0;
			i++;
		}
		tmp[k][j] = line[i];
		j++;
		i++;
	}
	tmp[k + 1] = 0;
	ft_sort_tokens(tmp);
}

int	main(void)
{
	ft_parsing("echo test $test");
	//ft_parsing("ARG=\"4 67 3 87 23\"; ./push_swap $ARG | ./checker_OS $ARG");
	return (0);
}
