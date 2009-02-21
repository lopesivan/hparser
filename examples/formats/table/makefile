 #============================================================================#
 #'hparser' examples.                                                         #
 #Copyright (C) 2007 Kevin P. Barry (ta0kira@users.sourceforge.net)           #
 #Licensed under the GPL.                                                     #
 #============================================================================#

NAME=table
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
         table-base.o \
         table-data.o \
         table-table.o \
         table-descr.o
	make -C $(COMMON)
	g++ -Wall $(INCL_PATH) main.o $(COMMON)/data-display.o $(COMMON)/file-interface.o $(COMMON)/change-output.o $(COMMON)/base-filter.o $(COMMON)/section-filter.o table-base.o table-data.o table-table.o table-descr.o -o $(NAME) $(LIB_PATH) -lhpaux

main.o: $(COMMON)/main.cpp \
        $(COMMON)/file-interface.hpp \
        $(COMMON)/data-display.hpp \
	table-base.hpp
	g++ -Wall $(INCL_PATH) -DBASE_TYPE=TableBase -DBASE_TYPE_FILE=\"../table/table-base.hpp\" $(COMMON)/main.cpp -c -o main.o

table-base.o: table-base.cpp \
              table-base.hpp \
              table-descr.hpp \
              $(COMMON)/base-filter.hpp \
              $(COMMON)/modes.hpp
	g++ -Wall $(INCL_PATH) table-base.cpp -c -o table-base.o

table-data.o: table-data.cpp \
              table-data.hpp \
              table-descr.hpp \
              $(COMMON)/section-filter.hpp
	g++ -Wall $(INCL_PATH) table-data.cpp -c -o table-data.o

table-table.o: table-table.cpp \
               table-table.hpp \
               table-descr.hpp \
               $(COMMON)/section-filter.hpp \
               table-data.hpp
	g++ -Wall $(INCL_PATH) table-table.cpp -c -o table-table.o

table-descr.o: table-descr.cpp \
               table-descr.hpp
	g++ -Wall $(INCL_PATH) table-descr.cpp -c -o table-descr.o

clean:
	rm -f *~
	rm -f *.o
	rm -f $(NAME)
	make -C $(COMMON) clean
