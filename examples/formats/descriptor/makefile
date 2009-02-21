 #============================================================================#
 #'hparser' examples.                                                         #
 #Copyright (C) 2006 Kevin P. Barry (ta0kira@users.sourceforge.net)           #
 #Licensed under the GPL.                                                     #
 #============================================================================#

NAME=descr
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
         descr-base.o \
         descr-data.o \
         descr-table.o
	make -C $(COMMON)
	g++ -Wall $(INCL_PATH) main.o $(COMMON)/data-display.o $(COMMON)/file-interface.o $(COMMON)/change-output.o $(COMMON)/base-filter.o $(COMMON)/section-filter.o $(COMMON)/descr.o descr-base.o descr-data.o descr-table.o -o $(NAME) $(LIB_PATH) -lhpaux

main.o: $(COMMON)/main.cpp \
        $(COMMON)/file-interface.hpp \
        $(COMMON)/data-display.hpp \
	descr-base.hpp
	g++ -Wall $(INCL_PATH) -DBASE_TYPE=DescrBase -DBASE_TYPE_FILE=\"../descriptor/descr-base.hpp\" $(COMMON)/main.cpp -c -o main.o

descr-base.o: descr-base.cpp \
              descr-base.hpp \
              $(COMMON)/base-filter.hpp \
              $(COMMON)/modes.hpp
	g++ -Wall $(INCL_PATH) descr-base.cpp -c -o descr-base.o

descr-data.o: descr-data.cpp \
              descr-data.hpp \
              $(COMMON)/descr.hpp
	g++ -Wall $(INCL_PATH) descr-data.cpp -c -o descr-data.o

descr-table.o: descr-table.cpp \
               descr-table.hpp \
               $(COMMON)/section-filter.hpp \
               $(COMMON)/descr.hpp \
               descr-data.hpp
	g++ -Wall $(INCL_PATH) descr-table.cpp -c -o descr-table.o

clean:
	rm -f *~
	rm -f *.o
	rm -f $(NAME)
	make -C $(COMMON) clean
