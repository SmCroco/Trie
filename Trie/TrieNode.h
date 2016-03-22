/*
 * TrieNode.h
 *
 *  Created on: 2016年3月11日
 *      Author: smallcroco
 */

#ifndef TRIE_TRIENODE_H_
#define TRIE_TRIENODE_H_

union character {
	struct Bit {
		char byte7:1;
		char byte6:1;
		char byte5:1;
		char byte4:1;
		char byte3:1;
		char byte2:1;
		char byte1:1;
		char byte0:1;
	}byBit;
	char byChar;
};

struct ST_trieNode {
	long key;	// 汉字对应的编号，作为数组的下标
	long encode; // 汉字的编码
	char value[6]; // 汉字的值
    bool isEnd; // 关键词的结尾标记
    long count; // 以该字结尾的词的个数
    long *arrary; // 数组表
    ST_trieNode * parent; // 指向父结点
    ST_trieNode * faile; // 指向匹配失败后的失败结点
};

#endif /* TRIE_TRIENODE_H_ */
