NAME			=	libft.a

CC				=	gcc

CFLAGS			=	-Wall -Wextra -Werror -Isrc -Iinclude

RM				=	rm -rf

# Paths and Files
VPATH			=	src:src/conversion:src/memory:src/output:src/string:src/get_next_line
SRCS			=	ft_atoi.c ft_itoa.c ft_bzero.c ft_calloc.c \
					ft_memcpy.c ft_memset.c \
					ft_isalnum.c ft_isalpha.c ft_isdigit.c \
					ft_split.c ft_strchr.c ft_strcmp.c ft_strdup.c \
					ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c \
					ft_strncmp.c ft_strnstr.c ft_strtrim.c ft_substr.c \
					ft_strjoin_free.c ft_strdel.c ft_strcat.c  ft_strcpy.c\
					get_next_line.c get_next_line_utils.c
							
OBJS			=	$(addprefix obj/,$(SRCS:.c=.o))

# Rules
$(NAME):		$(OBJS)
				ar rcs $(NAME) $(OBJS)

all:			$(NAME)

obj:
				mkdir -p obj

obj/%.o:		%.c | obj
				mkdir -p $(dir $@)
				$(CC) $(CFLAGS) -c $< -o $@

clean:
				$(RM) obj

fclean:			clean
				$(RM) $(NAME)

re:				fclean all

.SILENT:

.PHONY:			all clean fclean re
