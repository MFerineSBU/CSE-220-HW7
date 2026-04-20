#include "hw7.h"

bst_sf* insert_bst_sf(matrix_sf *mat, bst_sf *root) {
    return NULL;
}

matrix_sf* find_bst_sf(char name, bst_sf *root) {
    return NULL;
}

void free_bst_sf(bst_sf *root) {
}

matrix_sf* add_mats_sf(const matrix_sf *mat1, const matrix_sf *mat2) {
    matrix_sf *mat3 = malloc(sizeof(matrix_sf) + mat1->num_rows * mat1-> num_cols * sizeof(int)); //Allocate memory needed to do matrix addition
    mat3->name = '!'; //Define name of matrix made on the fly 
    mat3->num_rows = mat1->num_rows;  //Define dimensions of matrix made on the fly 
    mat3->num_cols = mat1->num_cols;  
    for (size_t i = 0; i < mat1->num_rows * mat1->num_cols; i++) //Loop through the dimensions of the matrices 
    {
        mat3->values[i] = mat1->values[i] + mat2->values[i]; //New matrix value is equal to mat1+mat2 at the given index i 
    }
    
    return mat3; //return pointer to new matrix 
}

matrix_sf* mult_mats_sf(const matrix_sf *mat1, const matrix_sf *mat2) {
   matrix_sf *mat3 = malloc(sizeof(matrix_sf) + mat1->num_rows * mat2->num_cols * sizeof(int)); //Allocate memory needed for matrix multiplication
   if(mat1->num_cols != mat2->num_rows){ 
    return NULL; //If there is no shared dimension, return NULL
   }
   mat3->name = '!'; 
   mat3->num_rows = mat1->num_rows;
   mat3->num_cols = mat2->num_cols; //Define name and dimensions of new matrix
   for(size_t i = 0; i<mat1->num_rows; i++){ //Set up loops to go through all of the rows and cols of new matrix
    for(size_t j = 0; j<mat2->num_cols; j++){
        int mat_mult = 0;
        for(size_t k = 0; k<mat1->num_cols; k++){ //As well as the shared dimension of the matrix
            int a = mat1->values[i * mat1->num_cols + k];  //Compute row elements from matrix 1
            int b = mat2->values[k * mat2->num_cols + j];  //Compute column elements from matrix 2 
            mat_mult += a*b; //Compute the result by multiplying the two together 
        }
        mat3->values[i* mat2->num_cols + j] = mat_mult; //Define new value of multiplied matrix at index (i,j)
    }
   }
   return mat3; //Return multiplied matrix 
}

matrix_sf* transpose_mat_sf(const matrix_sf *mat) {
    matrix_sf *mat_r = malloc(sizeof(matrix_sf) + mat->num_cols * mat->num_rows * sizeof(int)); //Allocate memory for a matrix the size of the transposed matrix
    mat_r->name = '!'; 
    mat_r->num_rows = mat->num_cols;
    mat_r->num_cols = mat->num_rows;  //Define name and dimensions of transposed matrix 
    for(size_t i = 0; i<mat->num_rows; i++){ 
        for(size_t j = 0; i<mat->num_cols; j++){ //Loop through all rows and cols of matrix
            mat_r->values[j*mat_r->num_cols + i] = mat->values[i*mat->num_cols + j]; //Swap the values at (i,j) to (j,i)
        }
    }
    return mat_r; //return transpose matrix 
}

matrix_sf* create_matrix_sf(char name, const char *expr) {

}

char* infix2postfix_sf(char *infix) {
    return NULL;
}

matrix_sf* evaluate_expr_sf(char name, char *expr, bst_sf *root) {
    return NULL;
}

matrix_sf *execute_script_sf(char *filename) {
   return NULL;
}

// This is a utility function used during testing. Feel free to adapt the code to implement some of
// the assignment. Feel equally free to ignore it.
matrix_sf *copy_matrix(unsigned int num_rows, unsigned int num_cols, int values[]) {
    matrix_sf *m = malloc(sizeof(matrix_sf)+num_rows*num_cols*sizeof(int));
    m->name = '?';
    m->num_rows = num_rows;
    m->num_cols = num_cols;
    memcpy(m->values, values, num_rows*num_cols*sizeof(int));
    return m;
}

// Don't touch this function. It's used by the testing framework.
// It's been left here in case it helps you debug and test your code.
void print_matrix_sf(matrix_sf *mat) {
    assert(mat != NULL);
    assert(mat->num_rows <= 1000);
    assert(mat->num_cols <= 1000);
    printf("%d %d ", mat->num_rows, mat->num_cols);
    for (unsigned int i = 0; i < mat->num_rows*mat->num_cols; i++) {
        printf("%d", mat->values[i]);
        if (i < mat->num_rows*mat->num_cols-1)
            printf(" ");
    }
    printf("\n");
}
