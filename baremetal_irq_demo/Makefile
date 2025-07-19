# 交叉编译器
CC = arm-none-eabi-gcc
LD = arm-none-eabi-ld

# CPU 和架构参数
CPU = cortex-a7
ARCH = arm
CFLAGS = -mcpu=$(CPU) -marm -nostdlib -g -Wall -Werror -O0
LDFLAGS = -T linker.ld

SRCS = main.c vector.S
OBJS = $(SRCS:.c=.o)
OBJS += $(SRCS:.S=.o)

TARGET = app.elf

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.S
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	qemu-system-arm -M vexpress-a7 -cpu cortex-a7 -m 256M -serial stdio -kernel $(TARGET) -nographic
