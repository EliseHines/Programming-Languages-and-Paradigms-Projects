import argparse, re, string

#Recursive function that finds the kth most used words
def recFunc(k, finalWords, finalFreq, f):
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
        recFunc(k - 1, tempWord, tempFreq, f)

#Getting Command Line Arguments
parser = argparse.ArgumentParser()
parser.add_argument("string")
args = parser.parse_args()
#Error if empty
if not args:
    print("Error, not valid call synax. Follow syntax as below:")
    print("python3 topkword \"input=input.txt;k=2;output=topwords.txt\" ")
    exit()
x = args.string.split(";")
inputname = x[0].split("input=")
inputname = inputname[1]
outputname = x[2].split("output=")
outputname = outputname[1]
k = x[1].split("k=")
k = k[1]
k = int(k)

#Input File, add to list
i = open(inputname,"r+")
contents = i.read()
if not contents:
    print("Empty file, need words in file")
    exit()
i.close()

#We now have a list of all the words
#Now we need to remove punctuation, numbers, and caps

#Remove words that contain numbers
contents = re.sub("\S*\d\S*", "", contents).strip()

#Remove all caps
contents = contents.lower()

#Remove all punctuation
exclude = set(string.punctuation)
contents = ''.join(ch for ch in contents if ch not in exclude)

#Make it into a list
allWords = contents.split()

#All strings in allWords are correct
#We need to compute frequency of all the words
finalWords = []
finalFreq = []
z = 0
while len(allWords) is not 0:
    tempList = []
    wordCopy = allWords[0]
    finalWords.append(wordCopy)
    finalFreq.append(0)
    for j in range(len(allWords)):
        if allWords[j] == wordCopy:
            finalFreq[z] = finalFreq[z] + 1
        else:
            tempList.append(allWords[j])
    z = z+1
    allWords = tempList

#We need to call a recursive function to print the top k words
f = open(outputname, "w+");
recFunc(k, finalWords, finalFreq, f)
f.close()





