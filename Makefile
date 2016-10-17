CFLAGS = -Isrc -Iinc -O2

objs = src/main.o \
       src/convert_char_2_hex.o \
       src/convert_iso8859_2_gsm7.o \
       src/gsm7_packing_unpacking.o

all: $(objs)
	$(CC) -o Gsm_7bit_Tools $(objs) $(CFLAGS)

$(objs):%o:%c
	$(CC) -c $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	$(RM) Gsm_7bit_Tools $(objs)
