hepsi: derle bagla calistir

derle:
	g++ -c -I "./include" ./src/main.cpp -o ./lib/main.o
	g++ -c -I "./include" ./src/BSTlist.cpp -o ./lib/BSTlist.o
	g++ -c -I "./include" ./src/queue.cpp -o ./lib/queue.o
	g++ -c -I "./include" ./src/queueControl.cpp -o ./lib/queueControl.o

bagla:
	g++ ./lib/main.o ./lib/BSTlist.o ./lib/queue.o ./lib/queueControl.o -o ./bin/program

calistir:
	./bin/program
temizle:
	del "./bin/program.exe" "./lib/*.o" 
	# Linux/Mac kullaniyorsaniz del yerine rm -f kullanin