NAME = so_long

SRCS = src/*.c helpers/get_next_line/get_next_line.c

LIBRARY = -lmlx -framework OpenGL -framework AppKit

CFLAGS = -Wall -Wextra -Werror 

LIBFT = helpers/libft

all : $(NAME)


$(NAME): $(SRCS) $(LIBFT)/libft.a includes/so_long.h includes/dictionnary.h
	cc $(CFLAGS) $(SRCS) $(LIBRARY) $(LIBFT)/libft.a -o $(NAME)

$(LIBFT)/libft.a :
	make -C $(LIBFT)

clean :
	make clean -C $(LIBFT)
	$(RM) $(OBJS)

fclean :
	make fclean -C $(LIBFT)
	$(RM) $(OBJS) $(NAME)

re : fclean all



#cc -lmlx -framework OpenGL -framework AppKit src/*.c helpers/get_next_line/get_next_line.c helpers/libft/libft.a -o so_long