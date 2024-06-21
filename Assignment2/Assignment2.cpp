#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Node structure for the linked list
struct Node {
    int data;
    Node* next;

    Node(int val) : data(val), next(nullptr) {}
};

// Nested list structure
struct NestedList {
    int bound;
    Node* head;
    NestedList* next;

    NestedList(int b) : bound(b), head(nullptr), next(nullptr) {}
};

// Function to create a new list with a given bound
NestedList* createList(int bound) {
    return new NestedList(bound);
}

// Function to insert a new node at the front of the list
void insertFront(NestedList& list, int value) {
    Node* newNode = new Node(value);
    newNode->next = list.head;
    list.head = newNode;
}

// Function to insert a new node in the middle of the list
void insertMiddle(NestedList& list, int value, int position) {
    Node* newNode = new Node(value);
    Node* current = list.head;
    int index = 0;
    while (current && index < position - 1) {
        current = current->next;
        index++;
    }
    if (current) {
        newNode->next = current->next;
        current->next = newNode;
    }
}

// Function to insert a new node at the end of the list
void insertEnd(NestedList& list, int value) {
    Node* newNode = new Node(value);
    if (!list.head) {
        list.head = newNode;
    }
    else {
        Node* current = list.head;
        while (current->next) {
            current = current->next;
        }
        current->next = newNode;
    }
}

// Function to delete the front list
void deleteFrontList(NestedList*& myList) {
    if (!myList) return;
    NestedList* temp = myList;
    myList = myList->next;
    Node* current = temp->head;
    while (current) {
        Node* tempNode = current;
        current = current->next;
        delete tempNode;
    }
    delete temp;
}

// Function to delete the last item in the list
void deleteLastItem(NestedList& list) {
    if (!list.head) return;
    if (!list.head->next) {
        delete list.head;
        list.head = nullptr;
        return;
    }
    Node* current = list.head;
    while (current->next->next) {
        current = current->next;
    }
    delete current->next;
    current->next = nullptr;
}

// Function to search for a list with a specific bound
NestedList* searchListByBound(NestedList* myList, int bound) {
    NestedList* current = myList;
    while (current) {
        if (current->bound == bound) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

// Function to check if a value exists in the list
bool valueExistsInList(NestedList& list, int value) {
    Node* current = list.head;
    while (current) {
        if (current->data == value) {
            return true;
        }
        current = current->next;
    }
    return false;
}

// Function to delete all items in the list except a particular item
void deleteAllItemsExcept(NestedList& list, int value) {
    Node* current = list.head;
    Node* prev = nullptr;
    while (current) {
        if (current->data != value) {
            Node* temp = current;
            if (prev) {
                prev->next = current->next;
            }
            else {
                list.head = current->next;
            }
            current = current->next;
            delete temp;
        }
        else {
            prev = current;
            current = current->next;
        }
    }
}

// Function to merge two lists into a new list and store the merged values in the bound of the second list
NestedList* mergeLists(NestedList* list1, NestedList* list2, NestedList* myList, vector<int>& usedBounds) {
    int maxBound = max(list1->bound, list2->bound);

    Node* mergedHead = nullptr;
    Node* mergedTail = nullptr;

    Node* current = list1->head;
    while (current) {
        if (!valueExistsInList(*list2, current->data)) {
            Node* newNode = new Node(current->data);
            if (!mergedHead) {
                mergedHead = newNode;
                mergedTail = newNode;
            }
            else {
                mergedTail->next = newNode;
                mergedTail = newNode;
            }
        }
        current = current->next;
    }

    current = list2->head;
    while (current) {
        Node* newNode = new Node(current->data);
        if (!mergedHead) {
            mergedHead = newNode;
            mergedTail = newNode;
        }
        else {
            mergedTail->next = newNode;
            mergedTail = newNode;
        }
        current = current->next;
    }

    NestedList* mergedList = createList(maxBound);
    mergedList->head = mergedHead;

    // Updating the bound of the second list and replace its head with the merged list head
    list2->bound = maxBound;
    list2->head = mergedHead;

    if (!myList) {
        myList = list2;
    }
    else {
        NestedList* temp = myList;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = list2;
    }

    if (find(usedBounds.begin(), usedBounds.end(), maxBound) == usedBounds.end()) {
        usedBounds.push_back(maxBound);
    }

    return mergedList;
}

// Function to delete an item from a bound-list by index
void deleteItemByBoundAndIndex(NestedList* myList, int bound, int indexToDelete) {
    NestedList* current = myList;
    while (current) {
        if (current->bound == bound) {
            Node* prev = nullptr;
            Node* current_node = current->head;
            int index = 0;
            while (current_node) {
                if (index == indexToDelete) {
                    if (prev) {
                        prev->next = current_node->next;
                    }
                    else {
                        current->head = current_node->next;
                    }
                    delete current_node;
                    cout << "Item deleted successfully." << endl;
                    return;
                }
                prev = current_node;
                current_node = current_node->next;
                index++;
            }
            cout << "Index out of range." << endl;
            return;
        }
        current = current->next;
    }
    cout << "The list with bound " << bound << " couldn't be found." << endl;
}

// Function to display items in a list in reverse order using recursion
void displayReverse(Node* current) {
    if (current == nullptr) {
        return;
    }
    displayReverse(current->next);
    cout << current->data << " ";
}

// Function to display items in a list specified by the user in reverse order
void displayListReverse(NestedList* myList, int bound) {
    NestedList* displayList = searchListByBound(myList, bound);
    if (displayList) {
        cout << "Items in list with bound " << bound << " in reverse order: ";
        displayReverse(displayList->head);
        cout << endl;
    }
    else {
        cout << "List with bound " << bound << " not found." << endl;
    }
}

// Function to search for a list with a specific bound in the nested list
NestedList* searchNestedList(NestedList* myList, int bound) {
    NestedList* current = myList;
    while (current) {
        if (current->bound == bound) {
            return current;
        }
        current = current->next;
    }
    return nullptr; // Return nullptr if the list with the specified bound is not found
}

int main() {
    NestedList* myList = nullptr;
    vector<int> usedBounds;
    vector<int> boundOrder;
    int choice, bound, value;

    while (true)
    {
        cout << endl;
        cout << "<------------- BOUND LIST MENU ------------->" << endl;
        cout << "1. Create a new bound list" << endl;
        cout << "2. Insert numbers" << endl;
        cout << "3. Merge two bound lists" << endl;
        cout << "4. Delete " << endl;
        cout << "5. Display " << endl;
        cout << "6. Search" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter a bound number for the new list: ";
            cin >> bound;
            if (find(usedBounds.begin(), usedBounds.end(), bound) == usedBounds.end()) {
                usedBounds.push_back(bound);
                boundOrder.push_back(bound);
                if (!myList) {
                    myList = createList(bound);
                }
                else {
                    NestedList* newList = createList(bound);
                    newList->next = myList;
                    myList = newList;
                }
                cout << "New list with unique bound created " << bound << "." << endl;
            }
            else {
                cout << "Bound already exists" << endl;
            }
            break;


        case 2:
            while (true) {
                cout << endl;
                cout << "Insert Numbers:" << endl;
                cout << "1. Insert a number at the front" << endl;
                cout << "2. Insert a number in the middle" << endl;
                cout << "3. Insert a number at the end of the list" << endl;
                cout << "0. Back" << endl;
                cout << "Enter your insert choice: ";
                cin >> choice;

                switch (choice) {
                case 1:
                    if (!myList) {
                        cout << "Create a bound-list first." << endl;
                    }
                    else {
                        cout << "Enter the bound of the list to insert the number: ";
                        cin >> bound;
                        NestedList* insertList = searchListByBound(myList, bound);
                        if (insertList) {
                            cout << "Enter the value to insert: ";
                            cin >> value;
                            if (value <= bound) {
                                insertFront(*insertList, value);
                            }
                            else {
                                cout << "Cannot exceed bound value." << endl;
                            }
                        }
                        else {
                            cout << "The list with bound " << bound << " couldn't be found." << endl;
                        }
                    }
                    break;
                case 2:
                    if (!myList) {
                        cout << "Create a bound-list first." << endl;
                    }
                    else {
                        cout << "Enter the bound of the list to insert the number: ";
                        cin >> bound;
                        NestedList* insertList = searchListByBound(myList, bound);
                        if (insertList) {
                            cout << "Enter the value to insert: ";
                            cin >> value;
                            cout << "Enter the position to insert: ";
                            int position;
                            cin >> position;
                            if (value <= bound) {
                                if (position == 0) {
                                    insertFront(*insertList, value);
                                }
                                else {
                                    insertMiddle(*insertList, value, position);
                                }
                            }
                            else {
                                cout << "Cannot exceed bound value." << endl;
                            }
                        }
                        else {
                            cout << "The list with bound " << bound << " couldn't be found." << endl;
                        }
                    }
                    break;
                case 3:
                    if (!myList) {
                        cout << "Create a bound-list first." << endl;
                    }
                    else {
                        cout << "Enter the bound of the list to insert the number at the end: ";
                        cin >> bound;
                        NestedList* insertList = searchListByBound(myList, bound);
                        if (insertList) {
                            cout << "Enter the value to insert at the end: ";
                            cin >> value;
                            if (value <= bound) {
                                insertEnd(*insertList, value);
                            }
                            else {
                                cout << "Cannot exceed bound value." << endl;
                            }
                        }
                        else {
                            cout << "The list with bound " << bound << " couldn't be found." << endl;
                        }
                    }
                    break;
                case 0:
                    break;
                default:
                    cout << "Invalid choice" << endl;
                }
                if (choice == 0) break;
            }
            break;
        case 3:
            if (!myList) {
                cout << "Create a bound-list first." << endl;
            }
            else {
                int bound1, bound2;
                cout << "Enter the bound of the first list: ";
                cin >> bound1;
                cout << "Enter the bound of the second list: ";
                cin >> bound2;

                NestedList* list1 = searchListByBound(myList, bound1);
                NestedList* list2 = searchListByBound(myList, bound2);

                if (list1 && list2) {
                    NestedList* mergedList = mergeLists(list1, list2, myList, usedBounds);
                    cout << "Merged bound list created " << list2->bound << "." << endl;

                    // Display merged values
                    cout << "Merged values: ";
                    Node* mergedCurrent = mergedList->head;
                    while (mergedCurrent) {
                        cout << mergedCurrent->data << " ";
                        mergedCurrent = mergedCurrent->next;
                    }
                    cout << endl;
                }
                else {
                    cout << "Specified lists do not exist." << endl;
                }
            }
            break;


        case 4:
            while (true) {
                cout << endl;
                cout << "Delete:" << endl;
                cout << "1. Delete the front list" << endl;
                cout << "2. Delete an item from a bound-list by index" << endl;
                cout << "3. Delete the last item in a list" << endl;
                cout << "4. Delete all items in a list except a particular item" << endl;
                cout << "0. Back" << endl;
                cout << "Enter your delete choice: ";
                cin >> choice;

                switch (choice) {
                case 1:
                    if (!myList) {
                        cout << "Create a bound-list first." << endl;
                    }
                    else {
                        deleteFrontList(myList);
                        cout << "Front list deleted successfully." << endl;
                    }
                    break;
                case 2:
                    if (!myList) {
                        cout << "Create a bound-list first." << endl;
                    }
                    else {
                        cout << "Enter the bound of the list from which to delete an item: ";
                        cin >> bound;
                        NestedList* deleteList = searchListByBound(myList, bound);
                        if (deleteList) {
                            cout << "Enter the index of the item to delete: ";
                            int indexToDelete;
                            cin >> indexToDelete;
                            deleteItemByBoundAndIndex(myList, bound, indexToDelete);
                        }
                        else {
                            cout << "The list with bound " << bound << " couldn't be found." << endl;
                        }
                    }
                    break;
                case 3:
                    if (!myList) {
                        cout << "Create a bound-list first." << endl;
                    }
                    else {
                        cout << "Enter the bound of the list from which you want to delete the last item: ";
                        cin >> bound;
                        NestedList* deleteLastList = searchListByBound(myList, bound);
                        if (deleteLastList) {
                            if (deleteLastList->head) {
                                deleteLastItem(*deleteLastList);
                                cout << "Last item deleted " << bound << "." << endl;
                            }
                            else {
                                cout << "The list with bound " << bound << " is already empty." << endl;
                            }
                        }
                        else {
                            cout << "The list with bound " << bound << " couldn't be found." << endl;
                        }
                    }
                    break;
                case 4:
                    if (!myList) {
                        cout << "Create a bound-list first." << endl;
                    }
                    else {
                        cout << "Enter the bound of the list: ";
                        cin >> bound;
                        NestedList* deleteAllExceptList = searchListByBound(myList, bound);
                        if (deleteAllExceptList) {
                            cout << "Enter the value to keep: ";
                            cin >> value;
                            if (valueExistsInList(*deleteAllExceptList, value)) {
                                deleteAllItemsExcept(*deleteAllExceptList, value);
                                cout << "All items except " << value << " deleted from the bound-list " << bound << "." << endl;
                            }
                            else {
                                cout << "Item " << value << " couldn't be found " << bound << "." << endl;
                            }
                        }
                        else {
                            cout << "The list with bound " << bound << " couldn't be found." << endl;
                        }
                    }
                    break;
                case 0:
                    break;
                default:
                    cout << "Invalid choice. Please try again." << endl;
                }
                if (choice == 0) break;
            }
            break;


        case 5:
            while (true) {
                cout << endl;
                cout << "Display Options:" << endl;
                cout << "1. Display bound values" << endl;
                cout << "2. Display items in a list" << endl;
                cout << "3. Display reversed order" << endl;
                cout << "0. Back" << endl;
                cout << "Enter your display choice: ";
                cin >> choice;

                switch (choice) {
                case 1:
                    if (usedBounds.empty()) {
                        cout << "No bound values exist." << endl;
                    }
                    else {
                        cout << "Bound values in the lists:";
                        for (int bound : usedBounds) {
                            cout << " " << bound;
                        }
                        cout << endl;
                    }
                    break;
                case 2:
                    if (!myList) {
                        cout << "Create a bound-list first." << endl;
                    }
                    else {
                        cout << "Enter the bound of the list to display items: ";
                        cin >> bound;
                        NestedList* displayList = searchListByBound(myList, bound);
                        if (displayList) {
                            Node* current = displayList->head;
                            int index = 1;
                            while (current) {
                                cout << "Item " << index << ": " << current->data << endl;
                                current = current->next;
                                index++;
                            }
                        }
                        else {
                            cout << "The list with bound " << bound << " couldn't be found." << endl;
                        }
                    }
                    break;
                case 3:
                    if (!myList) {
                        cout << "Create a list first." << endl;
                    }
                    else {
                        cout << "Enter the bound of the list to display items in reverse order: ";
                        cin >> bound;
                        displayListReverse(myList, bound);
                    }
                    break;
                case 0:
                    break;
                default:
                    cout << "Invalid choice. Please try again." << endl;
                }
                if (choice == 0) break;
            }
            break;


        case 6:
            if (!myList) {
                cout << "Create a list first." << endl;
            }
            else {
                cout << "Enter the bound of the list to search: ";
                cin >> bound;
                NestedList* foundList = searchNestedList(myList, bound);
                if (foundList) {
                    cout << "Nested list with bound " << bound << " found." << endl;
                    // You can choose to display the contents of the found list here if needed
                }
                else {
                    cout << "Nested list with bound " << bound << " not found." << endl;
                }
            }
            break;


        case 0:
            cout << "Exiting program." << endl;
            while (myList) {
                NestedList* temp = myList;
                myList = myList->next;
                Node* current = temp->head;
                while (current) {
                    Node* tempNode = current;
                    current = current->next;
                    delete tempNode;
                }
                delete temp;
            }
            return 0;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
    }

    return 0;
}
