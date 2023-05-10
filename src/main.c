/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasdiamantis <nicolasdiamantis@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:50:25 by ivautrav          #+#    #+#             */
/*   Updated: 2023/05/10 19:42:58 by nicolasdiam      ###   ########.fr       */
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
		/*if (!check_syntax(&bash))
		{
			ft_printf("Syntax Error detected\n");
			continue ;
		}
		parsing_execve(&bash);
		execute_command(&bash);*/
		ft_delete_all_tokens(&vars);
	}
	return (0);
}
