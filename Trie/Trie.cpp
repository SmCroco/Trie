/*
 * Trie.cpp
 *
 *  Created on: 2016年3月21日
 *      Author: smallcroco
 */

#include <string.h>

#include <iostream>
#include "Trie.h"

using namespace std;

Trie::Trie(int num) {

	this->num = num + 1;
	this->root = new ST_trieNode();

	root->key = 0;
	root->encode = 0;
	root->value[0] = 0;
	root->value[1] = 0;
	root->value[2] = 0;
	root->value[3] = 0;
	root->value[4] = 0;
	root->value[5] = 0;
	root->isEnd = false;
	root->count = 0;
	root->arrary = new ST_trieNode*[this->num];
	for (int i=0; i<this->num; i++) {
		root->arrary[i] = NULL;
	}
	root->parent = NULL;
	root->faile = NULL;

	this->word_end = root;

	this->count = 0;
}
Trie::~Trie() {

}


bool Trie::insert(long key, long encode, int num, character* arg) {

	// 查看结点是否存在
	if (word_end->arrary[key] == NULL) { // 不存在

		ST_trieNode * node = new ST_trieNode();
		node->key = key;
		node->encode = encode;
		for (int i = 0; i < num; i++) {
			root->value[i] = arg[i].byChar;
		}
		node->count = 0;
		node->isEnd = false;
		node->arrary = new ST_trieNode*[this->num];
		for (int i=0; i<this->num; i++) {
			node->arrary[i] = NULL;
		}
		node->parent = word_end;
		node->faile = NULL;
		word_end->arrary[key] = node;
		word_end = node;

		return true;

	} else { // 存在

		word_end = word_end->arrary[key];

		return false;
	}
}

void Trie::setWordEnd() {
	word_end->isEnd = true;

	word_end = root;
}

int Trie::find(long key) {
	ST_trieNode* value = word_end->arrary[key];
	if (value == NULL) {
		word_end = root;
		return 0;
	} else {
		if (value->isEnd) {
			value->count++;
			count += 1;

			word_end = value;

			return 1;
		} else {
			word_end = value;

			return 2;
		}
	}
}

long Trie::getCount() {
	return count;
}
