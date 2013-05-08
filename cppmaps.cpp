#include<string.h>
#include<stdlib.h>
#include<utility>
template<class K, class E>
class MapIterator;

template<class K, class E>
class Map;
/************************************************************************************/
//K is the key and E is the element in the node
//Type K must support the < operator
template <class K, class E>
class MapNode{

    friend class Map<K,E>;

    private:
        MapNode<K,E>* copy(MapNode<K,E>* mymap1);
        E element;
        K key;
        MapNode<K,E>* left_child;
        MapNode<K,E>* right_child;
        MapNode<K,E>* parent;
};
/************************************************************************************/
/************************************************************************************/
template<class K, class E>
class MapIterator
{
    friend class Map<K,E>;
    friend class MapNode<K,E>;

    public:
        MapIterator(){p_current_node = NULL;};

        std::pair<K,E> & operator*(){
            std::pair<K,E> pair1;
            pair1.first = p_current_node->key;
            pair1.second = p_current_node->element;
            return pair1;
        };

        MapIterator<K,E> & operator++();

        bool operator==(const MapIterator &itr) const
            {return p_current_node == itr.p_current_node;};

        bool operator!=(const MapIterator &itr) const
            {return p_current_node != itr.p_current_node;};

    private:
        MapIterator(MapNode<K,E> *p){p_current_node = p;};
        MapNode<K,E> *p_current_node;


};
/************************************************************************************/
/************************************************************************************/
template<class K, class E>
class Map
{
    friend class MapIterator<K,E>;

    public:
        Map(){
            p_head_node = NULL;
            root = NULL;
            size_ = 0;
        };
        ~Map();
        Map operator=(Map<K,E> Map2);

        E & operator[](const K & key_);
        MapIterator<K,E> find(const K &KEY);
        MapIterator<K,E> & end();
        int count(const K &key_);

        int size(){return size_;};
        bool empty(){return size==0;};
        MapIterator<K,E> begin(){
            return MapIterator<K,E>::itr(p_head_node);
        };

        void clear();
        int erase(const K &key);
        void erase(MapIterator<K,E> itr);
        //swap()
    private:

        MapNode<K,E>* p_head_node;
        MapNode<K,E>* root;
        int size_;

};
/************************************************************************************/
/************************************************************************************/
template<class K, class E>
MapIterator<K,E> & MapIterator<K,E>::operator++(){

    MapNode<K,E>* y = NULL;
    MapNode<K,E>* x = p_current_node; //purely for more readable syntax

    if(x->right_child != NULL){
        x = x->right_child;

        while(x->left_child != NULL){
            y = x;
            x = x->left_child;
        }
        MapIterator<K,E> itr;
        return itr(y);
    }

    y = x->parent;
    while(y != NULL && x == y->right_child){
        x = y;
        y = y->parent;
    }
    return itr(y);
}
/************************************************************************************/
template<class K, class E>
MapNode<K,E>* MapNode<K,E>::copy(MapNode<K,E>* node){
    //for use in copy constructor and assignment operator
    MapNode<K,E>* p1, p2;
    if(node->left_child != NULL)
        p1 = copy(node->left_child);
    key = node.key;
    element = node.element;
    left_child = node.left_child;
    right_child = node.right_child;
    parent = node.parent;
    if(node->right_child != NULL)
        p2 = copy(node->right_child);
    node->left_child = p1;
    node->right_child = p2;
    p1->parent = node;
    p2->parent = node;
    MapIterator<K,E> itr;
    return itr(node);
}
/************************************************************************************/
template<class K, class E>
E & Map<K,E>::operator[](const K &_key){

        MapIterator<K,E> itr;
        MapNode<K,E>* x = root;
        while(x != NULL){
            itr.current_node = x;
            if(_key == x->key)
                return x->element;
            if(_key < x->key)
                x = x->left_child;
            else
                x = x->right_child;
        }
        MapNode<K,E> insert_node;
        insert_node.key = _key;
        insert_node.parent = itr.current_node;
        if(_key < itr->first)
            itr.current_node->left_child = insert_node;
        else
            itr.current_node->right_child = insert_node;
        ++size;
        return insert_node->element;
}
/************************************************************************************/
template<class K, class E>
MapIterator<K,E> & Map<K,E>::end(){
    MapIterator<K,E> itr;
    itr.current_node = NULL;
    MapNode<K,E>* x = root;
    while(x != NULL){
        itr.current_node = x;
        x = x->right_child;
    }
    return itr;
}
/************************************************************************************/
template<class K, class E>
int Map<K,E>::count(const K & key_){
    int count = 0;
    for(MapIterator<K,E> itr = begin(); itr != end(); itr++){
        if(itr->first == key_)
            count++;
    }

    return count;
}
/************************************************************************************
template<class K, class E>
Map<K,E>::~Map(){
    //delete all elements from beginning to end

}
************************************************************************************/
template<class K, class E>
MapIterator<K,E> Map<K,E>::find(const K &KEY){
    for(MapIterator<K,E> itr = begin(); itr != end(); itr++){
        if(itr->first == KEY)
            return itr;
    }
    return end();
}
/************************************************************************************
template<class K, class E>
void Map<K,E>::clear(){
    //similar to destructor
    for(MapIterator<K,E> itr = begin(); itr != end(); itr++){
        erase(itr->first);
    }
    p_head_node = NULL;
    size_ = 0;
}
************************************************************************************/
template<class K, class E>
int Map<K,E>::erase(const K & _key_){
    //Tree-Delete Algorithm
    int erase_count = 0;
    for(MapIterator<K,E> itr = begin(); itr != end(); itr++){
        if(itr->first == _key_){
            MapNode<K,E>* y = itr.current_node->parent;
            //case node to delete has no children
            if(itr.current_node->left_child == NULL && itr.current_node->right_child == NULL){
                if(y->right_child == itr.current_node){
                    y->right_child == NULL;
                    itr.current_node->parent == NULL;
                }
                erase_count++;
                size--;
            }
            //case node to delete has right child
            else if(itr.p_current_node->left_child == NULL && itr.p_current_node->right_child != NULL){
                //check whether node to delete was left or right child of its parent
                if(y->right_child == itr.current_node)
                    y->right_child = itr.current_node->right_child;
                else
                    y->left_child = itr.current_node->right_child;

                itr.current_node->right_child->parent = y;
                itr.current_node->parent = NULL;
                erase_count++;
                size--;
            }
            //case node to delete has left child
            else if(itr.current_node->right_child == NULL && itr.current_node->left_child != NULL){
                //check whether node to delete was left or right chlid of its parent
                if(y->right_child == itr.current_node)
                    y->right_child = itr.current_node->left_child;
                else
                    y->left_child = itr.current_node->left_child;

                itr.current_node->left_child->parent = y;
                itr.current_node->parent = NULL;
                erase_count++;
                size--;
            }
            //case node to delete has two children
            else{
                MapNode<K,E>* x = itr.current_node->right_child;
                //find successor and swap it with node to delete
                while(x->left_child != NULL)
                    x = x->left_child;
                x->parent->left_child == NULL;
                x->parent = y;
                x->left_child = itr.current_node->left_child;
                x->right_child = itr.current_node->right_child;
                if(y->right_child = itr.current_node)
                    y->right_child = x;
                if(y->left_child = itr.current_node)
                    y->left_child = x;
                erase_count++;
                size--;
            }


            }

            }
            //return number of nodes erased, as specified by C++ STL Maps
            return erase_count;
        }
/************************************************************************************/
template<class K, class E>
void Map<K,E>::erase(MapIterator<K,E> itr){
    itr.p_current_node == NULL;
    delete itr.p_current_node;
}
/************************************************************************************
//copy constructor
template<class K, class E>
Map<K,E>::Map(Map<K,E>* mymap1){
    copy(mymap1.root);
}
************************************************************************************
template<class K, class E>
Map<K,E> & Map<K,E>::operator=(Map<K,E> _mymap){
    root = _mymap.root
    copy(root);
}
************************************************************************************/





int main()
{

return 0;

}
