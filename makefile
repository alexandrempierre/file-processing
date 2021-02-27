INCLUDES=-Iincludes
OPTIONS=-Wall --pedantic -g

BUILD_DIR=build
SRC_DIR=src
BIN_DIR=bin

SOURCES=$(wildcard $(SRC_DIR)/*.c)
OBJECTS=$(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SOURCES))

MD=mkdir -p
RM=rm -f
CC=gcc
CFLAGS=$(INCLUDES) $(OPTIONS)

$(BIN_DIR)/file_processor: $(OBJECTS) | $(BIN_DIR)
	$(CC) -o $(BIN_DIR)/file_processor $(OBJECTS) file_processor.c $(CFLAGS)

$(BIN_DIR)/generate_input_file: $(OBJECTS) | $(BIN_DIR)
	$(CC) -o $(BIN_DIR)/generate_input_file $(OBJECTS) generate_input_file.c $(CFLAGS)

generate_input_file: $(BIN_DIR)/generate_input_file ;

$(OBJECTS): $(BUILD_DIR)/%.o : $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< $(LIB_PATH) $(LIBS) -o $@

$(BUILD_DIR):
	$(MD) $(BUILD_DIR)

$(BIN_DIR):
	$(MD) $(BIN_DIR)

file.txt:
	touch file.txt

testes: testes.tar.gz
	tar -xzvf testes.tar.gz

clean:
	$(RM) $(BUILD_DIR)/* $(BIN_DIR)/*
