#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

using namespace std;

struct node{
  string dataType;
  string name;
};

//Test if an input is an integer or a string
string checkType(string s){
  for(int i = 0; i < s.length(); i++){
    if(isdigit(s[i])){
        return "int";
    }else if(s[i] == '\"'){
      return "string";
    }
  }
return "";
}

//Check if a line has an assignment but not ==
bool checkEqual(string s){
  for(int i = 0; i < s.length(); i++){
    if(s[i] == '=' && s[i+1] != '=') return true;
  }
  return false;
}

//Check if a line has an operator or not
bool hasOperator(string s){
  for(int i = 0; i < s.length(); i++){
    if(s[i] == '+' || s[i] == '*') return true;
  }
  return false;
}

string isLegal(node *arr, string temp, int c){
  string dataType = "";
  string variable;
  for(int i = 0; i < temp.length(); i++){
    if(temp[i] == '[') return "list";
  }
  for(int i = 0; i < temp.length(); i++){
    if(temp[i] == '+' || temp[i] == '*'){
      bool flag = false;
      for(int j = 0; j < c; j++){
        if(arr[j].name == variable){
          flag = true;
          dataType = arr[j].dataType;
          break;
        }
      }

      if(!flag) dataType = checkType(variable);

      if(temp[i] == '*' && dataType == "string"){
        return "#error";
      }
      //If it already exists then check if its valid
      flag = false;
      for(int j = 0; j < c; j++){
        if(arr[j].name == variable){
          if(dataType != "" && dataType != arr[j].dataType){
            return "#error";
          }else if(dataType == arr[j].dataType){
            flag = true;
            break;
          }
        }
      }
      if(flag){
      variable = "";
      continue;
      } 
     // cout << variable << " " << checkType(variable) << endl;
      //If it doesnt exist, then test its dataType
      if(checkType(variable) == dataType && dataType != ""){
        variable = "";
        continue;
      }else if(dataType == ""){
        dataType = checkType(variable);
      }else{
        return "#error";
      }
      variable = "";
    }else if(temp[i] != '+' || temp[i] != '*'){
      if(!isspace(temp[i])) variable += temp[i];

      if(i == (temp.length()-1)){
        for(int j = 0; j < c; j++){
        if(arr[j].name == variable){
          if(dataType != "" && dataType != arr[j].dataType){
            return "#error";
          }else if(dataType == arr[j].dataType){
            continue;
          }
        }
      }
      //If it doesnt exist, then test its dataType
      if(checkType(variable) == dataType && dataType != ""){
        continue;
      }else if(dataType == ""){
        dataType = checkType(variable);
      }else{
        return "#error";
      }
      }
    }
 
  }
    //cout << "im here";
return dataType;
}






int main(int argc, char** argv) {
 //Open input and output
 ifstream inputFile(argv[1]);
 if(!inputFile.is_open()) return -1;
 string pls = argv[1];
 string outputname = pls.substr(0, pls.find('.')) + ".out";
 ofstream outputFile(outputname.c_str());
 if(!outputFile.is_open()) return -1;
 
 //Input parse and output
 node data[100]; //To hold all variables and their data types
 int currData = 0; //Number correlates to how many variables 
 string tempLine; //tempLine containts the entire line that we work on
 bool ifFlag = false;
 int scope = 0;

 while(getline(inputFile, tempLine)){ //Line by line
  if(tempLine[0] == '#') { //Ignore comments, output the line onto output
    outputFile << tempLine << endl;
    continue;
  }

  //If it has an equal sign, its an assignment
  if(checkEqual(tempLine)){
    if(currData == 0){
      //Assuming valid code, the very first assignment can be assumed to be correct
      string temp = tempLine.substr(0,tempLine.find('='));
      for(int j = 0; j < temp.length(); j++){
        if(temp[j] == ' '){
          temp.erase(j);
          j--;
        }
      }
      
      string temp1 = tempLine.substr(tempLine.find('=')+1);
      string check = isLegal(data, temp1, currData);
      if(check == "#error"){
        outputFile << check << endl;
      }else{
        data[0].name = temp;
        data[0].dataType = check;
        currData++;
      }
       outputFile << tempLine << endl;
      continue;
    }else{
       string temp = tempLine.substr(0,tempLine.find('='));
       
       for(int j = 0; j < temp.length(); j++){
        if(temp[j] == ' '){
          temp.erase(j);
          j--;
        }
      }
      bool flag = false;
      int i;
      for(i = 0; i <currData; i++){
        if(data[i].name == temp){
          flag = true;
          break;
        }
      } //Does this name already exist or not

      if(hasOperator(tempLine)){
        string temp1 = tempLine.substr(tempLine.find('=')+1);
        string check = isLegal(data, temp1, currData);
        if(check != "#error"){
          if(flag == true){
            if(data[i].dataType != check){
              outputFile << "#warning" << endl;
              data[i].dataType = check;
              outputFile << tempLine << endl;
              continue;
            }
          }
          data[currData].name = temp;
          data[currData].dataType = check;
          outputFile << tempLine << endl;
          currData++;
          continue;
        }else{
          outputFile << "#error" << endl;
          outputFile << tempLine << endl;
          continue;
        }
      }else{
      if(flag == true){
        temp = tempLine.substr(tempLine.find('=')+1);
        if(checkType(temp) != data[i].dataType){
        outputFile << "#warning" << endl;
        }
        data[i].dataType = checkType(temp);
        outputFile << tempLine << endl;
        continue;
      }else{
        data[currData].name = temp;
        temp = tempLine.substr(tempLine.find('=')+1);
        data[currData].dataType = isLegal(data, temp, currData);
        currData++;
        outputFile << tempLine << endl;
      }//End of else for if an assignment with no operator exists or not
    } //End of else for if the assignment has an operator
    } //End of else statement for if currData != 0
  }else if(tempLine.find('.')){
    
    if(tempLine.find(".insert") != std::string::npos){
      string temp = tempLine.substr(tempLine.find(',')+1);
      temp.erase(temp.length()); //erase the ) at the end
      
      string dt = checkType(temp);
      temp = tempLine.substr(0, tempLine.find('.'));
      bool flag = false;
      for(int i = 0; i <currData; i++){
        if(data[i].name == temp){
          if(data[i].dataType == "list"){
            data[i].dataType += " " + dt;
          }else{
            if(data[i].dataType == ("list " + dt)){
              //do nothing, why is this code here lol
            }else{
              outputFile << "#warning" << endl;
              data[i].dataType = "list " + dt; 
            }
          }
          
          outputFile << tempLine << endl;
          flag = true;
          break;
        }
      } //Does this name already exist or not
      if(flag) continue;
      data[currData].name = temp;
      data[currData].dataType = "list " + dt;
      currData++;
      outputFile << tempLine << endl;
      
    }else if(tempLine.find(".append") != std::string::npos){
      string temp = tempLine.substr(tempLine.find('(')+1);
      temp.erase(temp.length()); //erase the ) at the end
      
      string dt = checkType(temp);
      temp = tempLine.substr(0, tempLine.find('.'));
      bool flag = false;
      for(int i = 0; i <currData; i++){
        if(data[i].name == temp){
          if(data[i].dataType == "list"){
            data[i].dataType += " " + dt;
          }else{
            if(data[i].dataType == ("list " + dt)){
              //do nothing, why is this code here lol
            }else{
              outputFile << "#warning" << endl;
              data[i].dataType = "list " + dt; 
            }
          }
          
          outputFile << tempLine << endl;
          flag = true;
          break;
        }
      } //Does this name already exist or not
      if(flag) continue;
      data[currData].name = temp;
      data[currData].dataType = "list " + dt;
      currData++;
      outputFile << tempLine << endl;
    }
  }//End of hasEqual if/else statement

 }

 inputFile.close();
 outputFile.close();
  return 0;
}