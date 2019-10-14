#include <vector>
#include <iostream>

using namespace std;

template <class T, class Comparator>
void mergeSort (vector<T>& myArray, Comparator comp);

template <class T, class Comparator>
void helper(vector<T>& myArray, vector<T>& output, Comparator comp, int low, int high);

template <class T, class Comparator>
void merge (vector<T>& myArray, vector<T>& output, Comparator comp, int low, int pivot, int high);




template <class T, class Comparator>
void mergeSort (vector<T>& myArray, Comparator comp)
{
	vector<T> output = myArray;
	if(int(myArray.size()) > 1)
	{
		//helper array takes in extra low and high int values as parameter
		helper(myArray, output, comp, 0, int(myArray.size())-1);
	}
}

template <class T, class Comparator>
void helper (vector<T>& myArray, vector<T>& output, Comparator comp, int low, int high)
{
	//check to see if we've reached a sub-vector of size 1
	if (low >= high)
	{
		return;
	}
	else
	{
		int pivot = (low+high)/2;
		//lower half
		helper(myArray, output, comp, low, pivot);
		//upper half
		helper(myArray, output, comp, pivot+1, high);

		merge(myArray, output, comp, low, pivot, high);
	}
}

template <class T, class Comparator>
void merge (vector<T>& myArray, vector<T>& output, Comparator comp, int low, int pivot, int high)
{
	//index of start of first half of sub-vector
	int i = low;
	//index of start of second half of sub-vector
	int j = pivot+1;
	//index of vector we passed in 
	int k = low;
	//check to see if we've reached end of either sub-vector
	while(i <= pivot && j <= high)
	{
		//use functor defined separately
		if(comp(output[i], output[j]))
		{
			myArray[k] = output[i];
			k++;
			i++;
		}
		else
		{
			myArray[k] = output[j];
			k++;
			j++;
		}
	}
	//check if there any elements in lower half of sub-vector to be copied
	while(i <= pivot)
	{
		myArray[k] = output[i];
		i++;
		k++;
	}
	//check if there are any elements in upper half of sub-vector to be copied
	while(j <= high)
	{
		myArray[k] = output[j];
		j++;
		k++;
	}
	
	//update the copy vector for next iteration
	for (i = low; i < k; i++)
    {
        output[i] = myArray[i];
    }
}

