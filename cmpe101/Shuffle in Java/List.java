/*
  Herman Chin
  hchin
  Program 1
  CS101 Summer 2011
  Tantalo

  Description: This is the library for a double-linked list in java
*/

import java.util.Scanner;
import java.io.*;

public class List{


	public static Node current = new Node();



	public static class Node{
		int data;
		Node next;
		Node prev;
	}

	static boolean isEmpty(Node current){
		if(current.prev == null &&
			current.next == null){
			if(current == null){
				return true;
			}
		}
		return false;
	}
	static boolean offEnd(Node current){
		if(current == null) return true;
		return false; 
	}
	static boolean atFirst(Node current){
		if(!isEmpty(current)){
			if(current.prev == null){
				return true;
			}
		}
		return false;
	}
	static boolean atLast(Node current){
		if(!isEmpty(current)){
			if(current.next == null){
				return true;
			}
		}
		return false;
	}
	static int getFirst(Node current){
		if(isEmpty(current)){
			System.err.println("List is Empty");
		}
		Node temp = current;
		while(temp.prev != null){
			temp = temp.prev;
		}
		return temp.data;
	}
	static int getLast(Node current){
                if(isEmpty(current)){
			System.err.println("List is Empty");
		}
                Node temp = current;
		while(temp.next != null){
                        temp = temp.next;
                }
                return temp.data;
	}
	static int getCurrent(Node current){
                if(isEmpty(current) && offEnd(current)){
			System.err.println("List is Empty");
		}
		return current.data;
	}
	static int getLength(Node current){
		Node temp = current;
		while(temp.prev != null){
                        temp = temp.prev;
                }
		int length;
		if(current == null){
			length = 0;
		}else{
			length = 1;
		}

		while(temp.next != null){
			length++;
			temp = temp.next;
		}
		return length;
	}
	static boolean equals(Node L){
		Node temp = current;
                while(temp.prev != null){
                        temp = temp.prev;
                }
		while(L.prev != null){
			L = L.prev;
		}
		while(L.next != null || temp.next != null){
			if(L.data != temp.data){
				return false;
			}
		}
		return true;
	}

	static void makeEmpty(Node current){
		current.prev = null;
		current.next = null;
		current = null;
		if(!isEmpty(current)){
			System.err.println("List Not Empty");
		}
	}	
	
	static void makeFirst(Node current){
		if(!isEmpty(current)){
			while(current.prev != null){
				current = current.prev;
			}
		}else{
                        System.err.println("List is Empty");
		}
		if(offEnd(current)) System.err.println("OffEnd");
	}
	static void moveLast(Node current){
		if(!isEmpty(current)){
			while(current.next != null){
				current = current.next;
			}
		}
                if(offEnd(current)) System.err.println("OffEnd");
	}
	static void movePrev(Node current){
		if(!isEmpty(current) && !offEnd(current)){
			current = current.prev;
		}else{
                        System.err.println("List is Empty/OffEnd");
		}
	}
	static void moveNext(Node current){
                if(!isEmpty(current) && !offEnd(current)){
                        current = current.next;
                }else{
                        System.err.println("List is Empty/OffEnd");
                }
	}
	static void insertBeforeFirst(Node current, int data){
		Node newNode = new Node();
		newNode.data = data;
		newNode.prev = null;
		while(current.prev != null){
			current = current.prev;
		}
		newNode.next = current;
		current.prev = newNode;
		if(isEmpty(current)) System.err.println("Didn't Insert");
	}
	static void insertAfterLast(Node current, int data){
                Node newNode = new Node();
                newNode.data = data;
                newNode.next = null;
                while(current.next != null){
                        current = current.next;
                }
                newNode.prev = current;
                current.next = newNode;
                if(isEmpty(current)) System.err.println("Didn't Insert After Last");
	}
	static void insertBeforeCurrent(Node current, int data){
		if(isEmpty(current) && offEnd(current)){
			System.err.println("Didn't Insert Before Current");
			current.next = null;
			current.prev = null;
			current.data = data;
		}else{
			Node newNode = new Node();
			newNode.data = data;
			if(current.prev == null){
				newNode.prev = null;
				current.prev = newNode;
				newNode.next = current;
			}else{
				newNode.next = current;
				current.prev = newNode;
				newNode.prev = current.prev;
				current.prev.next = newNode;
			}
			current = newNode;
		}
	}
	static void insertAfterCurrent(Node current, int data){
                if(isEmpty(current) && offEnd(current)){
                        System.err.println("Didn't Insert After Current");
                        current.next = null;
                        current.prev = null;
                        current.data = data;
                }else{
		        Node newNode = new Node();
                        newNode.data = data;
			if(current.next == null){
	                        newNode.next = null;
	                        current.next = newNode;
	                        newNode.prev = current;
	                }else{
				newNode.next = current.next;
				current.next.prev = newNode;
				current.next = newNode;
				newNode.prev = current;
			}
			current = newNode;
		}
	}
	static void deleteFirst(Node current){
                if(isEmpty(current)){
                        System.err.println("Can't Delete Empty List");
                }
		Node temp = current;
                while(temp.prev != null){
                        temp = temp.prev;
                }
		temp = temp.next;
		temp.prev = null;		
	}
	static void deleteLast(Node current){
                if(isEmpty(current)){
                        System.err.println("Can't Delete Empty List");
                }
		Node temp = current;
                while(temp.next != null){
                        temp = temp.next;
                }
                temp = temp.prev;
                temp.next = null;
	}
	static void deleteCurrent(Node current){
                if(isEmpty(current) && offEnd(current)){
                        System.err.println("Can't Delete Empty List");
                }
		Node temp = current;
		if(temp.prev == null){
			temp = temp.next;
			temp.prev = null;
			current = temp;
		}else if(temp.next == null){
			temp = temp.prev;
			temp.next = null;
			current = temp;
		}else{
			temp.prev.next = temp.next;
			temp.next.prev = temp.prev;
		}
		if(offEnd(current)) System.err.println("Can't Delete Empty List");
	}
	private Node copy(Node current){
		Node fnewNode = new Node();
		Node head = fnewNode;
		fnewNode.data = current.data;
		fnewNode.prev = null;
		fnewNode.next = null;
		current = current.next;
		while(current != null){
			insertAfterCurrent(fnewNode,current.data);
			current = current.next;
			fnewNode = fnewNode.next;
		}
		return head;
	}
}
