##------------------------------------------------------------------##
# Variables.

## Name
NAME-CLIENT			= client
NAME-SERVER			= server
NAME-CLIENTB		= client_bonus
NAME-SERVERB		= server_bonus
NAME-LIBFT			= ./lib/libft.a

## Compiler, flags, & other commands
CC 					= cc
CFLAGS 				= -Wall -Werror -Wextra -I
AR					= ar rcs
RM					= rm -f

## Sources & header
SRC-CLIENT			= ./src/client.c
SRC-SERVER			= ./src/server.c
HEADER				= ./src/
SRC-CLIENTB			= ./src_bonus/client_bonus.c
SRC-SERVERB			= ./src_bonus/server_bonus.c
HEADERB				= ./src_bonus

## Text colors
RED					=	\033[1;31m
GREEN				=	\033[1;32m
COLOFF				=	\033[0m

##------------------------------------------------------------------##
# Build rules

all:				$(NAME-LIBFT) $(NAME-CLIENT) $(NAME-SERVER)

bonus:				$(NAME-LIBFT) $(NAME-CLIENTB) $(NAME-SERVERB)

clean:
					@$(RM) $(NAME-CLIENT) $(NAME-SERVER) $(NAME-CLIENTB) $(NAME-SERVERB)
					@echo "$(RED)Minitalk's gone, baby, gone!$(COLOFF)"

fclean:				clean
					@make fclean -C ./lib
					@echo "$(RED)Libft's gone, baby, gone!$(COLOFF)"

re:					fclean all

re-bonus:			fclean bonus

##------------------------------------------------------------------##
# Targets
$(NAME-LIBFT):
		@make -C./lib
		@echo "$(GREEN)Libft ready!$(COLOFF)"

$(NAME-CLIENT): ./src/client.c $(NAME-LIBFT)
		@$(CC) $(CFLAGS) $(HEADER) $(SRC-CLIENT) $(NAME-LIBFT) -o $(NAME-CLIENT)
		@echo "$(GREEN)Client ready!$(COLOFF)"

$(NAME-SERVER): ./src/server.c $(NAME-LIBFT)
		@$(CC) $(CFLAGS) $(HEADER) $(SRC-SERVER) $(NAME-LIBFT) -o $(NAME-SERVER) 
		@echo "$(GREEN)Server ready!$(COLOFF)"

$(NAME-CLIENTB): ./src_bonus/client_bonus.c $(NAME-LIBFT)
		@$(CC) $(CFLAGS) $(HEADERB) $(SRC-CLIENTB) $(NAME-LIBFT) -o $(NAME-CLIENTB) 
		@echo "$(GREEN)Client_bonus ready!$(COLOFF)"

$(NAME-SERVERB): ./src_bonus/server_bonus.c $(NAME-LIBFT)
		@$(CC) $(CFLAGS) $(HEADERB) $(SRC-SERVERB) $(NAME-LIBFT) -o $(NAME-SERVERB)  
		@echo "$(GREEN)Server_bonus ready!$(COLOFF)"

##------------------------------------------------------------------##
#.PHONY
.PHONY: clean fclean all re
