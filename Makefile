all:
	g++ -g -w -std=c++11 main.cpp DynamicExperimentalMeasurement.h IDataInitializer.h IExperimentalMeasurement.h IDataStorage.h IntegerTable.h Experimentor.h SequentialColumnPusher.h ThreadedColumnPusher.h -pthread
clean:
	rm -r *.gch
one:
	g++ -g -w -std=c++11 main.cpp IDataInitializer.h
