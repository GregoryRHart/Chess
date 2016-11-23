################################################################################
# CS 240 Chess Project Makefile
#
# INSTRUCTIONS: This is a starting makefile for the chess project. You are to 
# keep this up-to-date as you add source files. In addition to keeping it 
# up-to-date with new files you create, you need to make the following changes 
# to this makefile:
# 
#	- compile the object files associated with the View into a shared library, 
#	- add pseudo-targets for the different run modes (namely "runhh", "runhc",
#		"runch", and "runcc"),
#	- add a "test" pseudo-target (you will probably want to make a new executable
#		for this with its own main method),
#	- add a "lib" pseudo-target,
#	- edit the command associated with the memcheck pseudo-target (i.e.,
#		the valgrind command. See the note above it for details).
# 
# NOTES: 
# 1. All the code for the GUI side of this project is provided for you. As a 
# result, there are some things in this makefile which you do not need to alter.
# Such items will be clearly marked with comments.
# 2. Out-of-the-box, without making any changes to this initial makefile, 
# running "make run" will compile the code and bring up an empty GUI. 
################################################################################

 
############### --- BEGIN UNTOUCHABLE SECTION - Do Not Edit --- ################
# Macros for GUI libraries.
GTKMM = gtkmm-2.4
SIGC = sigc++-2.0
LIBGLADE = libglademm-2.4

# TODO Re-phrase: CFLAGS are the -I values needed to compile files using the 
# GTKMM, SIGC, and LIBGLADE libraries
CFLAGS = `pkg-config $(GTKMM) $(SIGC) $(LIBGLADE) --cflags`
# TODO Re-phrase: LIBS are the paths to the static libraries for GTKMM, SIGC,
# and LIBGLADE needed for linking
LIBS   = `pkg-config $(GTKMM) $(SIGC) $(LIBGLADE) --libs`
####################### --- END UNTOUCHABLE SECTION --- ########################


# TODO Re-phrase: Macros for directory tree locations
MODEL_SRC = model/src/
MODEL_INC = model/inc/
MODEL_OBJ = model/obj/
VIEW_SRC = view/src/
VIEW_INC = view/inc/
VIEW_OBJ = view/obj/
CONT_SRC = controller/src/
CONT_INC = controller/inc/
CONT_OBJ = controller/obj/
EXE = bin/chess			# normal executable
MEXE = bin/mchess			# executable for memory testing
TEXE = bin/test
CPPS      = $(wildcard $(MODEL_SRC)*.cpp)
LIBCPPS   = $(wildcard utils/src/*.cpp)
SOURCE    = $(foreach source,$(CPPS),$(notdir $(basename $(source))))
LIBSOURCE = $(foreach source,$(LIBCPPS),$(notdir $(basename $(source))))
OS        = $(foreach source,$(SOURCE),$(MODEL_OBJ)$(source).o)
LIBOS     = $(foreach source,$(LIBSOURCE),utils/obj/$(source).o)
LIB       = utils/libcs240utils.a
SLIB 	  = utils/libchessgui.so

# Macros for compilation flags
INCLUDES = -I$(MODEL_INC) -I$(VIEW_INC) -I$(CONT_INC) -Iutils/inc/
DEBUG = -Wall -g # Uncomment this if you want to compile with debug info

# Uncomment the flag on this next line to turn off the logging messages from the
# GUI
LOG_FLAG = #'-DLOG_LEVEL_HIDE_MASK=(G_LOG_LEVEL_DEBUG|G_LOG_LEVEL_INFO)'


# There are two different main.o files. One is for memory testing.
MAIN_O = $(CONT_OBJ)main.o
MEMMAIN_O = $(CONT_OBJ)memcheck_main.o
TEST_O = test.o

# This macro should be used to store all of the object files created 
# from *your* source files
MY_OBJS =  $(OS) $(CONT_SRC)chessController.cpp $(CONT_SRC)chessPlayerh.cpp $(CONT_SRC)chessPlayerc.cpp

# These are all the object files that go into the library
LIB_OBJS = $(VIEW_OBJ)ChessView.o \
      $(VIEW_OBJ)ChessGuiBoardCell.o \
      $(VIEW_OBJ)ChessGuiBoard.o \
      $(VIEW_OBJ)ChessGui.o \
      $(VIEW_OBJ)ChessGuiImages.o \
      $(VIEW_OBJ)SelectDialog.o





################################################################################
# Pseudo-targets

bin: $(EXE)

runhh: $(EXE)
	export LD_LIBRARY_PATH=/users/guest/g/goryh/CS240/chessprog; $(EXE) 1 &

runhc: $(EXE)
	export LD_LIBRARY_PATH=/users/guest/g/goryh/CS240/chessprog; $(EXE) 2 &

runch: $(EXE)
	export LD_LIBRARY_PATH=/users/guest/g/goryh/CS240/chessprog; $(EXE) 3 &

runcc: $(EXE)
	export LD_LIBRARY_PATH=/users/guest/g/goryh/CS240/chessprog; $(EXE) 4 &

test: $(TEXE)
	./$(TEXE)

$(TEXE): test.o $(MY_OBJS) $(LIB)
	g++ $(INCLUDES) -o $(TEXE) $(TEST_O) $(MY_OBJS) $(CFLAGS) $(LIB) $(LIBS) $(SLIB)

test.o: test.cpp
	g++ -c $(INCLUDES) -o test.o test.cpp
	

# Run the executable for memory testing
# Instructions: Edit the command below so that it runs the  
# memory-check executable in Human-Human mode (i.e., add necessary command  
# line arguments to the end of valgrind the command below).	
memcheck: $(MEXE)
	valgrind --tool=memcheck --leak-check=yes --max-stackframe=5000000 --show-reachable=yes --suppressions=string.supp $(MEXE) 1 

# Clean removes all of the .o files, libraries, and executables
clean:
	@rm -f $(MODEL_OBJ)*.o
	@rm -f $(VIEW_OBJ)*.o
	@rm -f $(CONT_OBJ)*.o
	@rm -f utils/obj/*.o
	@rm -f $(EXE)
	@rm -f $(MEXE)
	@rm -f $(TEXE)
	@rm -f $(LIB)
	@rm -f $(SLIB)
	@rm -f test.o


################################################################################
# Targets for executables and main object files

# Explanation: There are two different executables, with two different main 
# object files, because main.cpp needs to be built differently depending on 
# whether you are doing memory testing or not. This is because the GTK library,
# and other GUI tools, have memory leaks that we cannot figure out how to 
# suppress. Therefore, when building an executable for memory testing, we use a
# macro (MEMCHECK) to tell the compiler to not include the code that builds the
# GUI. So when we check for memory leaks during passoff, we don't have to use
# the GUI.

# Main executable
# Note: Once you have added the ability to make a library out of the View files, 
# the executable should be dependent on, and link in the library file, not the 
# .o files! That means, instead of linking in $(LIB_OBJS) below, you should link
# in the actual library file.
$(EXE): $(MAIN_O) $(MY_OBJS) $(LIB_OBJS) $(LIB)
	@# Re-link executable. Again, this should link the library file, not the .o's
	g++ $(INCLUDES) -o $(EXE) $(MAIN_O) $(MY_OBJS) $(CFLAGS) $(LIB) $(LIBS) $(SLIB)
	chmod ugo+x $(EXE)

# Executable for memory testing
$(MEXE): $(MEMMAIN_O) $(MY_OBJS) $(LIB_OBJS) $(LIB)
	@# Re-link executable. Again, this should link the library file, not the .o's
	g++ $(INCLUDES) -o $(MEXE) $(MEMMAIN_O) $(MY_OBJS) $(CFLAGS) $(LIB) $(LIBS) $(SLIB)
	chmod ugo+x $(MEXE)
	

# Main object file
$(MAIN_O): $(CONT_SRC)main.cpp $(VIEW_INC)ChessGuiImages.h $(VIEW_INC)ChessView.h
	g++ $(DEBUG) $(INCLUDES) $(CFLAGS) $(LIBS) -o $(MAIN_O) -c $(LOG_FLAG) $(CONT_SRC)main.cpp

# Main .o for memory testing
$(MEMMAIN_O): $(CONT_SRC)main.cpp $(VIEW_INC)ChessGuiImages.h $(VIEW_INC)ChessView.h
	g++ -DMEMCHECK $(DEBUG) $(INCLUDES) $(CFLAGS) $(LIBS) -o $(MEMMAIN_O) -c $(LOG_FLAG) $(CONT_SRC)main.cpp



################################################################################
# Targets for YOUR object files...

lib: $(LIB_OBJS) 
	g++ -shared -o $(SLIB) $(VIEW_OBJ)*.o

$(LIB): $(LIBOS)
	ar r $@ $^

depends : 
	@ rm -f depends.mk
	@ for f in $(SOURCE); do g++ $(DEBUG) $(INCLUDES) -MM $(MODEL_SRC)$$f.cpp -MT $(MODEL_OBJ)$$f.o >> depends.mk; done
	@ g++ $(DEBUG) $(INCLUDES) -MM $(CONT_SRC)chessController.cpp -MT $(CONT_OBJ)chessController.o >> depends.mk
	@ g++ $(DEBUG) $(INCLUDES) -MM $(CONT_SRC)chessPlayerh.cpp -MT $(CONT_OBJ)chessPlayerh.o >> depends.mk
	@ g++ $(DEBUG) $(INCLUDES) -MM $(CONT_SRC)chessPlayerc.cpp -MT $(CONT_OBJ)chessPlayerc.o >> depends.mk
	@ rm -f libdepends.mk
	@ for f in $(LIBSOURCE); do g++ $(DEBUG) $(INCLUDES) -MM utils/src/$$f.cpp -MT utils/obj/$$f.o >> libdepends.mk; done

$(MODEL_OBJ)%.o : $(MODEL_SRC)%.cpp $(LIB)
	g++ $(DEBUG) -c $(INCLUDES) -o $@ $< $(LIB)

$(CONT_OBJ)%.o : $(CONT_SRC)%.cpp lib
	g++ $(DEBUG) -c $(INCLUDES) -o $@ $< $(CFLAGS) $(LIBS) $(SLIB)

utils/obj/%.o : utils/src/%.cpp
	g++ $(DEBUG) -c $(INCLUDES) -o $@ $< 

target :
	@ for f in $(LIBCPPS); do echo $$f; done
	@ for f in $(LIBOS); do echo $$f; done

include depends.mk
include libdepends.mk


################################################################################
# Targets for GUI-related object files
# Instructions: These will have to be recompiled as position-independent code, 
# so that they can be put into a shared library.

$(VIEW_OBJ)ChessView.o: $(VIEW_SRC)ChessView.cpp $(VIEW_INC)SelectDialog.h $(VIEW_INC)ChessView.h $(CONT_INC)IChessController.h
	g++ -fPIC $(DEBUG) $(INCLUDES) $(CFLAGS) $(LIBS) -o $(VIEW_OBJ)ChessView.o -c $(LOG_FLAG) $(VIEW_SRC)ChessView.cpp

$(VIEW_OBJ)ChessGuiBoardCell.o: $(VIEW_SRC)ChessGuiBoardCell.cpp $(VIEW_INC)ChessGuiBoardCell.h $(VIEW_INC)ChessGuiImages.h
	g++ -fPIC $(DEBUG) $(INCLUDES) $(CFLAGS) $(LIBS) -o $(VIEW_OBJ)ChessGuiBoardCell.o -c $(VIEW_SRC)ChessGuiBoardCell.cpp

$(VIEW_OBJ)ChessGuiBoard.o: $(VIEW_SRC)ChessGuiBoard.cpp $(VIEW_INC)ChessGuiBoard.h $(VIEW_INC)ChessGui.h $(VIEW_INC)ChessGuiImages.h
	g++ -fPIC $(DEBUG) $(INCLUDES) $(CFLAGS) $(LIBS) -o $(VIEW_OBJ)ChessGuiBoard.o -c $(VIEW_SRC)ChessGuiBoard.cpp

$(VIEW_OBJ)ChessGui.o: $(VIEW_SRC)ChessGui.cpp $(VIEW_INC)ChessGui.h $(VIEW_INC)ChessGuiImages.h $(VIEW_INC)SelectDialog.h
	g++ -fPIC $(DEBUG) $(INCLUDES) $(CFLAGS) $(LIBS) -o $(VIEW_OBJ)ChessGui.o -c $(VIEW_SRC)ChessGui.cpp

$(VIEW_OBJ)ChessGuiImages.o: $(VIEW_SRC)ChessGuiImages.cpp $(VIEW_INC)ChessGuiImages.h $(VIEW_INC)Inline.h
	g++ -fPIC $(DEBUG) $(INCLUDES) $(CFLAGS) $(LIBS) -o $(VIEW_OBJ)ChessGuiImages.o -c $(VIEW_SRC)ChessGuiImages.cpp

$(VIEW_OBJ)SelectDialog.o: $(VIEW_SRC)SelectDialog.cpp
	g++ -fPIC $(DEBUG) $(INCLUDES) $(CFLAGS) $(LIBS) -o $(VIEW_OBJ)SelectDialog.o -c $(VIEW_SRC)SelectDialog.cpp

