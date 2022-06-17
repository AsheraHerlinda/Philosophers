NAME = 			philo
NAME_bonus = 	philo_bonus

SRCS =			man/philo.c \
				man/end_programm.c \

SRCS_bonus =	bonus/end_programm.c \


OBJS =			${SRCS:.c=.o}
OBJS_bonus =	${SRCS_bonus:.c=.o}

CC 		=		gcc 
RM 		=		rm -f
FLAGS 	=		-Wall -Wextra -Werror
HEAD	=		./inc/philo.h \
				./inc/philo_bonus.h \


all:	${NAME}

${NAME}: ${OBJS}
		${CC} -o ${NAME} $^

bonus:	${LFT} ${NAME_bonus}

${NAME_bonus}:	${OBJS_bonus}
				${CC} -o ${NAME_bonus} $^ ${LIB}

%.o:	%.c ${HEAD} Makefile
		${CC} ${FLAGS} -c $< -o $@

clean:
		${RM} ${OBJS} ${OBJS_bonus}


fclean: clean
		${RM} ${NAME} ${NAME_bonus}

re: fclean all

re_bonus: fclean bonus

.PHONY: all clean fclean re bonus re_bonus