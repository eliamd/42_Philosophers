# =============================== VARIABLES =================================== #

NAME			= philo
CC				= cc
CFLAGS			= -Wall -Wextra -Werror -g2
RM				= rm -f

# ================================ COULEURS =================================== #

DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m
NC = \033[0m # No Color

# =============================== SOURCES ===================================== #

SRCS = 	philo/utils/ft_atol.c \
		philo/utils/check_args.c \
		philo/utils/gettime.c \
		philo/utils/cleanup.c \
		philo/init/init.c \
		philo/run/routine.c \
		philo/run/single_philo.c \
		philo/run/thread_run.c \
		philo/run/observer.c \
		philo/main.c \

OBJS = $(SRCS:.c=.o)

# ============================= PROGRESS BAR ================================= #

TOTAL_FILES := $(words $(SRCS))
CURRENT_FILE := 0
PROGRESS_WIDTH := 40

define update_progress
	$(eval CURRENT_FILE=$(shell echo $$(($(CURRENT_FILE) + 1))))
	$(eval PERCENTAGE=$(shell echo $$(($(CURRENT_FILE) * 100 / $(TOTAL_FILES)))))
	$(eval PROGRESS=$(shell echo $$(($(CURRENT_FILE) * $(PROGRESS_WIDTH) / $(TOTAL_FILES)))))
	printf "\r$(BLUE)[%3d%%] $(GREEN)Building %-50s$(NC)" $(PERCENTAGE) "$1"
endef

# ============================== REGLES PRINCIPALES ========================== #

all:		$(NAME)

$(NAME): $(OBJS)
			$(CC) $(OBJS) -o $(NAME) -fsanitize=thread
			@printf "$(BLUE)[100%%] $(GREEN)$(NAME) is compiled !! $(NC)\n"

%.o: %.c
			@$(call update_progress,$<)
			@$(CC) $(CFLAGS) -c $< -o $@
			@printf "\n"

# ================================== CLEAN ==================================== #

clean:
			@echo "$(YELLOW)Cleaning object files...$(NC)"
			@rm -f $(OBJS)
			@echo "$(GREEN)Object files cleaned!$(NC)"

fclean:		clean
			@echo "$(YELLOW)Cleaning all files...$(NC)"
			@rm -f $(NAME)
			@echo "$(GREEN)All files cleaned!$(NC)"

# ================================= REBUILD =================================== #

re:			fclean all
			@echo "$(GREEN)>>> Cleaned and rebuilt everything! <<<$(DEF_COLOR)"

# ================================ PHONY ====================================== #

.PHONY:		all clean fclean re
