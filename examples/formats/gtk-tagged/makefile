 #============================================================================#
 #'hparser' examples.                                                         #
 #Copyright (C) 2006,2008 Kevin P. Barry (ta0kira@users.sourceforge.net)      #
 #Licensed under the GPL.                                                     #
 #============================================================================#

NAME=gtk-tagged
LIB_PATH=-L/usr/lib -L/usr/local/lib
COMMON=../common
INCL_PATH=-I$(COMMON)
COMPILE_OPT=`pkg-config --cflags gtk+-2.0` $(INCL_PATH)
LINK_OPT=`pkg-config --libs gtk+-2.0`

.PHONY: clean

$(NAME): main.o \
         $(COMMON)/data-display.o \
         $(COMMON)/file-interface.o \
         $(COMMON)/change-output.o \
         $(COMMON)/base-filter.o \
         $(COMMON)/section-filter.o \
         gtk-tagged-base.o \
         gtk-tagged-data.o \
         gtk-tagged-section.o
	make -C $(COMMON)
	g++ -Wall $(LINK_OPT) main.o $(COMMON)/data-display.o $(COMMON)/file-interface.o $(COMMON)/change-output.o $(COMMON)/base-filter.o $(COMMON)/section-filter.o gtk-tagged-base.o gtk-tagged-data.o gtk-tagged-section.o -o $(NAME) $(LIB_PATH) -lhpaux

main.o: main.cpp \
        $(COMMON)/file-interface.hpp \
        $(COMMON)/data-display.hpp \
	gtk-tagged-base.hpp \
        gtk-proxy.hpp
	g++ -Wall $(COMPILE_OPT) main.cpp -c -o main.o

gtk-tagged-base.o: gtk-tagged-base.cpp \
                   gtk-tagged-base.hpp \
                   $(COMMON)/base-filter.hpp \
                   $(COMMON)/modes.hpp \
                   gtk-proxy.hpp
	g++ -Wall $(COMPILE_OPT) gtk-tagged-base.cpp -c -o gtk-tagged-base.o

gtk-tagged-data.o: gtk-tagged-data.cpp \
                   gtk-tagged-data.hpp \
                   gtk-proxy.hpp
	g++ -Wall $(COMPILE_OPT) gtk-tagged-data.cpp -c -o gtk-tagged-data.o

gtk-tagged-section.o: gtk-tagged-section.cpp \
                      gtk-tagged-section.hpp \
                      $(COMMON)/section-filter.hpp \
                      gtk-tagged-data.hpp \
                      gtk-proxy.hpp
	g++ -Wall $(COMPILE_OPT) gtk-tagged-section.cpp -c -o gtk-tagged-section.o

clean:
	rm -f *~
	rm -f *.o
	rm -f $(NAME)
	make -C $(COMMON) clean
