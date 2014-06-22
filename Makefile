include config.mk
all:
	gcc $(CFLAGS) main.c -o $(TARGET)
debug:
	gcc $(CFLAGS) $(DEBUGFLAGS) main.c -o $(TARGET)
install:
	@echo installing to $(DESTDIR)$(PREFIX)/bin
	@install -D -m755 $(TARGET) $(DESTDIR)$(PREFIX)/bin/$(TARGET)
clean:
	rm -f $(TARGET)
