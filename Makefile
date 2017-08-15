# Modify as appropriate
STELLARISWARE=/mnt/c/StellarisWare

CC=arm-none-eabi-gcc -std=gnu11 -Wall  -Os -march=armv7-m -mcpu=cortex-m3 -mthumb -mfix-cortex-m3-ldrd -Wl,--gc-sections
SEARCH_RULE= -I${STELLARISWARE} -L${STELLARISWARE}/driverlib/gcc-cm3 $(DEBUG)
DEPENDENCIES= systick.h kernel.h
LFLAGS= -Tlinkscript.x -Wl,-Map,crschep.map -Wl,--entry,ResetISR
LIBS= -ldriver-cm3
DEBUG = -g
SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)


%.o: %.c $(DEPENDENCIES)
	@${CC} -c -o $@ $< $(SEARCH_RULE)
	@echo "compiling $<"

p3Test.elf: $(OBJ)
	@echo "START LINKING...."
	@${CC} -o $@ $(SEARCH_RULE) $(LFLAGS) $^ $(LIBS)
	@echo "Done..."

.PHONY: clean
clean:
	rm -f *.elf *.map *.o

# vim: noexpandtab  
