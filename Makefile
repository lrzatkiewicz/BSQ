# Makefile for BSQ Project

# Compiler and Flags
CC = clang
CFLAGS = -Wall -Wextra -Werror

# Source Files: Automatically include all .c files in the directory
SRCS = $(wildcard *.c)

# Object Files: Replace .c with .o for each source file
OBJS = $(SRCS:.c=.o)

# Executable Name
NAME = bsq

# Perl Script
PERL_SCRIPT = generate_map.pl

# Default Target
all: $(NAME)

# Link Object Files to Create Executable
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

# Compile .c files to .o files
%.o: %.c project.h
	$(CC) $(CFLAGS) -c $< -o $@

# Clean Object Files
clean:
	rm -f $(OBJS)

# Clean Object Files and Executable
fclean: clean
	rm -f $(NAME)

# Rebuild the Project
re: fclean all

# Generate Map using Perl Script
# Usage: make generate_map X=<width> Y=<height> D=<density>
generate_map:
	@if [ -z "$(X)" ] || [ -z "$(Y)" ] || [ -z "$(D)" ]; then \
		echo "Usage: make generate_map X=<width> Y=<height> D=<density>"; \
		exit 1; \
	fi
	./$(PERL_SCRIPT) $(X) $(Y) $(D) > map.txt
	@echo "Map generated and saved to map.txt"

# Phony Targets
.PHONY: all clean fclean re generate_map
