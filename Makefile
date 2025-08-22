# Makefile multiplataforma para projeto SDL2

# Variáveis comuns
CC := gcc
CFLAGS := -Wall -g -Iinclude -Iinclude/SDL2 -Isrc -Isrc/core
LIB_DIR := src/lib
SDL2MAIN_A := $(LIB_DIR)/libSDL2main.a
SDL2_IMPORT := $(LIB_DIR)/libSDL2.dll.a
SDL2_DLL := $(LIB_DIR)/SDL2.dll
OBJDIR := bin
BINDIR := build
SRCS := \
	src/main.c \
	src/core/algebra.c \
	src/core/objeto.c \
	src/core/camera.c \
	src/core/tela.c \
	src/core/controls.c
OBJS := $(SRCS:src/%.c=$(OBJDIR)/%.o)

# Linux/bash
linux: $(BINDIR)/programa.exe

$(OBJDIR):
	@mkdir -p $(OBJDIR)/core

$(BINDIR):
	@mkdir -p $(BINDIR)

$(OBJDIR)/%.o: src/%.c | $(OBJDIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -MMD -c $< -o $@

$(BINDIR)/programa.exe: $(OBJS) $(SDL2MAIN_A) $(SDL2_IMPORT) | $(BINDIR)
	$(CC) $^ -o $@ -lmingw32 $(SDL2MAIN_A) $(SDL2_IMPORT)
	cp $(SDL2_DLL) $(BINDIR)/

linux-clean:
	rm -rf $(OBJDIR) $(BINDIR)

# Windows/cmd
windows: $(BINDIR)/programa.exe-win

$(OBJDIR)-win:
	@if not exist $(OBJDIR) mkdir $(OBJDIR) & if not exist $(OBJDIR)\core mkdir $(OBJDIR)\core

$(BINDIR)-win:
	@if not exist $(BINDIR) mkdir $(BINDIR)

$(OBJDIR)/%.o: src/%.c | $(OBJDIR)-win
	@if not exist $(dir $@) mkdir $(dir $@)
	$(CC) $(CFLAGS) -MMD -c $< -o $@

$(BINDIR)/programa.exe-win: $(OBJS) $(SDL2MAIN_A) $(SDL2_IMPORT) | $(BINDIR)-win
	$(CC) $^ -o $@ -lmingw32 $(SDL2MAIN_A) $(SDL2_IMPORT)
	copy $(SDL2_DLL) $(BINDIR)\

windows-clean:
	@if exist $(OBJDIR) rmdir /s /q $(OBJDIR)
	@if exist $(BINDIR) rmdir /s /q $(BINDIR)

.PHONY: linux linux-clean windows windows-clean