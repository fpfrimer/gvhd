CC = gcc
CFLAGS = -Wall -Wextra -O2
TARGET = gvhd
INSTALL_DIR = C:/gvhd/$(TARGET)

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c

install: $(TARGET)
	if not exist "$(INSTALL_DIR)" mkdir "$(INSTALL_DIR)"
	copy $(TARGET).exe "$(INSTALL_DIR)"
	setx /M PATH "%PATH%;$(INSTALL_DIR)"

clean:
	del /Q /F $(TARGET).exe

.PHONY: all install clean
