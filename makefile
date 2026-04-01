CC      := gcc
CFLAGS  := -Wall -Wextra -Iinclude -Ideps -Ideps/argon2/include
DIRS    := src gui cli
SRCS    := $(foreach dir,$(DIRS),$(wildcard $(dir)/*.c))
OBJS    := $(SRCS:.c=.o)
TARGET  := myprog
LIBS := -lsodium

ARGON2_LIB := deps/argon2/libargon2.a

$(TARGET): $(ARGON2_LIB) $(OBJS)
	$(CC) $(OBJS) $(ARGON2_LIB) -o $(TARGET) $(LIBS)

# Build argon2's static lib using its own Makefile
$(ARGON2_LIB):
	$(MAKE) -C deps/argon2 libargon2.a

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
	$(MAKE) -C deps/argon2 clean
