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

// caprice esthétique de ma part, pour afficher le directoire de travail
// actuel (ou cwd pour Current Working Directory), récupère le path
// complet avec getcwd(), puis coupe tout ce qui précède le dernier /
// (compris) et ajoute " > "
// sera superflu d'appeler cette fonction entre chaque commande
// uniquement appeler en changeant de directoire
char	*make_cwd(void)
{
	char	*cwd;

    cwd = getcwd(NULL, 0);
    cwd = trunc_cwd(cwd);
    return (cwd);
}
