# Red-black Tree & Map

Project contains two types of containers: basic red-black tree (RBTree) and my shortened version of std::map (Map)

RBTree can be based on any data type that has overloaded operators ">", "<", and "==" (and optionaly  for printing tree info through TreeInfoViewer it needs overloaded "<<" with std::ostream).

Example for class with such overloads is in main.cpp file.

RBTree and Map are inherited from RBTreeBase that contains methods for adding keys, for erasing tree, receiving amount of elements in tree, checking if tree is empty and method that check if tree contains specific element;

RBTree and Map can be const, so they support std::initializer_list.

RBTree and Map have copy and move versions of constructors and assignment operators. RBTree and Map also can be copied from each other. 

Map additionally has overloaded operator[], methods insert and insert_or_assign (they support KEY,VAlUE or std::pair<KEY,VALUE> as arguments), and supports foreach loop.

Examples of using RBTree and Map are contained in a main.cpp file.

Project has my own red-black tree balancing algorithm, my own algorithm for finding next node by key value from any node (used in foreach loop), and uses smart pointers.

Project also contains files for unit-testing using Google Test framework.

----- MyMap's main files -----

- Map.h & Map.inl // Needed for Map

- MapIterator.h & MapIterator.inl // Needed for Map

- MapNode.h & MapNode.inl // Needed for Map

- RBNode.h & RBNode.inl // Needed for RBTree

- RBNodeBase.h & RBNodeBase.inl // Needed for RBTree and Map

- RBTree.h & RBTree.inl // Needed for RBTree

- RBTreeBase.h & RBTreeBase.inl  // Needed for RBTree and Map

----- MyMap's optional files -----

- TreeInfoViewer.h & TreeInfoViewer.inl // Contains code for printing info on console and for testing reasons, can be ignored

- main.cpp // Contains some examples of using containers and TreeInfoViewer, needs TreeInfoViewer.h & TreeInfoViewer.inl

------ Google Test framework files ------

- rbtree_tests.cc // Contains tests for RBTree, needs TreeInfoViewer.h & TreeInfoViewer.inl

- map_tests.cc // Contains tests for Map, needs TreeInfoViewer.h & TreeInfoViewer.inl

- mutual_tests.cc // Contains tests for copying Map from RBTree and vice versa

- CMakeLists.txt // needed for cmake 


tsadext222
