###########
# Options #
###########

# Compiler
CXX = g++
CXXFLAGS = -g -Wno-write-strings

# Linker
LD = g++
LDFLAGS = -g

# Bison
YACC = bison
YFLAGS = -d

# Flex
LEX = flex
LFLAGS = -+

# Makedepend
DEP = makedepend
DEPFLAGS = -m -Y

# Date
DATE = `date +%h%d_%H.%M.%S`

# For tarball creation
TARNAME = cclc_$(DATE).tar

# Location of the dropbox folder
DROPBOX = ~/Dropbox/CCL

# List of object files for linking
OBJS =  Source/main.o \
		Source/bison/parser.o \
		Source/flex/flexScanner.o \
		Source/error/error.o \
		Source/strconv/strconv.o \
		Source/scanner/scanner.o \
		Source/symbolTable/symbolTable.o \
		Source/symbolTable/symbolTableDeclaration.o \
		Source/programTree/programTree.o \
		Source/programTree/abstractProgramTreeVisitors.o \
		Source/programTree/programTreeVisitors.o \
		Source/typeTree/typeTree.o \
		Source/typeTree/abstractTypeTreeVisitors.o \
		Source/typeTree/typeTreeVisitors.o \
		Source/options/options.o \
		Source/codeGenerator/codeGenerator.o \
		Source/programTree/syntaxTree.o \
		Source/stringFormat/stringFormat.o \
		Source/commandParser/commandParser.o

# List of Source Files for the dependency generator
SRCS =  Source/codeGenerator/codeGenerator.h \
		Source/codeGenerator/codeGenerator.cpp \
		Source/options/options.h \
		Source/options/options.cpp \
		Source/scanner/scanner.h \
		Source/scanner/scanner.cpp \
		Source/programTree/abstractProgramTreeVisitors.h \
		Source/programTree/abstractProgramTreeVisitors.cpp \
		Source/programTree/syntaxTree.h \
		Source/programTree/programTree.h \
		Source/programTree/programTreeForwards.h \
		Source/programTree/programTree.cpp \
		Source/programTree/programTreeVisitorsForwards.h \
		Source/programTree/programTreeVisitors.cpp \
		Source/programTree/programTreeVisitors.h \
		Source/programTree/syntaxTree.cpp \
		Source/strconv/strconv.cpp \
		Source/strconv/strconv.h \
		Source/typeTree/typeTree.h \
		Source/typeTree/typeTreeForwards.h \
		Source/typeTree/abstractTypeTreeVisitors.h \
		Source/typeTree/typeTreeVisitors.cpp \
		Source/typeTree/typeTree.cpp \
		Source/typeTree/typeTreeVisitorsForwards.h \
		Source/typeTree/abstractTypeTreeVisitors.cpp \
		Source/typeTree/typeTreeVisitors.h \
		Source/main.cpp \
		Source/symbolTable/symbolTableDeclaration.h \
		Source/symbolTable/symbolTableDeclaration.cpp \
		Source/symbolTable/symbolTable.h \
		Source/symbolTable/symbolTable.cpp \
		Source/error/error.h \
		Source/error/error.cpp \
		Source/stringFormat/stringFormat.h \
		Source/stringFormat/stringFormat.cpp \
		Source/commandParser/commandParser.h \
		Source/commandParser/commandParser.cpp \
		Source/codeGenerator/vecFunc.h

# List of all source files
# Mainly so that I can do linecounts and searches easily
ALL =  $(SRCS) Makefile.real Makefile.inc Makefile Source/bison/parser.yy Source/flex/flexScanner.ll

# makedepend can't handle flex or bison files,
# so we need to explictly say how to build these

# bison the parser file
Source/bison/parser.hpp Source/bison/parser.cpp: Source/bison/parser.yy
	$(YACC) $(YFLAGS) -o Source/bison/parser.cpp Source/bison/parser.yy
	bisonfix Source/bison/parser.cpp Source/bison/parser.hpp

# Empty rule for the actual parser source file
Source/bison/parser.yy:

# compile the parser object file
Source/bison/parser.o: Source/bison/parser.hpp Source/bison/parser.cpp

# flex the scanner file
Source/flex/flexScanner.cpp:
	$(LEX) $(LFLAGS) -o Source/flex/flexScanner.cpp Source/flex/flexScanner.ll

# empty rule for the actual scanner source file
Source/flex/flexScanner.ll:

# compile the scanner object file
Source/flex/flexScanner.o: Source/flex/flexScanner.cpp
