#ifndef SIZED_ARRAY_H
#define SIZED_ARRAY_H

// A type designed to hold an init_declarator_list (may be useful otherwise)
struct SizedArr {
    // Array of id's from comma-separated declarator list
    char ids[100][100];
    // Number of id's in the array
    int size;
};

#endif // #ifndef SIZED_ARRAY_H
