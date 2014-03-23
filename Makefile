FLEX_FILE = flex/lex.l
FLEX = $(FLEX_FILE:.l=.c)
PROJECT_SOURCES = $(wildcard src/*.cpp)
FLEX_SOURCES = $(wildcard flex/*.cpp)
FLEX_C_SOURCES = $(wildcard flex/*.c)

PROJECT_OBJECTS = $(PROJECT_SOURCES:.cpp=.o)
FLEX_OBJECTS = $(FLEX_SOURCES:.cpp=.o)
FLEX_OBJECTS +=  $(FLEX_C_SOURCES:.c=.o)
PROJECT_EXECUTABLE = lexicalanalyzer	
FLEX_EXECUTABLE = flexanalyzer

program_INCLUDE_DIRS :=
program_LIBRARY_DIRS :=
program_LIBRARIES :=

CC = g++ 
CPPFLAGS += -std=c++0x -w
CPPFLAGS += $(foreach includedir,$(program_INCLUDE_DIRS),-I$(includedir))
LDFLAGS += $(foreach librarydir,$(program_LIBRARY_DIRS),-L$(librarydir))
LDFLAGS += $(foreach library,$(program_LIBRARIES),-l$(library))

.PHONY: all clean distclean lexical_analyzer flex_analyzer

all: lexical_analyzer flex_analyzer

lexical_analyzer: $(PROJECT_EXECUTABLE)

flex_analyzer: $(FLEX_EXECUTABLE)

$(PROJECT_EXECUTABLE): $(PROJECT_OBJECTS)
	$(CC) $(PROJECT_OBJECTS) -o $(PROJECT_EXECUTABLE)

$(FLEX_EXECUTABLE):$(FLEX) $(FLEX_OBJECTS) 	
	$(CC) $(FLEX_OBJECTS) -o $(FLEX_EXECUTABLE)

clean:
	@- $(RM) $(PROJECT_EXECUTABLE) $(FLEX_EXECUTABLE)
	@- $(RM) $(PROJECT_OBJECTS) $(FLEX_OBJECTS)

distclean: clean