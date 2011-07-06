# These are phony targets since they don't actually create files with those names
.PHONY : cclc clean realclean squeakyclean deleteBackups todo linecount depend dropbox tarball

cclc: Makefile.dep
	make --no-print-directory -f Makefile.real cclc

include Makefile.inc

# Cleans up the source directory's object files
# And files that were created automatically by flex and bison
clean:
	rm -f	$(OBJS)
	rm -f	Source/bison/parser.cpp \
		Source/bison/parser.hpp \
		Source/flex/flexScanner.cpp

# Cleans up everything that was created at compile time
# Including the automatically created dependencies
realclean: clean
	rm -f 	cclc \
		Makefile.dep

# Delete backup files (created automatically by my text editor)
deleteBackups:
	rm -f `find . | grep ".*~"`

# Deletes everthing realclean does, as well as backup files
squeakyclean: realclean deleteBackups

# Searches all the files for the "TO_DO" tag
# (added an underscore to prevent it from finding that)
todo:
	grep "TODO" $(ALL)

# Performs a line count of all the files i've written
linecount:
	wc -l $(ALL)

# Creates a tarball of all the files
tarball: clean deleteBackups
	tar cvf $(TARNAME) bisonfix Makefile* Source/

# Moves the files to my dropbox folder
dropbox: cclc clean deleteBackups
	# Make sure the directory exists and is cleaned out
	if [ ! -d $(DROPBOX) ] ; then mkdir $(DROPBOX) ; \
	else rm -rf $(DROPBOX)/* ; fi
	# Copy the files to the folder
	cp -r cclc Makefile Makefile.inc Makefile.real Source/ $(DROPBOX)
	# Create a tarball for easy download
	tar cvf cclc.tar Makefile Makefile.inc Makefile.real Source/
	mv cclc.tar $(DROPBOX)

# Make the dependency file
# We need to have build flex and bison already, since we use those cpp files to
# build our dependencies.
Makefile.dep: $(SRCS) Source/bison/parser.hpp
	if [ ! -e Makefile.dep ] ; then touch Makefile.dep ; fi
	$(DEP) $(DEPFLAGS) -fMakefile.dep -- $(CXXFLAGS) -- $(SRCS) 2> /dev/null
	rm -f Makefile.dep.bak

# for convenience
depend: Makefile.dep
