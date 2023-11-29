SRC = main.c parsing/check_map.c parsing/check_textures.c parsing/check_rgb.c parsing/ft_rgb_insert.c parsing/ft_rgb_c_insert.c \
		textures/draw_textures.c textures/textures_move.c parsing/check_walls.c parsing/check_elements.c \
		parsing/ft_separate_map.c
NAME = cub3d
CC = cc
CFLAGS =
RM = rm -rf
INCLUDES = -Iinclude ./MLX42/libmlx42.a  -lglfw -L"/Users/sbellafr/.brew/opt/glfw/lib" 
INCLUDE =
 .SILENT: 
all: $(NAME)
	@echo "\033[104mThe mandatory part is made\033[0m"

$(NAME): $(SRC)
		 make bonus -C libft
		 $(CC) -Ilibft $(INCLUDES) -framework Cocoa -framework OpenGL -framework IOKit $(CFLAGS) ./libft/libft.a $(SRC)  -o $(NAME)

%.o : %.c
	$(CC) -Ilibft $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME) 

re: fclean all