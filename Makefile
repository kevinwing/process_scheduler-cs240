# compiler settings
CC				:= gcc
STD				:= c99
CFLAGS			:= -Wall -Wextra -pedantic -pedantic-errors
# DFLAGS			:=
DFLAGS			:= -g -fsanitize=address

# directories
SRC_DIR			:= src
BUILD_DIR		:= build
INCLUDE_DIR		:= include

# subproject executable names
BIN				:= proc_scheduler

# get source files
SRCS			:= $(wildcard $(SRC_DIR)/*.c)

# get object names
# OBJS			:= $(addprefix $(BUILD_DIR)/, $(notdir $(SRCS:.c=.o)))
OBJS			:= $(addprefix $(BUILD_DIR)/, $(notdir $(SRCS:.c=.o)))

# include directories
# INCLUDE			:= $(addprefix $(SRC_DIR)/, $(INCLUDE_DIR))

# build targets
TARGET			:= $(addprefix $(BUILD_DIR)/, $(BIN))

# shell commands
MD := mkdir -p
RM := rm -f

# default rule
all: $(TARGET)
	@echo Building 'all' complete!

# rules to be explicitly called
.PHONY: clean

# build junk
$(TARGET): $(OBJS) | $(BUILD_DIR)
	$(CC) -std=$(STD) $(CFLAGS) $(DFLAGS) -o $(TARGET) $(OBJS)
	@echo Building 'find' complete!

# create build directory
$(BUILD_DIR):
	$(MD) $@

# pattern rule for object compilation into build directory
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) -std=$(STD) $(CFLAGS) $(DFLAGS) -c $< -o $@ -I$(INCLUDE_DIR)

# delete build files
clean:
	$(RM) $(OBJS)
	$(RM) $(TARGET)