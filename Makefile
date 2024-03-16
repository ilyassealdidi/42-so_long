NAME = so_long

B_NAME = so_long_bonus

SRCS = src/main.c src/map.c src/gameplay.c src/parse.c src/utils.c src/window.c helpers/get_next_line/get_next_line.c

OBJS = $(SRCS:.c=.o)

B_SRCS = bonus/src/main.c bonus/src/map.c bonus/src/gameplay.c bonus/src/parse.c bonus/src/utils.c bonus/src/window.c \
		helpers/get_next_line/get_next_line.c

LIBRARY = -lmlx -framework OpenGL -framework AppKit

INC = includes/so_long.h includes/dictionnary.h

CFLAGS = -Wall -Wextra -Werror 

LIBFT = helpers/libft/libft.a

FT_PRINTF = helpers/ft_printf/libftprintf.a

all : $(NAME)

$(NAME) : $(OBJS) $(LIBFT) $(FT_PRINTF)
	cc $(OBJS) $(LIBFT) $(FT_PRINTF) $(LIBRARY) -o $(NAME)

%.o : %.c $(INC)
	cc $(CFLAGS) -c $< -o $@

$(LIBFT):
	make -C helpers/libft/

$(FT_PRINTF):
	make -C helpers/ft_printf/

bonus: $(B_NAME)

$(B_NAME) : $(B_SRCS) $(LIBFT) $(FT_PRINTF) bonus/includes/so_long_bonus.h includes/dictionnary.h
	cc $(CFLAGS) $(B_SRCS) $(LIBRARY) $(LIBFT) $(FT_PRINTF) -o $(B_NAME)

clean :
	make clean -C helpers/libft/
	make clean -C helpers/ft_printf/
	$(RM) $(OBJS)

fclean : clean
	make fclean -C helpers/libft/
	make fclean -C helpers/ft_printf/
	$(RM) $(NAME) $(B_NAME)

re : fclean all
