// You can edit anything you want in this file.
// However you need to implement all public DSpotify function, as provided below as a template

#include "dspotify25b1.h"


DSpotify::DSpotify():playlists(),songs(){

}

DSpotify::~DSpotify(){

// First, delete all playlists
    if (playlists.root != nullptr) {
        delete_playlists_tree(playlists.getRoot());
    }

    // Then, delete all songs
    songs.treeClear(); // Assuming this safely deletes all nodes in the songs AVL_Tree

//    for (auto it = playlists.begin(); *it != nullptr; ++it) {
//        (*it)->getData()->getSongsByID()->treeClear();
//        (*it)->getData()->getSongsByPlays()->treeClear();
//    }

    //songs.treeClear();
//    auto it = playlists.begin();
//    while ( *it != nullptr) {
//        auto temp =++it;
//        delete (*it)->getData()->getSongsByID();
//        delete (*it)->getData()->getSongsByPlays();
//        delete *it;
//        it = temp;
//    }

    //playlists.treeClear();

}

StatusType DSpotify::add_playlist(int playlistId){
    if( playlistId <=0 )
    {
        return StatusType::INVALID_INPUT;
    }
    if(playlists.find(playlistId)!= nullptr)
    {
        return StatusType::FAILURE;
    }

    try{

        playlists.insert(playlistId,{playlistId});

    } catch (std::bad_alloc& e){
        return StatusType::ALLOCATION_ERROR;
    }catch (const AlreadyExist& e) {
        return StatusType::FAILURE;
    }
    return StatusType::SUCCESS;

}

StatusType DSpotify::delete_playlist(int playlistId){
    if(playlistId <= 0){
        return StatusType::INVALID_INPUT;
    }
    Node<int,Playlist>* playlist_node = playlists.find(playlistId);
    if(playlist_node == nullptr || (playlist_node->getData()->getSongsByID() != nullptr &&
                                    playlist_node->getData()->getSongsByID()->getSize() > ZERO)){
        return StatusType::FAILURE;
    }
    try{
       // delete_playlists_tree(playlist_node);
        Playlist* playlist = playlist_node->getData();

        if (playlist->getSongsByID()) {
            playlist->getSongsByID()->treeClear();
            delete playlist->getSongsByID();
        }

        if (playlist->getSongsByPlays()) {
            playlist->getSongsByPlays()->treeClear();
            delete playlist->getSongsByPlays();
        }
        playlists.remove(playlistId);

    } catch(const DoNotExist& e){ //impossible case
        return StatusType::FAILURE;
    }
    catch( const std::bad_alloc& e){
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;

}

StatusType DSpotify::add_song(int songId, int plays){
    if( songId <=0 || plays < 0){
        return StatusType::INVALID_INPUT;
    }
    if(songs.find(songId)!= nullptr)
    {
        return StatusType::FAILURE;
    }


    try{
        songs.insert(songId,{songId,plays});
    } catch (std::exception& e){
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

StatusType DSpotify::add_to_playlist(int playlistId, int songId){
    if(playlistId <= 0 || songId <= 0) {
        return StatusType::INVALID_INPUT;
    }

    Node<int, Song>* song_node = songs.find(songId);
    Node<int, Playlist>* playlist_node = playlists.find(playlistId);

    if(song_node == nullptr || playlist_node == nullptr) {
        return StatusType::FAILURE;
    }
    if( playlist_node->getData()->getSongsByID()->find(songId)!= nullptr){
        return StatusType::FAILURE;
    }

    try{
        playlist_node->getData()->getSongsByID()->insert(
                song_node->getData()->getID(),
                {song_node->getData()->getID(),song_node->getData()->getNumOfPlays()});



        Node<int, Song>* n= playlist_node->getData()->getSongsByID()->find(songId);
        n->getData()->setSongPtr(song_node->getData());
        song_node->getData()->setCounter(song_node->getData()->getCounter() + 1);

        playlist_node->getData()->getSongsByPlays()->insert(
                {song_node->getData()->getNumOfPlays(), songId},
                {song_node->getData()->getNumOfPlays(),
                 song_node->getData()->getNumOfPlays()});

    } catch (std::exception& e){
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

StatusType DSpotify::delete_song(int songId){
    if(songId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    Node<int, Song>* song_node = songs.find(songId);
    if(song_node == nullptr || song_node->getData()->getCounter() != 0){
        return StatusType::FAILURE;
    }
    songs.remove(songId);

    return StatusType::SUCCESS;
}

StatusType DSpotify::remove_from_playlist(int playlistId, int songId){
    if(playlistId <= 0 || songId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    Node<int, Playlist>* playlist_node = playlists.find(playlistId);
    if(playlist_node == nullptr) {
        return StatusType::FAILURE;
    }
    Node<int,Song>* song_nodeID = playlist_node->getData()->getSongsByID()->find(songId);
    if(song_nodeID == nullptr) {
        return StatusType::FAILURE;
    }
    Node<SongPlaysKey,Song>* song_nodePlays = playlist_node->getData()->getSongsByPlays()->find(
            {song_nodeID->getData()->getNumOfPlays(),songId});
    if(song_nodePlays == nullptr){
        return StatusType::FAILURE;
    }

    song_nodeID->getData()->getSongPtr()->setCounter(song_nodeID->getData()->getSongPtr()->getCounter() - 1);
    int plays = song_nodeID->getData()->getNumOfPlays();

    playlist_node->getData()->getSongsByID()->remove(songId);
    playlist_node->getData()->getSongsByPlays()->remove({plays, songId});
    return StatusType::SUCCESS;
}

output_t<int> DSpotify::get_plays(int songId){
    if(songId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    Node<int, Song>* song_node = songs.find(songId);
    if(song_node == nullptr){
        return StatusType::FAILURE;
    }
    return {song_node->getData()->getNumOfPlays()};
}

output_t<int> DSpotify::get_num_songs(int playlistId){
    if(playlistId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    Node<int, Playlist>* playlist_node = playlists.find(playlistId);
    if(playlist_node == nullptr){
        return StatusType::FAILURE;
    }
    if(playlist_node->getData()->getSongsByID()->root == nullptr){
        return {0};
    }
    return {playlist_node->getData()->getSongsByID()->getSize()};
}

output_t<int> DSpotify::get_by_plays(int playlistId, int plays){
    if (playlistId <= 0 || plays < 0) {
        return {StatusType::INVALID_INPUT};
    }

    auto* playlist_node = playlists.find(playlistId);
    if (!playlist_node) return {StatusType::FAILURE};

    SongPlaysKey search_key{plays, 0}; // Start from songId = 0 to get smallest
    Node<SongPlaysKey, Song>* match = playlist_node->getData()->getSongsByPlays()->lower_bound(search_key);

    if (!match) {
        return {StatusType::FAILURE};
    }

    return {match->key->songId};
}

StatusType DSpotify::unite_playlists(int playlistId1, int playlistId2){

    if (playlistId1 <= 0 || playlistId2 <= 0 || playlistId1 == playlistId2) {
        return StatusType::INVALID_INPUT;
    }

    auto* playlist_node1 = playlists.find(playlistId1);
    auto* playlist_node2 = playlists.find(playlistId2);

    if (!playlist_node1 || !playlist_node2) {
        return StatusType::FAILURE;
    }

    auto songsByID1 = playlist_node1->getData()->getSongsByID();
    auto songsByID2 = playlist_node2->getData()->getSongsByID();

    auto songsByPlays1 = playlist_node1->getData()->getSongsByPlays();
    auto songsByPlays2 = playlist_node2->getData()->getSongsByPlays();


    int size1 = songsByID1->getSize();
    int size2 = songsByID2->getSize();

    // Create arrays for deep copy of song nodes
    Node<int, Song>** arr1 = new Node<int, Song>*[size1];
    Node<int, Song>** arr2 = new Node<int, Song>*[size2];
    Node<SongPlaysKey, Song>** arr11 = new Node<SongPlaysKey, Song>*[size1];
    Node<SongPlaysKey, Song>** arr22 = new Node<SongPlaysKey, Song>*[size2];
    int index1 = 0, index2 = 0,index3 = 0, index4=0;

    if (songsByID1->root) store_in_order(songsByID1, arr1, index1);
    if (songsByID2->root) store_in_order(songsByID2, arr2, index2);


    if (songsByPlays1->root) store_in_order2(songsByPlays1, arr11, index3);
    if (songsByPlays2->root) store_in_order2(songsByPlays2, arr22, index4);


    int merged_size = 0;
    Node<int, Song>** merged = nullptr;
    try {
        merged = merge_arrays(arr1, size1, arr2, size2, merged_size);
    } catch (...) {
        delete[] arr1;
        delete[] arr2;
        return StatusType::ALLOCATION_ERROR;
    }

    // Build new AVL tree from merged array
    AVL_Tree<int, Song>* newSongsByID = nullptr;
    try {
        newSongsByID = build_balanced_tree(merged, 0, merged_size - 1);
        newSongsByID->size = merged_size;
    } catch (...) {
        delete[] arr1;
        delete[] arr2;
        delete[] merged;
        return StatusType::ALLOCATION_ERROR;
    }




    //FOR PLAYS!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    int merged_size2 = 0;
    Node<SongPlaysKey, Song>** merged2 = nullptr;
    try {
        merged2 = merge_arrays2(arr11, size1, arr22, size2, merged_size2);
    } catch (...) {
        delete[] arr11;
        delete[] arr22;
        return StatusType::ALLOCATION_ERROR;
    }

    // Build new AVL tree from merged array
    AVL_Tree<SongPlaysKey, Song>* newSongsByPlays = nullptr;
    try {
        newSongsByPlays = build_balanced_tree2(merged2, 0, merged_size2 - 1);
        newSongsByPlays->size = merged_size2;
    } catch (...) {
        delete[] arr11;
        delete[] arr22;
        delete[] merged2;
        return StatusType::ALLOCATION_ERROR;
    }




    playlist_node1->getData()->getSongsByID()->treeClear();
    delete playlist_node1->getData()->getSongsByID();
//    playlist_node2->getData()->getSongsByID()->treeClear();
//    delete playlist_node2->getData()->getSongsByID();


    playlist_node1->getData()->getSongsByPlays()->treeClear();
    delete playlist_node1->getData()->getSongsByPlays();
//    playlist_node2->getData()->getSongsByPlays()->treeClear();
//    delete playlist_node2->getData()->getSongsByPlays();


//    delete_playlist(playlistId2);


    playlist_node1->getData()->setSongsByID(newSongsByID);
    playlist_node1->getData()->setSongsByPlays(newSongsByPlays);

    // Decrement counters from playlist2


    // Remove playlist2


    delete[] arr1;
    delete[] arr2;
    delete[] merged;

    delete[] arr11;
    delete[] arr22;
    delete[] merged2;


    playlist_node2->getData()->getSongsByID()->treeClear();
    delete playlist_node2->getData()->getSongsByID();
//    playlist_node2->getData()->getSongsByID()->treeClear();
//    delete playlist_node2->getData()->getSongsByID();


    playlist_node2->getData()->getSongsByPlays()->treeClear();
    delete playlist_node2->getData()->getSongsByPlays();

    playlists.remove(playlistId2);
    return StatusType::SUCCESS;
}

//