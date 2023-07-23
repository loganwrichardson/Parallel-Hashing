//
// Created by lwrdev on 7/20/23.
//

#ifndef COMPREHENSIVE_VIDHI_AND_LOGAN_HASING_H
#define COMPREHENSIVE_VIDHI_AND_LOGAN_HASING_H

#endif //COMPREHENSIVE_VIDHI_AND_LOGAN_HASING_H

// Function Declarations
void init_hash_table();
int hash_func(int key);
struct node* get_element(struct node *list, int find_index);
void insert(int key, int value);
void rehash();
void remove_node(int key);
int find(int key, struct node *list);
