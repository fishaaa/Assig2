/*
 * Project: Rand write new
 * Created by CS106 C++ Assignment Wizard 0.1
 *
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * [TODO: Describe assignment]
 */
#include <iostream>
#include "genlib.h"
#include "vector.h"
#include "simpio.h"
#include <fstream>
#include "string.h"
#include "map.h"
#include "random.h"

static int NUM = 0;
bool findnext(string Maxstr, string text)
{
	cout << Maxstr;
	int n = Maxstr.size();
	++NUM;
	if(NUM == 2000)
		return false;
	char endstr = text[text.size() - 1];
	Vector <char> str;
	int index =0;
	while(index < (text.size() - n)){
		if(text.find(Maxstr, index) != string::npos) {
			index = text.find(Maxstr, index) + n;
			str.add(text[index]);
		} 
		else break;
	}
	char select = str[RandomInteger(0, str.size()-1)];
	//while(select == Maxstr[0]){
	//	select = str[RandomInteger(0, str.size()-1)];
	//}
	if(select == endstr)
		return false;
	else{
		Maxstr = Maxstr.erase(0) + select;
		findnext(Maxstr, text);
	}
}


int main()
{
	ifstream in;
	while(true){
		cout << "Please enter filename containing sourece text:";
		string Text = GetLine();
		in.open(Text.c_str());
		if(!in.fail()) break;
		cout << "Could not open file named" << Text << ". Please try again." <<endl;
		in.clear();
	}
	cout << "What order of analysis?<a number from 1 to 10>:";
	int n = 0;
	cin >> n;
	Map <int> map;
	
	string word;
	string text;
	while(true){
		char temp;
		while(word.size() < n){
			temp = in.get();
			word += temp;
		}
		text += temp;
		if(in.fail()) break;
		if(map.containsKey(word)){
			int count = map.getValue(word);
			map.add(word, count+1);
		} else
			map.add(word, 1);
		word.erase(0, 1);
	}
	Map<int>::Iterator itr = map.iterator();
	int max = 0;
	string Maxstr;
	while(itr.hasNext()){
		string key = itr.next();
		if(map[key] >= max){
			max = map[key];
			Maxstr = key;
		}
	}
	NUM = n;
	Randomize();
	findnext(Maxstr, text);

	return 0;
}


//int main()
//{
//	string a = "abcdefg";
//	int num = a.find("cd", 0);
//	cout << num;
//	return 0;
//}