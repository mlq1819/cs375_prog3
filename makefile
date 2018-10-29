P=program3
R=Filereader
Q=item
A=Algorithms
CFLAGS= -g -Wall

all: $(P)

$(P): $(P).o $(R).o $(Q).o $(A).o
	g++ $(CFLAGS) $(P).o $(R).o $(Q).o $(A).o -o $(P)

$(P).o: $(P).cpp $(R).h $(A).h
	g++ $(CFLAGS) -c $(P).cpp -o $(P).o

$(R).o: $(R).cpp $(R).h
	g++ $(CFLAGS) -c $(R).cpp -o $(R).o

$(Q).o: $(Q).cpp $(Q).h
	g++ $(CFLAGS) -c $(Q).cpp -o $(Q).o
	
$(A).o: $(A).cpp $(A).h
	g++ $(CFLAGS) -c $(A).cpp -o $(A).o
	
clean:
	rm -rf $(P)
	rm -rf $(P).o
	rm -rf $(R).o
	rm -rf $(Q).o
	rm -rf $(A).o
	rm -rf output.txt