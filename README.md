# ibmgraphblas
A plugable [GraphBLAS](http://graphblas.org)implementation.

How to use:

1. git clone https://github.com/IBM/ibmgraphblas.git
2. cd ibmgraphblas
4. cd build
5. cmake ..
6. cmake --build .
7. ctest -VV
8. ./algo_sssp_dist_main ../Algo/Matrix/house

Goal is to use ibmgraphblas as native component for [https://github.com/IBM/lagraph](https://github.com/IBM/lagraph "LAGraph")

