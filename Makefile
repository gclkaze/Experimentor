all:
	g++ -g -w -std=c++11 main.cpp IDataStorage.h IntegerTable.h Experimentor.h SequentialColumnPusher.h ThreadedColumnPusher.h -pthread
clean:
	rm -r *.gch
