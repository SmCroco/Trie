/*
 * Dictionary.h
 *
 *  Created on: 2016年3月18日
 *      Author: smallcroco
 */

#ifndef READDICTIONARY_DICTIONARY_H_
#define READDICTIONARY_DICTIONARY_H_

#include <string>
#include <fstream>
#include "TrieNode.h"

using namespace std;

class Dictionary {
public:
	Dictionary();
	~Dictionary();

	void InitDictionary(string path);
	void InitDictionary();

private:
	long getCharacter(ifstream &file, long &location);

	int getCharacterLen(character c);

	bool isExist(long id);

private:
	long * array; // 词库字符数组
	long arrary_size; // 字符数组大小
	long largest_key; // 最大的字符编码
	int character_num; // 字符个数

};

#endif /* READDICTIONARY_DICTIONARY_H_ */
