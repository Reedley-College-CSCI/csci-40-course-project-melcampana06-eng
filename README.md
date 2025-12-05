
# CS1 Final Project - [Book Log]

## 1. Overview

The program solves the problem of keeping track of the books a user has read. It makes it easier to search and revisit them.

This program is takes in the title of the users current read, along with the name of the author (first and last), the genre of the book, and the rating the user would give the book (using the 5 point system). The user can also choose to add a written review of the book. From there the user can revisit old book log entry's by entering the books title or they may also rewrite an old entry.

---

## 2. Design Decisions

I used the basic data types, such as strings and ints, along with a struct called bookData.

I chose to use structs because of their simplicity and usefulness. I can access all variables in the struct by using one object. 

I implemented Sorting by having an unsorted file and a sorted file. First I prompted the user for the needed information, then i put all that information went into the unsorted file. Then I moved the information from a file into an array and called a bubble Sort function to sort them alphabetically. Then I streamed the sorted array into the sorted file. I implemented searching by prompting the user for which title they where looking for. I then compared that with the first part of the line in the sorted fine, which was the title of the book. If they matched then it would call a function that got the rest of the parts withing the line and separated them into their correct variables. The information would then be printed for the user.

I implemented data persistence by using ios::app when first declaring an output file. This enables me to retain file information between runs.

An alternate approach I did consider was that instead of putting all my information in only two files, I could have spread my information into multiple files. Specifically, one file per category (meaning genre would have a file, title would have a file, etc.), and I access the information by relying on the index. I didn't end up using this because I though it would take too many files and it could get confusing really quickly, so I went with my current method for simplicities sake.

---

## 3. Testing Summary

Test Cast ID  |     Input              |  Expected Output           |  Actual Output                                     |  Pass/Fail 
--------------------------------------------------------------------------------------------------------------------------------------
   TC-01      |  a                     |		                    |                                                    |
              |  Percy Jackson         |                            |  welcome to your book log!                         | 
   Normal     |  Rick Riordan          |                            |                                                    |
              |  Fantasy               | [Show Menu again]	        |  if you want to add a new entry, enter 'a'         |    Pass
              |  5	                   |                            |  if you want to search for an old entry, enter 'b' |
              |  y                     |                            |  if you want edit a past entry, enter 'c'	         |
              |  Great Book            |                            |  if you want to exit, enter 'd'	                 |        	
----------------------------------------------------------------------------------------------------------------------------------------
   TC-02      |  b                     | Title: Percy Jackson       | Title: Percy Jackson                               |
              |  Percy Jackson         | Author: Rick Riordan       | Author: Rick Riordan                               |
 Data         |                        | Genre: Fantasy             | Genre: Fantasy                                     |
 Persistence  |                        | Rating: 5/5	    	    | Rating: 5/5                                        |  
              |                        | Review: Great Book         | Review: Great Book                                 |
              |                        |                            |                                                    |  Pass
              |                        |                            | welcome to your book log!                          |
              |			               | [Shows Menu again]         | if you want to add a new entry, enter 'a'          |
              |                        |                            | if you want to search for an old entry, enter 'b'  |
              |                        |                            | if you want edit a past entry, enter 'c'           |
              |                        |                            | if you want to exit, enter 'd'                     |
------------------------------------------------------------------------------------------------------------------------------------------
   TC-03      |  c                     |                             |                                                   |
              |  Percy Jackson         | Entry updated successfully. | Entry updated successfully.                       |
 Searching    |                        | [Shows Menu again]          | welcome to your book log!                         |
              |  The Lightning Theft   |                             | if you want to add a new entry, enter 'a'         | 
              |  Rick Riordan          |              		         | if you want to search for an old entry, enter 'b' |  Pass
              |  Fantasy               |                             | if you want edit a past entry, enter 'c'          |
              |  5                     |                             | if you want to exit, enter 'd'                    | 
              |  Amazing Book          |                             |                                                   |
-------------------------------------------------------------------------------------------------------------------------------------------
   TC-04      |  a                     |		                    |                                                    |
              |  The Hunger Games      |(invalid input, try again)  | (invalid input, try again)                         |
              |  Suzanne Collins       | [Shows review prompt again]|  welcome to your book log!                         |
  Invalid     |  Dystopian             | [Show Menu again]	        |  if you want to add a new entry, enter 'a'         |   Pass
  Input       |  5	                   |                            |  if you want to search for an old entry, enter 'b' |
              |  j                     |                            |  if you want edit a past entry, enter 'c'          |
              |  n                     |                            | if you want to exit, enter 'd'	            	 |
-------------------------------------------------------------------------------------------------------------------------------------------
 TC-05        |  d                     |		                    |                                                    |
   End        |                        |     [Program Ends]         |  Program Ended                                     |  Pass
   Program    |                        | 	                        |          	                                         |  
--------------------------------------------------------------------------------------------------------------------------------------------



---

## 4. Technical Walkthrough

link: https://youtu.be/UyeaKSrhGk8

---

## 5. Challenges and Lessons Learned

One of the biggest challenges I had while creating my program, was figuring out how I was going to split the one file line of information per book into it appropriate parts. After tinkering with this problem for a while, I ended up implementing the getPart() function. Which basically gets everything from then end of the last three spaces ("   ") to the end of the next including the spaces. The parameters line and index are used for this, line is the given file line we are working with and each index represent the start of each information part. For example, index 0 is at the start of the book name in the file, index 1 is at the start of the author name in the file, index 2 is at the start of the books genre in the file, etc.

From this experience I learned that it is very important to keep testing as you tweak and add parts of your code. Especially important to use different inputs from time to time to test how your program will react. Before adding the getPart() function, the program was only printing out the first line of information in the file. I didn't realize because i kept using that same book to test it, it wasn't until I switched to something different that i noticed the issue.

---

## 6. Future Improvements

If i had more time to work on this I may try to implement the multiped files, as well as adding a dynamically allocated array instead of just having a static one. I would also have more safety measures to ensure my program runs as intended. For example, I would make sure that the rating for the book could only be a number between 1 and 5. One thing I would also definitely fix is my space sensitive data. I used three spaces ("   ") to separate each piece of data from the other in the files, how ever I could see how this could very easily be broken by a faulty input. Furthermore, I can see how more features can be added to this code, like the ability to see all the past entries without changing them, that I would likely explore if I could.


