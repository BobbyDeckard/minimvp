/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeulema <imeulema@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 17:37:39 by imeulema          #+#    #+#             */
/*   Updated: 2025/05/09 12:18:43 by imeulema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

char	*get_str(const char *name)
{
	char	*str;

	str = getenv(name);
	if (!str)
	{
		perror(name);
		return (NULL);
	}
	return (str);
}

void	print_var(char *var, t_cmd cmd)
{
	ft_putstr_fd(var, cmd.fd_out);
	ft_putchar_fd('\n', cmd.fd_out);
}

void	print_variable(t_ast *env, const char *name)
{
	char	*var;
	char	*str;
	int		str_len;
	int		len;

	str = get_str(name);
	if (str)
	{
		str_len = ft_strlen(str);
		len = str_len + ft_strlen(name) + 2;	// + 2 accounts for the added '=' and the NULL-termination of the string
		var = (char *) malloc(len * sizeof(char));
		if (!var)
			malloc_error(env);
		ft_strlcat(var, name, len);
		ft_strlcat(var, "=", len);
		ft_strlcat(var, str, len);
		print_var(var, env->cmd);
		free(var);
	}
}

int	count_variables(t_ast *env)
{
	int	count;

	if (!env->root->envp)
		return (0);
	count = 0;
	while (env->root->envp[count])
		count++;
	return (count);
}

char	*get_variable(t_ast *env, char *full)
{
	char	*var;
	int		i;

	i = 0;
	while (full[i] != '=')
		i++;
	var = (char *) malloc(i * sizeof(char));
	if (!var)
		malloc_error(env);
	i = -1;
	while (full[++i] != '=')
		var[i] = full[i];
	var[i] = 0;
	return (var);
}

char	**get_env_variables(t_ast *env, int count)
{
	char	**variables;
	int		i;

	variables = (char **) malloc(count * sizeof(char *));
	if (!variables)
		malloc_error(env);
	i = -1;
	while (env->root->envp[++i])
		variables[i] = get_variable(env, env->root->envp[i]);
	return (variables);
}

int	env(t_ast *env)
{
	char	**variables;
	int		count;
	int		i;

	if (make_redirs(env, &env->cmd) == FAILURE)
		return (FAILURE);
	count = count_variables(env);
	if (count)
		variables = get_env_variables(env, count);
	i = -1;
	while (++i < count)
	{
		print_variable(env, variables[i]);
		free(variables[i]);
	}
	free(variables);
	return (SUCCESS);
}
