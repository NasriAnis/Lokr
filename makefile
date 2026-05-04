.PHONY: all gui clean

CC      := gcc
CFLAGS  := -Wall -Wextra -Iinclude -Ideps
DIRS := src src/auth src/crypto src/init src/misc src/vault gui cli gui/windows
SRCS    := $(foreach dir,$(DIRS),$(wildcard $(dir)/*.c))
OBJS    := $(SRCS:.c=.o)
TARGET  := lokr
LIBS    := -lsodium -largon2

# GTK4
GTK4_CFLAGS := $(shell pkg-config --cflags gtk4)
GTK4_LIBS   := $(shell pkg-config --libs gtk4)

# CLI-only sources (no gui/)
CLI_DIRS := src src/auth src/crypto src/init src/misc src/vault cli cli/features
# CLI_DIRS := src cli cli/features
CLI_SRCS := $(foreach dir,$(CLI_DIRS),$(wildcard $(dir)/*.c))
CLI_OBJS := $(CLI_SRCS:.c=.o)

# GUI sources (no cli/)
GUI_DIRS := src src/auth src/crypto src/init src/misc src/vault gui gui/windows gui/features
# GUI_DIRS := src gui gui/windows gui/features
GUI_SRCS := $(foreach dir,$(GUI_DIRS),$(wildcard $(dir)/*.c))
GUI_OBJS := $(GUI_SRCS:.c=.o)

# --- default: build CLI ------------------------------------------------
all:
	$(CC) $(CFLAGS) $(CLI_SRCS) -o $(TARGET) $(LIBS)

# --- gui target --------------------------------------------------------
gui:
	$(CC) $(CFLAGS) $(GTK4_CFLAGS) $(GUI_SRCS) -o $(TARGET)_gui $(LIBS) $(GTK4_LIBS)

# --- pattern rule ------------------------------------------------------
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET) $(TARGET)_gui
