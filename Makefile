blackjack: blackjack.cpp blackjack.h deck.cpp deck.h card.cpp card.h player.cpp player.h hand.cpp hand.h
	g++ -o blackjack blackjack.h blackjack.cpp deck.cpp deck.h card.cpp card.h player.cpp player.h hand.cpp hand.h

clean: blackjack
	rm -f blackjack

