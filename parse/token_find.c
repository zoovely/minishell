/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_find.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojoo <sojoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 04:18:06 by sojoo             #+#    #+#             */
/*   Updated: 2022/08/31 00:39:14 by sojoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static int	free_and_return(char *str, int i)
{
	if (str != NULL)
		free(str);
	return (i);
}

int	envp_in_value(t_token *tokenlist, int i, int *j)
{
	char	*envp;
	t_envp	*env;

	env = g_env;
	if (*j == i + 1)
		return (1);
	envp = ft_strdup_idx(i + 1, *j - 1, tokenlist->value);
	if (envp == NULL)
		return (0);
	while (env != NULL)
	{
		if (ft_strequal(envp, env->key))
		{
			if (replace_value(tokenlist, env, i, j) == 0)
				return (free_and_return(envp, 0));
			break ;
		}
		env = env->next;
	}
	if (env == NULL)
	{
		if (no_env_key(tokenlist, i, j) == 0)
			return (free_and_return(envp, 0));
	}
	return (free_and_return(envp, 1));
}

int	find_word(char *str, int i)
{
	i++;
	while (str[i] != ' ' && str[i] != '\0' && str[i] != '|' && str[i] != '>' \
		&& str[i] != '<' && str[i] != '\'' && str[i] != '\"')
		i++;
	return (i);
}
