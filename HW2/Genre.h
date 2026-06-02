//
// Created by assin on 6/15/2025.
//
#pragma once
#ifndef DS_WET2_SPRING_2025_GENRE_H
#define DS_WET2_SPRING_2025_GENRE_H

#include "Node.h"
class Song;
class Genre {
public:
    int genreId;
    int size;
    Node<Song>* flippedTreeRoot;
    Genre(int id):genreId(id),size(0),flippedTreeRoot(nullptr){}


};


#endif //DS_WET2_SPRING_2025_GENRE_H
