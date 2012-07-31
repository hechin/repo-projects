  Herman Chin
  hchin
  Program 1
  CS101 Summer 2011
  Tantalo

	This program takes in a user input when started in the format

		Shuffle input output

	The input would be containing the first line containing the 
	number of lines of permutations and the remaining lines will be
	permutation lists. The program then takes in the integers and
	calls the insertAfterCurrent function to create the doubly 
	linked list. The algorithm then enters a loop that for every
	line of permutation, it will create a linked list with integers
	1-9 according to the size of the permutations. Then it will
	shuffle the linked lists in the order inputed by using an integer
	marker to keep track of the pointer in the linked list. A pointer
	is set to the last node of the list to be modified and the
	marker is compared to the permutation list adjusting accordingly
	while moving the pointer for every increment and decrement of the
	marker. The new node is added to the end of the list and the
	old nodes in front are deleted. Then the first permutation is 
	written in the output file and the rest of the permutaions are
	done with a count keeping track of how many have been done, then
	it is written in the output file.		
