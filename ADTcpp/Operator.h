﻿#pragma once
#include <string>

const int N_OPTR = 9;

enum class Operator :int { ADD, SUB, MUL, DIV, POW, FAC, L_P, R_P, EOP };
struct OpString {
	std::string opWord[N_OPTR] {
		"ADD",
		"SUB",
		"MUL",
		"DIV",
		"POW",
		"FAC",
		"L_P",
		"R_P",
		"EOP"
	};
	std::string opSign[N_OPTR] {
		" + ",
		" - ",
		" * ",
		" / ",
		"^",
		"!",
		"(",
		")",
		"EOP"
	};
};

typedef Operator Op;
typedef OpString Ops;

const char Pri[N_OPTR][N_OPTR] =
{
	/*                       运算符优先等级 [栈顶] [当前]             */
	/*            |--------------- 当 前 运 算 符 ---------------| */
	/*              +    -    *    /    ^    !    (    )   \0    */
	/* --  + */    '>', '>', '<', '<', '<', '<', '<', '>', '>',
	/* |   - */    '>', '>', '<', '<', '<', '<', '<', '>', '>',
	/* 栈  * */    '>', '>', '>', '>', '<', '<', '<', '>', '>',
	/* 顶  / */    '>', '>', '>', '>', '<', '<', '<', '>', '>',
	/* 运  ^ */    '>', '>', '>', '>', '>', '<', '<', '>', '>',
	/* 算  ! */    '>', '>', '>', '>', '>', '>', ' ', '>', '>',
	/* 符  ( */    '<', '<', '<', '<', '<', '<', '<', '=', ' ',
	/* |   ) */    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
	/* -- \0 */    '<', '<', '<', '<', '<', '<', '<', ' ', '='
};