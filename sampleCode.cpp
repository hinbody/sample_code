/* ***********************************************************************************
 * Name:        Harley Inbody
 * Date:	November 10, 2011	
 * Project:	Homework 6	
 * Source file: MyFloat2.cpp	
 * Compiler:    gcc
 * Action:      This is a partial class definiton for the class MyFloat that operates
 * 		on floats between 0 and 1 with a maximum of 20 digits
 * Note:      	The digits of a MyFloat are stored in a character array which is
 * 		padded with 0's
 ----------------------------------------------------------------------------------*/

#include<iostream>
using namespace std;

class MyFloat
{
	public:
		int Digits(); //returns # of digits in a MyFloat
		int MaxDigits(); //returns max poss. digits
		MyFloat(); //default contructor
		//overloaded operators below
		MyFloat operator+(MyFloat& Float);
		int operator==(MyFloat& Float);
		friend ostream& operator<< (ostream& FloatOut, const MyFloat& Float);
		friend istream& operator>> (istream& FloatIn, MyFloat& Float);
		MyFloat& operator= (const char FloatStr[]);
		int operator> (const MyFloat& Rhs);

	private:
		enum {MAX_DIGITS = 20};
		char Number[MAX_DIGITS +1];
		char NumberofDigits;
		//friend void AssignValue(MyFloat& X);
};

/************************Digits()***********************************
 *       Action: Returns the number of digits in a MyFloat 
 * 
 *   Parameters:
 * 	     IN: None
 * 	    OUT: None
 * 
 *      Returns: Number of digits stored in a MyFloat
 * Precondition: None
 ******************************************************************/
int MyFloat::Digits()
{
	return NumberofDigits;
}

/************************MaxDigits()********************************
 *       Action: Returns the constant MAX_DIGITS
 * 
 *   Parameters:
 * 	     IN: None
 * 	    OUT: None
 * 
 *      Returns: Maximum number of digits for a MyFloat
 * Precondition: None
 ******************************************************************/
int MyFloat::MaxDigits()
{
	return MAX_DIGITS;
}

/************************operator>>*********************************
 *       Action: Overloads >> operator to allow assinging a MyFloat
 *       	 from stadard in
 * 
 *   Parameters:
 * 	     IN: MyFloat to store input in
 * 	    OUT: istream object
 * 
 *      Returns: istream object and assigns it to a MyFloat
 * Precondition: None
 ******************************************************************/
istream& operator>> (istream& FloatIn, MyFloat& Float)
{
	int k = 0;
	char Ch;
	Float.NumberofDigits = 0;
	cin >> Ch; //skip whitespace
	if(Ch != '.' && Ch != '0') //first char must be 0 or .
	{
		Float.NumberofDigits = 0;
	}
	else
	{
		while(Ch == '0') //skip leading 0
		{
			cin >> Ch;
		}
		cin.get(Ch);
		while(isdigit(Ch) && k < Float.MAX_DIGITS) //make sure char is digit
		{
			Float.Number[++k] = Ch - '0'; //subtract 0 to store as int
			cin.get(Ch);
		}
		cin.putback(Ch);
		Float.NumberofDigits = k;
		for(k; k < Float.MAX_DIGITS; k++)
		{
			Float.Number[++k] = 0; //pad with 0's
		}
	}
	return FloatIn;
}

/************************operator<<*********************************
 *       Action: Overloads << operator to allow sending a MyFloat 
 *       	 to standard out using cout << 
 * 
 *   Parameters:
 * 	     IN: MyFloat to be output
 * 	    OUT: ostream object
 * 
 *      Returns: An ostream object to standard out
 * Precondition: None
 ******************************************************************/
ostream& operator<< (ostream& FloatOut, const MyFloat& Float)
{
	cout << "0.";
	if(Float.NumberofDigits == 0) //error if # of digits is 0
	{
		cout << "?";
	}
	else
	{
		int i = 1;
		for(i; i <= Float.NumberofDigits; i++)
		{
			cout << int(Float.Number[i]);
		}
	}
	return FloatOut;
}

/************************operator+**********************************
 *       Action: Overloads + operator to allow addition of two 
 *       	 MyFloats
 * 
 *   Parameters:
 * 	     IN: Right hand side MyFloat
 * 	    OUT: None
 * 
 *      Returns: A MyFloat that is the sum of 2 MyFloats
 * Precondition: None
 ******************************************************************/
MyFloat MyFloat::operator+ (MyFloat& Float)
{
	MyFloat Temp;
	int Carry = 0;
	if(NumberofDigits > Float.NumberofDigits) //determine length new float
	{
		Temp.NumberofDigits = NumberofDigits;
	}
	else
	{
		Temp.NumberofDigits = Float.NumberofDigits;
	}
	int i = MAX_DIGITS;
	for(i; i > 0; i--)
	{
		if(((Number[i] + Float.Number[i]) - 0) >= 10) //carry the 1
		{
			Temp.Number[i] = ((Number[i] + Float.Number[i]) % 10) + Carry;
			Carry = 1;
		}
		else
		{
			Temp.Number[i] = (Number[i] + Float.Number[i]) + Carry;
			Carry = 0;
		}
	}	
	return Temp;
}

/************************operator==*********************************
 *       Action: Overloads == operator to determine if 2 MyFloats
 *       	 are equal or not
 * 
 *   Parameters:
 * 	     IN: Right hand side MyFloat
 * 	    OUT: None
 * 
 *      Returns: integer 1 if 2 MyFloats are equal, 0 otherwise
 * Precondition: None
 ******************************************************************/
int MyFloat::operator== (MyFloat& Float)
{
	int i = 1;
	for(i; i <= MAX_DIGITS; i++)
	{
		if(Number[i] != Float.Number[i]) //returns false if not equal
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}
}

/************************operator>**********************************
 *       Action: Overloads > operator to determine which of 2 MyFloats
 *               are greater
 * 
 *   Parameters:
 * 	     IN: Right hand side MyFloat
 * 	    OUT: None
 *
 *      Returns: integer 1 if left side is greater, 0 otherwise
 * Precondition: None
 ******************************************************************/
int MyFloat::operator> (const MyFloat& Rhs)
{
	int i = 1;
	for(i; i <= MAX_DIGITS; i++)
	{
		if(Number[i] > Rhs.Number[i]) //returns true if Lhs is greater than Rhs
		{
			return 1;
		}
		else //returns false if Lhs is not greater than Rhs
		{
			return 0;
		}
	}
}

/************************Constructor********************************
 *       Action: Initializes a MyFloat to a size NumberofDigits = 0
 *       	 and is called autmatically when MyFloat declared
 * 
 *   Parameters:
 * 	     IN: None
 * 	    OUT: None
 * 
 *      Returns: Nothing
 * Precondition: None
 ******************************************************************/
MyFloat::MyFloat()
{
	NumberofDigits = 0;
}

/************************operator=**********************************
 *       Action: Overloads the = operator to allow assigning a 
 *               string to a MyFloat 
 * 
 *   Parameters:
 * 	     IN: char array i.e. C-string
 * 	    OUT: 
 * 
 *      Returns: MyFloat to allow cascading of operator=
 * Precondition: None
 ******************************************************************/
MyFloat& MyFloat::operator= (const char FloatStr[])
{
	int i = 1;
	int CountDigits = 0; //counts digits in FloatStr[]
	int ZeroCount = 0; //flag for 0's before .
	int k = 0;
	if(FloatStr[k] != '.' && FloatStr[k] != '0')
	{
	NumberofDigits = CountDigits;
	}
	else
	{
		while(FloatStr[k] == '0')
		{
			k++;
		}
		if(FloatStr[k] == '.')
		{
			k++;
			while(FloatStr[k] != '\0' && isdigit(FloatStr[k]) && i <= MAX_DIGITS)
			{
				Number[i] = FloatStr[k] - '0';
				CountDigits++;
				i++;
				k++;
			}
			NumberofDigits = CountDigits;
		}
	}
	return *this; //provide possible cascading
}


/************************************************************************
 * The following functions are ones that I wrote using pointers and 
 * linked lists to add to a program that tested them that was written by
 * someone else
*************************************************************************/

/*****************************   ZapList  ********************************

  DESCRIPTION  Frees all the storage space currently occupied by the
               linked list pointed to by List. Does NOT delete the delete
               the dummy head node.

  PARAMETER

    OUT, List  A pointer to a singly linked list with a dummy head node.
               After this call, List will contain only the dummy head node.

  PRECONDITION List must point to a linked list that has a dummy head node
               and a tail node that points at NULL.
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
void ZapList (NodePtr List)
{
  NodePtr Temp;

  while(List -> Link != NULL)
  {
	  Temp = List -> Link; //skip dummy head node
	  List -> Link = Temp -> Link; //move pointer from dummy head node
	  			       //to next node
	  delete Temp; //delete node skipped above
  }

  delete List -> Link; //delete node pointing to NULL
  List -> Link = NULL; //dummy head node now points to NULL
}


/****************************   AddNode  *********************************

  DESCRIPTION  Adds a node containing NewChar to the end of List.

  PARAMETERS

    IN, NewChar The character to be added to the end of the list.

    IN, List    A pointer to a singly linked list with a dummy head node.
                The value of List (address of dummy head node) is not
                changed by this routine, so List is passed by value.
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
void AddNode (char NewChar, NodePtr List)
{
   NodePtr NewNode;

   NewNode = List; //start at beginning of list

   while(NewNode -> Link != NULL) //find end of list
   {
	   NewNode = NewNode -> Link; //move through list to end
   }

   NewNode -> Link = new Node; //create new node after last node
   NewNode = NewNode -> Link; //move to (new) last node
   NewNode -> Ch = NewChar; //assign newly entered char
   NewNode -> Link = NULL; //terminate list

}

/****************************    DeleteNode   ****************************

  DESCRIPTION  Deletes the first node of List that contains the char
               CharToDelete. The storage occupied by the deleted
               node is returned to the heap.

  PARAMETERS

    IN, CharToDelete  The character to be deleted.

    IN, List    A pointer to a singly linked list with a dummy head node.
                The value of List is not changed by this routine but the
                linked list itself is changed.

    OUT, CharFound Set to 1 if the CharToDelete is found and deleted and
         0 otherwise.
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
void DeleteNode (char CharToDelete, NodePtr List, int &CharFound)
{
  NodePtr NodeToBeDeleted;

  CharFound = 0;  //  Return false if never found

  while(List -> Link != NULL && !CharFound) //search to end of list and
	  				    //stop after first occurance
  {
	  NodeToBeDeleted = List -> Link; //skip dummy head node
	  if(NodeToBeDeleted -> Ch == CharToDelete)
	  {
		  List -> Link = NodeToBeDeleted -> Link; //remove node 
		  					  //from list
		  delete NodeToBeDeleted;
		  CharFound = 1; //notify calling function that change was made
	  }
	  else
	  {
		  List = List -> Link; //move along list
	  }
  }
}

/****************************   BuildList    *****************************

  DESCRIPTION   Builds a singly linked list with a dummy head node. The
                characters in the list are in the same order in which the
                user enters them, i.e. new characters are added to the tail
                end of the list.

                Input terminates when the enter key is pressed.

  PARAMETERS

    IN, List    A pointer to a singly linked list with a dummy head node.
                It is imperative that List be initialized before calling
                this routine.

  NOTE          Before building the new list, ZapList is called. This
                ensures that a memory leak does not develop.
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
void BuildList (NodePtr List)
{
  
  ZapList(List); 
  char NewChar;

  cin >> NewChar; //get input

  while(NewChar != '\n')
  {
	  List -> Link = new Node; //create node to store char
	  List = List -> Link; //move along the list
	  List -> Ch = NewChar; //assign char
	  List -> Link = NULL; //terminate list
	  cin.get(NewChar); //get next char input
  }
}

/****************************   ReadList    *****************************

  DESCRIPTION   Builds a singly linked list with a dummy head node. The
                characters in the list are read in from an external file
                in the same order in which they are found in file.

                Input to list terminates when the End of File is encountered

  PARAMETERS

    IN, List    A pointer to a singly linked list with a dummy head node.
                It is imperative that List be initialized before calling
                this routine.

    IN, FileName  A pointer to a string that has the name of the file to
                  open, if error in opening then return a 1;

  RETURNS      1 if file opening error, 0 if read from file successful

  NOTE          Before building the new list, ZapList is called. This
                ensures that a memory leak does not develop.
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
int ReadList (NodePtr List,char FileName[])
{
  ifstream indata;              //declare file variable to read from

  ZapList(List);                     //make sure list is empty

  char ChIn;
  indata.open(FileName);

  if(indata.fail()) //File input error
  {
	  return 1;
  }
  else if(indata.good())
  {
	  while(indata >> ChIn) //read in character
	  {
		  if(List -> Link != NULL)
		  {
			  List = List -> Link;
		  }
		  List -> Link = new Node; //new node for current char
		  List -> Link -> Ch = ChIn; //assign char to new node
	  }
	  List -> Link = NULL; //append NULL to end of list
  }
  
  indata.close(); //close the file
  return 0;

}

/**************************  SortList ************************************

Description  Arranges the singly linked list pointed to by List in
             natural order.  It is assumed that the list has a dummy
             head node.

             The algorithm used is a linked variation of the selection
             sort and works like this:
             Start with EndSorted aimed at first node of list

             repeat
               Find smallest char between EndSorted and end of list
               Swap smallest element with char in EndSorted
               Change EndSorted to next node
             until we get to end of list

             None of the pointers in linked list are changed

Parameters
  IN, List  A pointer to a singly linked list with a dummy head node
-----------------------------------------------------------------------*/
void SortList(NodePtr List)
{
   NodePtr SmallNode;        //points to smallest char
   NodePtr SearchNode;       //used to search each node in list
   NodePtr EndSorted;       //points to list to sort
   char TempCh;

   SmallNode = EndSorted = List -> Link; //start EndSorted and SmallNode at first node   
   SearchNode = EndSorted -> Link; //start searching at second node
   while(EndSorted -> Link != NULL) //contiune to last node
   {
	   while(SearchNode -> Link != NULL) //search until last node
	   {
		   if(SmallNode -> Ch > SearchNode -> Ch) //check for next node being smaller than current smallest
		   {
			   //following swaps current search node with smallest
			   TempCh = SearchNode -> Ch;
			   SearchNode -> Ch = SmallNode -> Ch;
			   SmallNode -> Ch = TempCh;
		   }
		   SearchNode = SearchNode -> Link; //advance search node
	   }
	   if(SmallNode -> Ch > SearchNode -> Ch)  //checks last node
		   {
			   TempCh = SearchNode -> Ch;
			   SearchNode -> Ch = SmallNode -> Ch;
			   SmallNode -> Ch = TempCh;
		   }
	   SmallNode = EndSorted = EndSorted -> Link; //advance through list
	   SearchNode = EndSorted -> Link;
   }
}
