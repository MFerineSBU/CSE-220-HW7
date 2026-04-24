#include "hw7.h"

bst_sf* insert_bst_sf(matrix_sf *mat, bst_sf *root) {
    if (root == NULL) { //If tree is empty, intitialize a new node at the root
        bst_sf *new_node = malloc(sizeof(bst_sf));
        new_node->mat = mat; 
        new_node->left_child = NULL;
        new_node->right_child = NULL;
        return new_node;
    }
    if (mat->name < root->mat->name) { //If the matrix name is less than the name at the current root, insert in left subtree recursively
        root->left_child = insert_bst_sf(mat, root->left_child);
    } else if (mat->name > root->mat->name) { //If the matrix name is greater than the name at the current root, insert in right subtree recursively
        root->right_child = insert_bst_sf(mat, root->right_child);
    } else {
            root->mat = mat;  //Otherwise replace with new matrix
        }
    return root; //Return the root of updated/new BST
}

matrix_sf* find_bst_sf(char name, bst_sf *root) {
    if(root == NULL){
        return NULL; //If NULL, return NULL 
    }
    if(name == root->mat->name){ //If the name and the name at the root are equal, recursively call the function in the left subtree to find the matrix
        return root->mat;
    }
    else if (name < root->mat->name){
        return find_bst_sf(name, root->left_child); 
    } else{
        return find_bst_sf(name, root->right_child); //Otherwise, recursively call the function in the right subtree to find the matrix
    }
}

void free_bst_sf(bst_sf *root) {
    if(root==NULL){ //If root is NULL return as it is already free
        return; 
    }
    free_bst_sf(root->left_child); //Recursively free left subtree
    free_bst_sf(root->right_child); //Recursively free right subtree
    free(root->mat); //Free the values 
    free(root); //Free the root
}

matrix_sf* add_mats_sf(const matrix_sf *mat1, const matrix_sf *mat2) {
    if (mat1->num_rows != mat2->num_rows || mat1->num_cols != mat2->num_cols) { //NULL checker
        return NULL; 
    }
    matrix_sf *mat3 = malloc(sizeof(matrix_sf) + mat1->num_rows * mat1-> num_cols * sizeof(int)); //Allocate memory needed to do matrix addition
    mat3->name = '?'; //Define name of matrix made on the fly 
    mat3->num_rows = mat1->num_rows;  //Define dimensions of matrix made on the fly 
    mat3->num_cols = mat1->num_cols;  
    for (size_t i = 0; i < mat1->num_rows * mat1->num_cols; i++) //Loop through the dimensions of the matrices 
    {
        mat3->values[i] = mat1->values[i] + mat2->values[i]; //New matrix value is equal to mat1+mat2 at the given index i 
    }
    
    return mat3; //return pointer to new matrix 
}

matrix_sf* mult_mats_sf(const matrix_sf *mat1, const matrix_sf *mat2) {
   if(mat1->num_cols != mat2->num_rows){ 
    return NULL; //If there is no shared dimension, return NULL
   }
   matrix_sf *mat3 = malloc(sizeof(matrix_sf) + mat1->num_rows * mat2->num_cols * sizeof(int)); //Allocate memory needed for matrix multiplication
   mat3->name = '?'; 
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
    if(!mat){
        return NULL;
    }
    matrix_sf *mat_r = malloc(sizeof(matrix_sf) + mat->num_cols * mat->num_rows * sizeof(int)); //Allocate memory for a matrix the size of the transposed matrix
    mat_r->name = '?'; 
    mat_r->num_rows = mat->num_cols;
    mat_r->num_cols = mat->num_rows;  //Define name and dimensions of transposed matrix 
    for(size_t i = 0; i<mat->num_rows; i++){ 
        for(size_t j = 0; j<mat->num_cols; j++){ //Loop through all rows and cols of matrix
            mat_r->values[j*mat_r->num_cols + i] = mat->values[i*mat->num_cols + j]; //Swap the values at (i,j) to (j,i)
        }
    }
    return mat_r; //return transpose matrix 
}

matrix_sf* create_matrix_sf(char name, const char *expr) {
    const char *p = expr;  //Pointer to expression
    char *resultp;  //Pointer to what will become the info regarding the resulting matrix
    long rows = strtol(p, &resultp, 10);  //Use strtol to find number of rows and cols and set to the result 
    p=resultp;
    long cols = strtol(p, &resultp, 10); 
    p = resultp; 
    matrix_sf *new_matrix = malloc(sizeof(matrix_sf) + rows * cols * sizeof(int)); //Allocate memory based on parsed rows and cols
    new_matrix->name = name;
    new_matrix->num_rows = rows; 
    new_matrix->num_cols = cols;  //Define new matrix 
    while(*p != '['){
        p++; 
    }
    p++; //Move to the values portion 
    for(long i = 0; i < rows; i++){
        for(long j = 0; j<cols; j++){ //Loop through rows and columns
            while(*p == ' ' || *p == '\n'){
                p++; //Skip whitespace 
            }
            long vals = strtol(p, &resultp, 10); //Use strtol to read the values
            p = resultp; 
            new_matrix->values[i*cols+j] = (int)vals; //Place new values in the new matrix 
        }
        while(*p == ' ' || *p == '\n'){
            p++; //Skip remaining whitespace
        }
        if(*p == ';'){
            p++; //These skip the semicolon
        }
    }
    while(*p != ']'){
        p++; //Skip till we reach the closing bracket 
    }
    p++;//Go to right past the closing bracket
    return new_matrix; //Return a pointer to our resulting matrix 
}

static int precedence(char c) {
    if (c == '\''){
        return 3;
    } 
    if (c == '*'){
        return 2;
    } 
    if (c == '+'){
        return 1; //Helper function to check precendence of operators 
    } 
    return 0;
}

  
char* infix2postfix_sf(char *infix) {
    if (!infix){
        return NULL; //null checker
    } 
    int length = strlen(infix);
    char *postfix = malloc(length + 1); //Allocate space for expression and null character
    char stack[MAX_LINE_LEN]; //Make the stack for the stack operation
    int top = -1; //Top of stack 
    int p = 0; //postfix index
    for (int i = 0; infix[i]; i++) {
        char c = infix[i];
        if (isspace((unsigned char)c)) {
            continue;  //Go through all characters skipping whitespace
        }
        if (isalpha((unsigned char)c)) {
            postfix[p++] = c; //Put characters into postfix output
        } else if (c == '(') {
            stack[++top] = c; //Push ( onto the stack
        } else if (c == ')') {
            while (top >= 0 && stack[top] != '(') {
                postfix[p++] = stack[top--]; //Pop operators until we are at the matching parenthesis
            }
            if (top >= 0){
                top--; //Pop (
            } 
        } else { 
            while (top >= 0 && stack[top] != '(' && precedence(stack[top]) >= precedence(c)) { //Pop operators in order of precedence
                postfix[p++] = stack[top--];
            }
            stack[++top] = c; //Then, push the operator onto the stack
        }
    }
    while (top >= 0) {
        postfix[p++] = stack[top--]; // Pop leftover operators
    }
    postfix[p] = '\0'; //Define null terminator
    return postfix; //Return postfix operation
}

matrix_sf* evaluate_expr_sf(char name, char *expr, bst_sf *root) {
    char *postfix = infix2postfix_sf(expr); //Convert expr to postfix 
    if (!postfix) {
        return NULL; //Null checker
    } 
    matrix_sf *stack[MAX_LINE_LEN];
    int top = -1; //Define a stack of matrix pointers to evaluate expr

    for (int i = 0; postfix[i]; i++) {
        char c = postfix[i];//Go through postfix operation

        if (isalpha((unsigned char)c)) {
            matrix_sf *m = find_bst_sf(c, root); //Search in BST for the matrix
            if (!m) { 
                free(postfix); return NULL;  //Null checker for the matrix
            }
            stack[++top] = m; //Push matrix onto the stack
        }

        else if (c == '\'') { //Handle unary operator transpose
            if (top < 0) { //Check if we have an operand on the stack
                 free(postfix); 
                 return NULL; 
                }
            matrix_sf *m = stack[top--];  
            //Create new matrix for transposed m
            matrix_sf *result = transpose_mat_sf(m);
            if (!result) {
                free(postfix); 
                return NULL; 
            }

            if (m->name == '?') {
                free(m);          //  free temps
            }

            stack[++top] = result; //Push result of transpose onto stack
        }

        else if (c == '+' || c == '*') { //Deal with other operators
            if (top < 1) { 
                free(postfix); 
                return NULL; 
            }
            matrix_sf *mat2 = stack[top--]; //Pop operands left to right
            matrix_sf *mat1 = stack[top--];


            matrix_sf *result = (c == '+') ? add_mats_sf(mat1, mat2): mult_mats_sf(mat1, mat2); //Depending on operator selected, either do matrix addition or multiplication 
            if (!result) { //If operation doesn't work, free temps, postfix and return null
                if (mat1->name == '?'){
                    free(mat1);
                } 
                if (mat2->name == '?'){
                    free(mat2);
                }
                free(postfix);
                return NULL;
            }
                
            
            if (mat1->name == '?'){  //Free temps
                free(mat1);
            }
            if (mat2->name == '?'){
                free(mat2);
            } 

            stack[++top] = result; //Push the result onto the stack 
        }
    }

    if (top != 0) {
        free(postfix); 
        return NULL;
    } //Ensure there is only one matrix on the stack

    matrix_sf *result = stack[top];
    free(postfix);
    if (!result){
        return NULL;
    }  //Null checker for result matrix

    matrix_sf *final;
    if (result->name == '?') {
        final = result;          //Reuse our temp to store result matrix
    } else {
        final = copy_matrix(result->num_rows, result->num_cols, result->values); //Copy our resulting matrix
        if (!final){
            return NULL;
        } 
    }

    final->name = name;
    return final; //Return our copy of the resulting matrix
}



matrix_sf *execute_script_sf(char *filename) {
    FILE *fp = fopen(filename, "r"); //Open our file
    if (!fp){
        return NULL; //Null checker
    } 

    bst_sf *root = NULL; //Define root and last matrix in script
    char last_name = '\0'; 

    char *line = NULL; //For the current line
    size_t max_line_size = MAX_LINE_LEN; //Define max line size

    while (getline(&line, &max_line_size, fp) != -1) {
        char *equals = strchr(line, '='); //Go through the script line by line, 
        if (!equals){ //Skip = 
            continue;
        } 
        //Get our matrix name
        char name = '\0';
        for (char *c = line; c < equals; c++) {
            if (isalpha((unsigned char)*c))
                name = *c; 
        }
        if (!name){
            continue;
        } 

        // Go to content after =, skipping whitespace
        char *content = equals + 1;
        while (*content && isspace((unsigned char)*content)){
            content++;
        }
            

        matrix_sf *mat = NULL;

        if (*content == '\0') {
            // if right of = is empty, skip
            continue;
        } else if (isdigit((unsigned char)*content) || *content == '-' ) {
            // If defining a matrix, create a matrix
            mat = create_matrix_sf(name, content);
        } else {
            // otherwise, defines matrix using existing matrices expression
            mat = evaluate_expr_sf(name, content, root);
        }

        if (mat) {//Insert into BST if creation worked
            root = insert_bst_sf(mat, root);
            last_name = name;
        }
    }

    fclose(fp); //Close our file and free line
    free(line);
 
    if (!last_name) { //If no matrix was made, return NULL and free our tree
        free_bst_sf(root);
        return NULL;
    }

    matrix_sf *last_mat = find_bst_sf(last_name, root); //Find the last matrix in the BST
    if (!last_mat) {
        free_bst_sf(root);
        return NULL;
    }

    matrix_sf *result = copy_matrix(last_mat->num_rows, last_mat->num_cols, last_mat->values);
    result->name = last_mat->name;//Create a copy of the last made matrix and give it the defined name

    free_bst_sf(root); //Free our BST 
    return result; //Return result matrix 
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
