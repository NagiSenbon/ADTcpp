#pragma once

template<typename T> struct BinNode;                             // �����������
template<typename T> using BinNodePosi = BinNode<template> *;    // ���������ָ��

template<typename T>
constexpr auto stature( T p ) { return ( ( p ) ? ( p )->height : -1 ); }

