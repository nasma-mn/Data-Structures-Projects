//
// Created by assin on 5/4/2025.
//

#ifndef MIVNI_ROUND2_HW1_PLAYLIST_H
#define MIVNI_ROUND2_HW1_PLAYLIST_H

#include "AVL_Tree.h"
#include "Song.h"
#include "SongPlaysKey.h"
class Playlist {
private:
    int ID;

    AVL_Tree<int,Song> *songs_by_id;
    AVL_Tree<SongPlaysKey,Song>* songs_by_plays;
public:
    Playlist(int id):ID(id){
        songs_by_id = new AVL_Tree<int,Song>();
        songs_by_plays = new AVL_Tree<SongPlaysKey,Song>();
    }
    ~Playlist(){

//    delete songs_by_id;
//
//    delete songs_by_plays;
    }
int getID () const{
    return ID;
}
AVL_Tree<int,Song>* getSongsByID() const{
    return songs_by_id;
}

AVL_Tree<SongPlaysKey,Song>* getSongsByPlays() const{
    return songs_by_plays;
}
void setSongsByID(AVL_Tree<int,Song>* s) {
    songs_by_id = s;
}
void setSongsByPlays(AVL_Tree<SongPlaysKey,Song>* s) {
    songs_by_plays = s;
}


};


#endif //MIVNI_ROUND2_HW1_PLAYLIST_H
