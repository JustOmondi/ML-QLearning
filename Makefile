CC=g++
CCFLAGS=-std=c++11 -w

all: qlearning

qlearning: main.o C2DMatrix.o CCollisionObject.o CContCollisionObject.o CContController.o CContMinesweeper.o CController.o CDiscCollisionObject.o CDiscController.o CDiscMinesweeper.o CMinesweeper.o CNeuralNet.o CParams.o CQLearningController.o CTimer.o utils.o
	$(CC) $(CCFLAGS) main.o C2DMatrix.o CCollisionObject.o CContCollisionObject.o CContController.o CContMinesweeper.o CController.o CDiscCollisionObject.o CDiscController.o CDiscMinesweeper.o CMinesweeper.o CNeuralNet.o CParams.o CQLearningController.o CTimer.o utils.o -o qlearning
	
C2DMatrix.o: C2DMatrix.cpp
	$(CC) $(CCFLAGS) C2DMatrix.cpp -c
	
CCollisionObject.o: CCollisionObject.cpp
	$(CC) $(CCFLAGS) CCollisionObject.cpp -c
		
CContCollisionObject.o: CContCollisionObject.cpp
	$(CC) $(CCFLAGS) CContCollisionObject.cpp -c
	
CContController.o: CContController.cpp
	$(CC) $(CCFLAGS) CContController.cpp -c

CContMinesweeper.o: CContMinesweeper.cpp
	$(CC) $(CCFLAGS) CContMinesweeper.cpp -c

CController.o: CController.cpp
	$(CC) $(CCFLAGS) CController.cpp -c

CDiscCollisionObject.o: CDiscCollisionObject.cpp
	$(CC) $(CCFLAGS) CDiscCollisionObject.cpp -c
	
CDiscController.o: CDiscController.cpp
	$(CC) $(CCFLAGS) CDiscController.cpp -c

CDiscMinesweeper.o: CDiscMinesweeper.cpp
	$(CC) $(CCFLAGS) CDiscMinesweeper.cpp -c
	
CMinesweeper.o: CMinesweeper.cpp
	$(CC) $(CCFLAGS) CMinesweeper.cpp -c
	
CNeuralNet.o: CNeuralNet.cpp
	$(CC) $(CCFLAGS) CNeuralNet.cpp -c
	
CParams.o: CParams.cpp
	$(CC) $(CCFLAGS) CParams.cpp -c
	
CQLearningController.o: CQLearningController.cpp
	$(CC) $(CCFLAGS) CQLearningController.cpp -c

CTimer.o: CTimer.cpp
	$(CC) $(CCFLAGS) CTimer.cpp -c
	
main.o: main.cpp
	$(CC) $(CCFLAGS) main.cpp -c
	
utils.o: utils.cpp
	$(CC) $(CCFLAGS) utils.cpp -c

clean:
	rm -rf *.o
	
run:
	qlearning.exe