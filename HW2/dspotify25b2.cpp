// You can edit anything you want in this file.
// However you need to implement all public DSpotify function, as provided below as a template

#include "dspotify25b2.h"


DSpotify::DSpotify():m_genres(), m_songs()
{

}

DSpotify::~DSpotify(){
    for (int i = 0; i < m_genres.genres.getCapacity(); ++i) {
        Node<Genre>* curr = m_genres.genres.getHashTable()[i].getStart();
        while(curr!= nullptr){
            Node<Genre> *temp = curr;
            curr = curr->m_next;
            delete temp->getData();
            delete temp;
        }
    }
    for (int i = 0; i < m_songs.getCapacity(); ++i) {
        Node<Song>* curr = m_songs.getHashTable()[i].getStart();
        while(curr!= nullptr){
            Node<Song> *temp = curr;
            curr = curr->m_next;
            delete temp->getData();
            delete temp;
        }
    }
}

StatusType DSpotify::addGenre(int genreId){
    if(genreId <= 0){
        return StatusType::INVALID_INPUT;
    }
    if(m_genres.genres.find(genreId) != nullptr){
        return StatusType::FAILURE;
    }

    try{
        auto* genreNode = new Node<Genre>(genreId,genreId );
        m_genres.genres.insert(genreNode);

    }catch (std::exception& e){
        return StatusType::ALLOCATION_ERROR;
    }

    return StatusType::SUCCESS;

}

StatusType DSpotify::addSong(int songId, int genreId){
    if(songId <= 0 || genreId <= 0){
        return StatusType::INVALID_INPUT;
    }
    Node<Genre>* g = m_genres.genres.find(genreId);
    Node<Song>* s = m_songs.find(songId);
    if(g == nullptr || s != nullptr){
        return StatusType::FAILURE;
    }
    try{
        Node<Song>* songNode = new Node<Song>(songId,songId );
        m_songs.insert(songNode);

        if (g->getData()->flippedTreeRoot == nullptr) {
            g->getData()->flippedTreeRoot = songNode;
            songNode->set_father(nullptr);
            songNode->getData()->genre = g;
        } else {
            songNode->set_father(g->getData()->flippedTreeRoot);
            songNode->getData()->numOfGenreChanges = (1 - g->getData()->flippedTreeRoot->getData()->numOfGenreChanges);
        }
        g->getData()->size = g->getData()->size + 1;
    }catch (std::exception& e){
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

StatusType DSpotify::mergeGenres(int genreId1, int genreId2, int genreId3){

    if(genreId1 <= 0 || genreId2 <= 0 ||genreId3 <= 0 || genreId1 == genreId2 || genreId1 == genreId3
        || genreId2 == genreId3 ){
        return StatusType::INVALID_INPUT;
    }
    Node<Genre>* genre1=m_genres.genres.find(genreId1);
    Node<Genre>* genre2 =m_genres.genres.find(genreId2);
    Node<Genre>* genre3 =m_genres.genres.find(genreId3);

    if(genre1 == nullptr || genre2 == nullptr || genre3 != nullptr){
        return StatusType::FAILURE;
    }

    addGenre(genreId3);


    genre3 = m_genres.genres.find(genreId3);
    m_genres.unite(genre1,genre2,genre3);

    return StatusType::SUCCESS;
}

output_t<int> DSpotify::getSongGenre(int songId){
    if(songId <= 0){
        return{StatusType::INVALID_INPUT};
    }
    Node<Song>* s=m_songs.find(songId);
    if(s == nullptr){
        return {StatusType::FAILURE};
    }
    return {m_genres.Find(s)->getData()->genreId};
}

output_t<int> DSpotify::getNumberOfSongsByGenre(int genreId){
    if(genreId <= 0){
        return{StatusType::INVALID_INPUT};
    }
    Node<Genre>* g=m_genres.genres.find(genreId);
    if(g == nullptr){
        return {StatusType::FAILURE};
    }
    return {g->getData()->size};
}

output_t<int> DSpotify::getNumberOfGenreChanges(int songId){
    if(songId <= 0){
        return{StatusType::INVALID_INPUT};
    }
    Node<Song>* s = m_songs.find(songId);
    if(s == nullptr){
        return {StatusType::FAILURE};
    }
    return {m_genres.Find2(s)};
}
