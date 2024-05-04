

SRC = $(wildcard *.c)
OBJS = $(SRC:%.c=%.o)
HEADERS = $(SRC:%.c=%.h)

PRG            = main
OBJ            = program.o 
MCU_TARGET     = attiny13
OPTIMIZE       = -Os

# DEFS           = -W1,-u,vprintf -lprintf_flt -lm
DEFS           =
LIBS           = 


# You should not have to change anything below here.

CC             = avr-gcc
CXX             = avr-g++

# Override is only needed by avr-lib build system.

# override CFLAGS        = -g -Wall $(OPTIMIZE) -mmcu=$(MCU_TARGET) $(DEFS) -I/usr/local/avr/include
override CFLAGS        = -g -Wall $(OPTIMIZE) -mmcu=$(MCU_TARGET) $(DEFS) -I/usr/local/avr/avr/include
override CFLAGS        = -g -Wall $(OPTIMIZE) -mmcu=$(MCU_TARGET) $(DEFS) -I/usr/lib/avr/include/avr

override CXXFLAGS        = -g -Wall $(OPTIMIZE) -mmcu=$(MCU_TARGET) $(DEFS)
override LDFLAGS       = -Wl,-Map,$(PRG).map 

OBJCOPY        = avr-objcopy
OBJDUMP        = avr-objdump

all: $(PRG).elf lst text eeprom size

$(PRG).elf: $(SRC) $(HEADERS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(PRG).elf $(SRC) $(LIBS)

clean:
	rm -rf *.o $(PRG).elf *.eps *.png *.pdf *.bak 
	rm -rf *.lst *.map $(EXTRA_CLEAN_FILES)

install: 
	avrdude -p t13 -e -U flash:w:$(PRG).hex

usbinstall:
	avrdude -c avrisp2 -P usb -p t13 -e -U flash:w:$(PRG).hex    

aspinstall:
	avrdude -c usbasp -P usb -p t13 -e -U flash:w:$(PRG).hex

usbfuseintslow:
usbfusedefault:
	avrdude -c avrisp2 -P usb -p t13 -U hfuse:w:0xFF:m -U lfuse:w:0x6A:m

usbfuseintfast:
	avrdude -c avrisp2 -P usb -p t13 -U hfuse:w:0xFF:m -U lfuse:w:0x7A:m
	
aspfuseintfast:
	avrdude -c usbasp -P usb -p t13 -U hfuse:w:0xFF:m -U lfuse:w:0x7A:m	

#usbfuseext:
#	avrdude -c avrisp2 -P usb -p t13 -U hfuse:w:0xD9:m -U lfuse:w:0xEF:m

lst:  $(PRG).lst

%.lst: %.elf
	$(OBJDUMP) -h -S $< > $@

# Rules for building the .text rom images

text: hex bin srec

hex:  $(PRG).hex
bin:  $(PRG).bin
srec: $(PRG).srec

%.hex: %.elf
	$(OBJCOPY) -j .text -j .data -O ihex $< $@

%.srec: %.elf
	$(OBJCOPY) -j .text -j .data -O srec $< $@

%.bin: %.elf
	$(OBJCOPY) -j .text -j .data -O binary $< $@

# Rules for building the .eeprom rom images

eeprom: ehex ebin esrec

ehex:  $(PRG)_eeprom.hex
ebin:  $(PRG)_eeprom.bin
esrec: $(PRG)_eeprom.srec

%_eeprom.hex: %.elf
	$(OBJCOPY) -j .eeprom --change-section-lma .eeprom=0 -O ihex $< $@

%_eeprom.srec: %.elf
	$(OBJCOPY) -j .eeprom --change-section-lma .eeprom=0 -O srec $< $@

%_eeprom.bin: %.elf
	$(OBJCOPY) -j .eeprom --change-section-lma .eeprom=0 -O binary $< $@

# Every thing below here is used by avr-libc's build system and can be ignored
# by the casual user.

FIG2DEV                 = fig2dev
EXTRA_CLEAN_FILES       = *.hex *.bin *.srec


size: ${PRG}.elf
	avr-size -C --mcu=${MCU_TARGET} ${PRG}.elf


