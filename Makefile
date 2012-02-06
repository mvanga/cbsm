SOURCES=main.o f_cbsf.o f_cbsf_header.o f_cbsf_line.o
CXXFLAGS+=-Wall -Wextra

all: andromeda

andromeda: $(SOURCES)
	g++ $(CXXFLAGS) $(SOURCES) $(LDFLAGS) -o andromeda

clean:
	rm -rf $(SOURCES) andromeda
