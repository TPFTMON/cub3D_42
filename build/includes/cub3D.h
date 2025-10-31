/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 21:56:46 by abaryshe          #+#    #+#             */
/*   Updated: 2025/10/31 21:03:11 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// <<<<<<<<<<<<<<<<<<<<< INCLUDES >>>>>>>>>>>>>>>>>>>>>

# include "libft.h"
# include "mlx.h"

# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

// <<<<<<<<<<<<<<<<<<<<< MACROS >>>>>>>>>>>>>>>>>>>>>

// --- General ---
# define SUCCESS 0
# define FAIL 1

// --- File Descriptors ---
# define STDIN_FD 0
# define STDOUT_FD 1
# define STDERR_FD 2

// --- Exit Codes ---
# define EXC_OK 0   // We MAY want to add our own different codes. MAYBE for parsing.
# define EXC_CRIT 1 // !!!
# define EXC_PARS 2 // !!!

// --- Internal Error Codes ---
# define OKAY 0
# define CRITICAL 1
# define SYNTAX 2

// --- Messages ---
# define ERR_CRITICAL "\e[1;31mcritical error\e[0m: memory failure.\n"


// // --- Some Colors ---
// # define RESET "\e[0m"
// # define BOLD "\e[1m"
// # define GREEN "\e[32m"
// # define YELLOW "\e[33m"
// # define CYAN "\e[36m"

// --- Required By Game ---
# define TILE_EMPTY 0
# define TILE_WALL 1
# define TILE_OUT  -1

// <<<<<<<<<<<<<<<<<<<<< STRUCTURES >>>>>>>>>>>>>>>>>>>>>

typedef enum	e_tex
{
	NO, 	// North
	SO, 	// South
	WE, 	// West
	EA, 	// East
	TEX_NB  // Number of textures
}			t_tex;

typedef struct s_img
{
	void		*img_ptr;
	char		*addr; // mlx_get_data_addr

	int			bpp;
	int			line_len;
	int			endian;
	int			width;
	int			height;
}				t_img;

typedef struct s_player
{
	double		pos_x;
	double		pos_y;             // position in map coords (float)

	double		dir_x;
	double		dir_y;       // direction vector (normalized)

	double		plane_x;
	double		plane_y; // camera plane (perp to dir)

	double		move_speed;
	double		rot_speed;

	t_tex		direction;
}				t_player;

typedef struct s_map
{
	char		**raw;     // array of strings from parser (keep for error messages)

	int			width;      // max row length
	int			height;     // number of rows
	char		**grid;    // rectangular map (same dims as width x height)

	char		*texture_paths[TEX_NB];
}				t_map;

typedef struct s_cube
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			win_width;
	int			win_height;

	t_img		screen;
	t_img		textures[TEX_NB]; // EA, WE, NO, SO
	int			floor_color; // packed RGB
	int			ceil_color;

	t_player	player;
	t_map		map;

	bool		key_w;
	bool		key_s;
	bool		key_a;
	bool		key_d;
	bool		key_lar;
	bool		key_rar;

	double		delta_time;
}				t_cube;

// <<<<<<<<<<<<<<<<<<<<< FUNCTIONS >>>>>>>>>>>>>>>>>>>>>

// -------------------- general --------------------
// init.c:
int				init_mlx_cube(t_cube *cube);


// -------------------- parsing --------------------

// ...

// -------------------- engine --------------------


// testing: parsing.c + engine.c:
void			parsing_report(void);
void			engine_report(void);

#endif
