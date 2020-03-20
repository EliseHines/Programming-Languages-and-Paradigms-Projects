import argparse, string



"""READ MEEE
To do list:
 - fix the while loop at the bottom
    - this loop is to compute frequencies. we need to make it recursive and remove mutation bits
 - make selection sort not have mutation
 - change mostFreq and leastFreq to not have iteration
    - make sure that most and leastFreq dont have mutation
        - ****i didnt check if they had mutation or not, i just copied and pasted the code from hw1


READ MEEE"""

#Since mutation is not allowed, custom insert function to return a new list
def add(str, list):
    return list + [str]

def isStop(stop, wordCopy):
    for i in range(len(stop)):
        if(wordCopy == stop[i]):
            return True
    	
    return False

def minIndex(freq, word, i, j):
    if i == j:
        return i
    k = minIndex(freq,word,i+1,j)
    if freq[k] < freq[i]:
        return k
    elif (freq[k] > freq[i]):
        return i
    elif (word[k] < word[i]):
        return k
    else:
        return i

def maxIndex(freq, word, i, j):
    if i == j:
        return i
    k = maxIndex(freq,word,i+1,j)
    if freq[k] > freq[i]:
        return k
    elif (freq[k] < freq[i]):
        return i
    elif (word[k] < word[i]):
        return k
    else:
        return i

def recurSelectionSort(a, b, n, key, index = 0):
    if index == n:
        return -1

    if key[1] == 'Y':
        k = maxIndex(b, a, index, n-1)
    else:
        k = minIndex(b, a, index, n-1)

    if k != index:
        a[k], a[index] = a[index], a[k]
        b[k], b[index] = b[index], b[k]

    recurSelectionSort(a,b,n,key,index+1)

#A is a list that is going to contain all the valid words
a = []
def addWords(i, contents):
    if(i == len(contents)):
        return a;
    else:
        if(((contents[i].isdigit() == True) | (contents[i].isalpha() == True))):
            add(contents[i], a)
        addWords(i+1, contents)

#Reusing code from hw1, idk if this mutates at all (brain isnt awake)
#This function is for most frequent k
def mostFreq(k, finalWords, finalFreq, f):
    if(k <= 0):
        return
    else:
        if len(finalFreq) != 0:
            localMax = max(finalFreq)
        tempWord = []
        tempFreq = []
        
        for word in range(len(finalWords)):
            if(finalFreq[word] == localMax):
                f.write(finalWords[word])
                f.write(" ")
                f.write(str(finalFreq[word]))
                f.write('\n')
            else:
                tempWord.append(finalWords[word])
                tempFreq.append(finalFreq[word])
        mostFreq(k - 1, tempWord, tempFreq, f)

#This function is for least frequent k
def leastFreq(k, finalWords, finalFreq, f):
    if(k <= 0):
        return
    else:
        if len(finalFreq) != 0:
            localMin = min(finalFreq)
        tempWord = []
        tempFreq = []

        for word in range(len(finalWords)):
            if(finalFreq[word] == localMin):
                f.write(finalWords[word])
                f.write(" ")
                f.write(str(finalFreq[word]))
                f.write('\n')
            else:
                tempWord.append(finalWords[word])
                tempFreq.append(finalFreq[word])
        leastFreq(k - 1, tempWord, tempFreq, f)

#Getting Command Line Arguments
parser = argparse.ArgumentParser()
parser.add_argument("string")
args = parser.parse_args()
#Error if empty
if not args:
    print("Error, not valid call synax. Follow syntax as below:")
    print("python3 keyword.py \"input=input.txt;k=2;mostfrequent=Y;uppercase=N;output=topwords.txt\" ")
    exit()
x = args.string.split(";")
inputname = x[0].split("input=")
inputname = inputname[1]
outputname = x[4].split("output=")
outputname = outputname[1]
k = x[1].split("k=")
k = k[1]
k = int(k)
key = x[2].split("mostfrequent=")
uppercasee = x[3].split("uppercase=")

#Input File, add to list
i = open(inputname,"r+")
contents = i.read()
if not contents:
    print("Empty file, need words in file")
    exit()
i.close()
#We now have a list of all the words

ii = open("stopwords.txt", "r+")
stopwords = ii.read()
stop = stopwords.split()
i.close()

#Dont add expression with numbers in it
#Exclude punctuation
#No caps
#Can't be in stopwords.txt
#Then take care of caps, TA says this doesnt mutate


#We need to make sure that we dont add an expression with numbers to the final list
#Exclude puncutation, idk if this counts as mutation
#If it does, create another function to fix this
exclude = set(string.punctuation)
contents = ''.join(ch for ch in contents if ch not in exclude)
contents = contents.lower()


#TA says split doesnt mutate
allWords = contents.split()
allWords = [x for x in allWords if not any(c.isdigit() for c in x)]

tempWords = []
for i in range(len(allWords)):
    if(isStop(stop, allWords[i]) == False):
         tempWords = add(allWords[i], tempWords)
allWords = tempWords
if(uppercasee[1] == 'Y'):
    allWords = [x.upper() for x in allWords]




#allWords should be a list of all valid words
finalWords = []
finalFreq = []
z=0
#Compute frequency of all the words
#This was copy and pasted from hw1, needs to be changed so no mutation and recursive
while len(allWords) is not 0:
    tempList = []
    wordCopy = allWords[0]
    finalWords = add(wordCopy, finalWords)
    finalFreq = add(0, finalFreq) 

    for j in range(len(allWords)):
        if allWords[j] == wordCopy:
            finalFreq[z] = finalFreq[z] + 1
        else:
            tempList.append(allWords[j])
    z = z+1
    allWords = tempList


#Output the final recursive function call for most or least k words\
recurSelectionSort(finalWords, finalFreq, len(finalWords), key)
f = open(outputname, "w+")
if(key[1] == 'Y'):
    mostFreq(k,finalWords, finalFreq, f)
else:
    leastFreq(k, finalWords, finalFreq, f)

f.close()