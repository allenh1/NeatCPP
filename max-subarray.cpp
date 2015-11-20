/**
 * This is the max-subarray problem.
 * This implementation is the O(n) version.
 */
#include <iostream>

/**
 * @brief      Returns the max subarray of A.
 *
 * @param      A     Array of integers
 * @param[in]  n     Number of values within A.
 *
 * @return     Max sum of a subarray.
 */
 int maxSubarray(int * A, size_t n) {
 	if (n == 0 || A == NULL)
 		return 0;
 	if (n == 1)
 		return A[0];

 	int * M = new int[n]; //fill array of prefix maximums.

 	for (unsigned short x = 1; x < n; ++x)
 		M[x] = (M[x - 1] + A[x] > 0) ? M[x - 1] + A[x] : 0;
 	
 	int m = 0;

 	for (unsigned short x = 1; x < n; ++x)
 		m = (m > M[x]) ? m : M[x];
 	return m;
}

int main (int argc, char ** argv)
{
	int m1[] = {1, 2, 3, 4, 5, -2, -3, -12};
	int m2[] = {-2, -4, 3, -1, 5, 6, -7, -2, 4, -3, 2};

	int maxSub1 = maxSubarray(m1, 8);
	int maxSub2 = maxSubarray(m2, 11);

	std::cout<<"Array: {1, 2, 3, 4, 5, -2, -3, -12}"<<std::endl;
	std::cout<<"Max Subarray: "<<maxSub1<<std::endl;

	std::cout<<std::endl;

	std::cout<<"Array: {-2, -4, 3, -1, 5, 6, -7, -2, 4, -3, 2}"<<std::endl;
	std::cout<<"Max Subarray: "<< maxSub2 <<std::endl;

	return 0;
}