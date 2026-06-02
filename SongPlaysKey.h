//
// Created by assin on 5/4/2025.
//

#ifndef MIVNI_ROUND2_HW1_SONGPLAYSKEY_H
#define MIVNI_ROUND2_HW1_SONGPLAYSKEY_H


class SongPlaysKey {
public:
    int plays;
    int songId;

SongPlaysKey(int plays,int songId):plays(plays),songId(songId){}
    bool operator<(const SongPlaysKey& other) const {
        if (plays != other.plays)
            return plays < other.plays;
        return songId < other.songId;
    }

    bool operator==(SongPlaysKey& other) const {
        return plays == other.plays && songId == other.songId;
    }

    bool operator>(const SongPlaysKey& other) const {
        if (plays != other.plays)
            return plays > other.plays;
        return songId > other.songId;
    }

};


#endif //MIVNI_ROUND2_HW1_SONGPLAYSKEY_H
