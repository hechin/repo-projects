class Listtest{
   public static void main(String[] args){
      List A = new List();
      List B = new List();

      for(int i=1; i<=10; i++){
         A.insertAfterLast(i);
         B.insertBeforeFirst(i);
      }
      System.out.println("A = " + A);
      System.out.println("B = " + B);
      A.moveFirst();
      B.moveFirst();
      for(int i=1; i<=5; i++){
	 System.out.println("B = " + B);
         System.out.println("A = " + A);
         A.moveNext();
         B.moveNext();
      }
      System.out.println("A " + (A.equals(B)?"equals":"does not equal") + " B");
   }
}



