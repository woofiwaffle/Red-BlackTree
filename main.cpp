#include <iostream>
#include <cstdlib>
#include <vector>



struct Tree{
    int key;
    Tree* parent;
    Tree* leftChild;
    Tree* rightChild;
    bool isRed;
};



Tree* createTree(int key){
    Tree* node = new Tree;
    node->key = key;
    node->parent = nullptr;
    node->leftChild = nullptr;
    node->rightChild = nullptr;
    node->isRed = true;
    return node;
}



void rotateLeft(Tree*& root, Tree* node){
    Tree* rightChild = node->rightChild;
    node->rightChild = rightChild->leftChild;

    if(rightChild->leftChild != nullptr){
        rightChild->leftChild->parent = node;
    }

    rightChild->parent = node->parent;

    if(node->parent == nullptr){
        root = rightChild;
    }
    else if(node == node->parent->leftChild){
        node->parent->leftChild = rightChild;
    }
    else{
        node->parent->rightChild = rightChild;
    }

    rightChild->leftChild = node;
    node->parent = rightChild;
}



void rotateRight(Tree*& root, Tree* node){
    Tree* leftChild = node->leftChild;
    node->leftChild = leftChild->rightChild;

    if(leftChild->rightChild != nullptr){
        leftChild->rightChild->parent = node;
    }

    leftChild->parent = node->parent;

    if(node->parent == nullptr){
        root = leftChild;
    }
    else if(node == node->parent->leftChild){
        node->parent->leftChild = leftChild;
    }
    else{
        node->parent->rightChild = leftChild;
    }

    leftChild->rightChild = node;
    node->parent = leftChild;
}



void insertFixing(Tree*& root, Tree* node){
    while(node != root && node->parent->isRed){

        if(node->parent == node->parent->parent->leftChild){

            Tree* siblingChild = node->parent->parent->rightChild;

            if(siblingChild != nullptr && siblingChild->isRed){
                node->parent->isRed = false;
                siblingChild->isRed = false;
                node->parent->parent->isRed = true;
                node = node->parent->parent;
            }
            else{
                if(node == node->parent->rightChild){
                    node = node->parent;
                    rotateLeft(root, node);
                }
                node->parent->isRed = false;
                node->parent->parent->isRed = true;
                rotateRight(root, node->parent->parent);
            }
        }
        else{
            Tree* siblingChild = node->parent->parent->leftChild;
            if(siblingChild != nullptr && siblingChild->isRed){
                node->parent->isRed = false;
                siblingChild->isRed = false;
                node->parent->parent->isRed = true;
                node = node->parent->parent;
            }
            else{
                if(node == node->parent->leftChild){
                    node = node->parent;
                    rotateRight(root, node);
                }
                node->parent->isRed = false;
                node->parent->parent->isRed = true;
                rotateLeft(root, node->parent->parent);
            }
        }
    }
    root->isRed = false;
}



void insertTree(Tree*& root, Tree* node){
    Tree* y = nullptr;
    Tree* x = root;

    while(x != nullptr){
        y = x;
        if(node->key < x->key){
            x = x->leftChild;
        }
        else{
            x = x->rightChild;
        }
    }

    node->parent = y;
    if(y == nullptr){
        root = node;
    }
    else if(node->key < y->key){
        y->leftChild = node;
    }
    else{
        y->rightChild = node;
    }

    insertFixing(root, node);
}



void printTree(Tree* node, std::string indent = "", bool isLeft = true){
    if(node != nullptr){

        std::cout << indent;

        if(isLeft){
            std::cout << "*-- ";
            indent += "    ";
        }
        else{
            std::cout << "`-- ";
            indent += "|   ";
        }

        if(!node->isRed){
            std::cout << node->key << " (black)" << std::endl;
        }
        else{
            std::cout << node->key << " (red)" << std::endl;
        }

        printTree(node->leftChild, indent, false);

        printTree(node->rightChild, indent, true);
    }
}



int main() {
    Tree *root = nullptr;
    std::vector<int> elements;

    while(true){
        int choice;
        std::cout << "1. Create a Red-Black tree with random numbers\n";
        std::cout << "2. Print Red-Black tree\n";
        std::cout << "3. Exit\n";
        std::cout << "Choice: ";
        std::cin >> choice;
        std::cout << "\n------------------------------------------------------------------------------------\n";
        switch(choice){
            case 1: {
                int numElements;
                std::cout << "Enter the number of elements:";
                std::cin >> numElements;

                for(int i = 0; i < numElements; i++){
                    int num = rand() % 99;
                    elements.push_back(num);
                }

                std::cout << "Red-Black tree created\n";
                std::cout << "\n------------------------------------------------------------------------------------\n";
                break;
            }
            case 2: {
                for(int element : elements){
                    Tree* node = createTree(element);
                    insertTree(root, node);
                }
                printTree(root);
                std::cout << "\n------------------------------------------------------------------------------------\n";
                break;
            }
            case 3: {
                return 0;
            }
            default: {
                std::cout << "Invalid option. Please try again\n";
                std::cout << "\n------------------------------------------------------------------------------------\n";
                break;
            }
        }
    }
}