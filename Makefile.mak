CC65_HOME=C:\\Users\\bradc\\AppData\\Roaming\\cc65\\bin
CC65=$(CC65_HOME)\\cc65.exe
CA65=$(CC65_HOME)\\ca65.exe
CL65=$(CC65_HOME)\\cl65.exe

PRODUCT=sr
TARGET=atari
SRC_DIR=src

DIR2ATR_PATH=C:\Users\bradc\Projects\Atari

.SUFFIXES:
.SUFFIXES: .c .s .o .dat .srm

all: $(PRODUCT).xex

c_files: $(SRC_DIR)\*.c
    @echo Building $(**) to .s...
    @$(MAKE) -nologo /f Makefile.mak $(**:.c=.s)

s_files: $(SRC_DIR)\*.s
    @echo Building $(**) to .o...
    @$(MAKE) -nologo /f Makefile.mak $(**:.s=.o)

link_files: $(SRC_DIR)\*.o
    $(CL65) -t $(TARGET) -g -o $(PRODUCT).xex --config $(SRC_DIR)\$(PRODUCT).xex.$(TARGET).cfg --mapfile $(PRODUCT).map -Ln $(PRODUCT).lbl $(**) $(TARGET).lib

.s.o:
  $(CA65) -t $(TARGET) -g $<

.c.s:
  $(CC65) -t $(TARGET) -g $<

.dat.srm:
  python3 tools\import_map.py

$(PRODUCT).xex: c_files s_files link_files

clean: s_products c_products
  del $(PRODUCT).xex $(PRODUCT).map
  rmdir /Q /S diskdir

c_products: $(SRC_DIR)\*.c
    @echo Cleaning $(**:.c=.s)
    del $(**:.c=.s)

s_products: $(SRC_DIR)\*.s
    @echo Cleaning $(**:.s=.o)
    del $(**:.s=.o)

diskdir: $(PRODUCT).xex
    mkdir diskdir
    copy DOS.SYS diskdir\\
    copy $(PRODUCT).xex diskdir\AUTORUN.SYS
    copy *.srm diskdir\\

#    $(DIR2ATR_PATH)\dir2atr -d -b PicoBoot406 -P speedr.atr diskdir
#    $(DIR2ATR_PATH)\dir2atr -d -a -b MyPicoDos406 -P speedr.atr diskdir
disk: diskdir
    @echo Building bootable disk
    $(DIR2ATR_PATH)\dir2atr -E -b Dos25 -P speedr.atr diskdir

debug: disk
  Altirra64 /defprofile:800 /ntsc /burstio /fastboot /debug /debugbrkrun /debugcmd: ".loadsym sr.lbl" /disk speedr.atr

