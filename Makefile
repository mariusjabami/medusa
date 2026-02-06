# Diretórios
SRC_DIR := src
BUILD_DIR := build
INCLUDE_DIR := includes

# Arquivos
SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))
TARGET := $(BUILD_DIR)/medusa

# Compilador e flags
CC := gcc
CFLAGS := -I$(INCLUDE_DIR) -Wall -Wextra -O2
LDFLAGS := -lcurl -lcjson

# Alvo padrão
all: $(TARGET)

# Cria build e compila objetos
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Linka todos os objetos
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

# Cria diretório build se não existir
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Limpeza
clean:
	rm -rf $(BUILD_DIR)/*.o $(TARGET)

.PHONY: all clean
