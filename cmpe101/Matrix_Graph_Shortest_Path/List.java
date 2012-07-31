/*
  Herman Chin
  hchin
  Program 3 
  CS101 Summer 2011
  Tantalo
*/

public class List{

	public class Node{
		Object data;
		Node next;
		Node prev;
		Node(Object data){this.data = data; next = null; prev = null;}
		public String toString(){return String.valueOf(data);}
	}
// Fields
	public Node head;
	public Node tail;
	public Node current;
	public int length;
// Constructor
	List(){head = tail = current = null;length = 0;} 

        public String toString(){
           String str = "";
           for(Node N=head; N!=null; N=N.next){
              str += N.toString() + " ";
           }
           return str;
        }

// Access Fucntions

	boolean isEmpty(){
		return length == 0;
	}
	boolean offEnd(){
		if(current == null) return true;
		return false; 
	}
	boolean atFirst(){
		if(head == null) return true;
		return false;
	}
	boolean atLast(){
		if(tail == null) return true;
		return false;
	}
        Object getFirst(){
		if(isEmpty()){
			throw new RuntimeException("Error: getFirst");
		}
		return head.data;
	}
	Object getLast(){
                if(isEmpty()){
                        throw new RuntimeException("Error: getLast");
                }
                return tail.data;
	}
	Object getCurrent(){
                if(isEmpty()){
                        throw new RuntimeException("Error: getCurrent");
                }
                if(offEnd()){
                        throw new RuntimeException("Error: getCurrent");
                }
		return current.data;
	}
	Object getLength(){
		return length;
	}
	boolean equals(List x){
		Node A = head;
		Node B = x.head;
		while(A!=null && B!=null){
			if(A.data != B.data){
				return false;
			}
			A = A.next;
			B = B.next;
		}
		return true;
	}
	void makeEmpty(){
		head = tail = current = null;
		length = 0;
                if(isEmpty()){
                       System.out.print("Emptied");
                }
	}	
	
	void moveFirst(){
                if(isEmpty()){
                        throw new RuntimeException("Error: moveFirst");
                }
		current = head;
                if(offEnd()){
                        throw new RuntimeException("Error: offend moveFirst");
                }
	}
	void moveLast(){
                if(isEmpty()){
                        throw new RuntimeException("Error: moveLast");
                }
		current = tail;
                if(offEnd()){
                        throw new RuntimeException("Error: moveLast");
                }
	}
	void movePrev(){
		if(isEmpty()){
                        throw new RuntimeException("Error: movePrev");
                }
		current = current.prev;
                if(offEnd()){
                        throw new RuntimeException("Error: movePrev");
                }
	}
	void moveNext(){
                if(isEmpty()){
                        throw new RuntimeException("Error: moveNext");
                }
                current = current.next;
                if(offEnd()){
                        throw new RuntimeException("Error: moveNext");
                }
	}
	void insertBeforeFirst(Object data){
                Node newNode = new Node(data);
		if(!isEmpty()){
			newNode.next = head;
			head.prev = newNode;
			head = newNode;
		}else{
			tail = head = current = newNode;
		}
		length++;
                if(offEnd()){
                        throw new RuntimeException("Error: insertBeforeFirst");
                }
	}
	void insertAfterLast(Object data){
                Node newNode = new Node(data);
		if(!isEmpty()){
                	newNode.prev = tail;
			tail.next = newNode;
			tail = newNode;
		}else{
			head = tail = current = newNode;
		}
		length++;
                if(offEnd()){
                        throw new RuntimeException("Error: insertAfterLast");
                }
	}
	void insertBeforeCurrent(Object data){
                Node newNode = new Node(data);
		if(!isEmpty() && current != head){
			newNode.prev = current.prev;
			current.prev.next = newNode;
			newNode.next = current;
			current.prev = newNode;
		}else if(current == head){
			insertBeforeFirst(data);
		}else{
			head = tail = current = newNode;
		}
		length++;
                if(offEnd()){
                        throw new RuntimeException("Error: insertBeforeCurrent");
                }
	}
	void insertAfterCurrent(Object data){
                Node newNode = new Node(data);
		if(!isEmpty() && current != tail){
	       	        newNode.next = current.next;
	       	        current.next.prev = newNode;
	                newNode.prev = current;
	                current.next = newNode;
		}else if(current == tail){
			insertAfterLast(data);
                }else{
                        head = tail = current = newNode;
                }
		length++;
                if(offEnd()){
                        throw new RuntimeException("Error: insertAfterCurrent");
                }
	}
	void deleteFirst(){
                if(isEmpty()){
                        throw new RuntimeException("Error: deleteFirst");
                }
		head = head.next;
		head.prev = null;
		length--;
	}
	void deleteLast(){
                if(isEmpty()){
                        throw new RuntimeException("Error: deleteLast");
                }
		tail = tail.prev;
		tail.next = null;
		length--;
	}
	void deleteCurrent(){
                if(isEmpty()){
                        throw new RuntimeException("Error: deleteCurrent");
                }
                if(offEnd()){
                        throw new RuntimeException("Error: deleteCurrent");
                }
		if(current != head && current != tail){
			current.next.prev = current.prev;
			current.prev.next = current.next;
		}else if(current == head){
			deleteFirst();
		}else if(current == tail){
			deleteLast();
		}
		current = current.next;
		length--;
                if(offEnd()){
                        throw new RuntimeException("Error: deleteCurrent");
                }
	}
}
