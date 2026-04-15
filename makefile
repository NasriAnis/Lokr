CC      := gcc
CFLAGS  := -Wall -Wextra -Iinclude -Ideps -Ideps/argon2/include
DIRS    := src gui cli gui/windows
SRCS    := $(foreach dir,$(DIRS),$(wildcard $(dir)/*.c))
OBJS    := $(SRCS:.c=.o)
TARGET  := myprog
LIBS    := -lsodium

ARGON2_LIB := deps/argon2/libargon2.a

# GTK4
GTK4_CFLAGS := $(shell pkg-config --cflags gtk4)
GTK4_LIBS   := $(shell pkg-config --libs gtk4)

# CLI-only sources (no gui/)
CLI_DIRS := src cli
CLI_SRCS := $(foreach dir,$(CLI_DIRS),$(wildcard $(dir)/*.c))
CLI_OBJS := $(CLI_SRCS:.c=.o)

# GUI sources (no cli/)
GUI_DIRS := src gui gui/include gui/windows
GUI_SRCS := $(foreach dir,$(GUI_DIRS),$(wildcard $(dir)/*.c))
GUI_OBJS := $(GUI_SRCS:.c=.o)

# ── default: build CLI ─────────────────────────────────────────────
all: $(ARGON2_LIB)
	$(CC) $(CFLAGS) $(CLI_SRCS) $(ARGON2_LIB) -o $(TARGET) $(LIBS)

# ── gui target ────────────────────────────────────────────────────
gui: $(ARGON2_LIB)
	$(CC) $(CFLAGS) $(GTK4_CFLAGS) $(GUI_SRCS) $(ARGON2_LIB) -o $(TARGET)_gui $(LIBS) $(GTK4_LIBS)

# ── argon2 static lib ─────────────────────────────────────────────
$(ARGON2_LIB):
	$(MAKE) -C deps/argon2 libargon2.a

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET) $(TARGET)_gui
	$(MAKE) -C deps/argon2 clean
