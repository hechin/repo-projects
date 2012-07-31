/*
  Herman Chin
  hchin
  Program 1
  CS101 Summer 2011
  Tantalo

  Description: This file tests the basic functions in the List library
*/
import java.io.*;
import java.util.Scanner;

class ListTest extends List{

   public static void main(String[] args){
	System.out.println("Start Test");
	System.out.println("--------------------------");
	System.out.println("enter inputs and create list");
	System.out.println("input 'X' when finished");
//  open up standard input
        String input = "nothing";
        String exit = "X";
	int firstnode = 0;
	Node curr = new Node();
        curr.next = null;
        curr.prev = null;
        curr.data = 0;

        while(input.compareTo(exit) != 0){
                System.out.print("Enter Input: ");
                BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
//  read the input from the command-line; need to use try/catch with the
//  readLine() method
                try {
                        input = br.readLine();
                } catch (IOException ioe) {
                        System.out.println("error trying to read input!");
                        System.exit(1);
                }
                int integer;
// break when exited
                if(input.compareTo(exit) == 0){
                        break;
                }
// check for integer
                try {
                        integer = Integer.parseInt(input);
                } catch (NumberFormatException nfe) {
                        System.err.println("Please Enter An Integer");
                        continue;
                }
//insert after current
                if(firstnode != 0){
                        Node newNode = new Node();
                        newNode.next = null;
                        newNode.prev = null;
                        newNode.data = integer;
                        insertAfterCurrent(curr, integer);
                        Node temp = curr;
                        System.out.print("Linked List: ");
                        while(temp != null){
                                System.out.print(temp.data + " ");
                                temp = temp.next;
                        }
                        System.out.println();
                }else{
                        curr.data = integer;
                        firstnode++;
                        System.out.println("Linked List: " + curr.data);
                }
        }
// insert before
	input = "null";
	System.out.println("InsertBeforeCurrent");
        while(input.compareTo(exit) != 0){
                System.out.print("Enter Input: ");
                BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
//  read the input from the command-line; need to use try/catch with the
//  readLine() method
                try {
                        input = br.readLine();
                } catch (IOException ioe) {
                        System.out.println("error trying to read input!");
                        System.exit(1);
                }
// break when exited
                if(input.compareTo(exit) == 0){
                        break;
                }
		int integer;
// check for integer
                try {
                        integer = Integer.parseInt(input);
                } catch (NumberFormatException nfe) {
                        System.err.println("Please Enter An Integer");
                        continue;
                }
//insert after current
                if(firstnode != 0){
                        Node newNode = new Node();
                        newNode.next = null;
                        newNode.prev = null;
                        newNode.data = integer;
                        insertBeforeCurrent(curr, integer);
                        Node temp = curr;
			System.out.println();
                }else{
                        curr.data = integer;
                        firstnode++;
                        System.out.println("Linked List: " + curr.data);
                }
        }
	int eight = 8;
	insertAfterLast(curr, eight);
	System.out.println("Inserted 8 Before First");
	insertBeforeFirst(curr, eight);
	System.out.println("Inserted 8 After Last");
        

// test isempty
	String sEmpty = "false";
	if(isEmpty(curr)){
		sEmpty = "true";
	}
	System.out.println("isEmpty: " + sEmpty);
// test offend
        String ffEnd = "false";
        if(offEnd(curr)){
                ffEnd = "true";
        }
        System.out.println("offEnd: " + ffEnd);
// atFirst
        String tFirst = "false";
        if(atFirst(curr)){
                tFirst = "true";
        }
        System.out.println("atFirst: " + tFirst);
// atLast
        String tLast = "false";
        if(atLast(curr)){
                tLast = "true";
        }
        System.out.println("atLast: " + tLast);
// getFirst
	int etFirst = getFirst(curr);
	System.out.println("getFirst: " + etFirst);
// getLast
	int etLast = getLast(curr);
	System.out.println("getLast: " + etLast);
// getCurrent
	int etCurrent = getCurrent(curr);
	System.out.println("getCurrent: " + etCurrent);
// getLength
	int etLength = getLength(curr);
	System.out.println("getLength: " + etLength);
// equals
        String quals = "false";
        if(equals(curr)){
                quals = "true";
        }
        System.out.println("equals: " + quals);
// makeFirst
	makeFirst(curr);
        System.out.println("makeFirst: " + curr.data);
// moveLast
	moveLast(curr);
        System.out.println("moveLast: " + curr.data);
// movePrev
	movePrev(curr);
        System.out.println("movePrev: " + curr.data);
// moveNext
	moveNext(curr);
        System.out.println("moveNext: " + curr.data);
// makeEmpty
	makeEmpty(curr);
	if(isEmpty(curr)){
	        System.out.println("makeEmpty");
	}
// delete first
	deleteFirst(curr);
	Node tempp = curr;
	while(tempp.prev != null){
		tempp = tempp.prev;
	}
	while(tempp != null){
		System.out.println(tempp.data);
                System.out.println();
		tempp = tempp.next;
	}
// delete last
	deleteLast(curr);
        Node tempp1 = curr;
        while(tempp1.prev != null){
                tempp1 = tempp1.prev;
        }
        while(tempp1 != null){
                System.out.print(tempp1.data);
		System.out.println();
                tempp1 = tempp1.next;
        }
// delete current
	deleteCurrent(curr);
	System.out.println("current deleted");

   }
}

