// 
// 234218 Data Structures 1.
// Semester: 2025B (Spring).
// Wet Exercise #1.
// 
// The following header file contains all methods we expect you to implement.
// You MAY add private methods and fields of your own.
// DO NOT erase or modify the signatures of the public methods.
// DO NOT modify the preprocessors in this file.
// DO NOT use the preprocessors in your other code files.
// 

#ifndef DSPOTIFY25SPRING_WET1_H_
#define DSPOTIFY25SPRING_WET1_H_
#include "SongPlaysKey.h"
#include "wet1util.h"
#include "exceptions.h"
#include "Playlist.h"
#include "Song.h"
#include "AVL_Tree.h"

class DSpotify {
private:
    const int ZERO = 0;
    AVL_Tree<int,Playlist> playlists;
    AVL_Tree<int,Song> songs;

    //
    // Here you may add anything you want
    //


    void store_in_order(AVL_Tree<int, Song>* tree, Node<int, Song>** arr, int& index) {
        for (auto it = tree->begin(); *it != nullptr; ++it) {
            arr[index++] = *it;
        }
    }
    void store_in_order2(AVL_Tree<SongPlaysKey, Song>* tree, Node<SongPlaysKey, Song>** arr, int& index) {
        for (auto it = tree->begin(); *it != nullptr; ++it) {
            arr[index++] = *it;
        }
    }

    Node<int, Song>** merge_arrays(Node<int, Song>** arr1, int size1,
                                   Node<int, Song>** arr2, int size2, int& merged_size) {
        int i = 0, j = 0, k = 0;
        Node<int, Song>** merged = new Node<int, Song>*[size1 + size2];

        while (i < size1 && j < size2) {
            if (*(arr1[i]->key) < *(arr2[j]->key)) {
                merged[k++] = arr1[i++];
            } else if (*(arr1[i]->key) > *(arr2[j]->key)) {
                merged[k++] = arr2[j++];
            } else {
                // Equal keys: choose one (e.g. from arr1) and skip duplicate

                merged[k] = arr1[i];

                //print_node_array<int,Song>(merged,k);

                arr2[j]->data->getSongPtr()->setCounter(arr2[j]->data->getSongPtr()->getCounter() - 1);
                k++; i++;
                j++;
            }
        }

        while (i < size1) {
            merged[k++] = arr1[i++];
        }

        while (j < size2) {
            merged[k++] = arr2[j++];
        }

        merged_size = k;
        return merged;
    }

    Node<SongPlaysKey, Song>** merge_arrays2(Node<SongPlaysKey, Song>** arr1, int size1,
                                             Node<SongPlaysKey, Song>** arr2, int size2, int& merged_size) {
        int i = 0, j = 0, k = 0;
        Node<SongPlaysKey, Song>** merged = new Node<SongPlaysKey, Song>*[size1 + size2];

        while (i < size1 && j < size2) {
            if (*(arr1[i]->key) < *(arr2[j]->key)) {
                merged[k++] = arr1[i++];
            } else if (*(arr1[i]->key) > *(arr2[j]->key)) {
                merged[k++] = arr2[j++];
            } else {
                // Equal keys: choose one (e.g. from arr1) and skip duplicate

                merged[k] = arr1[i];
                k++; i++;
                j++;
            }
        }

        while (i < size1) {
            merged[k++] = arr1[i++];
        }

        while (j < size2) {
            merged[k++] = arr2[j++];
        }

        merged_size = k;
        return merged;
    }

// Helper function to build a balanced subtree from array

    Node<int, Song>* build_balanced_subtree(Node<int, Song>** arr, int start, int end) {
        if (start > end) return nullptr;

        int mid = (start + end) / 2;

        Node<int, Song>* node = new Node<int, Song>(*(arr[mid]->key), *(arr[mid]->getData()));


        node->left = build_balanced_subtree(arr, start, mid - 1);
        node->right = build_balanced_subtree(arr, mid + 1, end);

        if (node->left) node->left->father = node;
        if (node->right) node->right->father = node;

        node->updateHeight();

        return node;
    }

    AVL_Tree<int, Song>* build_balanced_tree(Node<int, Song>** arr, int start, int end) {
        AVL_Tree<int, Song>* tree = new AVL_Tree<int, Song>();
        tree->root = build_balanced_subtree(arr, start, end);
        return tree;
    }

    Node<SongPlaysKey, Song>* build_balanced_subtree2(Node<SongPlaysKey, Song>** arr, int start, int end) {
        if (start > end) return nullptr;

        int mid = (start + end) / 2;

        Node<SongPlaysKey, Song>* node = new Node<SongPlaysKey, Song>(*(arr[mid]->key), *(arr[mid]->getData()));


        node->left = build_balanced_subtree2(arr, start, mid - 1);
        node->right = build_balanced_subtree2(arr, mid + 1, end);

        if (node->left) node->left->father = node;
        if (node->right) node->right->father = node;

        node->updateHeight();

        return node;
    }

    AVL_Tree<SongPlaysKey, Song>* build_balanced_tree2(Node<SongPlaysKey, Song>** arr, int start, int end) {
        AVL_Tree<SongPlaysKey, Song>* tree = new AVL_Tree<SongPlaysKey, Song>();
        tree->root = build_balanced_subtree2(arr, start, end);
        return tree;
    }
    void delete_playlists_tree(Node<int, Playlist>* node) {
        if (!node) return;

        delete_playlists_tree(node->left);
        delete_playlists_tree(node->right);

        Playlist* playlist = node->getData();

        if (playlist->getSongsByID()) {
            playlist->getSongsByID()->treeClear();
            delete playlist->getSongsByID();
        }

        if (playlist->getSongsByPlays()) {
            playlist->getSongsByPlays()->treeClear();
            delete playlist->getSongsByPlays();
        }
    }

public:
    // <DO-NOT-MODIFY> {
    DSpotify();

    virtual ~DSpotify();

    StatusType add_playlist(int playlistId);

    StatusType delete_playlist(int playlistId);

    StatusType add_song(int songId, int plays);

    StatusType add_to_playlist(int playlistId, int songId);

    StatusType delete_song(int songId);

    StatusType remove_from_playlist(int playlistId, int songId);

    output_t<int> get_plays(int songId);

    output_t<int> get_num_songs(int playlistId);

    output_t<int> get_by_plays(int playlistId, int plays);

    StatusType unite_playlists(int playlistId1, int playlistId2);
    // } </DO-NOT-MODIFY>
};


#endif // DSPOTIFY25SPRING_WET1_H_