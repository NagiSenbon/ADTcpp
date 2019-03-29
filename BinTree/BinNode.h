#pragma once

template<typename T>
struct BinNode;                      // �����������

template<typename T>
using BinNodePosi = BinNode<T> *;    // ���������ָ��

template<typename T>                 // �ڵ�߶� ( �����߶�Ϊ-1 )
constexpr auto stature( T p ) {
	return ( ( p ) ? ( p )->height : -1 );
}

typedef enum { RB_RED, RB_BLACK } RBColor;  // �ڵ���ɫ

template<typename T>struct BinNode {
	T data;
	BinNodePosi<T> parent; // ���ڵ�
	BinNodePosi<T> lc;     // ��ڵ�
	BinNodePosi<T> rc;     // �ҽڵ�
	int height;            // ���ĸ߶�
	int npl;               // Null Path Length ( ���϶� )
	RBColor color;
	BinNode() : data( 0 ), parent( nullptr ), lc( nullptr ), rc( nullptr ),
		height( 0 ), npl( 1 ), color( RB_RED ) {}
	BinNode( T e,
			 BinNodePosi<T> p = nullptr,
			 BinNodePosi<T> lc = nullptr,
			 BinNodePosi<T> rc = nullptr,
			 int h = 0, int l = 1,
			 RBColor c = RB_RED ) :
		data( e ), parent( p ), lc( lc ), rc( rc ),
		height( h ), npl( l ), color( c ) {}

};

template<typename T>
constexpr bool IsRoot( T x ) { return  ( !x.parent ); }

template<typename T>
constexpr bool IsLChirld( T x ) { return ( !IsRoot( x ) and ( &x == x.parent->lc ) ); }

template<typename T>
constexpr bool IsRChirld( T x ) { return ( !IsRoot( x ) and ( &x == x.parent->rc ) ); }

template<typename T>
constexpr bool HasParent( T x ) { return ( !IsRoot( x ) ); }
