#include "HashMap.h"

Iterator::Iterator(int index, Node** hashArray, int sizeOfArray)
{
	//Set the index
	this->index = index;
	//Point to the hasharray
	this->hashArray = hashArray;
	//Point to the first node
	this->current = hashArray[index];
	//Set the size
	this->sizeOfArray = sizeOfArray;
}

Iterator::Iterator()
{
	index = 0;
	current = nullptr;
	hashArray = nullptr;
	sizeOfArray = 0;
}

string Iterator::operator*()
{
	return current->key;
}

void Iterator::operator++()
{
	//If the next value is nullptr
	if (current->next == nullptr)
	{
		//Increase the index
		index++;
		//See if we are out of bounds
		if (index == sizeOfArray)
		{
			//Set current to nullptr
			current = nullptr;
			//End function
			return;
		}
		//Set current to the hashtables new index
		current = hashArray[index];
		//while the bucket you are looking in is empty
		while (current == nullptr)
		{
			//Move the current to the next bucket
			index++;
			//See if we are out of bounds
			if (index == sizeOfArray)
			{
				//End the array has been found. End the funciton
				current = nullptr;
				return;
			}
			current = hashArray[index];
		}
	}
	//if the next value is not a null ptr
	else
	{
		//set current to next item
		current = current->next;
	}
}

bool Iterator::operator!=(Iterator& other)
{
	bool matches = false;
	//if (this->current != nullptr && this->current->key != other.current->key)
	if(current != other.current)
		matches = true;
	return matches;
}
