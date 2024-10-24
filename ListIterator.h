#pragma once
#include "SortedIteratedList.h"


//DO NOT CHANGE THIS PART
class ListIterator{
	friend class SortedIteratedList;
private:
	const SortedIteratedList& list;
	ListIterator(const SortedIteratedList& list);

	SDLLNode* currentElement;

public:
	void first();
	void last();
	void next();
	void previous();
	bool valid() const;
    TComp getCurrent() const;
};


