CC = gcc
CFLAGS = -g -Wall -Wextra -I/usr/include/libxml2
LDFLAGS = -lcurl -lxml2

SRCDIR = src
OBJDIR = obj
BINDIR = bin

SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SOURCES))
TARGET = $(BINDIR)/ava

PREFIX = /usr/local
BINDIR_INSTALL = $(PREFIX)/bin

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

install: $(TARGET)
	@mkdir -p $(BINDIR_INSTALL)
	install -m 0755 $(TARGET) $(BINDIR_INSTALL)

clean:
	$(RM) -r $(OBJDIR) $(BINDIR)

.PHONY: all clean
