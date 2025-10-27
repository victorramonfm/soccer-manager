TARGET = main
SRC_DIR = src
BUILD_DIR = build

CXX = g++
CXXFLAGS = -Wall -std=c++17 -I$(SRC_DIR)

# Pega todos os .cpp
SRCS = $(shell find $(SRC_DIR) -name '*.cpp')

# Função para trocar src/xxx/yyy.cpp em build/xxx/yyy.o
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

# Regra padrão
all: $(TARGET)

# Linka o executável
$(TARGET): $(OBJS)
	$(CXX) $^ -o $@

# Regra para compilar .cpp em .o no build/
# A receita cria a pasta build/ para cada .o, se precisar
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(TARGET)
