#Compiler and Linker
CXX	= g++
LD	= g++

#The Directories, Source, Includes, Objects, Binary and Resources
BUILDDIR	= build
TARGETDIR 	= bin
SRCEXT		= cpp
OBJEXT		= o

#Flags, Libraries and Includes
INCLIST = $(shell find -name include -type d)
INCLIST += ./libs/libevent-2.1.8/include
INCLIST += ./libs//snmp++-3.3.11/include/snmp_pp
INC		= $(addprefix -I, $(INCLIST))
LIBS	= -levent -lsnmp++
#LIBS	= -lsnmp++
#LIBDIR	= ./libs/libevent-2.1.8/.libs 
LIBDIR	+= ./libs/snmp++-3.3.11/src/.libs
#The Target Binary Program
TARGET 	 = EPP
CXXFLAGS = -std=c++14  -Wall -Wextra -Wshadow -Werror -Wl,-z,relro,-z,now -g
CXXFLAGS+= -fstack-protector-strong -pedantic-errors
LDFLAGS	 = $(addprefix -L, $(INCLIST))
LDFLAGS	+= -Wl,-rpath,$(LIBDIR) 

#---------------------------------------------------------------------------------
#DO NOT EDIT BELOW THIS LINE
#---------------------------------------------------------------------------------

#List of all sources and objects
#SOURCES = $(shell find -name *.cpp)
SOURCES = $(shell find -path ./libs -prune -o -type f -name '*.cpp' -print)
OBJECTS = $(addprefix $(BUILDDIR)/,$(patsubst %.cpp,%.o, $(notdir $(SOURCES))))
VPATH 	= $(dir $(SOURCES))

#Default Make
all: directories $(TARGET)

#Remake
remake: clean all

#Create directories
directories:
	@mkdir -p $(BUILDDIR)
	@mkdir -p $(TARGETDIR)

#Linking
$(TARGET): $(OBJECTS)
	$(LD) $(LDFLAGS) $(OBJECTS) -o $(TARGETDIR)/$(TARGET) $(LIBS)

#Compiling
$(BUILDDIR)/%.o : %.cpp
	$(CXX) $(INC) $(CXXFLAGS) -c $< -o $@

#Clean all
clean:
	rm -rf $(BUILDDIR)
	rm -rf $(TARGETDIR)

#TO-DO: Create Test rule:

#Non-File Targets
.PHONY: all remake clean directories
