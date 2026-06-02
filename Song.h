//
// Created by assin on 5/4/2025.
//

#ifndef MIVNI_ROUND2_HW1_SONG_H
#define MIVNI_ROUND2_HW1_SONG_H

class Song {
private:
    int ID;
    int numOfPlays;
    int counter;
    Song* song_ptr;
public:
    Song(int id, int num):ID(id),numOfPlays(num),counter(0),song_ptr(nullptr){}
//    Song(int id, int num,Song* ptr):ID(id),numOfPlays(num),counter(0),song_ptr(ptr){}
    Song(const Song& s)
            : ID(s.ID), numOfPlays(s.numOfPlays), counter(s.counter), song_ptr(s.song_ptr) {}
int getID () const{
    return ID;
}
int getNumOfPlays () const{
    return numOfPlays;
}
void setNumOfPlays(int n){
    numOfPlays = n;
}
    int getCounter () const{
        return counter;
    }
    void setCounter(int n){
        counter = n;
    }
    Song* getSongPtr () const{
        return song_ptr;
    }
    void setSongPtr(Song* s){
        song_ptr = s;
    }
//    friend std::ostream& operator<<(std::ostream& os, const Song& song) {
//        os << "SongID: " << song.ID
//           << ", Plays: " << song.numOfPlays
//           << ", Counter: " << song.counter;
//
//        if (song.song_ptr) {
//            os << ", SongPtr -> ID: " << song.song_ptr->ID;
//        } else {
//            os << ", SongPtr: nullptr";
//        }
//
//        return os;
//    }

};


#endif //MIVNI_ROUND2_HW1_SONG_H
