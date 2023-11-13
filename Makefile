SRC = main.c drawing/check.c drawing/dda.c drawing/draw.c drawing/render.c
NAME = cub3d
CC = cc
CFLAGS = 
RM = rm -rf
INCLUDES = -Iinclude ./MLX42/build/libmlx42.a  -lglfw -L"/Users/zbenaiss/goinfre/homebrew/opt/glfw/lib"
# INCLUDE = -Iinclude
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