CC := gcc

CFLAGS :=-fPIE -Iinclude/ -Ilib/ -Wall -Werror

SRCDIR := src/
LIBDIR := lib/
OBJDIR := build/obj/
LIBDIR := lib/

NAME := urbrowser

SFILES := c
OFILES := o

LIBS :=

SOURCES := $(shell find $(SRCDIR) -name "*.$(SFILES)")
LIBSOURCES := $(shell find $(LIBDIR) -name "*.$(SFILES)")
OBJECTS := $(patsubst $(SRCDIR)%.$(SFILES), $(OBJDIR)%.$(OFILES), $(SOURCES))
OBJECTS += $(patsubst $(LIBDIR)%.$(SFILES), $(OBJDIR)%.$(OFILES), $(LIBSOURCES))

all: directories $(NAME)

directories:
	mkdir -p $(OBJDIR)

$(NAME): $(OBJECTS)
	$(CC) $^ $(LIBS) -o $@
$(OBJDIR)%$(OFILES): $(SRCDIR)%$(SFILES)
	$(CC) $(CFLAGS) -c $< -o $@
$(OBJDIR)%$(OFILES): $(LIBDIR)%$(SFILES)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR)		
