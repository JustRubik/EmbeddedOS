TARGET  = firmware
BUILD   = build

CC      = arm-none-eabi-gcc
AS      = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
SIZE    = arm-none-eabi-size

CFLAGS  = -mcpu=cortex-m3 -mthumb -Os -ffreestanding -fno-builtin \
          -fdata-sections -ffunction-sections -Wall -Wextra -Werror \
          -std=c11 -g3
ASFLAGS  = -mcpu=cortex-m3 -mthumb -x assembler-with-cpp
LDFLAGS  = -T linker.ld -nostdlib -Wl,--gc-sections -Wl,-Map,$(BUILD)/$(TARGET).map

SRCS = startup.s main.c
OBJS = $(SRCS:%.s=$(BUILD)/%.o)
OBJS := $(OBJS:%.c=$(BUILD)/%.o)

all: $(BUILD)/$(TARGET).elf $(BUILD)/$(TARGET).bin

$(BUILD):
	mkdir -p $(BUILD)

$(BUILD)/%.o: %.s | $(BUILD)
	$(AS) $(ASFLAGS) -c $< -o $@

$(BUILD)/%.o: %.c | $(BUILD)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)/$(TARGET).elf: $(OBJS) linker.ld
	$(CC) $(OBJS) $(LDFLAGS) -o $@
	$(SIZE) $@

$(BUILD)/$(TARGET).bin: $(BUILD)/$(TARGET).elf
	$(OBJCOPY) -O binary $< $@

clean:
	rm -rf $(BUILD)

.PHONY: all clean
