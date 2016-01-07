///*
// * Project: Maze_fish
// * Created by CS106 C++ Assignment Wizard 0.1
// *
// * Name: [TODO: Maze game!]
// * Section: [TODO: enter section leader here]
// * [TODO: Describe assignment]
// */
#include <iostream>
#include "maze.h"
#include "simpio.h"
#include "genlib.h"
#include "Grid.h"
#include "Random.h"
#include "Vector.h"
#include "set.h"
#include "queue.h"
#include "stack.h"

const int mazerow = 20;
const int mazecol = 35;

bool findmazeflag(Vector<pointT> mazeflag, pointT point)
{
	bool flag = false;
	for(int i = 0; i < mazeflag.size(); ++i){
		if((mazeflag[i].col == point.col) && (mazeflag[i].row == point.row)){
			flag = true;
			break;
		}
	}
	if(flag == true) 
		return true;
	else	return false;
}

pointT choose_neig(char dir, pointT point)
{
	pointT neighbors = point;
	switch(dir){
		case 'u':
			neighbors.row = point.row + 1;
			break;
		case 'd':
			neighbors.row = point.row - 1;
			break;
		case 'l':
			neighbors.col = point.col - 1;
			break;
		case 'r':
			neighbors.col = point.col + 1;
			break;
		default:
			break;
	}
	return neighbors;
}

pointT randompoint()//生成随机点的函数
{
	pointT point;
	point.row = RandomInteger(0, mazerow - 1);
	point.col = RandomInteger(0, mazecol - 1);
	return point;
}

Vector<char> findneigbors(Maze maze, pointT p)	//查找与当前point点相邻相同的邻点
{
	pointT up, down, left, right ;
	up = down = left = right = p;
	up.row += 1;	//定义p的左右上下点，判断是否存在wall
	down.row -= 1;
	left.col -= 1;
	right.col += 1;
	Vector<char> dir;
	if(maze.pointInBounds(up)){
		if(!maze.isWall(up, p))
			dir.add('u');
	}
	if(maze.pointInBounds(down)){
		if(!maze.isWall(down, p))
			dir.add('d');
	}
	if(maze.pointInBounds(left)){
		if(!maze.isWall(left, p))
			dir.add('l');
	}
	if(maze.pointInBounds(right)){
		if(!maze.isWall(right, p))
			dir.add('r');
	}
	return dir;
}

Vector<pointT> findnext(Maze maze, pointT top, Vector<pointT> &solveflag){
	Vector<pointT> nextpath;
	Vector<char> nowall = findneigbors(maze, top);//找到当前点没有wall的相邻点
	for(int i = 0; i < nowall.size(); ++i){//将temp点所有可以查询的path enqueue进队列
		pointT next = choose_neig(nowall[i], top);//避免重复查询
		if(!findmazeflag(solveflag, next)){
			nextpath.add(next);
			solveflag.add(next);
		}
		else continue;		
	}
	return nextpath;
}



int main ()
{	
	//*********************************************// generate maze
	cout << "let's begin the maze! Please input \"start\" to begin the maze!" << endl;
	string begin;
	while(cin >> begin){
		if(begin != "start")
			cout << "Please input \"start\" begin the maze!!" << endl;
		else break;
	}
	string restart = "again";
	while(restart == "again"){
		Randomize();//产生随机种子
		Maze maze(mazerow, mazecol, true);//生成Maze
		maze.draw();
		
		pointT point = randompoint();//生成随机的点
		Vector<pointT> mazeflag;//放入maze标记表中，以保证maze中每一个Cell均被遍历
		mazeflag.add(point);
		
		while(mazeflag.size() < mazerow * mazecol){
			Vector<char> dir;//定义方向矩阵
			dir.add('u');dir.add('d');dir.add('l');dir.add('r');
			pointT neighbors;
			while(dir.size() > 0){//while 循环，在dir中找个一个可行的随机的在Maze界内neighbors
				int temp = RandomInteger(0, dir.size() - 1);
				neighbors = choose_neig(dir[temp], point);//根据随机选择的方向选择neighbors
				if(!maze.pointInBounds(neighbors))//判断是否在界内
					dir.removeAt(temp);
				else
					break;	
			}
			/*if(dir.size() == 0 ){
				point = randompoint();
				continue;
			}*/
			if( ! findmazeflag(mazeflag, neighbors)){
				maze.setWall(point, neighbors, false);
				mazeflag.add(neighbors);
				point = neighbors;
			}
			else point = neighbors;
		}
		maze.draw();

	//**************************************************// sovel the maze
		cout << "put \"fish\" to solve: ";
		string s;
		while(cin >> s){
			if(s != "fish")
				cout << "input fish to solve the maze!"<<endl;
			else break;
		}
		pointT start, end;
		start.row = start.col = 0;
		end.row = mazerow - 1;
		end.col = mazecol - 1;

		Vector <pointT> solveflag;//标记已遍历的点
		Queue <Stack<pointT> > queue;
		Stack<pointT> path;
		path.push(start);// 压入初始点
		solveflag.add(start);
		queue.enqueue(path);
		path = queue.dequeue();
		pointT top = path.peek();

		while(!((top.col==end.col)&& (top.row == end.row))){
			Vector<pointT> nextpoint = findnext(maze, path.peek(), solveflag);
			for(int i = 0; i < nextpoint.size(); ++i){
				Stack<pointT> temp = path;
				temp.push(nextpoint[i]);
				queue.enqueue(temp);
			}
			path = queue.dequeue();
			top = path.peek();
		}
		while(!path.isEmpty()){
			pointT mark = path.pop();
			maze.drawMark(mark, "Red");
		}
		cout << "input \"again\" to play again! Or input anyone to end the game!" <<endl;
		cin >> restart;
	}
	cout << "END OF MAZE!";
	return 0;
}