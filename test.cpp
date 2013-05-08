#include<cppmaps.cpp>
#include<iostream>
using std::cout;

int main(){
//begin(), end(), and iterator operations are all implicitly tested through other methods

Map<string, int> mymap;
mymap["Sean"] = 1;
mymap["Patrick"] = 2;
mymap["Lyons"] = 3; //test indexing operator

cout << "Map size is: " << mymap.size() << 'n'; //test size()
cout << "The element at index Patrick is: " << mymap.find(Patrick)->second << 'n'; //test find
cout << "There are " << mymap.count("Sean") << "node(s) with key Sean" << 'n';
mymap.erase("Sean");
cout << "There are now " << mymap.count("Sean" << "node(s) with key Sean" << 'n';
MapIterator<string, int> itr;
itr(mymap["Patrick"]); //set iterator to node with key "Patrick"
mymap.erase(itr); //erase iterator
cout << itr.current_node == NULL; << 'n';
Map<string, int> mymap2;
mymap2();
cout << "Size of new map is " << mymap2.size();





















}
