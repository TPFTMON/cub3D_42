/* ************************************************************************** */
/*                                                                            */
/*                                                                 */
/*   cub3D.h                                            +      +    +   */
/*                                                    ++ ++         ++     */
/*   By abaryshe <abaryshe@student.42.fr>          +#+  ++       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created 2025/10/21 215646 by abaryshe          #+#    #+#             */
/*   Updated 2025/12/16 150446 by abaryshe         ###   ########.fr       */
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
# define EXC_OK 0
# define EXC_CRIT 1
# define EXC_PARS 2

// --- Internal Error Codes ---
# define OKI 0
# define CRITICAL 1
# define SYNTAX 2

// --- Window Dimensions ---
# define WIN_WIDTH 1280
# define WIN_HEIGHT 720

// --- Keycodes ---
# define KEY_ESC 65307
# define KEY_W 119
# define KEY_S 115
# define KEY_A 97
# define KEY_D 100
# define KEY_LAR 65361
# define KEY_RAR 65363

// --- Messages ---
# define ERROR "Error\n"
# define ERR_CRITICAL "\e[1;31mcritical error\e[0m: memory failure.\n"

# define ERR_NO_TEX "Error\nParsing: wrong path to North texture\n"
# define ERR_SO_TEX "Error\nParsing: wrong path to South texture\n"
# define ERR_EA_TEX "Error\nParsing: wrong path to East texture\n"
# define ERR_WE_TEX "Error\nParsing: wrong path to West texture\n"

# define MSG_EXIT "\e[1;32mExiting cub3D... Bye!\e[0m\n"

// <<<<<<<<<<<<<<<<<<<<< STRUCTURES >>>>>>>>>>>>>>>>>>>>>

typedef enum e_tex
{
	NO,    // North
	SO,    // South
	WE,    // West
	EA,    // East
	TEX_NB // Number of textures
}				t_tex;

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
	double		pos_y;           // position in map coords (float)

	double		dir_x;
	double		dir_y;       // direction vector (normalized)

	double		plane_x;
	double		plane_y; // camera plane (perp to dir)

	double		move_speed;
	double		rot_speed;
}				t_player;

/**
 * This is the main struct for the parser to populate
 */
typedef struct s_map
{
	char		**raw;   // array of strings from parser (keep for error messages)

	int			width;     // max row length
	int			height;       // number of rows

	int			color_floor;     // packed RGB
	int			color_ceil;

	char		*texture_paths[TEX_NB];
	t_tex		player_direction;

	int			spawn_x;
	int			spawn_y;
	bool		has_spawn; // will need for cude->player.pos_x/pos_y
	bool		has_floor;
	bool		has_ceil;

	char		**grid; // rectangular map (same dims as width x height)
}				t_map;

typedef struct s_cube
{
	void		*mlx_ptr;
	void		*win_ptr;

	t_img		screen;
	t_img		textures[TEX_NB]; // NO, SO, WE, EA

	t_player	player;
	t_map		map;

	bool		key_w;
	bool		key_s;
	bool		key_a;
	bool		key_d;
	bool		key_lar;
	bool		key_rar;

	long long	last_frame_time;
	double		delta_time;
}				t_cube;

// <<< engine structs >>>
typedef struct s_ray
{
	double		camera_x;
	double		dir_x;
	double		dir_y;
	int			map_x;
	int			map_y;
	int			step_x;
	int			step_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		perp_wall_dist;
	int			side;            // 0 for NS, 1 for EW
	int			line_height;
	int			draw_start;
	int			draw_end;
}				t_ray;

typedef struct s_render
{
	t_img		*texture;
	double		wall_x;
	int			tex_x;
	int			tex_y;
	double		step;
	double		tex_pos;
	int			y;
	int			color;
}				t_render;

// <<<<<<<<<<<<<<<<<<<<< FUNCTIONS >>>>>>>>>>>>>>>>>>>>>

// -------------------- engine --------------------

// game_loop.c
int				game_loop(void *arg);
void			update_player(t_cube *cube);

// hooks.c
void			init_hooks(t_cube *cube);

// raycaster.c
void			perform_raycasting(t_cube *cube);

// draw_and_extract.c
void			my_pixel_put(struct s_img *img, int x, int y, int color);
void			draw_ceiling_floor(t_img *img, int ceil_col, int floor_col);
int				get_texture_pixel_color(t_img *tex, int x, int y);

// player_move.c
void			move_player_forward(t_cube *cube);
void			move_player_backward(t_cube *cube);
void			move_player_left(t_cube *cube);
void			move_player_right(t_cube *cube);

// player_view.c
void			shift_view_left(t_cube *cube);
void			shift_view_right(t_cube *cube);

// textures.c
void			render_wall_strip(t_ray *ray, int x, t_cube *cube);

// testing engine:
void			test_ALL_engine(t_cube *cube);
void			test_set_ceil_floor(t_cube *cube);
void			test_fill_grid(t_map *map, int width, int height);
void			test_set_position_on_grid(t_cube *cube, int x, int y);
void			print_grid(t_map *map);
void			render_test_flat_color(t_ray *ray, int x, t_cube *cube);
// void    test_set_player(t_cube *cube);

// -------------------- core --------------------

// init.c
t_cube			*init_data_cube(void);
int				init_mlx_cube(t_cube *cube);

// init_player.c
void			init_player(t_cube *cube);

// init_textures.c
int				init_textures(t_cube *cube);

// cleanup.c
void			*free_cube(t_cube *cube);
int				ft_cleanup(t_cube *cube);

// -------------------- parsing --------------------
void			handle_error(const char *msg);
char			*skip_spaces(char *s);
void			trim_newline(char *s);
int				is_only_spaces(const char *s);
int				is_valid_map_char(char c);
int				pack_rgb(int r, int g, int b);
int				starts_with_id(const char *s, const char *id);
const char		*text_id(t_tex t);
void			parse_texture(t_map *map, char *line, t_tex texture_type);
int				parse_u8(char **p);
void			expect_char(char **p, char c);
void			parse_floor_ceiling_colors(t_map *map, char *line);
void			set_spawn(t_map *map, int x, int y, char c);
void			parse_map(t_map *map, char *line, int row);
char			cell(t_map *m, int y, int x);
void			build_grid(t_map *map);
void			validate_map(t_map *map);
bool			starts_with_id_local(const char *s, const char *id);
bool			looks_like_map_line(char *line);
void			parse_config_line(t_map *map, char *line);
void			require_all_elements(t_map *map);
void			parse_cub_file(t_cube *cube, const char *path);
void			parsing_report(void);

// textures.c
void			load_one(t_cube *cube, t_tex t);
int				load_textures(t_cube *cube);

void			engine_report(void);
void			update_player(t_cube *cube);

#endif
