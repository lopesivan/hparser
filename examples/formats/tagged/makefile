 #============================================================================#
 #'hparser' examples.                                                         #
 #Copyright (C) 2006 Kevin P. Barry (ta0kira@users.sourceforge.net)           #
 #Licensed under the GPL.                                                     #
 #============================================================================#

NAME=tagged
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
         tagged-base.o \
         tagged-data.o \
         tagged-section.o
	make -C $(COMMON)
	g++ -Wall $(INCL_PATH) main.o $(COMMON)/data-display.o $(COMMON)/file-interface.o $(COMMON)/change-output.o $(COMMON)/base-filter.o $(COMMON)/section-filter.o tagged-base.o tagged-data.o tagged-section.o -o $(NAME) $(LIB_PATH) -lhpaux

main.o: $(COMMON)/main.cpp \
        $(COMMON)/file-interface.hpp \
        $(COMMON)/data-display.hpp \
	tagged-base.hpp
	g++ -Wall $(INCL_PATH) -DBASE_TYPE=TaggedBase -DBASE_TYPE_FILE=\"../tagged/tagged-base.hpp\" $(COMMON)/main.cpp -c -o main.o

tagged-base.o: tagged-base.cpp \
               tagged-base.hpp \
               $(COMMON)/base-filter.hpp \
               $(COMMON)/modes.hpp
	g++ -Wall $(INCL_PATH) tagged-base.cpp -c -o tagged-base.o

tagged-data.o: tagged-data.cpp \
               tagged-data.hpp
	g++ -Wall $(INCL_PATH) tagged-data.cpp -c -o tagged-data.o

tagged-section.o: tagged-section.cpp \
                  tagged-section.hpp \
                  $(COMMON)/section-filter.hpp \
                  tagged-data.hpp
	g++ -Wall $(INCL_PATH) tagged-section.cpp -c -o tagged-section.o

clean:
	rm -f *~
	rm -f *.o
	rm -f $(NAME)
	make -C $(COMMON) clean
