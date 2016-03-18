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
	this->largest_key = 0;
	this->character_num = 0;

}

Dictionary::~Dictionary() {
	// TODO Auto-generated destructor stub
}

void Dictionary::InitDictionary(string path) {

	// 打开词库文件
	ifstream file(path.c_str());
	if (file.is_open()) {

			// 用来标记每一个UTF8字符占几个字节
			int n = 0;

			// 循环读取文件中的一个字符
			character c;
			while ((c.byChar = file.get()) != EOF) {

				if (c.byChar != '\r'){
				// 获取utf8单个字符的长度
				n = getCharacterLen(c);

				long char_encode = 0;
				switch(n) {
				case 1:{
					char value1 = c.byChar;
					char_encode = value1;
					if (isExist(char_encode) == false) {
						character_num += 1;
						this->array[char_encode] = character_num;
					}
				};break;

				case 2:{
					char value1 = c.byChar;
					char value2 = file.get();
					char_encode = ((value1&0x1f)<<6) + (value2&0x3f);
					if (isExist(char_encode) == false) {
						character_num += 1;
						this->array[char_encode] = character_num;
					}

				};break;

				case 3: {
					char value1 = c.byChar;
					char value2 = file.get();
					char value3 = file.get();
					char_encode =((value1 & 0x0f) << 12) + ((value2 & 0x3f) << 6) + (value3 & 0x3f);

					if (isExist(char_encode) == false) {
						character_num += 1;
						this->array[char_encode] = character_num;
					}
				}; break;

				case 4:{
					char value1 = c.byChar;
					char value2 = file.get();
					char value3 = file.get();
					char value4 = file.get();
					char_encode = ((value1 & 0x07) << 18) + ((value2 & 0x3f) << 12) + ((value3 & 0x3f) << 6) + (value4 & 0x3f);

					if (isExist(char_encode) == false) {
						character_num += 1;
						this->array[char_encode] = character_num;
					}
				};break;

				case 5:{
					char value1 = c.byChar;
					char value2 = file.get();
					char value3 = file.get();
					char value4 = file.get();
					char value5 = file.get();

					char_encode = ((value1 & 0x03)<<24) + ((value2 & 0x3f)<<18) + ((value3 & 0x3f)<<12) + ((value4 & 0x3f)<<6) + (value5 & 0x3f);
					if (isExist(char_encode) == false) {
						character_num += 1;
						this->array[char_encode] = character_num;
					}
				};break;

				case 6:{
					char value1 = c.byChar;
					char value2 = file.get();
					char value3 = file.get();
					char value4 = file.get();
					char value5 = file.get();
					char value6 = file.get();

					char_encode = ((value1 & 0x1) << 30) + ((value2 & 0x3f) << 24) + ((value3 & 0x3f) << 18) + ((value4 & 0x3f) << 12) + ((value5 & 0x3f) << 6) + (value6 & 0x3f);
					if (isExist(char_encode) == false) {
						character_num += 1;
						this->array[char_encode] = character_num;
					}
				};break;

				default: {
					cout<<"字符不正确"<<endl;
				}
				}
			}

		}
	} else {
		cout<<"词库文件打开失败"<<endl;
	}
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

	if (c.byBit.byte0 == 1 && c.byBit.byte1 == 1 && c.byBit.byte2 == 1 &&
			c.byBit.byte3 == 0) {
		return 3;
	}

	if (c.byBit.byte0 == 1 && c.byBit.byte1 == 1 && c.byBit.byte2 == 1 &&
			c.byBit.byte3 == 1 && c.byBit.byte4 == 0) {
		return 4;
	}

	if (c.byBit.byte0 == 1 && c.byBit.byte1 == 1 && c.byBit.byte2 == 1 &&
			c.byBit.byte3 == 1 && c.byBit.byte4 == 1 && c.byBit.byte5 == 0) {
		return 5;
	}

	if (c.byBit.byte0 == 1 && c.byBit.byte1 == 1 && c.byBit.byte2 == 1 &&
			c.byBit.byte3 == 1 && c.byBit.byte4 == 1 && c.byBit.byte5 == 1 &&
			c.byBit.byte6 == 0) {
		return 6;
	}

	return 0;
}

bool Dictionary::isExist(long id) {

	// 如果超出数组范围，则重新分配数组
	if (id >= this->arrary_size) {

		this->largest_key = id;

		long* newArrary = new long[id+1];

		memset((char*)newArrary, 0, (id+1)*sizeof(long));

		memcpy((char*)newArrary, (char*)arrary_size, arrary_size*sizeof(long));

		delete this->array;
		this->array = newArrary;
		arrary_size = id + 1;

		return false;
	} else {
		return this->array[id];
	}
}
