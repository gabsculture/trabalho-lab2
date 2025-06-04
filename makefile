# Configurações do compilador
CC = gcc
CFLAGS = -Wall -Wextra -g
LDFLAGS =

# Nome do executável final
TARGET = trabalho_lab2

# Lista de arquivos fonte
SRCS = trabalho_lab2.c Dispositivos.c Sensores.c Evento.c Funcoes.c

# Gerar lista de objetos (.o) a partir dos fontes
OBJS = $(SRCS:.c=.o)

# Regra padrão - compila tudo
all: $(TARGET)

# Regra para linkar o executável final
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Regras de compilação para cada arquivo objeto com suas dependências

trabalho_lab2.o: trabalho_lab2.c Dispositivos.h Sensores.h Evento.h Funcoes.h estruturas.h
	$(CC) $(CFLAGS) -c $< -o $@

Dispositivos.o: Dispositivos.c Dispositivos.h estruturas.h
	$(CC) $(CFLAGS) -c $< -o $@

Sensores.o: Sensores.c Sensores.h estruturas.h Dispositivos.h
	$(CC) $(CFLAGS) -c $< -o $@

Evento.o: Evento.c Evento.h estruturas.h Sensores.h
	$(CC) $(CFLAGS) -c $< -o $@

Funcoes.o: Funcoes.c Funcoes.h estruturas.h Sensores.h Dispositivos.h
	$(CC) $(CFLAGS) -c $< -o $@

# Regra para limpar os arquivos gerados
clean:
	rm -f $(OBJS) $(TARGET)

# Regra para recompilar tudo
rebuild: clean all

# Indica que 'all' e 'clean' não são arquivos
.PHONY: all clean rebuild