//Xuchen Sun 2020-08-29
//Input:the matrxX size, the valude of  matrix X and b
//Output : The convergence value of X 
// Jacobi method is a square system of n linear equations, where Ax=b
/*   matrixA=[a11,a12,a13,a14....a1n
*            a21,a22,a23,a24....a2n
*                               a3n
*             an1,an2,an3........ann]
*b is a vertical column
*    b=[b1,
*	    b2,
*		b3,
*		b4,
*		...
*		bn]


* The output is the x
*    x =[x1,
*	     x2,
*		 x3,
*		 x4,
*		 ...
*		 xn

*Jacobi_Method_Parallel is a funtion to get the valuse of X

Input:the matrxX size, the valude of  matriX  and  b

Output: The convergence value of X 

*/
#include <iostream>
#include<cmath>
#include <omp.h>
using namespace std;
#define Random 0.001// set the random is 0.0001
#define array 20// the max size of array is limited to 20, if 
#define Max_Iterations 500// the total Iterations number is limited to 500

void Jacobi_Method_Parallel()
{
	int n_initialize_MatrixA, N;// define the n and N to initialize the MatrixA
	int control;// define k to control the random and Iterations
	float x[array];// define the array of X
	float matrixA[array][array];//define the matriX to get the value from input
	float rhs[array];// define the rhs array 
	float summary[array];// define the summary array and using it for iteration
	int number_thread;// define the number of thread
	int a_parallel, b_parallel;// i and j is variable for parallel 
	printf("Please input the matrixA size of Jacobibe method \n for example\n if A=[1 2 3;\n      4 5 6;\n      7 8 9], \n   the matrixA size is 3:\n ");
	printf("Attention: the Max size is 20, plese input a number which is less than 20:  \n");
	cin >> n_initialize_MatrixA;
	N = n_initialize_MatrixA;
	printf("Please input matrixA: \n");
	for (a_parallel = 0; a_parallel < n_initialize_MatrixA; a_parallel++) {   // chansfer the value into matrixA
		x[a_parallel] = 0; for (b_parallel = 0;
		b_parallel < n_initialize_MatrixA; b_parallel++) {
			cin >> matrixA[a_parallel][b_parallel];
		}
	}
	printf("Please input the value of matrixB : \n");
	for (a_parallel = 0; a_parallel < n_initialize_MatrixA; a_parallel++) { cin >> rhs[a_parallel]; }
	printf("Please input the number of threads : ");
	cin >> number_thread;
	omp_set_num_threads(number_thread);// use officl ompfunction

#pragma omp parallel  private(i_parallel,j)	// parallel progran by using the shared-variable, and the package must be included for "<omp.h>"
	{control = 1; while (control <= Max_Iterations && control > Random)
	{
#pragma  for collapse(2) // loop 
		for (a_parallel = 0; a_parallel < n_initialize_MatrixA; a_parallel++) {
			summary[a_parallel] = rhs[a_parallel];// define the i in parallel processing
			for (b_parallel = 0; b_parallel < n_initialize_MatrixA; b_parallel++) { if (a_parallel != b_parallel) { summary[a_parallel] = summary[a_parallel] - matrixA[a_parallel][b_parallel] * x[b_parallel]; } }
		}// define the j in parallel processing
#pragma omp parallel for  // use officle omp parallel function
		for (a_parallel = 0; a_parallel < n_initialize_MatrixA; a_parallel++) { x[a_parallel] = summary[a_parallel] / matrixA[a_parallel][a_parallel]; }control++;// use control to control the parallel
	}}
	printf("The value of X is  : \n"); for (int m = 0; m < N; m++) { printf("X[%d] = %f\n", m, x[m]); }
}
int main()
{Jacobi_Method_Parallel();// run the Jacobi method
cout << "\n Attention: If the value of X is infinite the output will be' - infi'";// The explanation of "-infi output"
cout << "Thanks for using. Have a good day!";
}