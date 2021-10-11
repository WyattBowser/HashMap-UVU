#include "HashMap.h"

//HASH MAP -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

HashMap::HashMap(int size)
{
	sizeOfArray = size;
	hashArray = new Node * [size];
	for (int i = 0; i < size; i++)
	{
		hashArray[i] = nullptr;
	}
}

HashMap::~HashMap()
{
	//Go through each hashBucket
	for (int i = 0; i < sizeOfArray; i++)
	{
		//Look at the top of the linked list in the bucket
		Node* tbd = hashArray[i];

		//Move down the list
		while (tbd != nullptr)
		{
			//Create a temp
			Node* tmp = tbd->next;
			delete tbd;
			tbd = tmp;
		}
	}
}

//This creates the hash for the key
int HashMap::GenerateHash(string key) const
{
	const int SCRAMBLE_VALUE = 3;
	int generatedHash = 0;
	for (unsigned int i = 0; i < key.size(); i++)
	{
		generatedHash += (key[i] * SCRAMBLE_VALUE);
	}
	generatedHash = abs(generatedHash % sizeOfArray);
	return generatedHash;
}

bool HashMap::IsKeyPresent(string const& key) const
{
	bool found = false;

	//Find the hash for the key ans search for it
	Node* cursor = hashArray[GenerateHash(key)];
	//Look through the chain in the bucket
	while (cursor != nullptr)
	{
		//If the word is found
		if (cursor->key == key)
		{
			//Set found to true
			found = true;
		}
		//Move the cursor over
		cursor = cursor->next;
	}

	//Return found
	return found;
}

void HashMap::SetKeyValue(string const& key, int value)
{
	//Find the hashkey
	int generatedHash = GenerateHash(key);

	Node* current = hashArray[generatedHash];
	//If the key already exists
	if (IsKeyPresent(key) == true)
	{
		//Go through the list in the bucket until the key is found
		while (current->key != key)
		{
			current = current->next;
		}
		//Adjust the value
		current->value = value;
	}

	else //The key doesnt exist
	{
		//See if the first item is null
		if (current == nullptr)
		{
			//set the first item to a new node
			hashArray[generatedHash] = new Node(key, value);
		}
		//if it isnt null, find the end of the list
		else
		{
			while (current->next != nullptr)
			{
				current = current->next;
			}
			//set add a new node
			current->next = new Node(key, value);
		}
	}
}

bool HashMap::GetKeyValue(string const& key, int& value)
{
	bool keyExists = false;
	//Get the hash for the key
	int hashKey = GenerateHash(key);
	//Get node 
	Node* currentNode = hashArray[hashKey];

	//Look in the linked list in the bucket
	while (currentNode != nullptr && currentNode->key != key)
	{
		//if the current node doesnt have the key
		//Move the current node pointer
		currentNode = currentNode->next;
	}
	if (currentNode != nullptr && currentNode->key == key)
	{
		//If the currentNode key is teh sought key
		value = currentNode->value;
		keyExists = true;
	}
	else
		value = 0;

	return keyExists;
}


Iterator HashMap::begin()
{
	//Return the first item in the hashmap that isnt null ptr
	int tempIndex = 0;
	while (tempIndex < sizeOfArray && hashArray[tempIndex] == nullptr)
	{
		tempIndex++;
	}
	return Iterator(tempIndex, hashArray, sizeOfArray);
}

Iterator HashMap::end()
{
	//Need to return a nullprt somehow
	return Iterator();
}

