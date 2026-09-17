/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/16 17:56:31 by nicolas           #+#    #+#             */
/*   Updated: 2026/09/17 02:04:14 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	main(int argc, char **argv)
{
	int			check;

	if (argc == 9)
		check = check_arg(argc - 1, &argv[1]);
	else
	{
		printf("ERROR! not 8 arguments!");
		return (1);
	}
	printf("%d\n", check);
	return (0);
}
