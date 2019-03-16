# You can override the CFLAGS and C compiler externally,
# e.g. make PLATFORM=cortex-m3
CFLAGS += -g -Wall -Werror -I include

ifeq ($(PLATFORM),cortex-m3)
  CC      = arm-none-eabi-gcc
  AR      = arm-none-eabi-ar
  CFLAGS += -mcpu=cortex-m3 -mthumb
  CFLAGS += -fno-common -Os
  CFLAGS += -ffunction-sections -fdata-sections
else ifeq ($(PLATFORM),cortex-m0)
  CC      = arm-none-eabi-gcc
  AR      = arm-none-eabi-ar
  CFLAGS += -mcpu=cortex-m0 -mthumb
  CFLAGS += -fno-common -Os
  CFLAGS += -ffunction-sections -fdata-sections
else ifeq ($(PLATFORM),m68k-elf)
  CC      = m68k-elf-gcc
  AR      = m68k-elf-ar
  CFLAGS += -mcpu=68000
  CFLAGS += -fno-common -Os
  CFLAGS += -ffunction-sections -fdata-sections
  CFLAGS += -ffreestanding
  CFLAGS += -DNO_UNISTD_H
endif

# With this, the makefile should work on Windows also.
ifdef windir
  RM = del
endif

# Just include all the source files in the build.
CSRC = $(wildcard src/*.c)
OBJS = $(CSRC:.c=.o)

# And the files for the test suite
TESTS_CSRC = $(wildcard tests/*_tests.c)
TESTS_OBJS = $(TESTS_CSRC:.c=)

# Some of the files uses "templates", i.e. common pieces
# of code included from multiple files.
CFLAGS += -Isrc/templates

all: libc.a

clean:
	$(RM) $(OBJS) $(TESTS_OBJS) libc.a

libc.a: $(OBJS)
	$(RM) $@
	$(AR) ru $@ $^

run_tests: $(TESTS_OBJS)
	$(foreach f,$^,$f)

tests/%: tests/%.c tests/tests_glue.c libc.a
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<
