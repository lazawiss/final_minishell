NAME = libft.a

ATOI = \
	   atoi/ft_atoi.c \
	   atoi/ft_atof.c \
	   atoi/ft_atol.c \
	   atoi/ft_atoi_base.c \
	   atoi/ft_itoa.c 

STR_IS = \
	   str_is/ft_tolower.c \
	   str_is/ft_toupper.c \
	   str_is/ft_isalpha.c \
	   str_is/ft_isalnum.c \
	   str_is/ft_isascii.c \
	   str_is/ft_isdigit.c \
	   str_is/ft_isspace.c \
	   str_is/ft_isprint.c 

PUTCHAR = \
	   putchar/ft_putnbr_fd.c \
	   putchar/ft_putstr_fd.c \
	   putchar/ft_putchar_fd.c \
	   putchar/ft_putendl_fd.c 

STRING = \
	   string/ft_strlen.c \
	   string/ft_strlcpy.c \
	   string/ft_strlcat.c \
	   string/ft_strcat.c \
	   string/ft_strcpy.c \
	   string/ft_strchr.c \
	   string/ft_strcmp.c \
	   string/ft_strncmp.c \
	   string/ft_strnstr.c \
	   string/ft_striteri.c \
	   string/ft_strrchr.c 

MEMORY = \
	   memory/ft_memcmp.c \
	   memory/ft_memchr.c \
	   memory/ft_memcpy.c \
	   memory/ft_memmove.c \
	   memory/ft_memset.c 

MALLOC = \
	   malloc/ft_bzero.c \
	   malloc/ft_free.c \
	   malloc/ft_calloc.c \
	   malloc/ft_substr.c \
	   malloc/ft_strtrim.c \
	   malloc/ft_strjoin.c \
	   malloc/ft_strdup.c \
	   malloc/ft_split.c \
	   malloc/ft_strmapi.c 

LINKED_LIST = \
			linked_list/ft_lstadd_back_bonus.c \
			linked_list/ft_lstadd_front_bonus.c \
			linked_list/ft_lstsize_bonus.c \
			linked_list/ft_lstlast_bonus.c \
			linked_list/ft_lstnew_bonus.c \
			linked_list/ft_lstmap_bonus.c \
			linked_list/ft_lstiter_bonus.c \
			linked_list/ft_lstdelone_bonus.c \
			linked_list/ft_lstclear_bonus.c

MATH = \
		math/ft_absolute.c \
		math/ft_swap.c \
		math/ft_pwr.c \
		math/ft_max.c


AR = ar rcs
CC = clang
CFLAGS = -Werror -Wall -Wextra -g3

OBJS_ATOI = $(ATOI:.c=.o)
OBJS_STR_IS = $(STR_IS:.c=.o)
OBJS_PUTCHAR = $(PUTCHAR:.c=.o)
OBJS_STRING = $(STRING:.c=.o)
OBJS_MEMORY = $(MEMORY:.c=.o)
OBJS_MALLOC = $(MALLOC:.c=.o)
OBJS_LINKED_LIST = $(LINKED_LIST:.c=.o)
OBJS_MATH = $(MATH:.c=.o)

all: $(NAME)

$(NAME): $(OBJS_ATOI) $(OBJS_STR_IS) $(OBJS_PUTCHAR) $(OBJS_STRING) $(OBJS_MEMORY) $(OBJS_MALLOC) $(OBJS_LINKED_LIST) $(OBJS_MATH)
	$(AR) $(NAME) $^ -o 

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS_LINKED_LIST) $(OBJS_ATOI) $(OBJS_STR_IS) $(OBJS_PUTCHAR) \
	 $(OBJS_STRING) $(OBJS_MEMORY) $(OBJS_MALLOC)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY : all clean fclean re
