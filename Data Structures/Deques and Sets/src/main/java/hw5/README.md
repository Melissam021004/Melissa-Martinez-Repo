# Discussion

## Flawed Deque
The test "testRemoveBackEmptyException" failed, which leads me to believe that the removeBack() method doesn't check if the deque is empty before trying to remove the last element. This is because I ran removeBack() on the freshly made deque, so it likely isn't an issue with the length since I didn't modify the deque at all. I also do not think it is an issue with the empty() function since the tests relating to that function pass in my "testEmpty()" test. 
Next, I believe the back() method doesn't throw an empty exception when the deque is empty because my "testBackEmptyException()" method fails on a new deque. I believe this is because the method simply doesn't check if it is empty before attempting to peek at the last element since my "testEmpty()" tests pass. 
Next, the test "testInsertFront()" fails when it tests the final assertEquals, where the expected is 3 and the actual was 2. This assert is after the only insertBack() called in this test which leads me to believe that length isn't updated in the insertBack() method. However, the rest of the method works which leads me to think that elements are inserted to the front correctly. 
The next test that fails is "testInsertBack()" which failed when checking the length of the deque after adding a second element. I switched around my asserts in this method and also found out that the back element isn't added all together. The addition of the first element worked correctly but the addition of the second element did not occur, as seen by the length being 1 instead of 2, and the deque.back() returning the first element added instead of the second. 
"testRemoveBack()" is another test that fails, and it fails when checking the length of the deque after adding 4 elements, which should be 4 but is instead 2. Combined with the outcome of the previous test, I think that insertBack() is not inserting elements correctly as what should be the 3rd element is what is returned instead of the 4th (last) element.
Furthermore, "testRemoveFrontEmptyException()" also fails, which is likely due to the removeFront() method not checking if the deque is empty before attempting to remove the first element, similar to my hypothesis as to why removeBack() wasn't working.
Also, the "testBackAccess()" method fails when checking the second element and instead returns the first element, similar to how "testInsertBack()" failed which leads me to believe that the insertBack() method is faulty and may not be adding elements to the back correctly. 
Lastly, my "testLength()" test fails when checking the length after inserting an element to the back of the list, but not when elements were inserted to the front which again provides reason to believe that elements aren't being added to the back of the deque correctly.


## Hacking Linear Search
In the TransposeArraySet, I realized that when it removed an item, it replaced the item at the removal index with the last element of the array, making the last element quicker to find. Meanwhile, the LinkedSet simply removes the element from the linked set without altering the order.
Moving the last element to the spot where the removed item was sort of defeats the purpose of the transposeArraySet heuristic, as it is moving up elements even when they aren't searched for, and this heuristic works best when more-frequently searched elements are towards the front. Therefore, this heuristic isn't completely accurate to what it's supposed to do.
I noticed that in TransposeArraySet, when I attempted to remove the value of an index that is valid for the data[] array but greater than numElements, the last element was placed at that index, and numElements was decreased. This seems like an error in the way ArraySet was implemented.


## Profiling
I performed two similar experiments to confirm that the heuristic showed improvements. I kept the setup the same and added a for loop in the experiment body that, in the first experiment, checked if the set had 0 for 500 iterations. In the second experiment, it checked for 0 and 1 for 500 iterations. 
In both experiments, moveToFront outperformed linkedSet and transposeSequence outperformed arraySet, with the former outperforming by a larger margin in both cases. This was expected because both heuristics work best when an element is accessed frequently, 0 and 1 in my case.
I ran a third experiment where I limited the number of items in the data to 500 in the setup() method and kept the 500 iterations of checking for 0 and 1. Once again, the heuristics outperformed their respective sets. 
