#include "ListIterator.h"
#include "SortedIteratedList.h"
#include <exception>

using namespace std;

ListIterator::ListIterator(const SortedIteratedList& list) : list(list){
	this->currentElement = this->list.head;
} // BC = WC = TC = Theta(1)


void ListIterator::first(){
	this->currentElement = this->list.head;
} // BC = WC = TC = Theta(1)


void ListIterator::last() {  // added now
	this->currentElement = this->list.tail;
} // BC = WC = TC = Theta(1)


void ListIterator::next(){
	if (this->currentElement == NULL)
		throw exception();

	this->currentElement = this->currentElement->next;
} // BC = WC = TC = Theta(1)


void ListIterator::previous() {  // added now
	if (this->currentElement == NULL)
		throw exception();

	this->currentElement = this->currentElement->prev;
} // BC = WC = TC = Theta(1)


bool ListIterator::valid() const{
	if (this->currentElement != NULL)
		return true;

	return false;
} // BC = WC = TC = Theta(1)

TComp ListIterator::getCurrent() const{
	if (this->currentElement == NULL)
		throw exception();

	TComp e = this->currentElement->info;
	return e;
} // BC = WC = TC = Theta(1)


