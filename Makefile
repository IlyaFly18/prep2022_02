TARGET = ./main.out
TST_TARGET = ./tests.out

HDRS_DIR = project/include


SRCS = \
		project/src/main.c \
		project/src/operations.c \
		project/src/person.c \
        project/src/transfer.c \

TST_SRCS = \
		project/src/test_main.c \
		project/src/test_print_to_file.c \
		project/src/person.c \
        project/src/transfer.c \

.PHONY: all build rebuild check test memtest clean my_test

all: clean check test memtest my_test

$(TARGET): $(SRCS)
	$(CC) -Wpedantic -Wall -Wextra -Werror -I $(HDRS_DIR) -o $(TARGET) $(CFLAGS) $(SRCS)

$(TST_TARGET): $(TST_SRCS)
	$(CC) -Wpedantic -Wall -Wextra -Werror -I $(HDRS_DIR) -o $(TST_TARGET) $(CFLAGS) $(TST_SRCS)

build: $(TARGET) $(TST_TARGET)

rebuild: clean build

check:
	./run_linters.sh

test: $(TARGET)
	./btests/run.sh $(TARGET)

memtest: $(TARGET)
	./btests/run.sh $(TARGET) --memcheck

clean:
	rm -rf $(TARGET) $(TST_TARGET) *.dat

my_test: $(TST_TARGET)
	$(TST_TARGET)

