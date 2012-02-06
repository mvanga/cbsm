SOURCES=main.o format_cbsm_header.o format_cbsm_line.o
CXXFLAGS+=-Wall -Wextra

all: andromeda

andromeda: $(SOURCES)
	g++ $(CXXFLAGS) $(SOURCES) $(LDFLAGS) -o andromeda

clean:
	rm -rf $(SOURCES) andromeda
