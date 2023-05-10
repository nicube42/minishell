/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivautrav <ivautrav@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 08:59:14 by ndiamant          #+#    #+#             */
/*   Updated: 2023/05/10 12:41:39 by ivautrav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_parsing(char *line, t_vars *vars)
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
		{
			quote = !quote;
			i++;
		}
		if (ft_is_quote(line[i]) == 2)
		{
			dquote = !dquote;
			i++;
		}
		if (ft_is_blank(line[i]) && !quote && !dquote)
		{
			k++;
			tmp[k] = malloc(sizeof(char) * (ft_token_len(line, 0) + 1));
			j = 0;
		}
		if (!ft_is_blank(line[i]) || quote || dquote)
		{
			tmp[k][j] = line[i];
			tmp[k][j + 1] = '\0';
			j++;
		}
		i++;
	}
	tmp[k + 1] = 0;
	ft_sort_tokens(tmp, vars);
}

char	**ft_parsing_execve(char **envp)
{
	int		i;
	char	*full_path;
	char	**splitted_path;

	i = 0;
	while (envp[++i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			full_path = envp[i] + 5;
	}
	splitted_path = ft_split(full_path, ':');
	i = -1;
	while (splitted_path[++i])
		splitted_path[i] = ft_strjoin(splitted_path[i], "/");
	return (splitted_path);
}

/*int	main(int ac, char **av, char **envp)
{
	t_vars	vars;

	(void) ac;
	(void) av;
	vars.splitted_path = ft_parsing_execve(envp);
	//ft_parsing("echo frkeofroe ls | cd $test", splitted_path);
	//ft_parsing("ARG=\"4 67 3 87 23\"; ./push_swap $ARG | ./checker_OS $ARG", splitted_path);
	ft_parsing("<< < ls -la | grep 'grep moi' ca | cd test $? $VAR >> >", &vars);
	return (0);
}*/
