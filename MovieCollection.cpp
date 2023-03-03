#include "MovieCollection.hpp"

#include <iostream>

using namespace std;

//returns the size of the list
int
MovieCollection::size() const
{
	MovieNode *curr=_head; //new node equals head
	int tamaño = 0;//variable that count the size
	
	while(curr!=NULL)
	{
		tamaño++;//add one every time it pass the while loop(equivalent to one node)
		curr = curr->next();//point to the next node	
	}
	
	return tamaño;//return the size
}

//remove a given node
MovieNode*
MovieCollection::remove(MovieNode *removeMe)
{
	if(removeMe == _head)//if we remove the head
		return removeHead();//use removehead instead
		
	//find the node immediately previous to removeMe
	MovieNode *prev = _head;
	while(prev!=NULL && prev->next()!=removeMe)//
		prev = prev->next();
	
	//check if the previous node is null
	//check if removeMe is null
	if(prev==NULL || removeMe ==NULL)
		return NULL;
	
	//skip past removeMe
	prev->next() = removeMe->next();
	
	//deal with removing the tail
	if(removeMe == _tail)
		_tail = prev;
	
	//clean up removed node
	removeMe ->next() = NULL;
	
	return removeMe;
}

//remove the head node
MovieNode*
MovieCollection::removeHead()
{
	if(_head == NULL)//if the head equals null
		return NULL;
	
	MovieNode *returnNode;//new node 
	returnNode = _head;//equals head
	
	_head = _head->next();//point the next node
	
	
	if(_head==NULL)//was the alast node that we just removed?
		_tail=NULL;
	
	returnNode -> next() = NULL;
	
	return returnNode;
}

//find a given movie
MovieNode*
MovieCollection::find(Movie m)const
{
	MovieNode *curr=_head;//new node equals head
	
	while(curr!=NULL)//while the node is not null
	{
		if(*curr->value() == m)//if the movie in the node equals the given movie
			return curr;//return that movie
		curr = curr->next();//next node
	}
	return NULL;//if not found return null
}

//retunr the rating of a given film
double
MovieCollection::getRating(string film, int year)
{
	MovieNode *curr=_head;//new node equals head
	Movie *comp = new Movie(film, year, 0);//create a new pointer with the parameters
	
	while(curr!=NULL)//while the node is not null
	{
		if(*curr->value() == *comp)//if finds the movie
			return curr->value()->rating();//return the rating
		curr = curr->next();//next node
	}
	return -1;//if the movie is not finded return -1
}

//add the value to the tail
void
MovieCollection::appendToTail(Movie m)
{
	
	if(_tail == NULL)//if the tail is null
	{
		insert(m);//insert the movie
		
		_tail = _head;//tail equals head
		return;
	}
	
	MovieNode *newNode = new MovieNode(m);//new node with the movie in it
	newNode->next() = NULL;//next node equals null
	
	_tail->next() = newNode;//next node equls the new node
	_tail = newNode;//the tail is the new node
}

//insert a movie in the list at front
void
MovieCollection::insert(Movie m)
{
	MovieNode *newNode = new MovieNode(m);//new node with the movie in it
	
	newNode->next() = _head;//point to the head
	
	if(_head == NULL)
	_tail = newNode; //if the head is null the newnode is the tail
	
	_head = newNode; //and the head	
}

//constructor from an input
MovieCollection::MovieCollection(ifstream &ifile)
{
	//inizializate the variables
	_head = NULL;
	_tail = NULL;
	
	//new movie
	Movie m;
	//pass the movie from the file to the new just created
	ifile >> m;
	//while the document has text
	while(ifile)
	{
		MovieNode *newNode = new MovieNode(m);//new node with the film
		appendToTail(m);//add it to the list
		newNode = newNode->next();//point the next node
		ifile >> m;//add the next values
	}
}

//copy constructor
MovieCollection::MovieCollection(const MovieCollection &other)
{
	//inizializate the variables
	_head = NULL;
	_tail = NULL;
	
	MovieNode *newNode = other._head;//newn node equals the head of the list intended to copy
	while (newNode != NULL)//while the other list has values
	{
		Movie *comp = newNode->value();//new movie equal the movie in the new node
		appendToTail(*comp);//add it to the list
		newNode = newNode->next();//pount the next node		
	}
}

//print the values of the list
std::ostream&
MovieCollection::print(std::ostream &os) const
{
	MovieNode* curr= _head;//new node equals head
	while(curr!=NULL)
	{
		os<< *curr<<endl;//store it on os
		curr = curr->next();	//go to the next values
	}
	
	return os;//return os
}

//<< operator overloading
ostream& operator<<(ostream &os, const MovieCollection &node)
{
	return node.print(os);//call the print method
}

//plus operator overloading
const MovieCollection& 
MovieCollection::operator+(const MovieCollection &other) const
{
	MovieCollection *answer = new MovieCollection(); //new moviecollection
	
	MovieNode *curr=_head;//new node equals the head
	//add all the values from LHS to teh new collection
	while(curr!=NULL)
	{	
		answer->appendToTail(*curr->value());
		curr = curr->next();
	}
	
	MovieNode *curr2=other._head;//new node equals the head of the RHS
	
	//add all the values of the RHS that are not already in the new collection
	while(curr2!=NULL)
	{	
		if(!answer->find(*curr2->value()))
			answer->appendToTail(*curr2->value());
		curr2 = curr2->next();
	}
	return *answer; //return the new collection
}

// /operator oveloading
const MovieCollection& 
MovieCollection::operator/(const MovieCollection &other) const
{
	MovieCollection *answer = new MovieCollection(); //new collection
	MovieNode *curr= other._head;//new node equals head
	
	//add all the values that are in bot RHS and LHS
	while(curr!=NULL)
	{
		if(find(*curr->value()))//can be find in LHS
		{
			answer->appendToTail(*curr->value());
		}
		curr = curr->next();
	}
	
	
	return *answer;
}

// plus equal operator overloading
const MovieCollection& 
MovieCollection::operator+=(const Movie &movieToAdd)
{	
        //add the movie to this only if it is not already in it
	if(!find(movieToAdd))
	{
		appendToTail(movieToAdd);
	}

	MovieCollection *answer = new MovieCollection(*this);
	return *answer;
}

// plus equal operator overloading with other collection
const MovieCollection& 
MovieCollection::operator+=(const MovieCollection &other)
{

	MovieNode *curr=other._head;//new node equals head
	//add the values that arent already in the collection by usinf the previous += operator
	while(curr!=NULL)
	{
		operator+=(*curr->value());
		curr = curr->next();
	}
	
	MovieCollection *answer = new MovieCollection(*this);
	return *answer;
}

//minus equal operator overloading
const MovieCollection& 
MovieCollection::operator-=(const Movie &movieToDel)
{
	MovieCollection *answer = new MovieCollection(); //new Moviecollection
	MovieNode *curr=_head;//new node equals head
	while(curr!=NULL)
	{
		//if it is not the same movie
		if(movieToDel!=*curr->value())
		{
			//add it to the new collections
			*answer+=(*curr->value());
		}
		else 
		{
			//else remove it
			remove(curr);
		}
		curr = curr->next();
	}
	return *answer;
}

//new node equals head with other collection
const MovieCollection& 
MovieCollection::operator-=(const MovieCollection &other)
{
	
	MovieCollection *answer = new MovieCollection();//new Moviecollection
	MovieNode *curr=other._head;//new node equals head
	while(curr!=NULL)
	{
		//remove the ones in common with the previous overloaded operator
		if(find(*curr->value()))
			this->operator-=(*curr->value());
		curr = curr->next();
	}
	
	//use assigment operator overloaded
	*answer = *this;
	return *answer;
}

//assgiment operator overloading
const MovieCollection& 
MovieCollection::operator=(const MovieCollection &other)
{
	MovieNode *curr=other._head;//new node equals head
	while(curr!=NULL)
	{
		//copy every value with the += operator
		operator+=(*curr->value());
		curr = curr->next();
	}
	return *this;
}

//clear the list
void
MovieCollection::clear()
{
	//if head is null the rest is not printed
	_head = NULL;
}


