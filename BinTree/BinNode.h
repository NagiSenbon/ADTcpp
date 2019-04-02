#pragma once

template<typename T>
struct BinNode;                      // �����������

template<typename T>
using BinNodePosi = BinNode<T> *;    // ���������ָ��

template<typename T>                 // �ڵ�߶� ( �����߶�Ϊ-1 )
constexpr int stature( T p ) {
	return ( ( p ) ? ( p )->height : -1 );
}

enum class RBColor { r, b };   // �ڵ���ɫ

template<typename T>
struct BinNode {
	T data;
	BinNodePosi<T> parent; // ���ڵ�
	BinNodePosi<T> lc;     // ��ڵ�
	BinNodePosi<T> rc;     // �ҽڵ�
	int height;            // ���ĸ߶�
	int npl;               // Null Path Length ( ���϶� )
	RBColor color;         // �ڵ���ɫ
	BinNode() : data( 0 ), parent( nullptr ), lc( nullptr ), rc( nullptr ),
		height( 0 ), npl( 1 ), color( RBColor::r ) {}
	BinNode( T e,
			 BinNodePosi<T> p = nullptr,
			 BinNodePosi<T> lc = nullptr,
			 BinNodePosi<T> rc = nullptr,
			 int h = 0, int l = 1,
			 RBColor c = RBColor::r ) :
		data( e ), parent( p ), lc( lc ), rc( rc ),
		height( h ), npl( l ), color( c ) {}

	int Color() {
		if ( color == RBColor::r )
			return 0;
		else if ( color == RBColor::b )
			return 1;
		else
			return -1;
	}

	BinNodePosi<T> inserAsLC( const T & e );   // �� e ����Ϊ��ǰ�ڵ�����
	BinNodePosi<T> inserAsRC( const T & e );   // �� e ����Ϊ��ǰ�ڵ��Һ���

};

template<typename T>
BinNodePosi<T> BinNode<T>::inserAsLC( const T & e ) {
	return lc = new BinNode( e, this );
}

template<typename T>
BinNodePosi<T> BinNode<T>::inserAsRC( const T & e ) {
	return rc = new BinNode( e, this );
}

template<typename T>
constexpr bool IsRoot( const BinNode<T> & x ) {
	return  !( &x ) or !( x.parent );
}

template<typename T>
constexpr bool IsLChild( const BinNode<T> & x ) {
	return ( !IsRoot( x ) and ( ( &x ) == ( x.parent->lc ) ) );
}

template<typename T>
constexpr bool IsRChild( const BinNode<T> & x ) {
	return ( !IsRoot( x ) and ( ( &x ) == ( x.parent->rc ) ) );
}

template<typename T>
constexpr bool HasParent( const BinNode<T> & x ) {
	return ( !IsRoot( x ) );
}

template<typename T>
constexpr bool HasLChild( const BinNode<T> & x ) {
	return ( &x ) ? x.lc : false;
}

template<typename T>
constexpr bool HasRChild( const BinNode<T> & x ) {
	return ( &x ) ? x.rc : false;
}

template<typename T>
constexpr bool HasChild( const BinNode<T> & x ) {
	return ( HasLChild( x ) or HasRChild( x ) );
}

template<typename T>
constexpr bool HasBothChild( const T & x ) {
	return ( HasLChild( x ) and HasRChild( x ) );
}

template<typename T>
constexpr bool IsLeaf( T  x ) {
	return !HasChild( x );
}

template<typename T>   // �����ֵܽڵ� 
constexpr BinNodePosi<T> sibling( BinNodePosi<T> x ) {
	if ( !IsRoot( *x ) ) {
		return  IsLChild( *x )
			? ( x->parent->rc )
			: ( x->parent->lc );
	} else
		return x;
}

template<typename T>   // ��������ڵ�
constexpr BinNodePosi<T> uncle( BinNodePosi<T> x ) {
	if ( !IsRoot( *( x->parent ) ) and !IsRoot( *( x->parent->parent ) ) ) {
		return  IsLChild( *( x->parent ) )
			? ( x->parent->parent->rc )
			: ( x->parent->parent->lc );
	} else {
		return x;
	}
}

template<typename T>   // ���ظ��ڵ�
constexpr BinNodePosi<T> FromParentTo( BinNode<T> & x ) {
	return IsRoot( x )
		? ( &x )
		: ( IsLChild( x )
			? ( x.parent->lc )
			: ( x.parent->rc ) );
}
