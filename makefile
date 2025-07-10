# Makefile para o Projeto do Laboratório 2

# Define o nome do executável final
TARGET = trabalho_lab2

# Define os arquivos objeto (.o) que serão gerados
OBJS = trabalho_lab2.o Arvores.o Dispositivos.o Sensores.o Evento.o

# Compilador a ser usado
CC = gcc

# Opções de compilação
# -W: Habilita avisos adicionais
# -Wall: Habilita todos os avisos comuns
# -ansi: Força a conformidade com o padrão ANSI C
# -pedantic: Força conformidade estrita com o padrão ANSI C, reportando todos os desvios
# -c: Compila o código fonte em um arquivo objeto sem linkar
CFLAGS = -W -Wall -ansi -pedantic -c

# Opções de linkagem (usadas para criar o executável final)
LDFLAGS =

# A regra 'all' é a regra padrão e será executada quando você digitar 'make'
all: $(TARGET)

# Regra para linkar o executável final
$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LDFLAGS)

# Regras para compilar cada arquivo .c em seu respectivo arquivo .o
# A dependência de .h garante que se um cabeçalho for modificado, o .c correspondente será recompilado

trabalho_lab2.o: trabalho_lab2.c Arvores.h Dispositivos.h Sensores.h Evento.h estruturas.h
	$(CC) $(CFLAGS) trabalho_lab2.c -o trabalho_lab2.o

Arvores.o: Arvores.c Arvores.h estruturas.h
	$(CC) $(CFLAGS) Arvores.c -o Arvores.o

Dispositivos.o: Dispositivos.c Dispositivos.h estruturas.h
	$(CC) $(CFLAGS) Dispositivos.c -o Dispositivos.o

Sensores.o: Sensores.c Sensores.h estruturas.h
	$(CC) $(CFLAGS) Sensores.c -o Sensores.o

Evento.o: Evento.c Evento.h estruturas.h
	$(CC) $(CFLAGS) Evento.c -o Evento.o

# Regra 'clean' para remover os arquivos gerados pela compilação
clean:
	rm -rf *.o *~ $(TARGET)