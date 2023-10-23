CC = clang
CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = inc
LIB_DIR = libmx

TARGET = pathfinder

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

LIBMX = $(LIB_DIR)/libmx.a

all: $(LIBMX) $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -I$(INC_DIR) $^ $(LIBMX) -o $@

$(OBJS): $(OBJ_DIR)/%.o : $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(LIBMX):
	make -C $(LIB_DIR)

clean:
	rm -rf $(OBJ_DIR)
	make -C $(LIB_DIR) clean

uninstall:
	make -C $(LIB_DIR) uninstall
	rm -rf $(OBJ_DIR)
	rm -rf $(TARGET)

reinstall: uninstall all

.PHONY: all clean uninstall reinstall
