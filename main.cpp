/*
 * main.cpp
 *
 *  Created on: 2016年3月18日
 *      Author: smallcroco
 */

#include "Dictionary.h"
#include <iostream>

using namespace std;

int main() {

	string filePath = "common-1.txt";
	Dictionary dic;
	dic.InitDictionary(filePath);

	// 文件路径
	string filepath = "testFile.txt";

	time_t begin, end;

	begin = clock();

	// 读取文件内容
	dic.ReadFile(filepath);

	end = clock();

	cout<<"runtime: "<<double(end-begin)/CLOCKS_PER_SEC<<endl;
	Trie* t= dic.trie;

	long count = t->getCount();

	cout<<count<<endl;

	int a = 0;

}
