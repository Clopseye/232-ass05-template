// ============================================================
// CSCI 232 Assignment 05 – Evolution of Data Structures
// Student Implementation
// ============================================================
// Author: [Your Name Here]
// ============================================================

#include "code.hpp"
#include <iostream>
#include <format>

// ============================================================
// STAGE 0: Legacy C Union
// ============================================================

/// Converts a LegacyData union to a formatted string.
/// Format specs:
/// 'i' -> integer value as string (e.g., "42")
/// 'd' -> double value formatted to 2 decimal places (e.g., "3.14")
/// 'c' -> string pointer content (or "nullptr" if cPtr is null)
/// default -> "unknown"

std::string printLegacyData(LegacyData data, char type) {
    std::string result = "unknown";

    if (type == 'i') {
        result = std::format("{}", data.i);
        return result;
    }

    if (type == 'd') {
        result = std::format("{:.2f}", data.d);
        return result;
    }

    if (type == 'c') {
        if (data.cPtr != NULL) {
            result = std::format("{}", data.cPtr);
            return result;
        }
        else {
            return "nullptr";
        }
    }
    return result;
}

// ============================================================
// STAGE 1: C-Style Struct
// ============================================================

/// Initializes a structNode with value, type indicator, and nullptr nextPtr.
void initStructNode(structNode* nPtr, LegacyData val, char type) {
    // TODO: Check if nPtr is nullptr before assigning fields
    if (nPtr == nullptr) {
        return;
    }

    nPtr->value = val;
    nPtr->typeData = type;
    nPtr->nextPtr = nullptr;
}

/// Dynamically allocates two structNodes.
/// Node 1: int 5 ('i')
/// Node 2: double 3.14 ('d')
/// Links Node 1 -> Node 2 -> nullptr
/// Returns pointer to Node 1.
structNode* createTwoStructNodes() {
    // TODO: Allocate dynamically using new, initialize both nodes, link them, and return head
    structNode *node1 = new structNode;
    LegacyData val1; val1.i = 5;

    initStructNode(node1, val1, 'i');

    structNode *node2 = new structNode;
    LegacyData val2; val2.d = 3.14;

    initStructNode(node2, val2, 'd');

    node1->nextPtr = node2;

    return node1;
}

// ============================================================
// STAGE 2: Early C++ Class (Classic Constructor)
// ============================================================

/// Constructor: Assign fields inside curly braces.
/// DO NOT use member initializer lists here!

// uncomment the following code to implement the classNode constructor

classNode::classNode(LegacyData val, char type) {
        this->value = val;
        this->typeData = type;
        this->nextPtr = nullptr;
}

/// Dynamically allocates two classNodes (int 5, double 3.14) and links them.
classNode* createTwoClassNodes() {
    LegacyData val1; val1.i = 5;
    classNode* node1 = new classNode(val1, 'i');

    LegacyData val2; val2.d = 3.14;
    classNode* node2 = new classNode(val2, 'd');

    node1->nextPtr = node2;
    // TODO: Allocate dynamically, link nodes, and return head
    return node1;
}

// ============================================================
// STAGE 3: C++98 Templates
// ============================================================

/// Dynamically allocates two classNodeT<int> objects (int 5, int 3) and links them.
classNodeT<int>* createTwoTemplateNodes() {
    // TODO: Instantiate classNodeT<int> nodes using new, link them, and return head
    classNodeT<int>* node1 = new classNodeT<int>(5);

    classNodeT<int>* node2 = new classNodeT<int>(3);

    node1->nextPtr = node2;

    return node1;
}

// ============================================================
// STAGE 4: C++17 Variant and LinkedList Manager
// ============================================================

// uncomment the following code to implement the LinkedList methods

LinkedList::LinkedList() : headPtr(nullptr), counter(0) {
    // TODO: Initialize headPtr to nullptr and counter to 0
}

LinkedList::~LinkedList() {
    // TODO: Clean up memory by calling destroyList()
    destroyList();
}

void LinkedList::destroyList() {
    // TODO: Iterate through list, delete all nodes, and reset counter to 0
    classNodeVariant* current = headPtr;
    while (current != nullptr) {
        classNodeVariant* nextNode = current->nextPtr;
        delete current;
        current = nextNode;
    }
    headPtr = nullptr;
    counter = 0;
}

int LinkedList::addFirst(classNodeVariant* newNodePtr) {
    // TODO: Prepend node to the front of list, increment counter
    // Return -1 if newNodePtr is nullptr, 0 on success
    if (newNodePtr == nullptr) {
        return -1;
    }
    newNodePtr->nextPtr = headPtr;
    headPtr = newNodePtr;
    counter++;
    return 0;
}

int LinkedList::addLast(classNodeVariant* newNodePtr) {
    // TODO: Append node to the end of list, increment counter
    // Return -1 if newNodePtr is nullptr, 0 on success
    if (newNodePtr == nullptr) {
        return -1;
    }
    newNodePtr->nextPtr = nullptr;
    
    if (headPtr == nullptr) {
        headPtr = newNodePtr;
    } else {
        classNodeVariant* current = headPtr;
        while (current->nextPtr != nullptr) {
            current = current->nextPtr;
        }
        current->nextPtr = newNodePtr;
    }
    counter++;
    return 0;
}

int LinkedList::deleteFirst() {
    // TODO: Delete first node, update headPtr, decrement counter
    // Return -1 if list is empty, 0 on success
    if (headPtr == nullptr) {
        return -1;
    }
    classNodeVariant* temp = headPtr;
    headPtr = headPtr->nextPtr;
    delete temp;
    counter--;
    return 0;
}

int LinkedList::deleteLast() {
    // TODO: Find second-to-last node, delete last node, decrement counter
    // Return -1 if list is empty, 0 on success
    if (headPtr == nullptr) {
        return -1;
    }
    
    if (headPtr->nextPtr == nullptr) {
        delete headPtr;
        headPtr = nullptr;
    } else {
        classNodeVariant* current = headPtr;
        while (current->nextPtr->nextPtr != nullptr) {
            current = current->nextPtr;
        }
        delete current->nextPtr;
        current->nextPtr = nullptr;
    }
    counter--;
    return 0;
}

int LinkedList::deleteValue(ModernData targetValue) {
    // TODO: Traverse list, find node matching targetValue, unlink and delete it
    // Decrement counter
    // Return 0 if found and removed, -1 if not found or list is empty
    if (headPtr == nullptr) {
        return -1;
    }
    
    // Check if the head node matches
    if (headPtr->value == targetValue) {
        classNodeVariant* temp = headPtr;
        headPtr = headPtr->nextPtr;
        delete temp;
        counter--;
        return 0;
    }
    
    // Traverse to find the node
    classNodeVariant* current = headPtr;
    while (current->nextPtr != nullptr) {
        if (current->nextPtr->value == targetValue) {
            classNodeVariant* temp = current->nextPtr;
            current->nextPtr = temp->nextPtr;
            delete temp;
            counter--;
            return 0;
        }
        current = current->nextPtr;
    }
    
    return -1; // Value not found
}

int LinkedList::printList() {
    // TODO: Iterate through list and print each variant value to std::cout
    // Use std::holds_alternative or std::get
    // Return -1 if list is empty, 0 on success
    if (headPtr == nullptr) {
        return -1;
    }
    
    classNodeVariant* current = headPtr;
    while (current != nullptr) {
        // Printing the variant value safely using std::visit
        std::visit([](auto&& arg) {
            std::cout << arg << " ";
        }, current->value);
        
        current = current->nextPtr;
    }
    std::cout << std::endl;
    return 0;
}

int LinkedList::listLength() {
    // TODO: Return node count
    return counter;
}