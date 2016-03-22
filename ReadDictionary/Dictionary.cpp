/*
 * Dictionary.cpp
 *
 *  Created on: 2016年3月18日
 *      Author: smallcroco
 */

#include "Dictionary.h"
#include <iostream>
#include <string.h>

using namespace std;

Dictionary::Dictionary() {
	// TODO Auto-generated constructor stub

	this->arrary_size = 65535;
	this->array = new long[arrary_size];
	this->largest_key = 65535;
	this->character_num = 0;

	this->trie = NULL;
}

Dictionary::~Dictionary() {
	// TODO Auto-generated destructor stub
}

void Dictionary::InitDictionary(string path) {

	// 打开词库文件
	ifstream file(path.c_str());
	if (file.is_open()) {

		file.seekg(0, ios::beg);
		// 用来标记每一个UTF8字符占几个字节
		int n = 0;

		// 记录每一个UTF8字符的unicode编码
		long char_encode = 0;

		// 循环读取文件中的字符
		character value[6];
		while ((value[0].byChar = file.get()) != EOF) {
			if (character_num == 10900) {
				int a = 0;
			}

			if (value[0].byChar != '\r' && value[0].byChar != '\n') {
				// 获取utf8单个字符的长度
				n = getCharacterLen(value[0]);

				if (n == 3) {
					value[1].byChar = file.get();
					value[2].byChar = file.get();

					char_encode = ((value[0].byChar & 0x0f) << 12)
							+ ((value[1].byChar & 0x3f) << 6)
							+ (value[2].byChar & 0x3f);

					if (isExist(char_encode) == false) {
						character_num += 1;
						this->array[char_encode] = character_num;
					}
				} else 	if (n == 1) {
					char_encode = value[0].byChar;

					if (isExist(char_encode) == false) {
						character_num += 1;
						this->array[char_encode] = character_num;
					}
				} else if (n == 2) {
					value[1].byChar = file.get();

					char_encode = ((value[0].byChar & 0x1f) << 6)
							+ (value[1].byChar & 0x3f);
					if (isExist(char_encode) == false) {
						character_num += 1;
						this->array[char_encode] = character_num;
					}
				} else if (n == 4) {
					value[1].byChar = file.get();
					value[2].byChar = file.get();
					value[3].byChar = file.get();

					char_encode = ((value[0].byChar & 0x07) << 18)
							+ ((value[1].byChar & 0x3f) << 12)
							+ ((value[2].byChar & 0x3f) << 6)
							+ (value[3].byChar & 0x3f);

					if (isExist(char_encode) == false) {
						character_num += 1;
						this->array[char_encode] = character_num;
					}
				} else if (n == 5) {
					value[1].byChar = file.get();
					value[2].byChar = file.get();
					value[3].byChar = file.get();
					value[4].byChar = file.get();

					char_encode = ((value[0].byChar & 0x03) << 24)
							+ ((value[1].byChar & 0x3f) << 18)
							+ ((value[2].byChar & 0x3f) << 12)
							+ ((value[3].byChar & 0x3f) << 6)
							+ (value[4].byChar & 0x3f);
					if (isExist(char_encode) == false) {
						character_num += 1;
						this->array[char_encode] = character_num;
					}
				} else if (n == 6){
					value[1].byChar = file.get();
					value[2].byChar = file.get();
					value[3].byChar = file.get();
					value[4].byChar = file.get();
					value[5].byChar = file.get();

					char_encode = ((value[0].byChar & 0x1) << 30)
							+ ((value[1].byChar & 0x3f) << 24)
							+ ((value[2].byChar & 0x3f) << 18)
							+ ((value[3].byChar & 0x3f) << 12)
							+ ((value[4].byChar & 0x3f) << 6)
							+ (value[5].byChar & 0x3f);
					if (isExist(char_encode) == false) {
						character_num += 1;
						this->array[char_encode] = character_num;
					}
				} else {
					cout << "字符不正确" << endl;
				}

			}

		}

		file.close();
	} else {
		cout << "词库文件打开失败" << endl;
	}

	InitTrie(path);
}

void Dictionary::InitDictionary() {

}

int Dictionary::getCharacterLen(character c) {

	if (c.byBit.byte0 == 0) {
		return 1;
	}

	if (c.byBit.byte0 == 1 && c.byBit.byte1 == 1 && c.byBit.byte2 == 0) {
		return 2;
	}

	if (c.byBit.byte0 == 1 && c.byBit.byte1 == 1 && c.byBit.byte2 == 1
			&& c.byBit.byte3 == 0) {
		return 3;
	}

	if (c.byBit.byte0 == 1 && c.byBit.byte1 == 1 && c.byBit.byte2 == 1
			&& c.byBit.byte3 == 1 && c.byBit.byte4 == 0) {
		return 4;
	}

	if (c.byBit.byte0 == 1 && c.byBit.byte1 == 1 && c.byBit.byte2 == 1
			&& c.byBit.byte3 == 1 && c.byBit.byte4 == 1 && c.byBit.byte5 == 0) {
		return 5;
	}

	if (c.byBit.byte0 == 1 && c.byBit.byte1 == 1 && c.byBit.byte2 == 1
			&& c.byBit.byte3 == 1 && c.byBit.byte4 == 1 && c.byBit.byte5 == 1
			&& c.byBit.byte6 == 0) {
		return 6;
	}

	return 0;
}

bool Dictionary::isExist(long id) {

	// 如果超出数组范围，则重新分配数组
	if (id >= this->arrary_size) {

		this->largest_key = id;

		long* newArrary = new long[id + 1];

		memset((char*) newArrary, 0, (id + 1) * sizeof(long));

		memcpy((char*) newArrary, (char*) arrary_size,
				arrary_size * sizeof(long));

		delete this->array;
		this->array = newArrary;
		arrary_size = id + 1;

		return false;
	} else {
		return this->array[id];
	}
}

void Dictionary::InitTrie(string path) {

	this->trie = new Trie(this->character_num);

	// 打开词库文件
	ifstream file(path.c_str());
	if (file.is_open()) {

		file.seekg(0, ios::beg);

		// 用来标记每一个UTF8字符占几个字节
		int n = 0;

		// 每一个utf8字符的字节
		character value[6];

		// 循环读取文件中的字节
		char word[200] = {0};
		memset(word, 0, 200*sizeof(char));

		while (!file.eof()) {
			file.getline(word, 200);

			// 换行字符
			for (int i = 0; (word[i] != '\r' && word[i] != 0); ) {

				value[0].byChar = word[i];
				i += 1;

				// 获取utf8单个字符的长度
				n = getCharacterLen(value[0]);

				// 记录utf8字符的unicode编码
				long char_encode = 0;

				switch (n) {
				case 1: {

					// utf8的字符编码
					char_encode = value[0].byChar;

					// 插入trie树
					trie->insert(array[char_encode], char_encode, 1, value);

				}
					break;

				case 2: {

					value[1].byChar = word[i];
					i += 1;

					// utf8的字符编码
					char_encode = ((value[0].byChar & 0x1f) << 6)
							+ (value[1].byChar & 0x3f);

					// 插入trie树
					trie->insert(array[char_encode], char_encode, 2, value);

				}
					break;

				case 3: {
					value[1].byChar = word[i];
					i += 1;

					value[2].byChar = word[i];
					i += 1;

					// utf8的字符编码
					char_encode = ((value[0].byChar & 0x0f) << 12)
							+ ((value[1].byChar & 0x3f) << 6)
							+ (value[2].byChar & 0x3f);

					// 插入trie树
					trie->insert(array[char_encode], char_encode, 3, value);

				}
					break;

				case 4: {
					value[1].byChar = word[i];
					i += 1;

					value[2].byChar = word[i];
					i += 1;

					value[3].byChar = word[i];
					i += 1;

					// utf8的字符编码
					char_encode = ((value[0].byChar & 0x07) << 18)
							+ ((value[1].byChar & 0x3f) << 12)
							+ ((value[2].byChar & 0x3f) << 6)
							+ (value[3].byChar & 0x3f);

					// 插入trie树
					trie->insert(array[char_encode], char_encode, 4, value);

				}
					break;

				case 5: {
					value[1].byChar = word[i];
					i += 1;

					value[2].byChar = word[i];
					i += 1;

					value[3].byChar = word[i];
					i += 1;

					value[4].byChar = word[i];
					i += 1;

					// utf8的字符编码
					char_encode = ((value[0].byChar & 0x03) << 24)
							+ ((value[1].byChar & 0x3f) << 18)
							+ ((value[2].byChar & 0x3f) << 12)
							+ ((value[3].byChar & 0x3f) << 6)
							+ (value[4].byChar & 0x3f);

					// 插入trie树
					trie->insert(array[char_encode], char_encode, 5, value);

				}
					break;

				case 6: {
					value[1].byChar = word[i];
					i += 1;

					value[2].byChar = word[i];
					i += 1;

					value[3].byChar = word[i];
					i += 1;

					value[4].byChar = word[i];
					i += 1;

					value[5].byChar = word[i];
					i += 1;

					// utf8的字符编码
					char_encode = ((value[0].byChar & 0x1) << 30)
							+ ((value[1].byChar & 0x3f) << 24)
							+ ((value[2].byChar & 0x3f) << 18)
							+ ((value[3].byChar & 0x3f) << 12)
							+ ((value[4].byChar & 0x3f) << 6)
							+ (value[5].byChar & 0x3f);

					// 插入trie树
					trie->insert(array[char_encode], char_encode, 6, value);

				}
					break;

				default: {
					cout << "字符不正确" << endl;
				}
				}

		}

			this->trie->setWordEnd();
			memset(word, 0, 200*sizeof(char));
		}

		file.close();
	} else {
		cout << "词库文件打开失败" << endl;
	}

}

void Dictionary::ReadFile(string path) {
	// 打开文件流
	file.open(path.c_str());

	// 判断文件是否打开成功
	if (file.is_open()) {

		// 标志utf8每个字符要多少个字节
		int n = 0;

		// 记录每一个UTF8字符的unicode编码
		long char_encode = 0;

		// 循环读取文件中的一个字符
		character value[6] = {0};
		while ((value[0].byChar = file.get()) != EOF) {
			// 获取utf8单个字符的长度
			n = getCharacterLen(value[0]);

			switch(n) {
			case 1:{
				char_encode = value[0].byChar;
			} break;

			case 2: {
				value[1].byChar = file.get();

				char_encode = ((value[0].byChar & 0x1f) << 6)
						+ (value[1].byChar & 0x3f);
			} break;

			case 3: {
				value[1].byChar = file.get();
				value[2].byChar = file.get();

				char_encode = ((value[0].byChar & 0x0f) << 12)
						+ ((value[1].byChar & 0x3f) << 6)
						+ (value[2].byChar & 0x3f);
			} break;

			case 4: {
				value[1].byChar = file.get();
				value[2].byChar = file.get();
				value[3].byChar = file.get();

				char_encode = ((value[0].byChar & 0x07) << 18)
						+ ((value[1].byChar & 0x3f) << 12)
						+ ((value[2].byChar & 0x3f) << 6)
						+ (value[3].byChar & 0x3f);
			} break;

			case 5: {
				value[1].byChar = file.get();
				value[2].byChar = file.get();
				value[3].byChar = file.get();
				value[4].byChar = file.get();

				char_encode = ((value[0].byChar & 0x03) << 24)
						+ ((value[1].byChar & 0x3f) << 18)
						+ ((value[2].byChar & 0x3f) << 12)
						+ ((value[3].byChar & 0x3f) << 6)
						+ (value[4].byChar & 0x3f);
			} break;

			case 6: {
				value[1].byChar = file.get();
				value[2].byChar = file.get();
				value[3].byChar = file.get();
				value[4].byChar = file.get();
				value[5].byChar = file.get();

				char_encode = ((value[0].byChar & 0x1) << 30)
						+ ((value[1].byChar & 0x3f) << 24)
						+ ((value[2].byChar & 0x3f) << 18)
						+ ((value[3].byChar & 0x3f) << 12)
						+ ((value[4].byChar & 0x3f) << 6)
						+ (value[5].byChar & 0x3f);
			} break;
			}

			int d = trie->find(char_encode);
			switch (d) {

			case 0: { // trie树没有找到以此字符开始的词
			}break;

			case 1: { // trie树找到一个以此字符结尾的词，继续往下查找

				// 记录当前位置
				long l = file.tellg();

				continueMatchFile();

				// 返回先前位置
				file.seekg(l, ios::beg);
			} break;

			case 2: { // trie树找到一个以此字符开始的关键词, 继续往下查找

				// 记录当前位置
				long l = file.tellg();

				continueMatchFile();

				// 返回先前位置
				file.seekg(l, ios::beg);
			}
			}
		}

		file.close();
	} else {
		cout<<"文件打开失败"<<endl;
	}
}

void Dictionary::continueMatchFile() {
	// 记录每一个UTF8字符的unicode编码
	long char_encode = 0;

	// 标志utf8每个字符要多少个字节
	int n = 0;

	// 循环读取文件中的一个字符
	character value[6] = {0};
	while ((value[0].byChar = file.get()) != EOF) {
		// 获取utf8单个字符的长度
		n = getCharacterLen(value[0]);

		switch(n) {
		case 1:{
			char_encode = value[0].byChar;
		} break;

		case 2: {
			value[1].byChar = file.get();

			char_encode = ((value[0].byChar & 0x1f) << 6)
					+ (value[1].byChar & 0x3f);
		} break;

		case 3: {
			value[1].byChar = file.get();
			value[2].byChar = file.get();

			char_encode = ((value[0].byChar & 0x0f) << 12)
					+ ((value[1].byChar & 0x3f) << 6)
					+ (value[2].byChar & 0x3f);
		} break;

		case 4: {
			value[1].byChar = file.get();
			value[2].byChar = file.get();
			value[3].byChar = file.get();

			char_encode = ((value[0].byChar & 0x07) << 18)
					+ ((value[1].byChar & 0x3f) << 12)
					+ ((value[2].byChar & 0x3f) << 6)
					+ (value[3].byChar & 0x3f);
		} break;

		case 5: {
			value[1].byChar = file.get();
			value[2].byChar = file.get();
			value[3].byChar = file.get();
			value[4].byChar = file.get();

			char_encode = ((value[0].byChar & 0x03) << 24)
					+ ((value[1].byChar & 0x3f) << 18)
					+ ((value[2].byChar & 0x3f) << 12)
					+ ((value[3].byChar & 0x3f) << 6)
					+ (value[4].byChar & 0x3f);
		} break;

		case 6: {
			value[1].byChar = file.get();
			value[2].byChar = file.get();
			value[3].byChar = file.get();
			value[4].byChar = file.get();
			value[5].byChar = file.get();

			char_encode = ((value[0].byChar & 0x1) << 30)
					+ ((value[1].byChar & 0x3f) << 24)
					+ ((value[2].byChar & 0x3f) << 18)
					+ ((value[3].byChar & 0x3f) << 12)
					+ ((value[4].byChar & 0x3f) << 6)
					+ (value[5].byChar & 0x3f);
		} break;
		}

		int d = trie->find(char_encode);
		switch (d) {
		case 0: { // 此次查找结束
			return;
		}
		case 1: { // 找到一个关键词, 然后继续往下找下一个词

		} break;
		case 2: { // 匹配成功，继续往下匹配

		}
		}
	}
}
