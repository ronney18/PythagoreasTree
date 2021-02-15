// Copyright 2018 Ronney Sanchez
#include "PTree.hpp"

PTree::PTree(int length, int depth)
    : initialDepth(depth) {
    int newDepth = initialDepth - 1;

    bottomLeft.x = length/3.0;
    bottomLeft.y = length;

    bottomRight.x = (length/3.0) + (length/3.0);
    bottomRight.y = length;

    sf::Vector2f delta;
    sf::Vector2f nextPtr;

    delta.x = bottomRight.x - bottomLeft.x;
    delta.y = bottomLeft.y - bottomRight.y;

    topRight.x = bottomRight.x - delta.y;
    topRight.y = bottomRight.y - delta.x;

    topLeft.x = bottomLeft.x - delta.y;
    topLeft.y = bottomLeft.y - delta.x;

    nextPtr.x = topLeft.x + (delta.x - delta.y)/2.0;
    nextPtr.y = topLeft.y - (delta.x + delta.y)/2.0;

    if (newDepth == 0) {
        child1 = NULL;
        child2 = NULL;
    } else {
        child1 = new PTree(topLeft, nextPtr, length/2.0, newDepth);
        child2 = new PTree(nextPtr, topRight, length/2.0, newDepth);
    }
}
PTree::PTree(sf::Vector2f bLeft, sf::Vector2f bRight, int length, int depth)
    : initialDepth(depth) {
    int newDepth = initialDepth - 1;

    sf::Vector2f delta;
    sf::Vector2f nextPtr;

    bottomLeft = bLeft;
    bottomRight = bRight;

    delta.x = bRight.x - bLeft.x;
    delta.y = bLeft.y - bRight.y;

    topRight.x = bRight.x - delta.y;
    topRight.y = bRight.y - delta.x;

    topLeft.x = bLeft.x - delta.y;
    topLeft.y = bLeft.y - delta.x;

    nextPtr.x = topLeft.x + (delta.x - delta.y)/2.0;
    nextPtr.y = topLeft.y - (delta.x + delta.y)/2.0;

    if (newDepth == 0) {
        child1 = NULL;
        child2 = NULL;
    } else {
        child1 = new PTree(topLeft, nextPtr, length/2.0, newDepth);
        child2 = new PTree(nextPtr, topRight, length/2.0, newDepth);
    }
}

PTree::~PTree() {
    if (child1 != NULL) {
        delete (child1);
        delete (child2);
    }
}

void PTree::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    sf::ConvexShape square;
    square.setPointCount(4);

    square.setPoint(0, topLeft);
    square.setPoint(1, topRight);
    square.setPoint(2, bottomRight);
    square.setPoint(3, bottomLeft);

    sf::Color myColor = sf::Color(255 - bottomLeft.y, 1 + topRight.y, 50 + bottomRight.y);
    square.setOutlineColor(sf::Color::Blue);
    square.setFillColor(myColor);
    square.setOutlineThickness(0.8);
    square.move(400, 200);

    target.draw(square);

    if (child1 != NULL) {
        child1->draw(target, states);
        child2->draw(target, states);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cout << "Pythagoras Tree [side-length][recursion-depth]" <<
            std::endl;
        return -1;
    }

    else {
    	int side = atoi(argv[1]);
    	int depth = atoi(argv[2]);
	if(depth > 12) {
		std::cout << "The depth is too high! Not enough buffer for higher depth!" << std::endl;
		std::cout << "It must be 12 maximum!" << std::endl;
		return -2;
	}

    	sf::RenderWindow window(sf::VideoMode(6*side, 4*side), "Pythagoras Tree");

    	PTree tree(side, depth);

    	while (window.isOpen()) {
        	sf::Event event;

        	while (window.pollEvent(event)) {
            		if (event.type == sf::Event::Closed) {
                		window.close();
            		}
        	}
        	window.clear();
        	window.draw(tree);
        	window.display();
	}
    }
    return 0;
}
