SOURCES = $(wildcard *.cpp)
EXES = $(basename $(SOURCES))

.PHONY : all
all : $(EXES)
	
CFLAGS := -g
CC := g++
$(EXES) : % : %.cpp
	$(CC) $(CFLAGS) $< -o $@
	

.PHONY : clean
clean :
	@rm -f $(EXES)
