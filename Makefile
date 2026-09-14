
NAME = hotrace
CC = cc

CFLAGS = -Wall -Wextra -Werror 

OBJ_PATH = objects/
INC = -Iincludes

SRC =	src/main.c \
		src/utils.c \
		src/arena.c \
		src/list.c \
		src/output.c \
		src/pool.c \
		src/process.c \
		src/reader.c

OBJ = $(SRC:.c=.o)
OBJS = $(addprefix $(OBJ_PATH), $(OBJ))

MAKEFLAGS += --silent

all: $(OBJ_PATH) $(NAME)

# Obje klasörünü oluştur
$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)

# Ana dizindeki .c dosyalarını okuyup objects/ klasörüne .o olarak derler
$(OBJ_PATH)%.o: %.c
	mkdir -p $(dir $@)
	echo "🔷 Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(NAME): $(OBJS)
	echo "✅ Building $(NAME)..."
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(INC)

clean:
	echo "🧹 Cleaning object files..."
	rm -rf $(OBJ_PATH)
	echo "✅ Cleaning completed!"

fclean: clean
	echo "🧹 Full cleaning is in progress..."
	rm -f $(NAME)
	echo "✅ Full cleaning completed!"

re: fclean all

.PHONY: all clean fclean re