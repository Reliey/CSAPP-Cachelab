/* 
 * trans.c - 矩阵转置B=A^T
 *每个转置函数都必须具有以下形式的原型：
 *void trans（int M，int N，int a[N][M]，int B[M][N]）；
 *通过计算，块大小为32字节的1KB直接映射缓存上的未命中数来计算转置函数。
 */ 
#include <stdio.h>
#include "cachelab.h"
int is_transpose(int M, int N, int A[N][M], int B[M][N]);
char transpose_submit_desc[] = "Transpose submission";  //请不要修改“Transpose_submission”


void transpose_submit(int M, int N, int A[N][M], int B[M][N])
{

//                          请在此处添加代码
//*************************************Begin********************************************************
    if (M == 32 && N == 32) 
    {
        for (int i = 0; i < N; i += 8)
        {
            for (int j = 0; j < M; j += 8) 
            {
                for (int m = i; m < i + 8; m++) 
                {
                    int v1 = A[m][j];
                    int v2 = A[m][j+1];
                    int v3 = A[m][j+2];
                    int v4 = A[m][j+3];
                    int v5 = A[m][j+4];
                    int v6 = A[m][j+5];
                    int v7 = A[m][j+6];
                    int v8 = A[m][j+7];
                    B[j][m] = v1;
                    B[j+1][m] = v2;
                    B[j+2][m] = v3;
                    B[j+3][m] = v4;
                    B[j+4][m] = v5;
                    B[j+5][m] = v6;
                    B[j+6][m] = v7;
                    B[j+7][m] = v8;
                }
            }
        }
    }

    if (M == 64 && N == 64)
    {
        for (int i = 0; i < N; i += 4)
        {
            for (int j = 0; j < M; j += 4) 
            {
                for (int m = i; m < i + 4; m++) 
                {
                    int v1 = A[m][j];
                    int v2 = A[m][j+1];
                    int v3 = A[m][j+2];
                    int v4 = A[m][j+3];
                    B[j][m] = v1;
                    B[j+1][m] = v2;
                    B[j+2][m] = v3;
                    B[j+3][m] = v4;
                }
            }
        }
    }
    if (M == 61 && N == 67) 
    {
        int i, j, v1, v2, v3, v4, v5, v6, v7, v8;
        int n = N / 8 * 8;
        int m = M / 8 * 8;
        for (j = 0; j < m; j += 8)
        {
            for (i = 0; i < n; ++i) 
            {
                v1 = A[i][j];
                v2 = A[i][j+1];
                v3 = A[i][j+2];
                v4 = A[i][j+3];
                v5 = A[i][j+4];
                v6 = A[i][j+5];
                v7 = A[i][j+6];
                v8 = A[i][j+7];
                
                B[j][i] = v1;
                B[j+1][i] = v2;
                B[j+2][i] = v3;
                B[j+3][i] = v4;
                B[j+4][i] = v5;
                B[j+5][i] = v6;
                B[j+6][i] = v7;
                B[j+7][i] = v8;
            }
        }
        for (i = 0; i < N; ++i)
        {
            for (j = m; j < M; ++j) 
            {
                v1 = A[i][j];
                B[j][i] = v1;
            }
        }
        for (i = n; i < N; ++i)
        {
            for (j = 0; j < M; ++j) 
            {
                v1 = A[i][j];
                B[j][i] = v1;
            }
        }  
    }






//**************************************End**********************************************************
}

/* 
 * 我们在下面定义了一个简单的方法来帮助您开始，您可以根据下面的例子把上面值置补充完整。
 */ 

/* 
 * 简单的基线转置功能，未针对缓存进行优化。
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }    

}

/*
 * registerFunctions-此函数向驱动程序注册转置函数。
 *在运行时，驱动程序将评估每个注册的函数并总结它们的性能。这是一种试验不同转置策略的简便方法。
 */
void registerFunctions()
{
    /* 注册解决方案函数  */
    registerTransFunction(transpose_submit, transpose_submit_desc); 

    /* 注册任何附加转置函数 */
    registerTransFunction(trans, trans_desc); 

}

/* 
 * is_transpose - 函数检查B是否是A的转置。在从转置函数返回之前，可以通过调用它来检查转置的正确性。
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}

