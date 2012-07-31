/*
  Herman Chin
  hchin
  Program 1
  CS101 Summer 2011
  Tantalo
*/
import java.io.*;
import java.util.Scanner;

class Shuffle extends List{

        public static void main(String[] args) throws IOException{

              Scanner in = null;
              PrintWriter out = null;
              String line = null;
              String[] token = null;
              int i, n, lineNumber = 0;
	      int Tint;	

              if(args.length < 2){
                 System.out.println("Usage: Shuffle infile outfile");
                 System.exit(1);
              }

              in = new Scanner(new File(args[0]));
              out = new PrintWriter(new FileWriter(args[1]));

              while( in.hasNextLine() ){
                 lineNumber++;
                 line = in.nextLine()+" ";    // add extra space so split works right
                 token = line.split("\\s+");  // split line around white space
                 n = token.length;
                if(lineNumber == 1){
                        int inputs = Integer.parseInt(token[0]);
                }else{
// link input into a linked list
                        int firstNode = Integer.parseInt(token[0]);
                        Node curr = new Node();
			Node temp1 = curr;
                        curr.data = firstNode;
                        curr.prev = null;
                        curr.next = null;
                        for(i=1; i<n; i++){
                                Tint = Integer.parseInt(token[i]);
                                insertAfterCurrent(temp1,Tint);
				temp1 = temp1.next;
                        }

// create list to be permuted
			n++;
                        Node plist = new Node();
			Node temp = plist;
			Node cplist = new Node();
			Node temp2 = cplist;
			cplist.data = 1;
			cplist.prev = null;
			cplist.next = null;
                        plist.data = 1;
                        plist.prev = null;
                        plist.next = null;
                        for(i=2; i<n; i++){
				insertAfterCurrent(temp2,i);
                                insertAfterCurrent(temp,i);
				temp = temp.next;
				temp2 = temp2.next;
                        }
// PERMUTE
			int counter = 1;
			Node permptr = curr;
			Node moveptr;
			while(permptr != null){
				moveptr = plist; 
// position permutation counter
				while(counter != permptr.data){
					if(counter < permptr.data){
						counter++;
						temp = temp.next;
					}else if(counter > permptr.data){
						counter--;
						temp = temp.prev;
					}
				}
// add to the existng list
				insertAfterCurrent(temp,moveptr.data);
				plist = plist.next;
				deleteCurrent(moveptr);
				permptr = permptr.next;
			}

// write first permutation
			temp = temp.next;
			while(temp.prev != null){
				temp = temp.prev;
			}
                        out.print("( ");
                        while(temp != null){
                                out.print(temp.data + " ");
                                temp = temp.next;
                        }



// count permutatinos
                        int permcounter = 1;
			int pcounter = 1;
                        temp = plist;
                        Node plistctr = cplist;
                        while(plistctr != null && temp != null){
// walk through linked lists comparing start to finish
                                if(plistctr.data != temp.data){
                                        permcounter = 1;
					pcounter++;
                                        Node cpermptr = curr;
                                        temp = plist;
                                        while(temp.next != null){
                                                temp = temp.next;
                                        }
                                        Node cmoveptr;
                                        while(cpermptr != null){
                                                cmoveptr = plist;
// position permutation counter fpr not equal
                                                while(permcounter != cpermptr.data){
                                                        if(permcounter < cpermptr.data){
                                                                permcounter++;
                                                                temp = temp.next;
                                                        }else if(permcounter > cpermptr.data){
                                                                permcounter--;
                                                                temp = temp.prev;
                                                        }
                                                }
// add to the existng list
                                                insertAfterCurrent(temp,cmoveptr.data);
                                                plist = plist.next;
                                                deleteCurrent(cmoveptr);
                                                cpermptr = cpermptr.next;
                                        }
                               
// reset to beginning of linked list
                                temp = temp.next;
				plistctr = cplist;
                                while(temp.prev != null){
                                        temp = temp.prev;
                                }
// else continue through linked list
                                }else{
                                        plistctr = plistctr.next;
                                        temp = temp.next;
                                }
                        }

// write line into file counters

                        out.println(")  order = " + pcounter );
                }
              }

              in.close();
              out.close();
        }

}
