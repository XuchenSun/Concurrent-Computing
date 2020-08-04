//Input:the matrxX size, the valude of  matrix X and b
//Output : The convergence value of X and running time(CPU clock cycle)
#include <iostream>
#include<cmath>
#include<time.h>
#include <omp.h>
#include <iostream>
// Jacobi method is a square system of n linear equations, where Ax=b
/*   matrixA=[a11,a12,a13,a14....a1n
*            a21,a22,a23,a24....a2n
*                               a3n
*             an1,an2,an3........ann]
*b is a bertical column
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

Output: The convergence value of X and The CPU clock cycle of Runing time 

*/
using namespace std;
#define Random 0.00001// set the random is 0.0001
#define array 20// the max size of array is limited to 20, if 
#define Max_Iterations 500// the total Iterations number is limited to 500

void Jacobi_Method_Parallel()
{

	int n, N;// define the n and N to initialize the MatrixX
	int control;// define k to control the random and Iterations
	float x[array];// define the array of X
	float matrixA[array][array];//define the matriX to get the value from input
	float rhs[array];// define the rhs array 
	float summary[array];// define the summary array and using it for iteration
	int number_thread;// define the number of thread
	int i_parallel, j_parallel;// i and j is variable for parallel 
	printf("Please input the matrixA size of Jacobibe method \n for example\n if A=[1 2 3;\n      4 5 6;\n      7 8 9], \n   the matrixA size is 3:\n ");
	printf("Attention: the Max size is 20, plese input a number which is less than 20:  \n");
	cin >> n;
	N = n;
	printf("Please input matrixA: \n");
	for (i_parallel = 0; i_parallel < n; i_parallel++) {   // chansfer the value into matrixA
		x[i_parallel] = 0; for (j_parallel = 0;
			j_parallel < n; j_parallel++) {
			cin >> matrixA[i_parallel][j_parallel];
		}
	}
	printf("Please input the value of matrixB : \n");
	for (i_parallel = 0; i_parallel < n; i_parallel++) { cin >> rhs[i_parallel]; }
	printf("Please input the number of threads : ");
	cin >> number_thread;
	omp_set_num_threads(number_thread);// use officl ompfunction

#pragma omp parallel  private(i_parallel,j)	// parallel progran by using the shared-variable 
	{control = 1; while (control <= Max_Iterations && control > Random)
	{
#pragma  for collapse(2) // loop 
		for (i_parallel = 0; i_parallel < n; i_parallel++) {
			summary[i_parallel] = rhs[i_parallel];// define the i in parallel processing
			for (j_parallel = 0; j_parallel < n; j_parallel++) { if (i_parallel != j_parallel) { summary[i_parallel] = summary[i_parallel] - matrixA[i_parallel][j_parallel] * x[j_parallel]; } }
		}// define the j in parallel processing
#pragma omp parallel for  // use officle omp parallel function
		for (i_parallel = 0; i_parallel < n; i_parallel++) { x[i_parallel] = summary[i_parallel] / matrixA[i_parallel][i_parallel]; }control++;// use control to control the parallel
	}}
	printf("The value of X is  : \n"); for (int m = 0; m < N; m++) { printf("X[%d] = %f\n", m, x[m]); }
}
int main()
{
	const clock_t start_time = clock();// define the program start time
	Jacobi_Method_Parallel();// run the Jacobi method
	float time = float(clock() - start_time);// define the function to calculate the program running time 
	cout << "\n The total runing time of the Parallel Jacobi method  is (CPU clock cycle):   " << time << endl;// output the time
	cout << "\n Attention: If the value of X is infinite the output will be' - infi'";
}// The explanation of "-infi output"