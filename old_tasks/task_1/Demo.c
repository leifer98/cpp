/**
 * Demo program for ADT exercise.
 *
 * Author: Evgeny Hershkovitch Neiterman
 * Since : 2023-02
 */

#include "AdptArray.h"
#include "book.h"
#include "Person.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

int main()
{

	// pbook b1 = creat_book("harry Potter",12345) ;
	// pbook b2= creat_book("C intro", 45678) ;
	// PAdptArray mybooks = CreateAdptArray(copy_book,delete_book,print_book);
	// SetAdptArrayAt(mybooks,3,b1);
	// SetAdptArrayAt(mybooks,5,b2);
	// printf("the size is %d\n",GetAdptArraySize(mybooks));  //should print 6
	// pbook b = GetAdptArrayAt(mybooks,4); // should return null;
	// assert(b==NULL); // doesn't fail
	// b = GetAdptArrayAt(mybooks,3);
	// printf("the book is %s\n",b->name); //should print "Harry Potter"
	// PrintDB(mybooks);

	// pperson p1 = creat_person("Harry","Potter", 934);
	// pperson p2 = creat_person("Ron","Weasley", 789);
	// PAdptArray HP_caracters = CreateAdptArray(copy_person,delete_person,print_person);
	// SetAdptArrayAt(HP_caracters,2,p1);
	// SetAdptArrayAt(HP_caracters,8,p2);
	// printf("the size is %d\n",GetAdptArraySize(HP_caracters)); // prints 9
	// PrintDB(HP_caracters); // prints:
	// //first name: Harry last name: Potter id: 934
	//     //first name: Ron last name: Weasley id: 789

	// DeleteAdptArray(mybooks);
	// DeleteAdptArray(HP_caracters);
	// delete_book(b1);
	// delete_book(b2);
	// delete_book(b);
	// delete_person(p1);
	// delete_person(p2);

	// Create some books and a book database
	pbook b1 = creat_book("Harry Potter", 12345);
	pbook b2 = creat_book("C intro", 45678);
	PAdptArray mybooks = CreateAdptArray(copy_book, delete_book, print_book);

	// Add the books to the database at valid indices
	SetAdptArrayAt(mybooks, 3, b1);
	SetAdptArrayAt(mybooks, 5, b2);

	// Check the size of the database
	printf("The size is %d\n", GetAdptArraySize(mybooks)); // should print 6

	// Try to get a book from an invalid index
	pbook b = GetAdptArrayAt(mybooks, 4); // should return NULL
	if (b == NULL)
	{
		printf("The book is NULL\n");
	} // doesn't fail

	// Try to get a book from an invalid index (-1)
	b = GetAdptArrayAt(mybooks, -1); // should return NULL
	if (b == NULL)
	{
		printf("The book is NULL\n");
	} // doesn't fail

	// Try to get a book from an invalid index (-10)
	b = GetAdptArrayAt(mybooks, -10); // should return NULL
	if (b == NULL)
	{
		printf("The book is NULL\n");
	} // doesn't fail

	// Try to get a book from an invalid index (beyond the end of the array)
	b = GetAdptArrayAt(mybooks, 10); // should return NULL
	if (b == NULL)
	{
		printf("The book is NULL\n");
	} // doesn't fail

	// Get a book from a valid index and print its name
	b = GetAdptArrayAt(mybooks, 3);
	printf("The book is %s\n", b->name); // should print "Harry Potter"

	// Print the book database
	PrintDB(mybooks);

	// Create some people and a person database
	pperson p1 = creat_person("Harry", "Potter", 934);
	pperson p2 = creat_person("Ron", "Weasley", 789);
	PAdptArray HP_caracters = CreateAdptArray(copy_person, delete_person, print_person);

	// Add the people to the database at valid indices
	SetAdptArrayAt(HP_caracters, 2, p1);
	SetAdptArrayAt(HP_caracters, 8, p2);

	// Check the size of the database
	printf("The size is %d\n", GetAdptArraySize(HP_caracters)); // should print 9

	// Try to get a person from an invalid index
	pperson p = GetAdptArrayAt(HP_caracters, 4); // should return NULL
	assert(p == NULL);							 // doesn't fail

	// Try to get a person from an invalid index (-1)
	p = GetAdptArrayAt(HP_caracters, -1); // should return NULL
	assert(p == NULL);					  // doesn't fail

	// Try to get a person from an invalid index (-10)
	p = GetAdptArrayAt(HP_caracters, -10); // should return NULL
	assert(p == NULL);					   // doesn't fail

	// Try to get a person from an invalid index (beyond the end of the array)
	p = GetAdptArrayAt(HP_caracters, 10); // should return NULL
	assert(p == NULL);					  // doesn't fail

	// Print the person database
	PrintDB(HP_caracters);

	// Delete the databases and objects
	DeleteAdptArray(mybooks);
	DeleteAdptArray(HP_caracters);
	delete_book(b1);
	delete_book(b2);
	delete_book(b);
	delete_person(p1);
	delete_person(p2);

	return 0;
}
