/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeulema <imeulema@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 13:03:56 by imeulema          #+#    #+#             */
/*   Updated: 2025/03/28 13:05:10 by imeulema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/mvp.h"

char	**split_paths(void)
{
	char	**paths;
	char	*str;

	str = getenv("PATH");
	paths = ft_split_path(str, ':');
	return (paths);
}
