all:
	gcc *.h *.c -o saida -pthread -Wno-deprecated-declarations `pkg-config --cflags --libs gtk+-2.0`

clean:
	rm -Rf *.gch

clear:
	rm -Rf a.out *.gch
