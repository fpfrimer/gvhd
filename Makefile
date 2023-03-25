# Detectar o sistema operacional
ifeq ($(OS),Windows_NT)
  PLATFORM = WINDOWS
else
  PLATFORM = $(shell uname -s)
endif

# Configurar variáveis de acordo com a plataforma
CC = gcc
CFLAGS = -Wall -Wextra -O2
TARGET = gvhd

ifeq ($(PLATFORM),WINDOWS)
  INSTALL_DIR = C:/gvhd/$(TARGET)
  RM = del /Q /F
  EXE_EXT = .exe
else
  INSTALL_DIR = /usr/local/bin/$(TARGET)
  RM = rm -f
  EXE_EXT =
endif

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET)$(EXE_EXT) $(TARGET).c

install: $(TARGET)
ifeq ($(PLATFORM),WINDOWS)
	if not exist "$(INSTALL_DIR)" mkdir "$(INSTALL_DIR)"
	copy $(TARGET)$(EXE_EXT) "$(INSTALL_DIR)"
	setx /M PATH "%PATH%;$(INSTALL_DIR)"
else
	mkdir -p "$(INSTALL_DIR)"
	cp $(TARGET)$(EXE_EXT) "$(INSTALL_DIR)"
	export PATH=$$PATH:$(INSTALL_DIR)
endif

clean:
	$(RM) $(TARGET)$(EXE_EXT)

.PHONY: all install clean
