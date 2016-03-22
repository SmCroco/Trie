/*
 * Dictionary.h
 *
 *  Created on: 2016年3月18日
 *      Author: smallcroco
 */

#ifndef READDICTIONARY_DICTIONARY_H_
#define READDICTIONARY_DICTIONARY_H_

#include <fstream>
#include <string>
#include "Trie.h"
#include "TrieNode.h"

using namespace std;

class Dictionary {
public:
	Dictionary();
	~Dictionary();

	void InitDictionary(string path);
	void InitDictionary();

	void ReadFile(string path);
//	void ReadFile(const char* content, long length);

	void continueMatchFile();

	void InitTrie(string path);

private:
	long getCharacter(ifstream &file, long &location);

	int getCharacterLen(character c);

	bool isExist(long id);

private:
	long * array; // 词库字符数组
	long arrary_size; // 字符数组大小
	long largest_key; // 最大的字符编码
	int character_num; // 字符个数

	Trie* trie;
	ifstream file;

};

#endif /* READDICTIONARY_DICTIONARY_H_ */
