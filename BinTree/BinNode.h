#pragma once

template<typename T>
struct BinNode;                             // �����������

template<typename T>
using BinNodePosi = BinNode<template> *;    // ���������ָ��

template<typename T>
constexpr auto stature( T p ) { return ( ( p ) ? ( p )->height : -1 ); } // �ڵ�߶� ( �����߶�Ϊ-1 )

typedef enum { RB_RED, RB_BLACK } RBColor;  // �ڵ���ɫ

template<typename T>struct BinNode {
	T data;
	BinNodePosi<T> parent; // ���ڵ�
	BinNodePosi<T> lc;     // ��ڵ�
	BinNodePosi<T> rc;     // �ҽڵ�
	int height;
	int npl;
	RBColor color;
	BinNode() : parent( nullptr ), lc( nullptr ), rc( nullptr ),
		height( 0 ), npl( 1 ), color( RB_RED ) {}


};