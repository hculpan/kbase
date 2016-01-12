SOURCES   = kbase-main.c

PROGRAM   = kbase
PLATFORM  = apple2enh

#CC65BASE  = /Users/harryculpan/src/cc65
CC65_HOME = $(CC65BASE)/bin
CC        = $(CC65_HOME)/cl65
CFLAGS    = -t $(PLATFORM) --create-dep -O --include-dir ./lib
LDFLAGS   = -t $(PLATFORM) -m $(PROGRAM).map --lib ./lib/tuilibap.o

AC        = java -jar AppleCommander-1.3.5.13.jar
RM        = rm -f
CP        = cp -f

define MAKEDEPEND
	sed -e"s!$(<:.c=.s)!$@!p" -e"s![^:]*:.\(.*\)!\1:!" < $(<:.c=.u) > $(@:.o=.d)
	$(RM) $(<:.c=.u)
endef

all: copy-to-disk

build-lib: ./lib/tuilibap.c ./lib/tuilibap.h
	$(CC) -c $(CFLAGS) -o ./lib/tuilibap.o ./lib/tuilibap.c
#	$(CP) lib/tuilibap.h $(CC65BASE)/include
#	$(CP) lib/tuilibap.o $(CC65BASE)/lib
#	$(RM) lib/tuilibap.o

clean-lib:
	$(RM) ./lib/*.o

%.o: %.c build-lib
	$(CC) -c $(CFLAGS) -o $@ $<
#	@$(MAKEDEPEND)

$(PROGRAM): $(SOURCES:.c=.o)
	$(CC) $(LDFLAGS) -o $@ $^

copy-to-disk: $(PROGRAM) $(PROGRAM).po
	$(AC) -d $(PROGRAM).po $(PROGRAM)
	$(AC) -cc65 $(PROGRAM).po $(PROGRAM) BIN < $(PROGRAM)

$(PROGRAM).po:
	cp prodos-raw/blank.po ./$(PROGRAM).po
	$(AC) -p $(PROGRAM).po PRODOS SYS < prodos-raw/PRODOS
	$(AC) -p $(PROGRAM).po BASIC.SYSTEM SYS < prodos-raw/BASIC.SYSTEM

clean:
	$(RM) $(SOURCES:.c=.o) $(SOURCES:.c=.d) $(PROGRAM) $(PROGRAM).map ./-O

clean-disk:
	rm -f $(PROGRAM).po

clean-all: clean clean-disk
