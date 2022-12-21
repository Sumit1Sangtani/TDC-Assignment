# Matrix Multiplication using OpenACC
**Name: Sumit Santosh Sangtani\
ID: 029405283**

**OpenACC** is a programming interface for developing applications that can be executed on a wide range of hardware platforms, including CPUs, GPUs, and other specialized accelerators. It is designed to make it easy for developers to write code that can be automatically parallelized and executed on these platforms, without having to write complex parallel algorithms or low-level code.

**Assignment Description**\
In this assignment, you will implement a code of your choice using OpenACC to parallelize the computation and run it on a GPU.\
You will write a serial version of the code function, add OpenACC directives to parallelize it, and then compare the performance of the serial and parallel versions.\
You will need to download and install an OpenACC compiler, such as the PGI Compiler from NVIDIA, and make sure you can compile and run OpenACC programs on your system. You will need to measure the performance of the serial and parallel versions and submit your code, a description of your approach, and a comparison of the performance.

**Evaluation Criteria**\
Correctness: Does the code function produce the correct result?\
Parallelism: Does the parallel code function use multiple threads on the GPU to speed up the computation?\
Performance: Is the parallel code function faster than the serial version?

**To download and use OpenACC, you will need to do the following:**\
Download and install an OpenACC compiler, such as the PGI Compiler from NVIDIA.\
Write your code in a programming language such as C or Fortran and use OpenACC directives to parallelize it.\
Compile your code using the OpenACC compiler. For example, you can use the following command to compile a C program with the PGI compiler:\
pgcc -acc -Minfo=accel -ta=nvidia my_program.c -o my_program\
Run your program to execute the parallel code on a GPU.

**Example Code**
Here is an example of a simple OpenACC program that computes the sum of an array in parallel:\
#include <stdio.h>\
#define N 1000000\
int main() \
{ \
    int a[N];\
    //Initialize array with random values\
    for (int i = 0; i < N; i++) {\
    a[i] = rand();\
 }\
 int sum = 0;

  // Compute sum of array in parallel using OpenACC\
  #pragma acc parallel loop reduction(+:sum)\
  for (int i = 0; i < N; i++) \
  {\
    sum += a[i];\
  }\
  printf("Sum = %d\n", sum);\
  return 0;\
}

**To compile and run this program, you would use the following commands:**\
pgcc -acc -Minfo=accel -ta=nvidia array_sum.c -o array_sum./array_sum\
This will compile the program with the PGI compiler and run it on the GPU, printing the sum of the array.

**Docker Info:**\
To create a Docker image, you will need to have Docker installed on your system. You can then create a Docker image by following these steps:\
Create a Dockerfile: This file is used to specify the instructions for building the image. The Dockerfile should start with a FROM directive that specifies the base image that your image will be built on top of. For example, you might specify FROM ubuntu:18.04 to use the latest version of Ubuntu as the base image.\
Add commands to the Dockerfile: Once you have specified the base image, you can then add additional commands to the Dockerfile to install dependencies, copy files, and configure the image. For example, you might use the RUN command to install packages, the COPY command to copy files from the host system into the image, or the ENV command to set environment variables.\
Build the image: Once you have written your Dockerfile, you can build the image by running the following command in the same directory as the Dockerfile:\
$ docker build -t my-image .\
This command will create a new image with the name my-image. You can specify a different name by replacing my-image with the desired name.\
Run the image: Once the image has been built, you can run it using the docker run command. For example, to run a container based on the my-image image, you would use the following command:\
$ docker run -it --name my-container my-image\
This will create and start a new container based on the my-image image. The -it flag allows you to interact with the container in a terminal, and the --name flag allows you to specify a custom name for the container.

**Deliverables:**\
Report: Document the steps you took, the speed up, and the reasons for it.\
Code: Submit your original/parallelized code

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
	
