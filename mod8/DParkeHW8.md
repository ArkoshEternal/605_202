# Homework Seven : More on Trees and Sorting

## Question One

> How many comparisons and interchanges (in terms of file size n) are performed by
> Simple insertion sort for the following files:
> i. A sorted file
> ii. A file that is sorted in reverse order (that is, from largest to smallest)
> iii. A file in which x[0], x[2], x[4]... are the smallest elements in sorted order, and
> in which x[1], x[3], x[5]... are the largest elements in sorted order, e.g.  [3, 14,
> 5, 15, 9, 8, 11, 19]

Sorted File:

* Comparisons: n-1, as there's no shift, but a comparison against everything
* Interchanges: 0, per above

Reverse Order:

* Comparisons: (n^2-n)/2, as everything compared with everything before it
* Interchanges: same, as there's a change per compare.

Alternating:
In the case where the order alternates as described, we'll end up in a situation where for half of the numbers, there will be no interchange and a single comparison, and for the other half, there's gonna be n=1 comparisons, and n-2 interchanges. 

* Comparisons: n/2 + n(n-1) which is n + 2(2(n-1))/2
* Interchanges: n(n-1)/2 or n^2 -n / 2


## Question Two

> How many comparisons and interchanges (in terms of file size n) are performed by
> Shell Sort using increments 2 and 1 for the following files:
> i. A sorted file
> ii. A file that is sorted in reverse order (that is, from largest to smallest)
> iii. A file in which x[0], x[2], x[4]... are the smallest elements in sorted order, and
> in which x[1], x[3], x[5]... are the largest elements in sorted order, e.g. [3, 14,
> 5   15, 9, 18, 11, 19]

Sorted: 
* Comparisons: n + n-1 for insertion, so 2n -1
* Interchanges: 0, since we're already sorted

Reverse Order:
* Comparisons: n^2/4 - n/2 + n(n-1)/2 
* Interchanges: same as comparisons since fully reversed

Alternating: 
* Comparisons: nothing at first, so just n-2 + n^2 + n - 2/2 from g1
* Interchanges: n(n-1)/2



## Question Three

> Determine the number of comparisons (as a function of n and m) that are performed
> in merging two ordered files a and b of sizes n and m, respectively, by the merge
> method presented in the lecture, on each of the following sets of ordered files:
> a. m=n and a[i] < b[i] < a[i+1], e.g. a=[6, 9, 12, 15, 29, 37] and b=[8, 10, 14, 25,
> 33, 45]
> b. m=n and a[n] < b[1], e.g. a=[2, 5, 9] and b=[12, 14, 16]
> a[i] refers the value in position i of file a, etc

a. when m==n & a,b is in an alternating pattern, then each item of a will be compared against two elements of b except a[0], so we'll have 2n-1, since n == m 
b. When all a is smaller than b, then you'll just need to exhaust a against b[0], so we'll just have n comparisons

## Question Four

> Determine the number of comparisons (as a function of n and m) that are performed
> in merging two ordered files a and b of sizes n and m, respectively, by the merge
> method presented in the lecture, on each of the following sets of ordered files:
> a. m=n and a[n/2] < b[1] < b[m] < a[(n/2)+1], e.g. a=[2, 5, 7,  55, 61, 72] and
> b=[9, 15, 17, 21, 29, 46]
> b. m=1 and b[1] < a[1]
> c. m=1 and a[n] < b[1], a[i] refers the value in position i of file a, etc

a. If m=n and b intersects a considering a fully merged array, we'll have a scenario where 3 comparisons for the first half of a against b[1], then six comparisons to exhaust b, then three more, so it'll just be equal to 2n 
b. if m = 1, and b[1] is lower than a[1] then it'll just be a single comparison
c. if m = 1 and b > a, then we'll have to compare every element of a, so n comparisons.