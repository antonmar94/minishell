/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonmar <antonmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 20:05:39 by albzamor          #+#    #+#             */
/*   Updated: 2022/05/31 22:44:38 by antonmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//FALTA LA MIERDA DE LAS COMILLAS AQUI TAMBIÉN

//Crear una lista con todos los archivos que voy a crear,
 //cuyo último será en el que este el resultado de lo que se ejecuta en la linea.

/* void	add_toline(char	**line, char **files)
{
	char	*no_arrow;
	char	*aux;

	no_arrow = *files;
	no_arrow++;
	while (*no_arrow && *no_arrow != '>') //buscar el proximo espacio que no tenga '>' despues
	{
		if (*no_arrow == ' ')
		{
			aux = no_arrow;
			while (*aux == ' ' && *aux != '>')
				aux++;
			if (*aux && *aux != '>')
			{
				*no_arrow++ = '\0';

			}
			no_arrow++;
		}
		no_arrow++;
	}	
		
	if (!*no_arrow)
	{
		no_arrow = *ptr;
		while (*no_arrow && *no_arrow != ' ')
			no_arrow++;
		if (*no_arrow == ' ')
		{
			*no_arrow++ = '\0';
			*line = ft_strjoin(*line, " ");
			*line = ft_strjoin(*line, ft_substr(no_arrow,
						0, ft_strlen(no_arrow)));
		}
	}
}

int	next_file(char **files, char **file_to_create)
{
	char	*ptr;
	int		size_file;

	ptr = *files;
	size_file = 0;
	while (*ptr && *ptr != '>')
	{
		ptr++;
		size_file++;
	}
	*file_to_create = ft_substr(*files, 0, size_file);
	if (!*ptr)
		return (0);
	open(*file_to_create, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	*files = ptr;
	return (1);
} 

void	find_files(char **line, char **redirect_file, int redirect_flag)
{
	char	*ptr;
	char	*files;
	char	*file_to_create;

	ptr = *redirect_file;
	files = *redirect_file;
	file_to_create = NULL;
	while (redirect_flag)
	{		
		while (*ptr && (*ptr == ' ' || *ptr == '>'))
			ptr++;
		files = ptr;
		add_toline(line, &files);
		redirect_flag = next_file(&files, &file_to_create);
		ptr = files;
	}
	*redirect_file = file_to_create;
}
*/

int	check_redirect(char **line, char **redirect_file)
{
	char	*ptr;

	ptr = *line;
	while (*ptr)
	{
		if (*ptr == '>')
		{
			*ptr++ = '\0';
			*redirect_file = ptr;
			if (*ptr == '>')
			{
				(*redirect_file)++;
				return (2);
			}
			else
				return (1);
		}
		ptr++;
	}
	return (0);
}

int	jump_quotes(char **line_to_ignore)
{
	char	quotes;
	int		size_quotes;

	size_quotes = 0;
	quotes = check_allquotes(*line_to_ignore);
	if (quotes)
	{
		(*line_to_ignore)++;
		size_quotes++;
		while (**line_to_ignore != quotes)
		{
			(*line_to_ignore)++;
			size_quotes++;
		}
		size_quotes++;
	}
	return (size_quotes);
}

int	get_file_size (char **line, char **files, char **next_file)
{
	char		*file_finder;
	int			size_file;
	char		*aux_append;
	int			size_append;
	
	size_file = 0;
	while (**files == '>' || **files == ' ')
		(*files)++;
	file_finder = *files;
	while (*file_finder && *file_finder != '>')
	{
		size_append = 0;
		size_file += jump_quotes(&file_finder);
		printf("file finder [%s]\n", file_finder);
		if (*file_finder == ' ')
		{
			while (*file_finder == ' ' && *file_finder != '>')
				file_finder++;
			printf("file finder encontro espacio [%s]\n", file_finder);
			if (!*file_finder || *file_finder != '>')
			{
				aux_append = file_finder;
				while (*aux_append && *aux_append != '>')
				{
					size_append += jump_quotes(&aux_append);
					aux_append++;
				}
				*line = ft_strjoin(*line, ft_substr(file_finder,
							0, size_append));
				*files = aux_append; 
				file_finder = *files;
			}
			else
				file_finder--;
		}
		size_file++;
		file_finder++;
	}
	*next_file = file_finder;
	return (size_file);
}

int	get_files(char **line, char **files, int num_arrows)
{
	int			size_file;
	char		*next_file;

	next_file = *files;
	printf("hola [%s]\n", next_file);
	while (next_file)
	{
		size_file = get_file_size(line, files, &next_file);
		printf("size file [%i]\n", size_file);
		if (!*next_file)
		{
			while (**files && **files == '>')
			{
				(*files)++;
				num_arrows++;
			}
			return (num_arrows);
		}
		open(ft_substr(*files, 0, size_file), O_WRONLY | O_CREAT | O_TRUNC, 0664);
		*files = next_file;
	}
	return (0);
}


void	do_redirect(t_shell *shell)
{
	int		num_arrows;
	char	*all_files;
	int		fd;

	all_files = NULL;
	num_arrows = check_redirect(&shell->line, &all_files);
	num_arrows = get_files(&shell->line, &all_files, num_arrows);
	if (num_arrows == 1)
	{
		fd = open(all_files, O_WRONLY | O_CREAT | O_TRUNC, 0664);
		dup2(fd, 1);
	}
	else if (num_arrows == 2)
	{
		fd = open(all_files, O_WRONLY | O_CREAT | O_APPEND, 0664);
		dup2(fd, 1);
	}
}
