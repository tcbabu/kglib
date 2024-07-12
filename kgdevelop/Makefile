include config.mak
#CC	=cc -pthread
CC	=g++   -pthread -I$(KULINA)/include
CFLAGS	= -g
kgdevelop	: kgdevelop.o Fileoptdia.o Itemoptdia.o Borderoptdia.o getStrings.o Options.o \
		  Optionsdia.o addcontroldia.o slided.o slidef.o buttoninfo.o Runcheckbox.o Runselectmenu.o Runthumbnail.o  editbuttons.o messagedata.o textboxdata.o slidebaropt.o \
		  ButnType.o ButnTypeCallbacks.o \
		  textelementdata.o textelementdataCallbacks.o \
		  tableelmt.o tableelmtCallbacks.o \
		 $(KULINA)/lib/libkulina.a 
		 $(CC) $(CFLAGS) -o kgdevelop kgdevelop.o Fileoptdia.o \
		 Itemoptdia.o  Borderoptdia.o  getStrings.o Options.o \
		 Optionsdia.o  addcontroldia.o slided.o slidef.o buttoninfo.o Runcheckbox.o  Runselectmenu.o  Runthumbnail.o   slidebaropt.o \
		 editbuttons.o   messagedata.o  textboxdata.o    \
		  ButnType.o ButnTypeCallbacks.o \
		  textelementdata.o textelementdataCallbacks.o \
		  tableelmt.o tableelmtCallbacks.o \
		 $(KULINA)/lib/libkulina.a $(KULINA)/lib/libgm.a -L/usr/X11R6/lib -lX11 -lXext -lm -lpthread  
clean	:
	 rm -f *.o kgdevelop
install	: kgdevelop 
	install -m 755   kgdevelop $(PREFIX)/bin/kgdevelop
