// volsort.h

#ifndef VOLSORT_H
#define VOLSORT_H

#include <string>

struct Node {
    std::string string;
    int         number;
    Node       *next;
};

struct List {
    Node       *head;
    size_t      size;

    List(); 					// define in list.cpp
    ~List();					// define in list.cpp

  //    void push_front(const std::string &s);	//define below
};


typedef bool(*CompareFunction)(const Node *, const Node*);

// Functions -------------------------------------------------------------------

bool node_number_compare(const Node *a, const Node *b); 	//define in node.cpp, used by quick, merge and stl
bool node_string_compare(const Node *a, const Node *b);		//define in node.cpp, used by quick, merge and stl

void dump_node(Node *n);					//define in node.cpp, also useful for debugging

void stl_sort(List &l, bool numeric);	// define in stl.cpp - sort using std::sort
void qsort_sort(List &l, bool numeric);	// define in qsort.cpp - sort using qsort from cstdlib
void merge_sort(List &l, bool numeric);	// define in merge.cpp - your implementation
void quick_sort(List &l, bool numeric);	// define in quick.cpp - your implementation

#endif
