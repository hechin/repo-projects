/* Herman Chin
   hchin@ucsc.edu
   Summer 2011
   Tantalo
   pa3
*/

public class Matrix{
// Constructor ////////////////////////
	private class Entry{
		int col;
		double val;
		Entry(int col,double val){
			this.col = col;
			this.val = val;
		}
	        public String toString() { 
			String strr = "";
			strr += String.valueOf("("+col+", ");
			strr += String.valueOf(val + ")"); 
			return strr;
		}
	}

        private List[] matrix;
	private int Size;
	private int NNZ;

	Matrix(int n){ // Makes a new n x n zero Matrix. pre: n>=1
		matrix = new List[n];
		for(int i =0;i<n;i++){
			List newM = new List();
			matrix[i] = newM;
		}
		Size = n;
		NNZ = 0;
	}
// Access functions ///////////////////
	int getSize(){ // Returns n, the number of rows and columns of this Matrix
		return Size;
	}
	int getNNZ(){ // Returns the number of non-zero entries in this Matrix
		return NNZ;
	}
/*	public boolean equals(Object x) // overrides Object's equals() method
// Manipulation procedures ////////////

	void makeZero() // sets this Matrix to the zero state
	Matrix copy()// returns a new Matrix having the same entries as this Matrix
*/
	void changeEntry(int i, int j, double x){
		if(i<=getSize() && i>=1 && j>=1 && j<=getSize() && x != 0){
			List temp = matrix[i];
			Entry newEntry = new Entry(j,x);
			Object newX = newEntry;
			if(temp.isEmpty()){
				temp.insertBeforeFirst(newX);
				NNZ++;
			}else{
	                        temp.moveFirst();
				Object A = temp.getCurrent();
				Object B = temp.getFirst();
				Object C = temp.getLast();
				Entry a = (Entry) A;
				if(j < a.col && A == B){
					temp.insertBeforeFirst(newX);
					NNZ++;
				}else if(a.col < j && A == C){
					temp.insertAfterLast(newX);
					NNZ++;
				}else if(j < a.col && A != B){
					while(j < a.col && A != B){
						temp.movePrev();
						A = temp.getCurrent();
						a = (Entry) A;
					}
					if(j < a.col && A == B){
						temp.insertBeforeFirst(newX);
						NNZ++;
					}else{
						temp.insertAfterCurrent(newX);
						NNZ++;
					}
				}else if(a.col < j && A != C){
					while(a.col < j && A != C){
						temp.moveNext();
						A = temp.getCurrent();
						a = (Entry) A;
					}
					if(a.col < j && A == C){
                                                temp.insertAfterLast(newX);
						NNZ++;
                                        }else{
                                                temp.insertBeforeCurrent(newX);
						NNZ++;
                                        }
				}
			}
		}
	}
// changes ith row, jth column of this Matrix to x
// pre: 1<=i<=getSize(), 1<=j<=getSize()
	Matrix scalarMult(double x){
		int SIZE = getSize();
                Matrix scalard = new Matrix(SIZE);
		List temp;
		Object A;
		Object B;
		Entry a;
		double newV;
		for(int i=0;i<SIZE;i++){
			temp = matrix[i];
			if(!temp.isEmpty()){
				temp.moveFirst();
				A = temp.getCurrent();
				B = temp.getLast();
				while(A != B){
					a = (Entry) A;
					newV = a.val*x;
					scalard.changeEntry(i,a.col,newV);
					temp.moveNext();
					A = temp.getCurrent();
				}
                                a = (Entry) A;
			        newV = a.val*x;
                                scalard.changeEntry(i,a.col,newV);
			}
		}
		return scalard;
	}
// returns a new Matrix that is the scalar product of this Matrix with x
	Matrix add(Matrix M){
                if(getSize() != M.getSize()){
                        throw new RuntimeException("Error: Matrix sub");
                }
		int row = getSize();
		List temp;
		List temp2;
		List addM;
		Object A;
		Object B;
		Entry a;
		Matrix R = new Matrix(row);
		for(int i=0;i<row;i++){
// go through both lists and add to array to be added 
			temp = matrix[i];
			temp2 = M.matrix[i];
			double[] temparray = new double[row];
			if(!temp.isEmpty()){
				temp.moveFirst();
				A = temp.getCurrent();
				B = temp.getLast();
				while(A != B){
					a = (Entry) A;
					temparray[a.col] = a.val;
					temp.moveNext();
					A = temp.getCurrent();
				}
				a = (Entry) A;
				temparray[a.col] = a.val;
			}
			if(!temp2.isEmpty()){
				temp2.moveFirst();
				A = temp2.getCurrent();
				B = temp2.getLast();
				while(A != B){
					a = (Entry) A;
					temparray[a.col] = temparray[a.col] + a.val;
					temp2.moveNext();
					A = temp2.getCurrent();
				}
                                a = (Entry) A;
                                temparray[a.col] = temparray[a.col] + a.val;
			}
// add to new matrix to be returned
			for(int j=0;j<row;j++){
				R.changeEntry(i,j,temparray[j]);
			}
		}
		return R;
	}

// returns a new Matrix that is the sum of this Matrix with M
// pre: getSize()==M.getSize()
	Matrix sub(Matrix M){
		if(getSize() != M.getSize()){
			throw new RuntimeException("Error: Matrix sub");
		}
                int row = getSize();
                List temp;
                List temp2;
                List addM;
                Object A;
                Object B;
                Entry a;
                Matrix R = new Matrix(row);
                for(int i=0;i<row;i++){
// go through both lists and add to array to be added
                        temp = matrix[i];
                        temp2 = M.matrix[i];
                        double[] temparray = new double[row];
                        if(!temp.isEmpty()){
                                temp.moveFirst();
                                A = temp.getCurrent();
                                B = temp.getLast();
                                while(A != B){
                                        a = (Entry) A;
                                        temparray[a.col] = a.val;
                                        temp.moveNext();
                                        A = temp.getCurrent();
                                }
                                a = (Entry) A;
                                temparray[a.col] = a.val;
                        }
                        if(!temp2.isEmpty()){
                                temp2.moveFirst();
                                A = temp2.getCurrent();
                                B = temp2.getLast();
                                while(A != B){
                                        a = (Entry) A;
                                        temparray[a.col] = temparray[a.col] - a.val;
                                        temp2.moveNext();
                                        A = temp2.getCurrent();
                                }
                                a = (Entry) A;
                                temparray[a.col] = temparray[a.col] - a.val;
                        }
// add to new matrix to be returned
                        for(int j=0;j<row;j++){
                                R.changeEntry(i,j,temparray[j]);
                        }
                }
                return R;
	}
// returns a new Matrix that is the difference of this Matrix with M
// pre: getSize()==M.getSize()
	Matrix transpose(){
		int SIZE = getSize();
		List temp;
		Object A;
		Object B;
		Entry a;
		Matrix trans = new Matrix(SIZE);
		for(int i=0;i<Size;i++){
			temp = matrix[i];
			if(!temp.isEmpty()){
				temp.moveFirst();
				A = temp.getCurrent();
				B = temp.getLast();
				while(A != B){
                                        a = (Entry) A;
					trans.changeEntry(a.col,i,a.val);
                                        temp.moveNext();
                                        A = temp.getCurrent();
                                }
				a = (Entry) A;
                                trans.changeEntry(a.col,i,a.val);
			}
		}
		return trans;
	}
// returns a new Matrix that is the transpose of this Matrix
	Matrix mult(Matrix M){
                if(getSize() != M.getSize()){
                        throw new RuntimeException("Error: Matrix sub");
                }
                int SIZE = getSize();
                Matrix MULTD = new Matrix(SIZE);
                List temp;
                List temp2;
                Object A;
                Object B;
		Entry a;
		double[] sumMultd = new double[SIZE];
		double[] sumMultd2 = new double[SIZE];
		double sumMult;
		Matrix MULTDT = M.transpose();
		for(int i=0;i<SIZE;i++){
			for(int j=0;j<SIZE;j++){
				sumMult = 0;
				temp = matrix[i];
				temp2 = MULTDT.matrix[j];
				if(!temp.isEmpty()){
					temp.moveFirst();
					A = temp.getCurrent();
					B = temp.getLast();
					while(A != B){
						a = (Entry) A;
						sumMultd[a.col] = a.val;
						temp.moveNext();
						A = temp.getCurrent();
					}
                                        a = (Entry) A;
                                        sumMultd[a.col] = a.val;
				}
                                if(!temp2.isEmpty()){
                                        temp2.moveFirst();
                                        A = temp2.getCurrent();
                                        B = temp2.getLast();
                                        while(A != B){
                                                a = (Entry) A;
                                               	sumMultd2[a.col] = a.val;
                                                temp2.moveNext();
                                                A = temp2.getCurrent();
                                        }
                                        a = (Entry) A;
                                        sumMultd2[a.col] = a.val;
                                }
				for(int k=0;k<SIZE;k++){
					sumMultd[k] = sumMultd[k] * sumMultd2[k];
					sumMult = sumMult + sumMultd[k];
					sumMultd[k] = 0;
					sumMultd2[k] = 0;
				}
				if(temp.isEmpty() || temp2.isEmpty()){
					sumMult = 0;
				}
			MULTD.changeEntry(i,j,sumMult);
			}
		}
/*                Object C;
                Object D;
                Entry a;
                Entry c;
                double multd = 0;
                double sumMultd;
                for(int i=0;i<SIZE;i++){
                        temp = matrix[i];
                        if(!temp.isEmpty()){
                                temp.moveFirst();
                                A = temp.getCurrent();
                                B = temp.getLast();
                                for(int j=0;j<SIZE;j++){
					sumMultd = 0;
	                                while(A != B){
	                                        a = (Entry) A;
	                                        temp2 = M.matrix[a.col];
	                                        if(!temp2.isEmpty()){
	                                                temp2.moveFirst();
	                                                C = temp2.getCurrent();
	                                                D = temp2.getLast();
							c = (Entry) C;
	                                                while(C != D){
	                                                        c = (Entry) C;
	                                                        if(c.col == j){
	                                                                multd = c.val * a.val;
	                                                        }
	                                                }
	                                                if(c.col == j){
	                                                        multd = c.val * a.val;
	                                                }
	                                        }
	                                        sumMultd = sumMultd + multd;
	                                        temp.moveNext();
	                                        A = temp.getCurrent();
	                                }
					a = (Entry) A;
					temp2 = M.matrix[a.col];
	       	                        if(!temp2.isEmpty()){
	                                        temp2.moveFirst();
	                                        C = temp2.getCurrent();
	                                        D = temp2.getLast();
	                                        c = (Entry) C;
	                                        while(C != D){
	                                                c = (Entry) C;
	                                                if(c.col == j){
	                                                        multd = c.val * a.val;
	                                                }
	                                        }
	                                        if(c.col == j){
	                                                multd = c.val * a.val;
	                                        }
	                                }
	                                sumMultd = sumMultd + multd;
	                                MULTD.changeEntry(i,j,sumMultd);
					temp.moveFirst();
					A = temp.getCurrent();
				}
                        }
                }
*/
		return MULTD;
	}

// returns a new Matrix that is the product of this Matrix with M
// pre: getSize()==M.getSize()
// Other functions ////////////////////
	public String toString(){ // overrides Object's toString() method
		String strr2 = "";
		int i = 1;
		int f = getSize();
		while(i < f){
			List printstring = matrix[i];
			if(!printstring.isEmpty()){
	                        strr2 += i+": ";
				printstring.moveFirst();
				Object D = printstring.getCurrent();
				Object E = printstring.getLast();
				while(D != E){
					Entry d = (Entry) D;
					strr2 += d.toString() + " ";
					printstring.moveNext();
					D = printstring.getCurrent();
				}
		                Entry d = (Entry) D;
                        	strr2 += d.toString() + "\n";
			}
			i++;
		}
		return strr2;
	}
}
