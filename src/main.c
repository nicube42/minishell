/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:50:25 by ivautrav          #+#    #+#             */
/*   Updated: 2023/05/17 08:48:20 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bashmaster.h>
#include <minishell.h>
#include <readline/readline.h>
#include <readline/history.h>

int	main(int ac, char *av[], char *envp[])
{
	t_vars	vars;
	t_token	*tmp;
	char	*input;

	(void) ac;
	(void) av;
	vars.splitted_path = ft_parsing_execve(envp);
	using_history();
	write(1, "\n", 1);
	while (TRUE)
	{
		vars.first = NULL;
		input = readline(GREEN "[ 🎓 BashMaster 🎓 ] > " RESET);
		if (input[0] == '\0')
			continue ;
		add_history(input);
		ft_parsing(input, &vars);
		(void) tmp;
		tmp = vars.first;
		//if (ft_check_syntax(&vars))
		//	execute_command(&vars);
		ft_print_tokens(&vars);
		ft_delete_all_tokens(&vars);
		//ft_print_tokens(&vars);
	}
	return (0);
}
