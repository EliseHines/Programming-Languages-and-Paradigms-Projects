Name: Robert Hines
--------

How to run the code:

Run the code by using the call syntax given by the pdf:
python3 topkword "input=input.txt;k=2;output=topwords.txt"

--------
A brief description of how you implement the program. How the recursion works. etc.

1. Get the entire input file into one string
2. Remove all words that contain a digit, using regex functions
3. Remove all captalization from the string
4. Remove the punctuation from words
5. Split all the words using str.split() to make a list of all words
6. Create a new list of unique words and another list with the frequencies of the list
7. Call a recursive function to calculate the kth words
 - Used if k <= 0 as the base case 
 - For every iteration
	- find the max number in the frequency
	- if the frequency of the word you are on is the max frequency, print out that word
	- if it isnt, add it to a temp array
 - pass this temp array of all the words that wasnt the max for this iteration to the next recursive call
 - this happens k amount of times
------

4. Please disclose the source(book, link) inside your code if that part of the code is not yours! It will help you to avoid plagiarism. 
Used regex functions from stack overflow because i dont know python very well