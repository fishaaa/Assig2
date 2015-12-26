/*
 * Project: Random writer
 * Created by CS106 C++ Assignment Wizard 0.1
 *
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * [TODO: Describe assignment]
 */
#include <iostream>
#include "genlib.h"
#include "simpio.h"
#include "vector.h"
#include "map.h"
#include <fstream>
#include "random.h"

static int outnum = 0;
Vector<string> Inputstr(ifstream &in)
{
	Vector<string> text;
	while(true){
		string line;
		getline(in, line);
		if(in.fail()) break;//！！注意此处的调用顺序，若下一句在此句之前，将使得text多一行
		text.add(line);
	}
	return text;
}

string findmax(Map<int> map)
{
	Map<int> ::Iterator itr = map.iterator();
	int Max = 0;
	string Maxstr;
	while(itr.hasNext()){
		string key = itr.next();
		//cout << "key=" << key << " ,num: " << map[key] <<endl;
		if(map[key] >= Max){
			Max = map[key];
			Maxstr = key;
		}
	}
	return Maxstr;
}

bool findnext(Vector<string> text, string str)
{
	Randomize();
	int n = str.size();
	outnum += n;
	Map<int> mapnext;
	bool flag = false;
	double num = 0.0;
 	for(int i = 0; i < text.size();++i){//找到下一个
		for(int j = 0; j< text[i].size()-n+1; ++j){
			string temp = text[i].substr(j,n);
			string s = "a";
			if(temp == str){
				char temp;
				if((j+n) >= text.size()){
					temp = '\0';
				} else
					 temp = text[i][j+n];
				s[0] = temp;
				++num;
				if(mapnext.containsKey(s)){
					int count = mapnext.getValue(s);
					mapnext.add(s, count + 1);
				} else
					mapnext.add(s, 1);
			}
		}
	}
	if(mapnext.isEmpty())
		flag = true;
	//if(flag == true) return false;
	Map<int> temp = mapnext;   
	int accout = mapnext.size();
	Vector<string> mapstr;
	while(accout >= 0){	//将map中key出现的次数按大到小排序下来，mapstr中存储的是其符号key
		string Maxstr = findmax(temp);
		mapstr.add(Maxstr);
		temp.remove(Maxstr);
		--accout;
	}
	//for(int i =0; i < mapstr.size(); ++i)
	//	cout << mapstr[i] << "  " << mapnext[mapstr[i]];

	string Maxstr;
	bool FF = true;
	for(int i = 0; i < mapstr.size(); ++i){
		Maxstr= mapstr[i];
		bool flag = RandomChance(mapnext[Maxstr] / num);
		if(flag){ 
			FF = false;
			break;
		}
		if((FF == false) && (i == mapstr.size()-1))
			i=0;
	}
	cout << Maxstr;//打印下一个符号
	if(outnum == 2000)
		return false;
	string strnext = str.substr(1,n)+Maxstr;
	if(flag == true) return false;
	if(findnext(text, strnext) == false)
		return false;

}

void Order(Vector<string> text, int n)
{
	Map<int> map;
	string word;
	//string strnext;
	//int d = text.size();
	double num = 0.0; //记录字符总数
	for(int i = 0; i < text.size(); ++i){
		for(int j = 0; j < text[i].size()-n+1; ++j){
			word = text[i].substr(j, n);
			++num;
			if(map.containsKey(word)){
				int count = map.getValue(word);
				map.add(word, count + 1);
			} else
				map.add(word, 1);
		}
	}
	string Maxstr;
	int Maxnum = 0;
	Map<int> ::Iterator itr = map.iterator();
	while(itr.hasNext()){
		string key = itr.next();
		if(map[key] >= Maxnum){
			Maxstr = key;
			Maxnum = map[Maxstr];
		}
		cout << "key=" << key << " ,num: " << map[key] <<endl;
	}
	cout << Maxstr;
	findnext(text, Maxstr);
}

int main ()
{
	ifstream in;
	cout << "Please enter filename containing source text:";
	
	while(true){	//读入数据f
		string txt = GetLine();
		in.open(txt.c_str());
		if(!in.fail()) break;
		cout << "Could not open file named " << txt << " Please try again." << endl;
		in.clear();
	}
	Vector<string> Text = Inputstr(in);//将文本数据放到Text中
	
	cout << "What order of analsis?<a number from 1 to 10>:";
	int n = 0;
	cin >> n;
	Order(Text, n);
	
	return 0;
}






/*
 *  File: lecture.cpp
 *  ------------------
 * Snippets from the live coding part of Wed 1/16 lecture
 * showing some simple use of fstream.
 */

#include "genlib.h"
#include <iostream>
#include <fstream>
#include "simpio.h"

int CountLines(ifstream &in)
{
	int count = 0;
	while (true) {
		string line;
		getline(in, line);
		if (in.fail()) break;
		count++;
	}
	return count;
}


int main()
{
	ifstream in;
	while (true) {
		cout << "Enter name: ";
		string s = GetLine();
		in.open(s.c_str());
		if (!in.fail()) break;
		cout << "Couldn't open file, try again!" << endl;
		in.clear();
	}
	cout << "Num lines = " << CountLines(in) << endl;
	return 0;
}






