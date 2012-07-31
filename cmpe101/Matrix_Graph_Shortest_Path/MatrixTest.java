class Matrixtest{
	public static void main(String[] args){
		Matrix A = new Matrix(11);
		Matrix B = new Matrix(11);
		Matrix C = null;
		double test = 4.2;
		A.changeEntry(1,2,4.2);
		A.changeEntry(1,3,8.0);
		A.changeEntry(2,3,0.0);
		A.changeEntry(3,2,2.1);
                B.changeEntry(1,2,4.2);
                B.changeEntry(2,3,5.2);
                B.changeEntry(1,3,1.0);
                B.changeEntry(3,2,8.1);
		System.out.println("A has "+A.getNNZ()+" non-zero entries:");
		System.out.println(A);
                System.out.println("B has "+B.getNNZ()+" non-zero entries:");
                System.out.println(B);
                System.out.println("(1.5)*A =");
		C = A.scalarMult(1.5);
                System.out.println(C);
		System.out.println("A+B = ");
                C = A.add(B);
		System.out.println(C);
		C = A.add(A);
                System.out.println("A+A = ");
                System.out.println(C);
		C = B.sub(A);
                System.out.println("B-A = ");
                System.out.println(C);
		C = A.sub(A);
                System.out.println("A-A = ");
                System.out.println(C);
		C = A.transpose();
                System.out.println("Transpose(A) =");
                System.out.println(C);
		C = A.mult(B);
                System.out.println("A*B =");
                System.out.println(C);
                C = B.mult(B);
                System.out.println("B*B =");
                System.out.println(C);

	}
}
