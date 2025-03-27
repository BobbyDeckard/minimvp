/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeulema <imeulema@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 23:06:16 by imeulema          #+#    #+#             */
/*   Updated: 2025/03/27 13:30:34 by imeulema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/mvp.h"

char	*trunc_cwd(char *full)
{
    char    *cwd;
    char    *ptr;
    int     len;
    int     i;

    ptr = full;
    while (*ptr)
        ptr++;
    while (*ptr != '/')
        ptr--;
    ptr++;
    len = ft_strlen(ptr);
    cwd = (char *) malloc((len + 4) * sizeof(char));
    if (!cwd)
        exit (1);
    i = -1;
    while (++i < len)
        cwd[i] = ptr[i];
    cwd[i++] = ' ';
    cwd[i++] = '>';
    cwd[i] = ' ';
    free(full);
    return (cwd);
}

char	*make_cwd(void)
{
	char	*cwd;

    cwd = getcwd(NULL, 0);
    cwd = trunc_cwd(cwd);
    return (cwd);
}
