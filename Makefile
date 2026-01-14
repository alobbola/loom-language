CC = gcc
CFLAGS = -Wall -g -Ideps -Isrc
LDFLAGS = -luv

CORE_SRC = $(filter-out src/main.c, $(wildcard src/*.c)) deps/picohttpparser.c deps/cJSON.c
MAIN_SRC = src/main.c $(CORE_SRC)

TARGET = build/loom
TEST_BUILD_DIR = build/tests

all: $(TARGET)

$(TARGET): $(MAIN_SRC)
	@mkdir -p build
	$(CC) $(CFLAGS) $(MAIN_SRC) -o $(TARGET) $(LDFLAGS)

tests:
	@mkdir -p $(TEST_BUILD_DIR)
	@found=0; \
	for test_file in tests/*.c; do \
		if [ -f "$$test_file" ]; then \
			found=1; \
			name=$$(basename $$test_file .c); \
			echo "--- [TESTE] Compilando e rodando: $$name ---"; \
			$(CC) $(CFLAGS) $$test_file $(CORE_SRC) -o $(TEST_BUILD_DIR)/$$name $(LDFLAGS) || exit 1; \
			./$(TEST_BUILD_DIR)/$$name || exit 1; \
			echo ""; \
		fi \
	done; \
	if [ $$found -eq 0 ]; then \
		echo "Nenhum teste encontrado em tests/*.c"; \
	fi


test:
	@mkdir -p $(TEST_BUILD_DIR)
	@if [ -z "$(t)" ]; then \
		echo "ERRO: Voce precisa especificar qual teste rodar."; \
		echo "Uso: make test t=memory-test.c"; \
		exit 1; \
	fi
	@echo "--- [SINGLE TEST] Rodando: $(t) ---"
	$(CC) $(CFLAGS) tests/$(t) $(CORE_SRC) -o $(TEST_BUILD_DIR)/single_test $(LDFLAGS)
	./$(TEST_BUILD_DIR)/single_test

clean:
	rm -rf build

.PHONY: all tests test clean