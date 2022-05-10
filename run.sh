cd src
gcc=g++
#gcc=/opt/compiler/gcc-8.2/bin/g++

cd tree
$gcc -std=c++11 -g ./preorder.cpp -o preorder
$gcc -std=c++11 -g ./preorder_not_recursive.cpp -o preorder_not_recursive

cd ../strs
$gcc -std=c++11 -g ./strstr.cpp -o strstr

cd ../framework

$gcc -std=c++11 -g ./singleton.cpp -o singleton

cd ../data_structures

$gcc -std=c++11 -g ./toposort.cpp -o toposort
