﻿#pragma once
#ifndef __ADT_VECTOR__
#define __ADT_VECTOR__

#include <cstdlib>

typedef int Rank;
static const int  DEFAULT_CAPACITY = 128;

template<typename T> void v_swap( T & a, T & b );
template<typename T> const T & v_max( T & a, T & b );
template<typename T> const T & v_min( T & a, T & b );


template<typename T>
class Vector {
protected:
	Rank _size;
	T *  _elem;
	int  _capacity = 0;
	void copyFrom( const T * A, Rank lo, Rank hi );  // 复制数组区间 [ lo, hi )
	void expend();                                   // 扩容
	void shrink();                                   // 缩容
	bool bubble( Rank lo, Rank hi );                 // 区间扫描交换 [ lo, hi )
	void bubbleSort( Rank lo, Rank hi );             // 区间冒泡排序 [ lo, hi )
	void merge( Rank lo, Rank mi, Rank hi );         // 归并有序区间 [ lo, mi ) 和 [ mi, hi )
	void mergeSort( Rank lo, Rank hi );              // 区间归并排序 [ lo, hi )
	Rank partition( Rank lo, Rank hi );              // 区间轴点构造 [ lo, hi ]
	void quickSort( Rank lo, Rank hi );              // 区间快速排序 [ lo, hi )
	void selectionSort( Rank lo, Rank hi );          // 区间选择排序 [ lo, hi )


public:
	// 构造 Vector
	Vector();
	Vector( const T * A, Rank n ) { copyFrom( A, 0, n ); }
	Vector( const T * A, Rank lo, Rank hi ) { copyFrom( A, lo, hi ); }
	Vector( const Vector<T> & vec ) { copyFrom( vec._elem, 0, vec.size ); }
	Vector( const Vector<T> & vec, Rank lo, Rank hi ) { copyFrom( vec._elem, lo, hi ); }
	Vector( int length );            // 规模为 length
	Vector( int length, int val );   // 规模为 length，初始元素为 val
	// 析构 Vector
	~Vector() { delete[] _elem; }

	T & operator[]( Rank index );                        // Vector 寻秩访问
	T & operator=( const Vector<T> & vec );              // Vector 赋值克隆

	Rank size() const { return _size; }                        // 规模
	bool empty() const { return !_size; }                      // 判空
	void insert( Rank index, const T & val );                  // 插入元素 val
	Rank push_back( const T & val );                           // 向末尾插入元素 val
	void remove( Rank lo, Rank hi );                           // 移出区间 [ lo, hi )
	const T & remove( Rank index );                            // 按秩移除元素
	bool isordered( bool ascending = true ) const;             // 是否升序排列
	Rank find( const T & val, Rank lo = 0, Rank hi = _size );  // 遍历查找元素 val
	Rank findRemove( const T & val );                          // 移除元素 val
	Rank deduplicate();                                        // 无序 Vector 去重
	// Sort Function( 1:MergeSort(default), 2:QuickSort, 3:BubbleSort, 4:SelectionSort )
	void sort( Rank lo, Rank hi, int SortType = 1 );           // 区间排序 [ lo, hi )
	void sort( int SortType = 1 );                             // 全局排序
};

template<typename T>
inline void Vector<T>::copyFrom( const T * A, Rank lo, Rank hi ) {
	_elem = new T[_capacity = (lo + hi) << 1];
	_size = 0;
	for ( int i = lo; i < hi; i++ ) {
		_elem[_size++] = A[i];
	}
}

template<typename T>
inline void Vector<T>::expend() {
	if ( _size < _capacity )
		return;
	if ( _capacity < DEFAULT_CAPACITY )
		_capacity = DEFAULT_CAPACITY;
	T * oldElem = _elem;
	_elem = new T[_capacity <<= 1];
	for ( int i = 0; i < _size; i++ ) {
		_elem[i] = oldElem[i];
	}
	delete[] oldElem;
}

template<typename T>
inline void Vector<T>::shrink() {
	if ( _capacity < DEFAULT_CAPACITY or (_size << 2) > _capacity )
		return;
	T * oldElem = _elem;
	_elem = new T[_capacity >>= 1];
	for ( int i = 0; i < _size; i++ ) {
		_elem[i] = oldElem[i];
	}
	delete[] oldElem;
}

template<typename T>
inline bool Vector<T>::bubble( Rank lo, Rank hi ) {
	bool sorted = true;
	while ( ++lo < hi ) {
		if ( _elem[lo - 1] > _elem[lo] ) {
			sorted = false;
			v_swap<T>( _elem[lo - 1], _elem[lo] );
		}
	}
	return sorted;
}

template<typename T>
inline void Vector<T>::bubbleSort( Rank lo, Rank hi ) {
	while ( !bubble( lo, hi-- ) );
}

template<typename T>
inline void Vector<T>::merge( Rank lo, Rank mi, Rank hi ) {
	T * A = _elem + lo;
	int ml = mi - lo;
	T * B = new int[ml];
	for ( Rank i = 0; i < ml; B[i] = A[i++] );
	int hm = hi - mi;
	T * C = _elem + mi;
	for ( Rank i = 0, j = 0, k = 0; (j < ml) or (k < hm); ) {
		if ( (j < ml) and (!(k < hm) or (B[j] <= C[k])) )
			A[i++] = B[j++];
		if ( (k < hm) and (!(j < ml) or (B[j] > C[k])) )
			A[i++] = C[k++];
	}
	delete[] B;
}

template<typename T>
inline void Vector<T>::mergeSort( Rank lo, Rank hi ) {
	if ( hi - lo < 2 )
		return;
	int mi = (lo + hi) >> 1;
	mergeSort( lo, mi ); mergeSort( mi, hi );
	merge( lo, mi, hi );
}

template<typename T>
inline Rank Vector<T>::partition( Rank lo, Rank hi ) {
	v_swap<T>( _elem[lo], _elem[(lo + hi) >> 1] );
	T pivot = _elem[lo];
	while ( lo < hi ) {
		while ( lo < hi )
			if ( _elem[hi] > pivot )
				hi--;
			else { _elem[lo++] = _elem[hi]; break; }

		while ( lo < hi )
			if ( _elem[lo] < pivot )
				lo++;
			else { _elem[hi--] = _elem[lo]; break; }
	}
	_elem[lo] = pivot;
	return lo;
}

template<typename T>
inline void Vector<T>::quickSort( Rank lo, Rank hi ) {
	if ( hi - lo < 2 )
		return;
	Rank mi = partition( lo, hi - 1 );
	quickSort( lo, mi ); quickSort( mi + 1, hi );
}

template<typename T>
inline void Vector<T>::selectionSort( Rank lo, Rank hi ) {
	while ( lo < hi ) {
		Rank index = lo;
		Rank max_index = lo;
		while ( index < hi ) {
			if ( _elem[index] > _elem[max_index] )
				max_index = index;
			++index;
		}
		v_swap<T>( _elem[--hi], _elem[max_index] );
	}
}

template<typename T>
inline Vector<T>::Vector() {
	_elem = new int[_capacity = DEFAULT_CAPACITY];
}

template<typename T>
inline Vector<T>::Vector( int length ) {
	_capacity = DEFAULT_CAPACITY;
	while ( length > _capacity ) {
		_capacity <<= 1;
	}
	_elem = new int[_capacity];
	_size = length;
}

template<typename T>
inline Vector<T>::Vector( int length, int val ) {
	_capacity = DEFAULT_CAPACITY;
	while ( length > _capacity ) {
		_capacity <<= 1;
	}
	_elem = new int[_capacity];
	for ( int i = 0; i < length; i++ ) {
		_elem[i] = val;
	}
	_size = length;
}

template<typename T>
inline T & Vector<T>::operator[]( Rank index ) {
	return _elem[index];
}

template<typename T>
inline T & Vector<T>::operator=( const Vector<T> & vec ) {
	if ( _elem )
		delete[] _elem;
	copyFrom( vec._elem, 0, vec.size() );
	return *this;
}

template<typename T>
inline void Vector<T>::insert( Rank index, const T & val ) {
	expend();
	for ( int i = _size; i > index; i-- ) {
		_elem[i] = _elem[i - 1];
	}
	_elem[index] = val;
	_size++;
}

template<typename T>
inline Rank Vector<T>::push_back( const T & val ) {
	expend();
	_elem[++_size] = val;
	return _size - 1;
}

template<typename T>
inline void Vector<T>::remove( Rank lo, Rank hi ) {
	if ( lo == hi )
		return;
	while ( hi < _size ) {
		_elem[lo++] = _elem[hi++];
	}
	_size = lo;
	shrink();
}

template<typename T>
inline const T & Vector<T>::remove( Rank index ) {
	T val = _elem[index];
	remove( index, index + 1 );
	return val;
}

template<typename T>
inline bool Vector<T>::isordered( bool ascending ) const {
	if ( _size < 2 )
		return true;
	if ( ascending ) {
		for ( int i = 1; i < _size; i++ ) {
			if ( _elem[i] <= _elem[i - 1] )
				return false;
		}
	} else {
		for ( int i = 1; i < _size; i++ ) {
			if ( _elem[i] >= _elem[i - 1] )
				return false;
		}
	}
	return true;
}

template<typename T>
inline Rank Vector<T>::find( const T & val, Rank lo, Rank hi ) {
	for ( int i = lo; i < hi; i++ ) {
		if ( _elem[i] == val )
			return i;
	}
	return -1;
}

template<typename T>
inline Rank Vector<T>::findRemove( const T & val ) {
	for ( int i = 0; i < _size; i++ ) {
		if ( _elem == val ) {
			int index = i + 1;
			while ( index < _size ) {
				_elem[index - 1] = _elem[index];
			}
			_size--;
			return i;
		}
	}
	return -1;
}

template<typename T>
inline Rank Vector<T>::deduplicate() {
	Rank oldSize = _size;
	Rank i = 1;
	while ( i < _size ) {
		(find( _elem[i], 0, i ) > 0) ? remove( i ) : i++;
	}
	return oldSize - _size;
}

template<typename T>
inline void Vector<T>::sort( Rank lo, Rank hi, int SortType ) {
	switch ( SortType ) {
		case 1: mergeSort( lo, hi ); break;
		case 2: quickSort( lo, hi ); break;
		case 3: bubbleSort( lo, hi ); break;
		case 4: selectionSort( lo, hi ); break;
	}
}

template<typename T>
inline void Vector<T>::sort( int SortType ) {
	sort( 0, _size, SortType );
}


// swap function
template<typename T>
void v_swap( T & a, T & b ) {
	T c( std::move( a ) ); a = std::move( b ); b = std::move( c );
};

// 随机置乱 Vector
template<typename T>
void unsort( Vector<T> & vec ) {
	for ( int i = vec.size(); i > 0; i-- ) {
		v_swap<T>( vec[i - 1], vec[std::rand() % i] );
	}
};

// the max of ( a, b )
template<typename T>
const T & v_max( T & a, T & b ) {
	return (a >= b) ? a : b;
}

// the min of ( a, b )
template<typename T>
const T & v_min( T & a, T & b ) {
	return (a <= b) ? a : b;
}


#endif // !__ADT_VECTOR__