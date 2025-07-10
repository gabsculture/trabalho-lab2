# Makefile para o Projeto do Laboratório 2

# Define o nome do executável final
TARGET = trabalho_lab2

# Define os arquivos objeto (.o) que serão gerados
OBJS = trabalho_lab2.o Arvore.o Dispositivos.o Sensores.o Evento.o Funcoes.o

# Compilador a ser usado
CC = gcc

# Opções de compilação
# -W: Habilita avisos adicionais
# -Wall: Habilita todos os avisos comuns
# -ansi: Força a conformidade com o padrão ANSI C
# -pedantic: Força conformidade estrita com o padrão ANSI C, reportando todos os desvios
# -c: Compila o código fonte em um arquivo objeto sem linkar
CFLAGS = -W -Wall -std=c99 -pedantic -c

# Opções de linkagem (usadas para criar o executável final)
LDFLAGS =

# A regra 'all' é a regra padrão e será executada quando você digitar 'make'
all: $(TARGET)

# Regra para linkar o executável final
$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LDFLAGS)

# Regras para compilar cada arquivo .c em seu respectivo arquivo .o
# Removidas as dependências explícitas dos arquivos .h
trabalho_lab2.o: trabalho_lab2.c
	$(CC) $(CFLAGS) trabalho_lab2.c -o trabalho_lab2.o

Arvores.o: Arvores.c
	$(CC) $(CFLAGS) Arvore.c -o Arvore.o

Dispositivos.o: Dispositivos.c
	$(CC) $(CFLAGS) Dispositivos.c -o Dispositivos.o

Sensores.o: Sensores.c
	$(CC) $(CFLAGS) Sensores.c -o Sensores.o

Evento.o: Evento.c
	$(CC) $(CFLAGS) Evento.c -o Evento.o

Funcoes.o: Funcoes.c
	$(CC) $(CFLAGS) Funcoes.c -o Funcoes.o

# Regra 'clean' para remover os arquivos gerados pela compilação
clean:
	rm -rf *.o *~ $(TARGET)