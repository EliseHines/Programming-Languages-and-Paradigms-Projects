#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

struct intList {
	string name;
	int arr[20] = { 0 };
};

struct strList {
	string name;
	string arr[20] = { "" };
};

struct intt {
	string name;
	int value;
};

struct stringg {
	string name;
	string value;
};

//Function to see if there is an assignment operator
bool checkEqual(string s) {
	for (int i = 0; i < s.length(); i++) {
		if (s[i] == '=' && s[i + 1] != '=') return true;
	}
	return false;
}

void printIntList(vector<intList> lst, string var, ofstream &outputFile, int index = 0, int element = -2)
{
	int i = 0;
	bool found = false;

	for (auto &x : lst)
	{
		if (x.name == var)
		{

			found = true;
            if (element != -2)
				{
					outputFile << ">>>" << x.arr[element] << endl;
					break;
				}
			outputFile << ">>>[";
			for (int arrSize = 0; arrSize < 20; arrSize++)
			{

				
				outputFile << x.arr[index];

				i++;
				// used for index slicing
				index++;
				if (x.arr[index] == 0 || index > 20)
				{
					break;
				}
				outputFile << ",";
			}
			outputFile << "]" << endl;


		}
	}
}

void printStrList(vector<strList> lst, string var, ofstream &outputFile, int index = 0, int elem = -2)
{
	int i = 0;
	bool found = false;
	for (auto &x : lst)
	{
		if (x.name == var)
		{

			found = true;
            if (elem != -2)
				{
					outputFile << ">>>" << x.arr[elem] << endl;
					break;
				}
                
			outputFile << ">>>[";
			for (int arrSize = 0; arrSize < 20; arrSize++)
			{
			

				outputFile << "\'" << x.arr[index] << "\'";

				i++;
				// used for index slicing
				index++;
				if (x.arr[index] == "" || index > 20)
				{
					break;
				}
				outputFile << ",";
			}
			outputFile << "]" << endl;


		}
	}
}

void findAndPrintString(string line, vector<strList> lst, ofstream &outputFile)
{

	size_t found = line.find("print(");
	if (found != string::npos)
	{
		string printLine = line.substr(found);
		size_t parenth = printLine.find("(");
		size_t parenthEnd = printLine.find(")");
		if (parenth != string::npos && parenthEnd != string::npos)
		{
			size_t paramSize = parenthEnd - parenth;
			string parameters = printLine.substr(parenth + 1, paramSize - 1);
			size_t findIndex = parameters.find("[");
			size_t findSlice = parameters.find(":");

			if (findIndex != string::npos)
			{
				if (findSlice != string::npos)
				{
					//index slicing 
					string slicedIndex = parameters.substr(findIndex + 1, 1);
					//outputFile << slicedIndex << endl;
					int indx = stoi(slicedIndex);
					string slicedParameters = parameters.substr(0, findIndex);
					//outputFile << slicedParameters;

					printStrList(lst, slicedParameters, outputFile, indx);
				}
				else
				{
					//index slicing 
					string slicedIndex = parameters.substr(findIndex + 1, 1);
					// outputFile << slicedIndex << endl;
					int indx = stoi(slicedIndex);
					string slicedParameters = parameters.substr(0, findIndex);
					//outputFile << slicedParameters;
					printStrList(lst, slicedParameters, outputFile, 0, indx);
				}
			}
			else
			{

				printStrList(lst, parameters, outputFile);
			}
		}


	}

}



void findAndPrintInts(string line, vector<intList> lst, ofstream &outputFile)
{

	size_t found = line.find("print(");
	if (found != string::npos)
	{
		string printLine = line.substr(found);
		size_t parenth = printLine.find("(");
		size_t parenthEnd = printLine.find(")");
		if (parenth != string::npos && parenthEnd != string::npos)
		{
			size_t paramSize = parenthEnd - parenth;
			string parameters = printLine.substr(parenth + 1, paramSize - 1);
			size_t findIndex = parameters.find("[");
			size_t findSlice = parameters.find(":");
			if (findIndex != string::npos)
			{
				if (findSlice != string::npos)
				{

					//index slicing 
					string slicedIndex = parameters.substr(findIndex + 1, 1);
					// outputFile << slicedIndex << endl;
					int indx = stoi(slicedIndex);
					string slicedParameters = parameters.substr(0, findIndex);
					//outputFile << slicedParameters;
					printIntList(lst, slicedParameters, outputFile, indx);
				}
				else
				{
					//index slicing 
					string slicedIndex = parameters.substr(findIndex + 1, 1);
					// outputFile << slicedIndex << endl;
					int indx = stoi(slicedIndex);
					string slicedParameters = parameters.substr(0, findIndex);
					//outputFile << slicedParameters;
					printIntList(lst, slicedParameters, outputFile, 0, indx);
				}

			}

			else
			{

				printIntList(lst, parameters, outputFile);
			}
		}


	}

}

int main(int argc, char** argv) {
	//Open input and output
	string pls = argv[1];
	string inputName = pls.substr(pls.find("=") + 1);
	ifstream inputFile(inputName.c_str());
	if (!inputFile.is_open()) return -1;

	string outputname = inputName.substr(0, inputName.find('.')) + ".out";
	ofstream outputFile(outputname.c_str());
	if (!outputFile.is_open()) return -1;

	intList allIntLists[10];
	int currInt = 0;
	strList allStringLists[10];
	int currStr = 0;
	intt allInts[10];
	int currint = 0;
	stringg allStrings[10];
	int currstr = 0;

	vector<intList> intLst;
	vector<strList> strLst;

	string first, tempLine;
	while (getline(inputFile, first)) {
		//Ignore comments
		if (first[0] == '#') {
			outputFile << tempLine << endl;
			continue;
		}
		tempLine = "";
		//Erase all whitespace
		for (int i = 0; i < first.length(); i++) {
			if (first[i] != ' ') {
				tempLine += first[i];
			}
		}

		if (checkEqual(tempLine)) {
			string name = tempLine.substr(0, tempLine.find('='));
			int place = tempLine.find("=") + 1;
			int tc = 0;
			string dataType = "";
			bool error = false;
			bool variable = false;
			string tempValue;

			for (int i = place; i < tempLine.length(); i++) {
				char ns;
				if (i != tempLine.length() - 1)
					ns = tempLine[i + 1];
				else
				{
					ns = '\0';

				}

				switch (tc) {
				case 0: //Entry point, Expected character should be "["
					if (tempLine[i] == '[') {
						if (isdigit(ns)) {
							tc = 1;
							dataType = "int";
						}
						else if (ns == '\'' || ns == '\"') {
							tc = 3;
							dataType = "string";
						}
						else if (isalpha(ns)) {
							tc = 13;
						}
					}
					else if (isalpha(tempLine[i])) {
						tempValue = tempLine[i];
						tc = 7;
						if (ns == '\0') {
							int k = -1;
							if (dataType == "") {

								for (k = 0; k < 10; k++) {
									if (tempValue == allStringLists[k].name) {
										dataType = "string";
										break;
									}
									if (tempValue == allIntLists[k].name) {
										dataType = "int";
										break;
									}

								}
							}


							if (dataType == "int") {
								//first find where its supposed to be 
								//then add every element from that position
								//k is the position of allxLists that we are searching for to add to the current list
								if (k == -1) {
									for (k = 0; k < currInt; k++) {
										if (tempValue == allIntLists[k].name) {
											break;
										}
									}
								}
								int j;
								for (j = 0; j < 20; j++) {
									if (allIntLists[k].arr[j] == 0) {
										break;
									}

								}
								int l = 0;
								for (int i = 0; i < 20; i++) {
									if ((i + j <= 20) && allIntLists[currInt].arr[i] == 0 && l <= j) {
										allIntLists[currInt].arr[i] = allIntLists[k].arr[l++];
									}
								}
							}
							else if (dataType == "string") {
								//first find where its supposed to be 
								//then add every element from that position
								//k is the position of allxLists that we are searching for to add to the current list
								if (k == -1) {
									for (k = 0; k < currStr; k++) {
										if (tempValue == allStringLists[k].name) {
											break;
										}
									}
								}
								int j;
								for (j = 0; j < 20; j++) {
									if (allStringLists[k].arr[j] == "") {
										break;
									}

								}
								int l = 0;
								for (int i = 0; i < 20; i++) {
									if ((i + j <= 20) && allStringLists[currStr].arr[i] == "" && l <= j) {
										allStringLists[currStr].arr[i] = allStringLists[k].arr[l++];
									}
								}
							}
							else {
								outputFile << "#error" << endl;
								error = true;
								tc = 4;
							}
						}
					}
					else if (isdigit(tempLine[i])) {
						tempValue += tempLine[i];
						tc = 11;
						dataType = "int";
						variable = true;
						if (i == tempLine.length() - 1) {

							allInts[currint].value = stoi(tempValue);
						}
					}
					else if (tempLine[i] == '\'' || tempLine[i] == '\"') {
						tc = 12;
						dataType = "string";
						variable = true;
					}
					break;
				case 1: //Entry was "[" and the next character is a int 
					if (dataType == "int") {
						tempValue += tempLine[i];
					}
					else {
						outputFile << "#error" << endl;
						error = true;
						tc = 4;
					}
					//test next letter and assign tc

					if (ns == ']') {
						tc = 2;
					}
					else if (isdigit(ns)) {
						tc = 1;
					}
					else if (ns == ',') {
						tc = 5;
					}
					else {
						outputFile << "#error" << endl;
						error = true;
						tc = 4;
					}
					break;
				case 2: //Closing point, expecting "]"

					if (dataType == "int") {

						for (int j = 0; j < 20; j++) {
							if (allIntLists[currInt].arr[j] == 0) {
								allIntLists[currInt].arr[j] = stoi(tempValue);
								tempValue = "";
								break;
							}
						}
					}

					if (ns != '\0') {
						if (ns == '+') {
							tc = 6;
						}
						else {
							outputFile << "#error" << endl;
							error = true;
							tc = 4;
						}
					}
					break;
				case 3://string case, tempLine[i] == '\''
					if (ns == '\'' || ns == '\"') {
						tc = 4;
						outputFile << "#error" << endl;
						error = true;
					}
					else {
						tc = 8;
					}
					break;
				case 4: //there is an error, continue to be here
					tc = 4;
					break;
				case 5: //int expecting comma
					for (int j = 0; j < 20; j++) {
						if (allIntLists[currInt].arr[j] == 0) {
							allIntLists[currInt].arr[j] = stoi(tempValue);
							tempValue = "";
							break;
						}
					}
					if (isdigit(ns)) {
						tc = 1;
					}
					else {
						outputFile << "#error" << endl;
						error = true;
						tc = 4;
					}
					break;
				case 6:
					tc = 0;
					break;
				case 7: //tempLine[i] is an alpha character
					if (i == tempLine.length() - 1) {
						int k = -1;
						tempValue += tempLine[i];

						if (dataType == "") {

							for (k = 0; k < 10; k++) {
								if (tempValue == allStringLists[k].name) {
									dataType = "string";
									break;
								}
								if (tempValue == allIntLists[k].name) {
									dataType = "int";
									break;
								}

							}
						}


						if (dataType == "int") {
							//first find where its supposed to be 
							//then add every element from that position
							//k is the position of allxLists that we are searching for to add to the current list
							if (k == -1) {
								for (k = 0; k < currInt; k++) {
									if (tempValue == allIntLists[k].name) {
										break;
									}
								}
							}
							int j;
							for (j = 0; j < 20; j++) {
								if (allIntLists[k].arr[j] == 0) {
									break;
								}

							}
							int l = 0;
							for (int i = 0; i < 20; i++) {
								if ((i + j <= 20) && allIntLists[currInt].arr[i] == 0 && l <= j) {
									allIntLists[currInt].arr[i] = allIntLists[k].arr[l++];
								}
							}
						}
						else if (dataType == "string") {
							//first find where its supposed to be 
							//then add every element from that position
							//k is the position of allxLists that we are searching for to add to the current list
							if (k == -1) {
								for (k = 0; k < currStr; k++) {
									if (tempValue == allStringLists[k].name) {
										break;
									}
								}
							}
							int j;
							for (j = 0; j < 20; j++) {
								if (allStringLists[k].arr[j] == "") {
									break;
								}

							}
							int l = 0;
							for (int i = 0; i < 20; i++) {
								if ((i + j <= 20) && allStringLists[currStr].arr[i] == "" && l <= j) {
									allStringLists[currStr].arr[i] = allStringLists[k].arr[l++];
								}
							}
						}
						else {
							outputFile << "#error" << endl;
							error = true;
							tc = 4;
						}
					}
					else if (isalnum(tempLine[i])) {
						tempValue += tempLine[i];
						tc = 7;
					}
					else if (tempLine[i] == '+') {
						int k = -1;
						if (dataType == "") {

							for (k = 0; k < 10; k++) {
								if (tempValue == allStringLists[k].name) {
									dataType = "string";
									break;
								}
								if (tempValue == allIntLists[k].name) {
									dataType = "int";
									break;
								}

							}
						}


						if (dataType == "int") {
							//first find where its supposed to be 
							//then add every element from that position
							//k is the position of allxLists that we are searching for to add to the current list
							if (k == -1) {
								for (k = 0; k < currInt; k++) {
									if (tempValue == allIntLists[k].name) {
										break;
									}
								}
							}
							int j;
							for (j = 0; j < 20; j++) {
								if (allIntLists[k].arr[j] == 0) {
									break;
								}

							}
							int l = 0;
							for (int i = 0; i < 20; i++) {
								if ((i + j <= 20) && allIntLists[currInt].arr[i] == 0 && l <= j) {
									allIntLists[currInt].arr[i] = allIntLists[k].arr[l++];
								}
							}
						}
						else if (dataType == "string") {
							//first find where its supposed to be 
							//then add every element from that position
							//k is the position of allxLists that we are searching for to add to the current list
							if (k == -1) {
								for (k = 0; k < currStr; k++) {
									if (tempValue == allStringLists[k].name) {
										break;
									}
								}
							}
							int j;
							for (j = 0; j < 20; j++) {
								if (allStringLists[k].arr[j] == "") {
									break;
								}

							}
							int l = 0;
							for (int i = 0; i < 20; i++) {
								if ((i + j <= 20) && allStringLists[currStr].arr[i] == "" && l <= j) {
									allStringLists[currStr].arr[i] = allStringLists[k].arr[l++];
								}
							}
						}
						else {
							outputFile << "#error" << endl;
							error = true;
							tc = 4;
						}

						tc = 0;
						tempValue = "";
					} //end



					break;
				case 8: //coming from case 3, tempLine[i] was open string, this should 
					if (tempLine[i] == '\'' || tempLine[i] == '\"') {
						//add string to data and reset tempValue
						for (int j = 0; j < 20; j++) {
							if (allStringLists[currStr].arr[j] == "") {
								allStringLists[currStr].arr[j] = tempValue;
								tempValue = "";
								break;
							}
						}
						tc = 9;
					}
					else {
						tempValue += tempLine[i];
						tc = 8;
					}
					break;
				case 9: //tempLine[i] == '\'', expecting either close bracket or comma for more string
					if (tempLine[i] == ',')
						tc = 3;
					else if (tempLine[i] == ']' && ns == '+')
						tc = 10;
					else
						tc = 4;
					break;
				case 10: //come from case 9 to buffer, this should either be a comma into case 3, or a ] followed either by nothing or a +
					tc = 0;
					break;

				case 11:
					tc = 11;
					tempValue += tempLine[i];
					if (i == tempLine.length() - 1) {
						allInts[currint].value = stoi(tempValue);
					}


					break;

				case 12:
					if (tempLine[i] != '\'' && tempLine[i] != '\"') {
						tc = 12;
						tempValue += tempLine[i];
					}
					else {
						allStrings[currstr].value = tempValue;
						tempValue = "";
					}
					break;
				case 13:
					if (tempLine[i] == ']') {


						int k = 0, l = 0;
						for (k; k < currint; k++) {
							if (tempValue == allInts[k].name)
							{
								dataType = "int";
								break;
							}

						}

						for (l; l < currstr; l++) {
							if (tempValue == allStrings[l].name)
							{
								dataType = "string";
								break;
							}

						}

						if (dataType == "int") {

							tempValue = to_string(allInts[k].value);


							for (int j = 0; j < 20; j++) {
								if (allIntLists[currInt].arr[j] == 0) {
									allIntLists[currInt].arr[j] = stoi(tempValue);
									tempValue = "";
									break;
								}
							}

						}
						else {

							tempValue = allStrings[l].value;
							for (int j = 0; j < 20; j++) {
								if (allStringLists[currStr].arr[j] == "") {
									allStringLists[currStr].arr[j] = tempValue;
									tempValue = "";
									break;
								}
							}

						}
						tc = 10;
					}
					else {
						tempValue += tempLine[i];

					}
					break;


				}
			}
			outputFile << tempLine << endl;
			if (!error && !variable) {
				if (dataType == "int") {
					allIntLists[currInt].name = name;
					intLst.push_back(allIntLists[currInt]);
					currInt++;

				}
				else if (dataType == "string") {
					allStringLists[currStr].name = name;
					strLst.push_back(allStringLists[currStr]);
					currStr++;
				}
			}
			else if (variable) {
				if (dataType == "int") {
					allInts[currint].name = name;
					currint++;
				}
				else if (dataType == "string") {
					allStrings[currstr].name = name;
					currstr++;
				}
			}
			else {
				if (dataType == "int") {

				}
				else if (dataType == "string") {

				}
			}
		}//end of assignment operator

		if (tempLine.find("print") != string::npos) {
			outputFile << tempLine << endl;
			findAndPrintInts(tempLine, intLst, outputFile);
			findAndPrintString(tempLine, strLst, outputFile);
		}
	}


	/*
	for (int i = 0; i < currInt; i++) {
		outputFile << "Name: " << allIntLists[i].name << endl;
		for (int j = 0; j < 20; j++) {
			if (allIntLists[i].arr[j] != 0)
				outputFile << "Data at " << j << ": " << allIntLists[i].arr[j] << endl;
		}

	}

	for (int i = 0; i < currStr; i++) {
		outputFile << "Name: " << allStringLists[i].name << endl;
		for (int j = 0; j < 20; j++) {
			if (allStringLists[i].arr[j] != "")
				outputFile << "Data at " << j << ": " << allStringLists[i].arr[j] << endl;
		}

	}*/

   
	inputFile.close();
	outputFile.close();

	return 0;
}