SRC				+=	main.cpp\
					PmergeMe.cpp\
					

########################################################################################################################
#                                                     --VARIABLE--                                                     #
########################################################################################################################
HEAD			+=  PmergeMe.hpp\

OBJS_D			:=	objs/
OBJS			:=	$(addprefix $(OBJS_D),$(SRC:%.cpp=%.o))

NAME			:=	PmergeMe


RM				:=	rm -rf
CC				:=	c++
CFLAGS			:=	-Wall -Wextra -Werror -g3 -std=c++98

########################################################################################################################
#                                                      --RULES--                                                       #
########################################################################################################################

all				:	$(NAME)

$(NAME)			:	$(OBJS_D) $(OBJS)
					@echo "${I_MAG}'OBJECTS'\t: ${GREEN} done ✅ ${RESET}\n"
					@echo "${I_MAG}'PmergeMe'\t\t: ${RED} Work In Progress ◌ ${RESET}"
					$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
					@echo "${I_MAG}'PmergeMe'\t\t: ${GREEN} done ✅ ${RESET}\n"
					@echo "${RESET}";

$(OBJS_D)%.o	:	%.cpp $(HEAD)
					$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_D)		:
					@echo "${I_MAG}'OBJECTS'\t: ${RED} Work In Progress ◌ ${RESET}"
					mkdir -p $(OBJS_D)

clean			:
					@echo "${I_MAG}'OBJECTS'\t: ${RED} deleted ❌ ${RESET}"
					$(RM) $(OBJS) $(OBJS_D)

fclean			:	clean
					@echo "${I_MAG}'PmergeMe'\t\t: ${RED} deleted ❌ ${RESET}\n"
					$(RM) $(NAME)

re				:	fclean all

.PHONY			:	all clean fclean re

########################################################################################################################
#                                                      --COLOR--                                                       #
########################################################################################################################

RED				=	\033[0;31m
GREEN			=	\033[0;32m
RESET			=	\033[0m
I_MAG			=	\033[3;35m
I_BLUE			=	\033[3;34m