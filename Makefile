SRCDIR = src
OBJDIR = obj
DEPDIR = dep

SRCFILES = $(wildcard $(SRCDIR)/*.cpp)
OBJFILES = $(subst $(SRCDIR)/,$(OBJDIR)/,$(SRCFILES:.cpp=.o))

CFLAGS = -fconcepts -std=c++2a -g -Wall -pedantic

Papo.out: $(OBJFILES)
	mkdir -p $(DEPDIR)
	$(CXX) -o $@ $^ $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.p
	mkdir -p $(OBJDIR)
	$(CXX) -c -o $@ $^ $(CFLAGS)

.PHONY: clean
clean:
	rm -f $(OBJFILES) Papo