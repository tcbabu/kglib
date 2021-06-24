include config.mak
#CC	=cc -pthread
CC	=g++   -pthread 
CFLAGS	= -g
kgdevelop	: kgdevelop.o Fileoptdia.o Itemoptdia.o Borderoptdia.o getStrings.o Options.o \
		  Optionsdia.o addcontroldia.o slided.o slidef.o buttoninfo.o Runcheckbox.o Runselectmenu.o Runthumbnail.o  editbuttons.o messagedata.o textboxdata.o slidebaropt.o \
		 $(KULINA)/lib/libkulina.a 
		 $(CC) $(CFLAGS) -o kgdevelop kgdevelop.o Fileoptdia.o \
		 Itemoptdia.o  Borderoptdia.o  getStrings.o Options.o \
		 Optionsdia.o  addcontroldia.o slided.o slidef.o buttoninfo.o Runcheckbox.o  Runselectmenu.o  Runthumbnail.o   slidebaropt.o \
		 editbuttons.o   messagedata.o  textboxdata.o    \
		 $(KULINA)/lib/libkulina.a $(KULINA)/lib/libgm.a -L/usr/X11R6/lib -lX11 -lXext -lm -lpthread  -lGL
clean	:
	 rm -f *.o kgdevelop
install	: kgdevelop 
	install -m 755 -s  kgdevelop $(PREFIX)/bin/kgdevelop
