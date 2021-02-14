// Copyright 2018 Ronney Sanchez
#ifndef PTree_INCLUDED
#define PTree_INCLUDED
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <cmath>

class PTree : public sf::Drawable {
 private:
        sf::Vector2f bottomLeft;
        sf::Vector2f bottomRight;
        sf::Vector2f topLeft;
        sf::Vector2f topRight;

        int initialDepth;

        PTree* child1;
        PTree* child2;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

 public:
        PTree(int length, int depth);
        PTree(sf::Vector2f bLeft, sf::Vector2f bRight, int length, int depth);
        ~PTree();
};

#endif
