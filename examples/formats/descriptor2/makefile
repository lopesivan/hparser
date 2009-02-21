 #============================================================================#
 #'hparser' examples.                                                         #
 #Copyright (C) 2006 Kevin P. Barry (ta0kira@users.sourceforge.net)           #
 #Licensed under the GPL.                                                     #
 #============================================================================#

NAME=descr2
LIB_PATH=-L/usr/lib -L/usr/local/lib
COMMON=../common
INCL_PATH=-I$(COMMON)

.PHONY: clean

$(NAME): main.o \
         $(COMMON)/data-display.o \
         $(COMMON)/file-interface.o \
         $(COMMON)/change-output.o \
         $(COMMON)/base-filter.o \
         $(COMMON)/section-filter.o \
         $(COMMON)/descr.o \
         descr2-base.o \
         descr2-data.o \
         descr2-table.o
	make -C $(COMMON)
	g++ -Wall $(INCL_PATH) main.o $(COMMON)/data-display.o $(COMMON)/file-interface.o $(COMMON)/change-output.o $(COMMON)/base-filter.o $(COMMON)/section-filter.o $(COMMON)/descr.o descr2-base.o descr2-data.o descr2-table.o -o $(NAME) $(LIB_PATH) -lhpaux

main.o: $(COMMON)/main.cpp \
        $(COMMON)/file-interface.hpp \
        $(COMMON)/data-display.hpp \
	descr2-base.hpp
	g++ -Wall $(INCL_PATH) -DBASE_TYPE=Descr2Base -DBASE_TYPE_FILE=\"../descriptor2/descr2-base.hpp\" $(COMMON)/main.cpp -c -o main.o

descr2-base.o: descr2-base.cpp \
               descr2-base.hpp \
               $(COMMON)/base-filter.hpp \
               $(COMMON)/modes.hpp
	g++ -Wall $(INCL_PATH) descr2-base.cpp -c -o descr2-base.o

descr2-data.o: descr2-data.cpp \
               descr2-data.hpp \
               $(COMMON)/change-output.hpp \
               $(COMMON)/descr.hpp
	g++ -Wall $(INCL_PATH) descr2-data.cpp -c -o descr2-data.o

descr2-table.o: descr2-table.cpp \
                descr2-table.hpp \
                $(COMMON)/section-filter.hpp \
                $(COMMON)/descr.hpp \
                descr2-data.hpp
	g++ -Wall $(INCL_PATH) descr2-table.cpp -c -o descr2-table.o

clean:
	rm -f *~
	rm -f *.o
	rm -f $(NAME)
	make -C $(COMMON) clean
