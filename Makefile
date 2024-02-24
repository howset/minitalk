##------------------------------------------------------------------##
# Variables.

## Name
NAME-CLIENT			= client
NAME-SERVER			= server
#NAME-CLIENTB		= client_bonus
#NAME-SERVERB		= server_bonus

## Compiler, flags, & other commands
CC 					= cc
CFLAGS 				= -Wall -Werror -Wextra -I
AR					= ar rcs
RM					= rm -f

## Sources
SRC-CLIENT			= client.c
SRC-SERVER			= server.c
#SRC-CLIENTB		= client_bonus.c
#SRC-SERVERB		= server_bonus.c

## Text colors
RED					=	\033[1;31m
GREEN				=	\033[1;32m
COLOFF				=	\033[0m

##------------------------------------------------------------------##
# Targets
$(NAME-CLIENT): minitalk.h client.c 
		@$(CC) @$(CFLAGS) $(SRC-CLIENT) -o $(NAME-CLIENT)
		@echo "$(GREEN)Client created!$(COLOFF)"

$(NAME-SERVER): minitalk.h server.c 
		@$(CC) @$(CFLAGS) $(SRC-SERVER) -o $(NAME-SERVER) 
		@echo "$(GREEN)Server created!$(COLOFF)"

#$(NAME_CLIENTB): minitalk.h client_bonus.c utils.c
#		@$(CC) @$(CFLAGS) $(SRC-C-B) -o $(NAME-C-B) 
#		@echo "$(GREEN)Client_bonus created$(NC)"

#$(NAME_SERVERB): minitalk.h server_bonus.c utils.c
#		@$(CC) @$(CFLAGS) $(SRC-S-B) -o $(NAME-S-B)  
#		@echo "$(GREEN)Server_bonus created$(NC)"

##------------------------------------------------------------------##
# Build rules

all:				$(NAME-CLIENT) $(NAME_SERVER)
					$(MAKE) -C ./lib

bonus:				$(NAME-CLIENTB) $(NAME-SERVERB)
					$(MAKE) -C ./lib

clean:
					$(RM) $(NAME-CLIENT) $(NAME-SERVER) $(NAME-CLIENTB) $(NAME-SERVERB)
					@echo "$(RED)They're gone, baby, gone!$(COLOFF)"

fclean:				clean


re:					fclean all

##------------------------------------------------------------------##
#.PHONY
.PHONY: clean fclean all re