CC = g++
CFLAGS  = -g -Wall

main: ConfigFile.o Engine.o shooting.o matching.o potentials.o variationalMC.o main.o
	$(CC) $(CFLAGS) -o main ConfigFile.o shooting.o matching.o Engine.o potentials.o variationalMC.o main.o

main.o: main.cpp shooting.hpp matching.hpp Engine.hpp potentials.hpp ConfigFile.h
	$(CC) $(CFLAGS) -c main.cpp

shooting.o : shooting.cpp shooting.hpp Engine.hpp potentials.hpp ConfigFile.h
	$(CC) $(CFLAGS) -c shooting.cpp

matching.o : matching.cpp matching.hpp Engine.hpp ConfigFile.h
	$(CC) $(CFLAGS) -c matching.cpp

variationalMC.o: variationalMC.cpp variationalMC.hpp Engine.hpp ConfigFile.h
	$(CC) $(CFLAGS) -c variationalMC.cpp

Engine.o: Engine.cpp Engine.hpp ConfigFile.h
	$(CC) $(CFLAGS) -c Engine.cpp

ConfigFile.o: ConfigFile.cpp ConfigFile.h
	$(CC) $(CFLAGS) -c ConfigFile.cpp

potentials.o: potentials.cpp potentials.hpp
	$(CC) $(CFLAGS) -c potentials.cpp

clean:
	$(RM) main *.o *~
	$(RM) *.out
