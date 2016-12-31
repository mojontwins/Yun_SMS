@echo off
echo remember: justcompile, compileandbanks, justassets.
echo and be prepared to waitttttt...
if [%1]==[justcompile] goto :justcompile
if [%1]==[compileandbanks] goto :compileandbanks

cd ..\gfx

rem Paletas
echo Converting palettes
..\utils\mkts.exe platform=sms mode=pals pals=pals0.png out=..\dev\work\pals0.h label=pals0 silent
..\utils\mkts.exe platform=sms mode=pals pals=pals1.png out=..\dev\work\pals1.h label=pals1 silent
..\utils\mkts.exe platform=sms mode=pals pals=pals2.png out=..\dev\work\pals2.h label=pals2 silent
..\utils\mkts.exe platform=sms mode=pals pals=pals3.png out=..\dev\work\pals3.h label=pals3 silent
..\utils\mkts.exe platform=sms mode=pals pals=pals4.png out=..\dev\work\pals4.h label=pals4 silent
copy /b ..\dev\work\pals0.h + ..\dev\work\pals1.h + ..\dev\work\pals2.h + ..\dev\work\pals3.h + ..\dev\work\pals4.h ..\dev\assets\palettes.h > nul

rem Gráficos
echo Converting graphics

rem Primero vamos a convertir los metatilesets de las fases
..\utils\mkts.exe platform=sms mode=mapped in=ts0.png pals=pals0.png out=..\dev\work\level0\ts_patterns0.bin tsmap=..\dev\banks\bank3\ts_meta0.h label=ts_meta0 offset=0,0 size=16,3 metasize=2,2 tmapoffset=256 silent
..\utils\mkts.exe platform=sms mode=mapped in=ts1.png pals=pals1.png out=..\dev\work\level1\ts_patterns1.bin tsmap=..\dev\banks\bank4\ts_meta1.h label=ts_meta1 offset=0,0 size=16,5 metasize=2,2 tmapoffset=256 silent
..\utils\mkts.exe platform=sms mode=mapped in=ts2.png pals=pals2.png out=..\dev\work\level2\ts_patterns2.bin tsmap=..\dev\banks\bank5\ts_meta2.h label=ts_meta2 offset=0,0 size=16,3 metasize=2,2 tmapoffset=256 silent
..\utils\mkts.exe platform=sms mode=mapped in=ts3.png pals=pals3s.png out=..\dev\work\level3\ts_patterns3.bin tsmap=..\dev\banks\bank6\ts_meta3.h label=ts_meta3 offset=0,0 size=16,4 metasize=2,2 tmapoffset=256 silent
rem CHANGE WHEN DONE:
..\utils\mkts.exe platform=sms mode=mapped in=ts0.png pals=pals0.png out=..\dev\work\level4\ts_patterns4.bin tsmap=..\dev\banks\bank7\ts_meta4.h label=ts_meta4 offset=0,0 size=16,3 metasize=2,2 tmapoffset=256 silent

rem Ahora, los metaspritesets fijos.
..\utils\mkts.exe platform=sms mode=chars in=ss-hud.png pals=pals0.png out=..\dev\work\main\ss_patterns_hud.bin size=16,1 silent
..\utils\mkts.exe platform=sms mode=sprites in=ss.png pals=pals0.png out=..\dev\work\main\ss_patterns_yun.bin tsmap=..\dev\assets\ss_yun.h label=ss_yun offset=0,0 size=7,1 metasize=2,3 sprorg=-4,-8 tmapoffset=16 genflipped simple silent
..\utils\mkts.exe platform=sms mode=sprites in=ss.png pals=pals0.png out=..\dev\work\main\ss_patterns_items.bin tsmap=..\dev\assets\ss_items.h label=ss_items offset=0,3 size=8,1 metasize=2,2 sprorg=0,0 tmapoffset=86 simple silent
..\utils\mkts.exe platform=sms mode=sprites in=ss.png pals=pals0.png out=..\dev\work\main\ss_patterns_enems_fixed.bin tsmap=..\dev\assets\ss_fixed0.h label=ss_fixed offset=0,15 size=5,1 metasize=2,2 sprorg=0,0 tmapoffset=118 genflipped upsidedown simple silent
..\utils\mkts.exe platform=sms mode=sprites in=ss.png pals=pals0.png out=..\dev\work\main\ss_patterns_enems_fixed2.bin tsmap=..\dev\assets\ss_fixed1.h label=ss_fixed2 offset=10,15 size=2,1 metasize=2,2 sprorg=0,0 tmapoffset=169 upsidedown simple silent

rem free @ 159 (160, in fact!)

rem Y los metaspritesets de cada fase
..\utils\mkts.exe platform=sms mode=sprites in=ss.png pals=pals0.png out=..\dev\work\level0\ss_patterns_enems0.bin tsmap=..\dev\banks\bank3\ss_enems0.h label=ss_enems0 offset=0,5 size=8,1 metasize=2,2 sprorg=0,0 tmapoffset=185 genflipped upsidedown simple silent
..\utils\mkts.exe platform=sms mode=sprites in=ss.png pals=pals0.png out=..\dev\work\level1\ss_patterns_enems1.bin tsmap=..\dev\banks\bank4\ss_enems1.h label=ss_enems1 offset=0,7 size=8,1 metasize=2,2 sprorg=0,0 tmapoffset=185 genflipped upsidedown simple silent
..\utils\mkts.exe platform=sms mode=sprites in=ss.png pals=pals0.png out=..\dev\work\level2\ss_patterns_enems2.bin tsmap=..\dev\banks\bank5\ss_enems2.h label=ss_enems2 offset=0,9 size=8,1 metasize=2,2 sprorg=0,0 tmapoffset=185 genflipped upsidedown simple silent
..\utils\mkts.exe platform=sms mode=sprites in=ss.png pals=pals3.png out=..\dev\work\level3\ss_patterns_enems3.bin tsmap=..\dev\banks\bank6\ss_enems3.h label=ss_enems3 offset=0,11 size=8,1 metasize=2,2 sprorg=0,0 tmapoffset=185 genflipped upsidedown simple silent
..\utils\mkts.exe platform=sms mode=sprites in=ss.png pals=pals0.png out=..\dev\work\level4\ss_patterns_enems4.bin tsmap=..\dev\banks\bank7\ss_enems4.h label=ss_enems4 offset=0,13 size=8,1 metasize=2,2 sprorg=0,0 tmapoffset=185 genflipped upsidedown simple silent

rem map data
echo Converting maps
cd ..\map
..\utils\unpackedmap.exe level0.MAP bin=..\dev\work\level0 4 6 15 0
..\utils\unpackedmap.exe level1.MAP bin=..\dev\work\level1 4 6 15 1
..\utils\unpackedmap.exe level2.MAP bin=..\dev\work\level2 4 6 15 2
..\utils\unpackedmap.exe level3.MAP bin=..\dev\work\level3 3 4 15 3
rem CHANGE WHEN DONE:
..\utils\unpackedmap.exe level0.MAP bin=..\dev\work\level4 4 6 15 4

echo Converting enems
cd ..\enems
..\utils\eneexp2.exe enems0.ene ..\dev\banks\bank3\enems0.h 0
..\utils\eneexp2.exe enems1.ene ..\dev\banks\bank4\enems1.h 1
..\utils\eneexp2.exe enems2.ene ..\dev\banks\bank5\enems2.h 2
..\utils\eneexp2.exe enems3.ene ..\dev\banks\bank6\enems3.h 3
rem CHANGE WHEN DONE:
..\utils\eneexp2.exe enems0.ene ..\dev\banks\bank7\enems4.h 4

rem compress & make available
echo Compressing main assets
cd ..\dev
..\utils\apack.exe work\main\ss_patterns_hud.bin banks\main\ss_patterns_hud_c.bin > nul
..\utils\apack.exe work\main\ss_patterns_yun.bin banks\main\ss_patterns_yun_c.bin > nul
..\utils\apack.exe work\main\ss_patterns_items.bin banks\main\ss_patterns_items_c.bin > nul
..\utils\apack.exe work\main\ss_patterns_enems_fixed.bin banks\main\ss_patterns_enems_fixed_c.bin > nul
..\utils\apack.exe work\main\ss_patterns_enems_fixed2.bin banks\main\ss_patterns_enems_fixed2_c.bin > nul

echo Importing main assets
..\utils\folder2c banks\main banks\maindata

echo Compressing and building data for level banks 3, 4, 5, 6, 7
..\utils\apack.exe work\level0\ts_patterns0.bin work\level0\ts_patterns0c.bin > nul
..\utils\apack.exe work\level1\ts_patterns1.bin work\level1\ts_patterns1c.bin > nul
..\utils\apack.exe work\level2\ts_patterns2.bin work\level2\ts_patterns2c.bin > nul
..\utils\apack.exe work\level3\ts_patterns3.bin work\level3\ts_patterns3c.bin > nul
..\utils\apack.exe work\level4\ts_patterns4.bin work\level4\ts_patterns4c.bin > nul

..\utils\apack.exe work\level0\ss_patterns_enems0.bin work\level0\ss_patterns_enems0c.bin > nul
..\utils\apack.exe work\level1\ss_patterns_enems1.bin work\level1\ss_patterns_enems1c.bin > nul
..\utils\apack.exe work\level2\ss_patterns_enems2.bin work\level2\ss_patterns_enems2c.bin > nul 
..\utils\apack.exe work\level3\ss_patterns_enems3.bin work\level3\ss_patterns_enems3c.bin > nul 
..\utils\apack.exe work\level4\ss_patterns_enems4.bin work\level4\ss_patterns_enems4c.bin > nul 

..\utils\apack.exe work\level0\map_0.bin work\level0\map_0c.bin > nul
..\utils\apack.exe work\level1\map_1.bin work\level1\map_1c.bin > nul
..\utils\apack.exe work\level2\map_2.bin work\level2\map_2c.bin > nul
..\utils\apack.exe work\level3\map_3.bin work\level3\map_3c.bin > nul
..\utils\apack.exe work\level4\map_4.bin work\level4\map_4c.bin > nul

..\utils\apack.exe work\level0\map_0_locks.bin work\level0\map_0_locksc.bin > nul
..\utils\apack.exe work\level1\map_1_locks.bin work\level1\map_1_locksc.bin > nul
..\utils\apack.exe work\level2\map_2_locks.bin work\level2\map_2_locksc.bin > nul
..\utils\apack.exe work\level3\map_3_locks.bin work\level3\map_3_locksc.bin > nul
..\utils\apack.exe work\level4\map_4_locks.bin work\level4\map_4_locksc.bin > nul

rem

..\utils\bin2c.exe -m -o banks\bank3\level0.h work\level0\ts_patterns0c.bin work\level0\ss_patterns_enems0c.bin work\level0\map_0c.bin work\level0\map_0_locksc.bin
..\utils\bin2c.exe -m -o banks\bank4\level1.h work\level1\ts_patterns1c.bin work\level1\ss_patterns_enems1c.bin work\level1\map_1c.bin work\level1\map_1_locksc.bin
..\utils\bin2c.exe -m -o banks\bank5\level2.h work\level2\ts_patterns2c.bin work\level2\ss_patterns_enems2c.bin work\level2\map_2c.bin work\level2\map_2_locksc.bin
..\utils\bin2c.exe -m -o banks\bank6\level3.h work\level3\ts_patterns3c.bin work\level3\ss_patterns_enems3c.bin work\level3\map_3c.bin work\level3\map_3_locksc.bin
..\utils\bin2c.exe -m -o banks\bank7\level4.h work\level4\ts_patterns4c.bin work\level4\ss_patterns_enems4c.bin work\level4\map_4c.bin work\level4\map_4_locksc.bin

rem Level music

..\utils\bin2c.exe -m -o banks\bank3\psg0.h work\ogt\m_ingame0.psg
..\utils\bin2c.exe -m -o banks\bank4\psg1.h work\ogt\m_ingame1.psg
..\utils\bin2c.exe -m -o banks\bank5\psg2.h work\ogt\m_ingame2.psg
..\utils\bin2c.exe -m -o banks\bank6\psg3.h work\ogt\m_ingame3.psg
..\utils\bin2c.exe -m -o banks\bank7\psg4.h work\ogt\m_ingame4.psg

rem here call my lil' app!
..\utils\generatebank.exe scan=banks\bank3 out=banks\bank3 bank=3
..\utils\generatebank.exe scan=banks\bank4 out=banks\bank4 bank=4
..\utils\generatebank.exe scan=banks\bank5 out=banks\bank5 bank=5
..\utils\generatebank.exe scan=banks\bank6 out=banks\bank6 bank=6
..\utils\generatebank.exe scan=banks\bank7 out=banks\bank7 bank=7

echo.

rem bank2, sfx & some sutff
echo Importing music
..\utils\folder2c banks\bank2 banks\bank2

:compileandbanks
echo Building banks
cd banks
sdcc -c -mz80 --constseg BANK2 bank2.c
sdcc -c -mz80 --constseg BANK3 bank3.c
sdcc -c -mz80 --constseg BANK4 bank4.c
sdcc -c -mz80 --constseg BANK5 bank5.c
sdcc -c -mz80 --constseg BANK6 bank6.c
sdcc -c -mz80 --constseg BANK7 bank7.c
echo Building main data asset
sdcc -c -mz80 maindata.c
del *.asm > nul
del *.lst > nul
del *.sym > nul
cd ..
echo.

:justcompile
if [%1]==[justassets] goto :skipmain 
echo Compiling...
set STARTTIME=%TIME%
sdcc -c -mz80 yun.c
set ENDTIME=%TIME%

rem measure time http://stackoverflow.com/questions/9922498/calculate-time-difference-in-windows-batch-file
for /F "tokens=1-4 delims=:.," %%a in ("%STARTTIME%") do (
   set /A "start=(((%%a*60)+1%%b %% 100)*60+1%%c %% 100)*100+1%%d %% 100"
)
for /F "tokens=1-4 delims=:.," %%a in ("%ENDTIME%") do (
   set /A "end=(((%%a*60)+1%%b %% 100)*60+1%%c %% 100)*100+1%%d %% 100"
)
set /A elapsed=end-start
set /A hh=elapsed/(60*60*100), rest=elapsed%%(60*60*100), mm=rest/(60*100), rest%%=60*100, ss=rest/100, cc=rest%%100
if %hh% lss 10 set hh=0%hh%
if %mm% lss 10 set mm=0%mm%
if %ss% lss 10 set ss=0%ss%
if %cc% lss 10 set cc=0%cc%

set DURATION=%hh%:%mm%:%ss%,%cc%

echo SDCC se ha tirado fumando exactamente %DURATION% 
echo en un %PROCESSOR_IDENTIFIER% con %NUMBER_OF_PROCESSORS% núcleos.

:skipmain

echo Linking...
sdcc -o yun.ihx -mz80 --no-std-crt0 --data-loc 0xC000 -Wl-b_BANK2=0x8000 -Wl-b_BANK3=0x8000 -Wl-b_BANK4=0x8000 -Wl-b_BANK5=0x8000 -Wl-b_BANK6=0x8000 -Wl-b_BANK7=0x8000 lib\crt0_sms.rel yun.rel lib\SMSlib.lib lib\PSGlib.rel lib\aPLib.rel banks\maindata.rel banks\bank2.rel banks\bank3.rel banks\bank4.rel banks\bank5.rel banks\bank6.rel banks\bank7.rel

echo Building cart image...
..\utils\ihx2sms yun.ihx yun.sms

echo.
echo DONE COJONE!
echo.

rem del yun.asm > nul
rem del yun.rel > nul
del yun.ihx > nul
del yun.lk  > nul
del yun.lst > nul
del yun.map > nul
del yun.noi > nul
del yun.sym > nul
