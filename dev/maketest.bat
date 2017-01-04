@echo off

sdcc -c -mz80 test.c
sdcc -o test.ihx -mz80 --no-std-crt0 --data-loc 0xC000 lib\crt0_sms.rel test.rel  lib\SMSlib.lib lib\PSGlib.rel lib\aPLib.rel 
..\utils\ihx2sms test.ihx test.sms

del test.ihx
del test.lk
del test.lst
del test.map
del test.noi
del test.rel
del test.sym
