#ifndef _Movie_NODE_HPP
#define _Movie_NODE_HPP

#include<iostream>

#include "Movie.hpp"


class MovieNode
{
private:
	Movie* _film; //pointer to the film in the node
	MovieNode* _next; //pointer to the next node
public:
	//constructor inizializate the _next and the _film
	MovieNode(Movie peli) : _next(NULL) {_film = new Movie(); *_film = peli;}
	
	//Modifier and accesor method of the value
	Movie* value() const {return _film;}
	Movie* & value() {return _film;}
	
	//modifier and accesor for the next 
	MovieNode* next() const {return _next;}
	MovieNode* & next(){return _next;}
	
	//overloading of << operator
	friend std::ostream& operator<<(std::ostream &os, const MovieNode &node);
	
};


#endif
