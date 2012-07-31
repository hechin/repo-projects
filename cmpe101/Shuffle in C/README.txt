/*
  Herman Chin
  hchin@ucsc.edu
  Summer 2011
  CMPS 101
  Tantalo
  Lab 4
*/

	In this program, the user enters the file name FindPath input output and takes in the first line as the order of the graph. The file creates a GraphRef struct and takes in every input after the first line appending it to thadjacency list of the GraphRef. The program searches for the dummy 0 0 line as well while appending onto the list. Once the dummy is found, it prints out the adjacency list to the output file and starts to take in the first integer of each row as the source and performs BFS on the graph. The program then takes in the second integer and calls getPath with the second integer as the destination vertex. The path is then inserted into the ListRef and is called on by printPath to print out the shortest path from source to destination into the output file. After all the required operations are complete, the program then calls freeGraph to free the allocated memory from the Graph struct. This program runs in linear time because it runs through each list once with only the amount of comparison required by the order of the graph.
