hepsi: derle calistir

derle:
	g++ -I ./include/ -o ./bin/program ./src/main.cpp ./src/BSTlist.cpp ./src/queue.cpp ./src/queueControl.cpp

calistir:
	./bin/program

temizle:
	rm -f ./bin/program