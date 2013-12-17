#include <stdlib.h>

#include "linkedlist.h"

Node::Node() :
	_value(0)
{}

Node::~Node()
{
	
}

LinkedList::LinkedList() :
	_head(NULL),
	_tail(NULL)
{}

LinkedList::~LinkedList()
{

}

bool LinkedList::init()
{

	return true;
}
