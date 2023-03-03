#ifndef _MOVIE_COLLECTION_HPP
#define _MOVIE_COLLECTION_HPP

#include<iostream>
#include<fstream>

#include "Movie.hpp"
#include "MovieNode.hpp"


class MovieCollection
{
private:
	MovieNode *_head;//pointer to the head node
	MovieNode *_tail;//pointer to the tail node
public:

	//return the size of the MovieCollection
	int size()const ;
	
	//retunr the rating of a given film
	double getRating(std::string film, int year);
	
	//add a node to the end of the list
	void appendToTail(Movie m);
	
	//add the node to the list
	void insert(Movie m);
	
	//Deault constructor
	MovieCollection(): _head(NULL), _tail(NULL) {};
	//constructor from an input
	MovieCollection(std::ifstream &ifile);
	//copy constructor
	MovieCollection(const MovieCollection & other);
	
	//modifiers of the tail and head nodes
	MovieNode* head() const {return _head;}
	MovieNode* tail() const {return _tail;}
	
	//find the movie given as a parameter
	MovieNode* find(Movie m) const;
	
	//remove the node given as a parameter
	MovieNode* remove(MovieNode *removeMe);
	//remove the head of the list
	MovieNode* removeHead();
	
	//overloading of plus operator
	const MovieCollection& operator+(const MovieCollection &other) const;
	//overloading of division operator
	const MovieCollection& operator/(const MovieCollection &other) const;
	
	//overloading of assigment operator
	const MovieCollection& operator=(const MovieCollection &other);
	
	//overloading of plus equal operator for a movie
	const MovieCollection& operator+=(const Movie &movieToAdd);
	//overloading of plus equal operator for a moviecollection
	const MovieCollection& operator+=(const MovieCollection &other);
	
	//overloading of minus equal operator for a movie
	const MovieCollection& operator-=(const Movie &movieToDel);
	//overloading of minus equal operator for a moviecollection
	const MovieCollection& operator-=(const MovieCollection &other);
	
	//clear the list
	void clear();
	//print the list
	std::ostream& print(std::ostream &os) const;
	//overloading of << operator
	friend std::ostream& operator<<(std::ostream &os, const MovieCollection &node);
};
#endif
