 #============================================================================#
 #'hparser' examples.                                                         #
 #Copyright (C) 2006 Kevin P. Barry (ta0kira@users.sourceforge.net)           #
 #Licensed under the GPL.                                                     #
 #============================================================================#

.PHONY: all clean

all: data-display.o file-interface.o change-output.o base-filter.o section-filter.o descr.o

data-display.o: data-display.cpp \
                data-display.hpp
	g++ -Wall data-display.cpp -c -o data-display.o

file-interface.o: file-interface.cpp \
                  file-interface.hpp \
                  modes.hpp
	g++ -Wall file-interface.cpp -c -o file-interface.o

change-output.o: change-output.cpp \
                 change-output.hpp
	g++ -Wall change-output.cpp -c -o change-output.o

base-filter.o: base-filter.cpp \
               base-filter.hpp \
               change-output.hpp
	g++ -Wall base-filter.cpp -c -o base-filter.o

section-filter.o: section-filter.cpp \
                  section-filter.hpp \
                  change-output.hpp
	g++ -Wall section-filter.cpp -c -o section-filter.o

descr.o: descr.cpp \
         descr.hpp
	g++ -Wall descr.cpp -c -o descr.o

clean:
	rm -f *~
	rm -f *.o
