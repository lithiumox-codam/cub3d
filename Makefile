NAME = CUB3D
vpath %.c src
vpath %.h include

SRC = main.c parser/index.c init/index.c parser/checker.c parser/array.c debug/array.c parser/handlers_path.c parser/handlers_rgba.c
LIBS = MLX42/build/libmlx42.a libft/libft.a
OBJS = $(addprefix build/, $(SRC:.c=.o))
CODAM_FLAGS = -Ofast -flto $(if $(DEBUG),-g3) #-Wall -Wextra -Werror
INCLUDES = -I $(CURDIR)/include -I MLX42/include/MLX42 -I libft/includes
MLX = MLX42/build/libmlx42.a
LIBFT = libft/libft.a

DEBUG = 0

ifeq ($(shell uname -m),arm64)
LINKERS = -L/opt/homebrew/lib -lglfw -framework IOKit -framework Cocoa
else ifeq ($(shell uname -m),x86_64)
LINKERS = -ldl -lglfw -pthread -lm
endif

COLOR_INFO = \033[1;36m
COLOR_SUCCESS = \033[1;32m
COLOR_RESET = \033[0m

EMOJI_INFO = 🌈
EMOJI_SUCCESS = 🎉
EMOJI_CLEAN = 🧹
EMOJI_RUN = 🚀

all: $(NAME)

$(NAME): $(MLX) $(LIBFT) $(OBJS)
	@printf "$(COLOR_INFO)$(EMOJI_INFO)  Compiling $(NAME)...$(COLOR_RESET)\t\t"
	@gcc $(OBJS) $(LIBS) $(INCLUDES) $(LINKERS) $(CODAM_FLAGS) -o $@
	@sleep 0.25
	@printf "✅\n"

build/%.o: %.c include/cub3d.h include/config.h include/structs.h
	@mkdir -p $(@D)
	@gcc $(INCLUDES) $(CODAM_FLAGS) -c $< -o $@

$(MLX):
	@printf "$(COLOR_INFO)$(EMOJI_INFO)  Initializing submodules...$(COLOR_RESET)\t"
	@git submodule update --init --recursive > /dev/null
	@sleep 0.25
	@printf "✅\n"
	@printf "$(COLOR_INFO)$(EMOJI_INFO)  Building MLX42...$(COLOR_RESET)\t\t"
	@cmake -S MLX42 -B MLX42/build -DGLFW_FETCH=1 > /dev/null
	@cmake --build MLX42/build --parallel > /dev/null
	@sleep 0.25
	@printf "✅\n"

$(LIBFT):
	@printf "$(COLOR_INFO)$(EMOJI_INFO)  Building Libft...$(COLOR_RESET)\t\t"
	@$(MAKE) -C libft > /dev/null
	@sleep 0.25
	@printf "✅\n"

clean:
	@printf "$(COLOR_INFO)$(EMOJI_CLEAN)  Cleaning up...$(COLOR_RESET)\t\t"
	@rm -rf MLX42/build
	@$(MAKE) -C libft clean > /dev/null
	@rm -rf build
	@sleep 0.25
	@printf "✅\n"

fclean: clean
	@printf "$(COLOR_INFO)$(EMOJI_CLEAN)  Forcibly cleaning up...$(COLOR_RESET)\t"
	@rm -rf MLX42/build
	@$(MAKE) -C libft fclean > /dev/null
	@rm -rf build
	@rm -f $(NAME)
	@sleep 0.25
	@printf "✅\n"

run: $(NAME)
	@printf "$(COLOR_INFO)$(EMOJI_RUN)  Compiled and started $(NAME)...$(COLOR_RESET)"
	@./$(NAME)

norm:
	@printf "$(COLOR_INFO)$(EMOJI_INFO)  Checking Norm...$(COLOR_RESET)\t\t"
	@norminette $(SRC) include/*.h | grep -v Norme -B1 || true
	@norminette libft | grep -v Norme -B1 || true
	@sleep 0.25
	@printf "✅\n"

re: fclean $(NAME)

bonus: all

module-update:
	@git submodule update --init --recursive

.PHONY: all clean fclean re bonus run norm
