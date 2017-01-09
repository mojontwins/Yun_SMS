CC=sdcc.exe
CFLAGS=-c -mz80 --peep-file lib\peep-rules.txt --peep-asm

all: yun.sms

yun.sms: yun.ihx
	../utils/ihx2sms.exe yun.ihx yun.sms

yun.ihx: yun.rel enems.rel fabolee_int.rel game.rel general.rel hotspots.rel hud.rel inits.rel level.rel map.rel player.rel printer.rel scroller.rel simplecoco.rel
	$(CC) -o yun.ihx -mz80 --no-std-crt0 --data-loc 0xC000 -Wl-b_BANK2=0x8000 -Wl-b_BANK3=0x8000 -Wl-b_BANK4=0x8000 -Wl-b_BANK5=0x8000 -Wl-b_BANK6=0x8000 -Wl-b_BANK7=0x8000 lib\crt0_sms.rel yun.rel enems.rel fabolee_int.rel game.rel general.rel hotspots.rel hud.rel inits.rel level.rel map.rel player.rel printer.rel scroller.rel simplecoco.rel lib\SMSlib.lib lib\PSGlib.rel lib\aPLib.rel banks\maindata.rel banks\bank2.rel banks\bank3.rel banks\bank4.rel banks\bank5.rel banks\bank6.rel banks\bank7.rel

yun.rel: yun.c
	$(CC) $(CFLAGS) yun.c

enems.rel: engine\enems.c
	$(CC) $(CFLAGS) engine\enems.c

fabolee_int.rel: engine\fabolee_int.c
	$(CC) $(CFLAGS) engine\fabolee_int.c

game.rel: engine\game.c
	$(CC) $(CFLAGS) engine\game.c

general.rel: engine\general.c
	$(CC) $(CFLAGS) engine\general.c

hotspots.rel: engine\hotspots.c
	$(CC) $(CFLAGS) engine\hotspots.c

hud.rel: engine\hud.c
	$(CC) $(CFLAGS) engine\hud.c

inits.rel: engine\inits.c
	$(CC) $(CFLAGS) engine\inits.c

level.rel: engine\level.c
	$(CC) $(CFLAGS) engine\level.c

map.rel: engine\map.c
	$(CC) $(CFLAGS) engine\map.c

player.rel: engine\player.c
	$(CC) $(CFLAGS) engine\player.c

printer.rel: engine\printer.c
	$(CC) $(CFLAGS) engine\printer.c

scroller.rel: engine\scroller.c
	$(CC) $(CFLAGS) engine\scroller.c

simplecoco.rel: engine\simplecoco.c
	$(CC) $(CFLAGS) engine\simplecoco.c
