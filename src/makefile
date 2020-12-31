
CXX = g++
CC = gcc
EXE = ../bin/glproj
LIBS =  -lassimp -lglfw3   -lX11 -lGL -lXrandr -ldl  -lXi -lpthread
SOURCES = $(wildcard *.cpp)
SOURCES += $(wildcard ./libs/*.c)
SOURCES += $(wildcard ./libs/*.cpp)
OBJS =   $(addsuffix .o, $(basename $(notdir $(SOURCES))))#generating names 
CXXFLAGS = -I ./libs -I ./render -I ./layout \ #this for the prepoc, resolving the includes of the local headers, used by each module.	
	-std=c++17 -lstdc++fs

CFLAGS = $(CXXFLAGS)

#should use search directories, vpath, instead of using relative paths in dependencies.
%.o : libs/%.c
	$(CC) $(CFLAGS) $(LIBS) -c $< -o $@ 
	@echo built object file $@

%.o : libs/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo built object file $@

	
%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo built object file $@

#all should be at the begining of the file, as the principal rule, depends on the principal target as it should.	
all : $(EXE) 
	@echo Build complete for $(EXE)
#all rule is executed after all rules, maybe inly if its prereqs change. 
 #if i do this it actually adds all the .o create file in the directory, dont think it would worlk with simple variables.
#when i did put it with the recipes it treated it as a command it didnt find, wich makes sense.
#have to do something about thos header only libs and header only classes

$(EXE):$(OBJS) 
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS) 


