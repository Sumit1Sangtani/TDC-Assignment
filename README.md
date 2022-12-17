# Matrix Multiplication using OpenACC
Name: Sumit Santosh Sangtani\
ID: 029405283

**OpenACC** is a programming interface for developing applications that can be executed on a wide range of hardware platforms, including CPUs, GPUs, and other specialized accelerators. It is designed to make it easy for developers to write code that can be automatically parallelized and executed on these platforms, without having to write complex parallel algorithms or low-level code.

**Normal Code Explaination (MatMulOpen):**\
In this code, matrix multiplication is performed normally using C.

**OpenAcc Code Explaination (MatMulOpenAcc):**
1) In this code, the #pragma acc data directive tells the compiler to generate GPU-accelerated code for the block of code that follows, which includes the matrix multiplication function.
2) The copyin and copyout clauses specify which arrays should be copied to and from the GPU's memory.
3) The #pragma acc parallel loop directive tells the compiler to generate GPU-accelerated code for the nested loops that follow
4) This allows the compiler to generate more efficient GPU code for the computation.

**To download and use OpenACC, you will need to do the following:**
1) Download and install an OpenACC compiler, such as the PGI Compiler from NVIDIA.
2) Write your code in a programming language such as C or Fortran and use OpenACC directives to parallelize it.
3) Compile your code using the OpenACC compiler. For example, you can use the following command to compile a C program with the PGI compiler:
pgcc -acc -Minfo=accel -ta=nvidia my_program.c -o my_program
4) Run your program to execute the parallel code on a GPU.

To **execute the code** use the follwing command lines:\
A) Without the result validation\
	pgcc -acc -fast ta=nvidia -Minfo=accel MatMulOpenAcc.c -o MatMulOpenAcc\
B) With result validation (OpenMP threaded)\
	pgcc -mp -acc -fast ta=nvidia -Minfo=accel -DCHECK  MatMulOpenAcc.c -o MatMulOpenAcc-ompcheck
