/*
 * Trie.h
 *
 *  Created on: 2016年3月18日
 *      Author: smallcroco
 */

#ifndef TRIE_TRIE_H_
#define TRIE_TRIE_H_

#include "TrieNode.h"

class Trie {
public:
	Trie(int num);
	~Trie();

	bool insert(long key, long encode, int num, character* arg);
	void setWordEnd();

	int find(long key);

	long getCount();

private:
	ST_trieNode * root;	// 树的根结点
	ST_trieNode * word_end; // 用于构造词语时指向词语结尾标志

	long count; // 总的匹配结果数
};

#endif /* TRIE_TRIE_H_ */
