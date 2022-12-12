//Matrix multiplication using OpenACC

In this example, the #pragma acc data directive tells the compiler to generate GPU-accelerated code for the block of code that follows, which includes the matrix multiplication function. 
The copyin and copyout clauses specify which arrays should be copied to and from the GPU's memory.
The #pragma acc parallel loop collapse(2) directive tells the compiler to generate GPU-accelerated code for the nested loops that follow, and the collapse(2) clause specifies that the two loops should be collapsed into a single loop with a 2-dimensional iteration space.
This allows the compiler to generate more efficient GPU code for the computation.
