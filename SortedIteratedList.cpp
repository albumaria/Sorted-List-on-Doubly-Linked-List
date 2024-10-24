#include "ListIterator.h"
#include "SortedIteratedList.h"
#include <iostream>
using namespace std;
#include <exception>

SortedIteratedList::SortedIteratedList(Relation r) {
	this->head = nullptr;
	this->tail = nullptr;
	this->rel = r;
	this->listSize = 0;
} // BC = WC = TC = Theta(1)


int SortedIteratedList::size() const {
	return this->listSize;
} // BC = WC = TC = Theta(1)


bool SortedIteratedList::isEmpty() const {
	if (this->listSize == 0)
		return true;

	return false;
} // BC = WC = TC = Theta(1)


ListIterator SortedIteratedList::first() const {
    ListIterator it(*this);
	it.first();

	return it;
} // BC = WC = TC = Theta(1)


TComp SortedIteratedList::getElement(ListIterator poz) const {
	return poz.getCurrent();
} // BC = WC = TC = Theta(1)


TComp SortedIteratedList::remove(ListIterator& poz) {
	if (!poz.valid())
		throw exception();

	SDLLNode* current = poz.currentElement;
	TComp removed = current->info;

	if (current == this->head) // if we need to remove the head
	{
		this->head = this->head->next; // changing the head to the next one
		if (this->head != nullptr) // if we didn't delete the only element, link head previous to null
			this->head->prev = nullptr;
		else
			this->tail = nullptr; // if we deleted the only element, update tail
	}
	else if (current == this->tail) // if we delete the tail
	{
		this->tail = this->tail->prev; // updating tail
		this->tail->next = nullptr;
	}
	else 
	{
		current->prev->next = current->next; // if not, the element is in the middle, we only need to update the connections
		current->next->prev = current->prev;
	}

	poz.next(); // Move the iterator to the next element
	delete current;
	this->listSize--;
	return removed;
}  // BC = WC = TC = Theta(1) because the position is given when removing an element, we don't need
   // to perform any searches, therefore it only needs to check where in the list the node given is:
   // (if it is the tail, head, or in between)


ListIterator SortedIteratedList::search(TComp e) const{
    ListIterator it(*this);

	while (it.valid() && it.getCurrent() != e)
		it.next();
	
	return it;
}  // BC = Theta(1) if we search for the first element
   // WC = Theta(listSize) if it is the last element in the list
   // TC = O(listSize)


void SortedIteratedList::add(TComp e) {
	SDLLNode* newNode = new SDLLNode;
	newNode->info = e;

	ListIterator it(*this);

	if (this->listSize == 0) // if we add the first element
	{
		this->head = newNode;
		this->tail = newNode;
		this->listSize++;
		return;
	}

	while (it.valid() && !this->rel(e, it.getCurrent())) // searching for the position where e goes
		it.next();

	//if the iterator becomes invalid, add to end.
	if (!it.valid())
	{
		this->tail->next = newNode;
		newNode->prev = this->tail;
		newNode->next = nullptr;
		this->tail = newNode;
		this->listSize++;
		return;
	}

	// add before head
	if (it.currentElement->prev == nullptr)
	{
		this->head->prev = newNode;
		newNode->prev = nullptr;
		newNode->next = this->head;
		this->head = newNode;
		this->listSize++;
		return;
	}

	// iterator stops at the node BEFORE which we
	// need to add
	{
		newNode->prev = it.currentElement->prev;
		newNode->next = it.currentElement;
		it.currentElement->prev->next = newNode;
		it.currentElement->prev = newNode;
		this->listSize++;
		return;
	}

} // BC = Theta(1) when adding the first element into the list or when the element is added on the first position
  // WC = Theta(listSize) when adding to the tail of the list, as the search was performed until the end of the list
  // TC = O(listSize)


SortedIteratedList::~SortedIteratedList() {
    ListIterator it(*this);

    while (it.valid()) {
        SDLLNode* current = it.currentElement;
        it.next();
        delete current;
    }
} // BC = WC = TC = Theta(listSize)

ListIterator SortedIteratedList::lastIndexOf1(TComp elem) const
{
	ListIterator it1(*this);
	ListIterator it2(*this);
	it2.next();
	// Now it1 is on the first element, it2 is on the second

	if (it1.getCurrent() == elem && (!it2.valid() || it2.getCurrent() != elem)) // it's on the first position, we don't need to search further
		return it1;

	while (it2.valid())
	{
		while (it2.getCurrent() == elem)
		{
			it1.next();
			it2.next();

			if (it2.getCurrent() != elem || !it2.valid())
				return it1;
		}
		it1.next();
		it2.next();
	}

	return it2; // returns invalid iterator, knowing that it left the while loop
} // BC = Theta(1) if it is on the first position and it is alone
  // WC = Theta(listSize) if we have to go to the end of the list to find the last instance of the element
  // TC = O(listSize)


ListIterator SortedIteratedList::lastIndexOf2(TComp elem) const
{
	ListIterator it(*this);
	it.last();

	while (it.valid())
	{
		if (it.getCurrent() == elem)
			return it;

		it.previous();
	}

	return it;
} // BC = Theta(1) if it is on the last position
  // WC = Theta(listSize) if we have to go to the very beginning of the list
  // TC = O(listSize)




