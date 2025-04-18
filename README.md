# Series of Practical Work in C Programming (S5 EII) 2024-2025

This series of practical exercises in C programming for the S5 EII semester in the 2024-2025 academic year explores fundamental programming concepts and data structures through nine practical exercises, each session is 2 hours long.

## Overview
This practical course aims to familiarize me with:
*   **Fundamental data structures** such as stacks, singly and doubly linked lists (with sentinels), and trees (binary search trees, AVL trees, Huffman trees).
*   **Dynamic memory management** techniques.
*   **Manipulating binary files**, particularly the BMP format.
*   **Modular programming principles** and using **Makefiles** for managing C projects.
*   Advanced concepts like **function pointers**, **variadic functions (ellipsis `...`)**, and the `static` keyword.
*   **Unit testing** basics.
*   Implementing **classic algorithms** such as postfix expression evaluation, sorting algorithms (implicitly through `qsort` in TP7), and Dijkstra's algorithm.
*   Introduction to practical applications like a media player and a coding method (Huffman).
*   Tools for development, including **Doxygen** for documentation and basic **memory leak detection** techniques.
---

## Summary of Practical Exercises
*   **TP1: Stack Data Structure**
    *   Main objectives: Implementing an integer stack (LIFO), using a variadic function (`fill_stack`), evaluating postfix expressions with a stack, using function pointers for operators, mastering the `static` keyword, introducing unit testing, and writing `Makefile` for multiple programs. 
*   **TP2: Image Structure: Dynamic Allocation and Binary Files**
    *   Main objectives: Dynamic memory allocation for a square image structure, implementing functions for creation, deallocation, access (getters/setters), filling, and displaying. Introduction to reading binary files to load images. 
*   **TP3: RGB Image: Dynamic Allocation**
    *   Main objectives: Deepening dynamic allocation for an RGB image structure (with pixel representation in memory as a 1D array), linking with third-party binary code (`BMPFile_teacher.o`), and writing a `Makefile` integrating this code for saving in BMP format.
*   **TP4: Binary Files: Bitmap Format**
    *   Main objectives: Reading and writing binary files by exploring the BMP image format. Manipulating headers (File Header and DIB Header) and handling pixel line padding. 
*   **TP5: Multimedia Application: Model with a List**
    *   Main objectives: Implementing a singly linked list module to manage a collection of multimedia objects (photos and videos), using dynamic memory allocation with lists, and introducing software design that promotes code reuse. 
*   **TP6: Doubly Linked List: Basic Memory Leak Detector**
    *   Main objectives: Implementing a doubly linked list with sentinel nodes, manipulating addresses (including `void` pointers), overloading functions with macros, and using the doubly linked list to implement a basic memory leak detector. 
*   **TP7: Balanced Trees: AVL Trees**
    *   Main objectives: Manipulating binary search trees, using recursive programming to implement AVL tree properties (self-balancing through rotations). Introduction to `qsort` and reading data from a binary file to construct a tree. 
*   **TP8: Trees: Huffman Coding**
    *   Main objectives: Implementing a binary tree, using recursion, constructing a tree with a bottom-up approach, and implementing Huffman coding for data compression. Possible use of precompiled code for list management and Huffman methods (`list_teacher.o`, `huffman_method_teacher.o`, `image-proba-teacher.o`). [30-34]
*   **TP9: Graphs: Dijkstra's Algorithm**
    *   Main objectives: Implementing functionality for a weighted directed graph using linked lists and implementing Dijkstra's algorithm to find the shortest path between two vertices. 

---
## Credits
This practical work material is provided by **Professor Muriel Pressigout** [mpressig@insa-rennes.fr]. I particularly thank her for designing the foundational structure of several exercises and for providing **starter code**, which greatly facilitated learning.
Additionally, some practical exercises use **precompiled object files** for specific functionalities, notably files with the `*teacher.o` suffix (e.g., `BMPFile_teacher.o`, `list_teacher.o`, `huffman_method_teacher.o`, `image-proba-teacher.o`). These files were provided to help advance the exercises by offering reference solutions or complex functionalities that have already been implemented.
