#h_source += convert_char_2_hex_data.h
#c_source += convert_char_2_hex_data.c

objs = convert_char_2_hex_data.o

all: $(objs)
	gcc -o gsm_7bit $(objs)

convert_char_2_hex_data.o: convert_char_2_hex_data.c convert_char_2_hex_data.h
	cc -c convert_char_2_hex_data.c

clean:
	rm -rf gsm_7bit *.o