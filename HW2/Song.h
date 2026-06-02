//
// Created by assin on 6/15/2025.
//
#pragma once
#ifndef DS_WET2_SPRING_2025_SONG_H
#define DS_WET2_SPRING_2025_SONG_H
#include "Node.h"
class Genre;
class Song {

public:
    int songId;
    int numOfGenreChanges;
    Node<Genre>* genre;

    Song(int id):songId(id),numOfGenreChanges(1),genre(nullptr){}
};


#endif //DS_WET2_SPRING_2025_SONG_H
