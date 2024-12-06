include config.mak
libgm.a	: rebuild config.mak
	 cat config.mak rebuild > build
	 chmod +x build
	 ./build 
install	: libgm.a
	  cp libgm.a $(KULINA)/lib
	  rm libgm.a
clean	:
	  rm -f libgm.a
