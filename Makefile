simplestack: simplestack.cpp
	g++ -o simplestack simplestack.cpp

ball: ball.cpp
	g++ -o ball ball.cpp

point3d: point2d.cpp
	g++ -o point2d point2d.cpp

pointvectormain: pointvectormain.cpp point3d.cpp point3d.h vector3d.cpp vector3d.h
	g++ -o pointvectormain pointvectormain.cpp point3d.cpp point3d.h vector3d.cpp vector3d.h

rgba: rgba.cpp
	g++ -o rgba rgba.cpp

monstergen: monstergen.cpp
	g++ -o monstergen monstergen.cpp

blackjack: blackjack.cpp
	g++ -o blackjack blackjack.cpp
