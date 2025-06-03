# Discussion

## PART I: MEASURED IndexedList

**Discuss from a design perspective whether iterating over a `MeasuredIndexedList`should 
affect the accesses and mutation counts. Note that for the purposes of this assignment we are NOT 
asking you to rewrite the `ArrayIndexedListIterator` to do so. However, if you wanted to include 
the `next()` and/or `hasNext()` methods in the statistics measured, can you inherit 
`ArrayIndexedListIterator` from `ArrayIndexedList` and override the relevant methods, or not? 
Explain.**

It should count towards the accesses and not the mutations. Every iteration accesses the information at that point and should therefore increase that counter.
The hasNext() should not increase the access count because it does not directly access the information of the array.
However, the next() method has the line "T t = data[nextIndex];" which accesses the data at every index, and would increase the access count by one every iteration. 
To inherit the ArrayIndexedListIterator private class in ArrayIndexedList, the class would have to be protected instead of private for it to be overridden.
Currently, the class is set to private which means it is not visible to any children class of ArrayIndexedList, such as MeasuredIndexedList.
It would be best to set to protected instead of public so that the user and other classes don't have access to the iterator. 


## PART II: EXPERIMENTS

**Explain the mistake in the setup/implementation of the experiment which resulted in a discrepancy 
between the results and what is expected from each sorting algorithm.**

The descending data isn't actually descending, instead, every 10th number or so is the number prior to it divided by 10. After that, it continues like normal.
As the list progresses, there are more examples of this, such as the aforementioned division occurring twice or three times back to back, giving a 2-digit number instead of a 4-digit number.
At the end of that same file, the number 0-1000 are mostly missing from the order. Although the majority of the numbers in this file are descending, these differences don't make it a truly descending data set, which is what should be used instead to test for more accuracy. 

Furthermore, when I set the size to 20, I noticed that the accesses and mutations were far higher than they should be for their respective tests.
I also noticed that the Gnome sort had a shorter time than other sorts when dealing with the random data.
As well as a concerning number of mutations for the ascending data, such as 160 mutations from bubble sort for a set of 20 ascending numbers.
Therefore, I decided to print out the data before and after sorting for about 20 numbers to see how the sorting looked.
I noticed what at first looked like a sort based on the first number, which made me realize that they were being sorted as strings.
For example, this is the following output for the random data set for all the sorts (except null) with 20 values:
Before : 7117 3815 0 5295 1350 6699 230 235 7949 4087 4561 9095 8218 9427 8217 3292 3891 1448 2603 5875
After : 0 1350 1448 230 235 2603 3292 3815 3891 4087 4561 5295 5875 6699 7117 7949 8217 8218 9095 9427
In the readData method in SortingAlgorithmDriver, the data is read as a string and kept as such when sorting.
Therefore, this seems to account for the fact that the accesses and mutations counts were higher than expected for the ascending data. They weren't actually sorted according to their numerical value, but by their ASCII value.


## PART III: ANALYSIS OF SELECTION SORT

**Determine exactly how many comparisons C(n) and assignments A(n) are performed by this 
implementation of selection sort in the worst case. Both of those should be polynomials of degree 2 
since you know that the asymptotic complexity of selection sort is O(n^2).**

The following analysis assumes that n is the size of int[] a.

Assignment:
The outer loop (line 3) has one assignment and n-1 incrementation, which sums to n assignments. 
Within the loop, the assignments on lines 4, 10, 11 , and 12 will occur n-1 times each, equating to 4n-4 times.
On line 5, there is another for-loop which will assign j=i+1 one time for every iteration of the outer loop minus 1, and increment n-1 times, then n-2, etc. This is equal to n + n-1 + n-2 ... = (n^2 - n)/2 - 1
On line 7, there is another assignment within the inner loop. Due to the incrementation of the outer loop, it will assign n-1 times, then n-2, etc. until it reaches 1 (the last comparison) in the worst case.
This equates to (n(n-1))/2 assignments for line 7.
In total, the sum would be n + 4n - 4 + (n^2 + n)/2 - 1 + (n(n-1))/2 = n^2 + 5n - 5 which is on the order of O(n^2) which aligns with the asymptotic complexity of selection sort.

Comparison:
On line three, the outer for-loop will have a total of n comparisons, including the final comparison that leads the loop to break.
On the first iteration, the inner loop will have n comparisons, then n-1 on the second iteration, etc until it reaches 2 comparisons (final comparison + break).
This equates to (n^2 - n)/2 + (n-1) iterations for line 5. 
In the worst case, line 6 will have n-1 comparisons for the first iteration of the outer loop, then n-2 on the second, etc until it reaches 1 comparison which equates to (n^2 - n)/2.
Therefore, the entire sum is n + (n^2 - n)/2 + (n^2 - n)/2 + (n-1) = n^2 + n - 1 which is on the order of O(n^2). 