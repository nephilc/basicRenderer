#
# Cross Platform Makefile
# Compatible with MSYS2/MINGW, Ubuntu 14.04.1 and Mac OS X
#
# You will need GLFW (http://www.glfw.org):
# Linux:
#   apt-get install libglfw-dev
# Mac OS X:
#   brew install glfw
# MSYS2:
#   pacman -S --noconfirm --needed mingw-w64-x86_64-toolchain mingw-w64-x86_64-glfw
#

#CXX = g++
#CXX = clang++

EXE = example_glfw_opengl3
SOURCES = main.cpp
SOURCES += ../imgui_impl_glfw.cpp ../imgui_impl_opengl3.cpp
SOURCES += ../../imgui.cpp ../../imgui_demo.cpp ../../imgui_draw.cpp ../../imgui_widgets.cpp
OBJS = $(addsuffix .o, $(basename $(notdir $(SOURCES))))#generating names
UNAME_S := $(shell uname -s)#simple var, expanded once 

CXXFLAGS = -I../ -I../../
CXXFLAGS += -g -Wall -Wformat
LIBS =

##---------------------------------------------------------------------
## OPENGL LOADER
##---------------------------------------------------------------------

## Using OpenGL loader: gl3w [default]
SOURCES += ../libs/gl3w/GL/gl3w.c
CXXFLAGS += -I../libs/gl3w -DIMGUI_IMPL_OPENGL_LOADER_GL3W

## Using OpenGL loader: glew
## (This assumes a system-wide installation)
 #CXXFLAGS += -DIMGUI_IMPL_OPENGL_LOADER_GLEW
 #LIBS += -lGLEW

## Using OpenGL loader: glad
 #SOURCES += ../libs/glad/src/glad.c
 #CXXFLAGS += -I../libs/glad/include -DIMGUI_IMPL_OPENGL_LOADER_GLAD

## Using OpenGL loader: glad2
# SOURCES += ../libs/glad/src/gl.c
# CXXFLAGS += -I../libs/glad/include -DIMGUI_IMPL_OPENGL_LOADER_GLAD2

## Using OpenGL loader: glbinding
## This assumes a system-wide installation
## of either version 3.0.0 (or newer)
# CXXFLAGS += -DIMGUI_IMPL_OPENGL_LOADER_GLBINDING3
# LIBS += -lglbinding
## or the older version 2.x
# CXXFLAGS += -DIMGUI_IMPL_OPENGL_LOADER_GLBINDING2
# LIBS += -lglbinding

##---------------------------------------------------------------------
## BUILD FLAGS PER PLATFORM
##---------------------------------------------------------------------

ifeq ($(UNAME_S), Linux) #LINUX
	ECHO_MESSAGE = "Linux"
	LIBS += -lGL `pkg-config --static --libs glfw3` -lm -lpthread

	CXXFLAGS += `pkg-config --cflags glfw3`
	CFLAGS = $(CXXFLAGS)
endif

ifeq ($(UNAME_S), Darwin) #APPLE
	ECHO_MESSAGE = "Mac OS X"
	LIBS += -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
	LIBS += -L/usr/local/lib -L/opt/local/lib
	#LIBS += -lglfw3
	LIBS += -lglfw

	CXXFLAGS += -I/usr/local/include -I/opt/local/include
	CFLAGS = $(CXXFLAGS)
endif

ifeq ($(findstring MINGW,$(UNAME_S)),MINGW)
	ECHO_MESSAGE = "MinGW"
	LIBS += -lglfw3 -lgdi32 -lopengl32 -limm32

	CXXFLAGS += `pkg-config --cflags glfw3`
	CFLAGS = $(CXXFLAGS)
endif

##---------------------------------------------------------------------
## BUILD RULES
##---------------------------------------------------------------------
#top down tree execution
#running a specific rule in the makefile
#making a target a prerequisite of another target
#dependency graphs
#time stamps for directories |types of prerequisites
#changing working directories in make file recipes
#canned recipes
#the uses of emty recipes
#the command line ovverides files argumments unless otherwise specified, references are expanded at substitution
#recursively expanded variables
#simple vars are expanded once and for all,at use,doesn't contain any reference to other variables
#there should be a make recipe cookbook
#variables used by implicit rules
#simple, recursive, conditional, automatic, used by implicit rules , special, command overriden variables
#the stem
#so some implicit rules run automatically
#so make just considers the rules, defined down here, and executes them for every instance of the prerequisites
#putting a file name in target
%.o:%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<
	@echo built object file $@
%.o:../%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<
	@echo built object file $@
%.o:../../%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<
	@echo built object file $@
%.o:../libs/gl3w/GL/%.c
	$(CC) $(CFLAGS) -c -o $@ $<
	@echo built object file $@
%.o:../libs/glad/src/%.c
	$(CC) $(CFLAGS) -c -o $@ $<
	@echo built object file $@
all: $(EXE)
	@echo Build complete for $(ECHO_MESSAGE)

#including the search directories in cxx flags is redundant in tis case
$(EXE): $(OBJS)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)

clean:
	rm -f $(EXE) $(OBJS)



