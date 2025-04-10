#ifndef RANKTREE_H
#define RANKTREE_H
#include "RankNode.h"

template<class T, class Cond>
class RankTree{
    RankNode<T,Cond> *root;
    int size{};
    RankNode<T,Cond> *smallest;
    RankNode<T,Cond> *biggest;
public:
    RankTree(): root(nullptr), size(0), smallest(nullptr),biggest(nullptr){};
    RankTree(RankNode<T, Cond>* arr[],int size, int start, int end);
    void insert(const Cond& key,const T& data);
    virtual ~RankTree();
    T* find(const Cond& key);
    void remove(const Cond& key);
    RankNode<T,Cond>* sortedArrayTo(RankNode<T, Cond>* arr[], int start, int end);
    int getSize();
    RankNode<T,Cond>* getRoot();
    RankNode<T,Cond>* getBiggest();
    RankNode<T,Cond>* getSmallest();
    void fillArray(RankNode<T,Cond>* arr[], int index);
    void fillArrayImpl(RankNode<T, Cond> *node, RankNode<T,Cond>* arr[], int* index);
};

template<class T,class Cond>
RankNode<T,Cond>* RankTree<T,Cond>::sortedArrayTo( RankNode<T, Cond>* arr[],
                                                   int start, int end)
{
    if (start > end)
        return nullptr;
    int mid = start + (end - start) / 2;
    RankNode<T,Cond>* currNode =  new RankNode<T,Cond>(arr[mid]->getKey(),arr[mid]->getNodeData(), end - start + 1);
    currNode->setLeft(sortedArrayTo(arr, start, mid - 1));
    currNode->setRight(sortedArrayTo(arr, mid + 1, end ));
    currNode->calcHeight();
    return currNode;
}

template<class T, class Cond>
RankTree<T,Cond>::RankTree(RankNode<T, Cond>* arr[],int size, int start, int end):root(this->sortedArrayTo(arr,start,end)),size(size),smallest(this->getSmallest()),biggest(this->getBiggest()){}

template<class T, class Cond>
RankTree<T,Cond>::~RankTree()
{
    delete this->root;
}

template<class T, class Cond>
void RankTree<T,Cond>::insert(const Cond &key,const T& data)
{
    if(this->root == nullptr)
        this->root =  new RankNode<T,Cond>(key,data);
    else
        this->root = this->root->insertNode(key,data);
    this->size++;
    this->smallest = this->getSmallest();
    this->biggest = this->getBiggest();
}

template<class T, class Cond>
T*  RankTree<T,Cond>::find(const Cond &key) {
    return root->findNode(key)->getNodeDataPointer();
}

template<class T, class Cond>
void RankTree<T,Cond>::remove(const Cond& key) {
    this->root = this->root->deleteNode(key);
    this->size--;
    this->smallest = this->getSmallest();
    this->biggest = this->getBiggest();
}

template<class T, class Cond>
int RankTree<T,Cond>::getSize()
{
    return this->size;
}

template<class T, class Cond>
RankNode<T,Cond>* RankTree<T,Cond>::getRoot()
{
    return this->root;
}

template<class T, class Cond>
RankNode<T,Cond>* RankTree<T,Cond>::getBiggest()
{
    if(!this->root)
        return nullptr;
    return this->root->findBiggest();
}

template<class T, class Cond>
RankNode<T,Cond>* RankTree<T,Cond>::getSmallest()
{
    if(!this->root)
        return nullptr;
    return this->root->findSmallest();
}

template<class T, class Cond>
void RankTree<T,Cond>::fillArray(RankNode<T,Cond>* arr[], int index) {
    fillArrayImpl(root,arr,&index);
}

template<class T, class Cond>
void RankTree<T,Cond>::fillArrayImpl(RankNode<T, Cond> *node, RankNode<T,Cond>* arr[], int* index) {
    if (node == nullptr)
        return;
    fillArrayImpl(node->getLeft(), arr, index);
    arr[(*index)++] = node;
    fillArrayImpl(node->getRight(), arr, index);
}

#endif //RANKTREE_H
