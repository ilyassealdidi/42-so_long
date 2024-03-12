NAME = so_long

B_NAME = so_long_bonus

SRCS = src/*.c helpers/get_next_line/get_next_line.c

B_SRCS = bonus/src/*.c helpers/get_next_line/get_next_line.c

LIBRARY = -lmlx -framework OpenGL -framework AppKit

CFLAGS = -Wall -Wextra -Werror 

LIBFT = helpers/libft

LIBFT = helpers/libft/libft.a

FT_PRINTF = helpers/ft_printf/libftprintf.a

all : $(NAME)

$(NAME): $(SRCS) $(LIBFT) $(FT_PRINTF) includes/so_long.h includes/dictionnary.h
	cc $(CFLAGS) $(SRCS) $(LIBRARY) $(LIBFT) $(FT_PRINTF) -o $(NAME)

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

fclean :
	make fclean -C helpers/libft/
	make fclean -C helpers/ft_printf/
	$(RM) $(NAME) $(B_NAME)

re : fclean all

#cc -lmlx -framework OpenGL -framework AppKit src/*.c helpers/get_next_line/get_next_line.c helpers/libft/libft.a -o so_long