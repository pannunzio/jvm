CC = gcc
CFLAGS = -m32 -std=c99
OUTFILE = JVM
OBJS = carregador.o leitor.o decodificador.o metodo.o frame.o instrucao.h main.o
SRCS = carregador.c leitor.c decodificador.c metodo.c frame.c instrucao.c main.c

$(OUTFILE): $(OBJS)
	$(CC) $(CFLAGS) -o $(OUTFILE) $(OBJS)
$(OBJS): $(SRCS)
	$(CC) $(CFLAGS) -c $(SRCS)

clean:
	rm -rf $(OBJS)
