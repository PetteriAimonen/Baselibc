CFLAGS  = -fno-common -Os -g -Wall -Werror -I include

# Platform specific settings
CC      = arm-none-eabi-gcc
CFLAGS += -mcpu=cortex-m3 -mthumb

FILES   = src/asprintf.o	src/atoi.o	src/atol.o \
	src/atoll.o	src/bsearch.o	src/bzero.o \
	src/calloc.o	src/fgets.o \
	src/inline.o \
	src/jrand48.o	src/lrand48.o	src/malloc.o	src/memccpy.o \
	src/memchr.o	src/memcmp.o	src/memcpy.o	src/memmem.o \
	src/memmove.o	src/memrchr.o	src/memset.o	src/memswap.o \
	src/mrand48.o	src/nrand48.o	src/qsort.o \
	src/realloc.o  \
	src/srand48.o	src/sscanf.o	src/strcasecmp.o \
	src/strcat.o	src/strchr.o	src/strcmp.o	src/strcpy.o \
	src/strcspn.o	src/strdup.o	src/strlcat.o \
	src/strlcpy.o	src/strlen.o	src/strncasecmp.o	src/strncat.o \
	src/strncmp.o	src/strncpy.o	src/strndup.o	src/strnlen.o \
	src/strntoimax.o	src/strntoumax.o	src/strpbrk.o \
	src/strrchr.o	src/strsep.o	src/strspn.o	src/strstr.o \
	src/strtoimax.o	src/strtok.o	src/strtok_r.o	src/strtol.o \
	src/strtoll.o	src/strtoul.o	src/strtoull.o \
	src/strtoumax.o

# For proper printf
#FILES += src/fprintf.o src/vasprintf.o	src/vfprintf.o	src/vprintf.o \
#	src/vsnprintf.o	src/vsprintf.o	src/vsscanf.o src/snprintf.o \
#       src/printf.o

# For tiny printf
FILES += src/tinyprintf.o


all: libc.a

clean:
	rm -f $(FILES) libc.a

libc.a: $(FILES)
	rm -f $@
	ar ru $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<
