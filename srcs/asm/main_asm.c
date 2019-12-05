/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_asm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtaja <gtaja@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 16:28:29 by gtaja             #+#    #+#             */
/*   Updated: 2019/11/03 18:02:12 by gtaja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
** Retourne le nom du fichier avec .cor au lieu de .s
*/

static char	*get_out_filename(char *source_file)
{
	char	*result;
	int		dot_pos;
	int		len;

	len = ft_strlen(source_file);
	dot_pos = len;
	while (--dot_pos > 0 && source_file[dot_pos] != '.')
		;
	result = ft_memalloc((len + 5) * sizeof(char));
	ft_strcpy(result, source_file);
	if (dot_pos <= 0)
		dot_pos = len;
	ft_strcpy(result + dot_pos, ".cor");
	return (result);
}

static int	print_usage(void)
{
	ft_putstr("Usage: ./asm <source1 [-o <output>]> ... ");
	ft_putstr("[source_n [-o <output>]]\n");
	return (0);
}

/*
** Affiche l'uage si besoin
** Retourne un boolean a TRUE si l'usage a été affiché
*/

static int	usage(int argc)
{
	if (argc > 1)
		return (FALSE);
	print_usage();
	return (TRUE);
}

int			main(int argc, char **argv)
{
	int		i;
	char	*source_file;
	char	*out_file;

	if (usage(argc))
		return (0);
	i = 0;
	while (++i < argc)
	{
		source_file = argv[i];
		ft_printf("[%20s] ", source_file);
		if (argc > i + 1 && ft_strequ("-o", argv[i + 1]))
		{
			if (argc <= i + 2)
				return (print_usage());
			out_file = ft_strdup(argv[i + 2]);
			i += 2;
		}
		else
			out_file = get_out_filename(source_file);
		parser_start(source_file, out_file);
		ft_memdel((void**)&out_file);
	}
	ft_clean_garbage();
	return (0);
}
