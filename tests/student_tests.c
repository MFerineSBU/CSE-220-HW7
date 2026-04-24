#include "unit_tests.h"
#include "hw7.h"

extern void inorder_sf(bst_sf *root, char *output);
extern void sort_string_sf(char *str);
extern bst_sf *build_bst();

Test(student_test_1, single_node) {
    bst_sf *root = NULL;
    matrix_sf *m = malloc(sizeof(matrix_sf));
    m->name = 'M';
    root = insert_bst_sf(m, root);
    cr_assert_not_null(root);
    cr_expect_eq(root->mat->name, 'M');
    cr_expect_null(root->left_child);
    cr_expect_null(root->right_child);
    free(m);
    free(root);
}

Test(student_test_1, smaller_on_left) {
    bst_sf *root = NULL;
    matrix_sf *m1 = malloc(sizeof(matrix_sf)); m1->name = 'M';
    matrix_sf *m2 = malloc(sizeof(matrix_sf)); m2->name = 'A';
    root = insert_bst_sf(m1, root);
    root = insert_bst_sf(m2, root);
    cr_expect_not_null(root->left_child);
    cr_expect_eq(root->left_child->mat->name, 'A');
    free(m1); free(m2);
    free(root->left_child); free(root);
}

Test(student_test_1, larger_on_right) {
    bst_sf *root = NULL;
    matrix_sf *m1 = malloc(sizeof(matrix_sf)); m1->name = 'M';
    matrix_sf *m2 = malloc(sizeof(matrix_sf)); m2->name = 'Z';
    root = insert_bst_sf(m1, root);
    root = insert_bst_sf(m2, root);
    cr_expect_not_null(root->right_child);
    cr_expect_eq(root->right_child->mat->name, 'Z');
    free(m1); free(m2);
    free(root->right_child); free(root);
}

Test(student_test_1, duplicate_replacement) {
    bst_sf *root = NULL;
    matrix_sf *m1 = malloc(sizeof(matrix_sf)); m1->name = 'K';
    matrix_sf *m2 = malloc(sizeof(matrix_sf)); m2->name = 'K';
    root = insert_bst_sf(m1, root);
    root = insert_bst_sf(m2, root);
    cr_expect_eq(root->mat, m2);
    free(m1); free(m2); free(root);
}

Test(student_test_1, inorder_sorted) {
    bst_sf *root = NULL;
    char names[] = "DCBA";
    matrix_sf *mats[4];
    for (int i = 0; i < 4; i++) {
        mats[i] = malloc(sizeof(matrix_sf));
        mats[i]->name = names[i];
        root = insert_bst_sf(mats[i], root);
    }
    char out[5] = {0};
    inorder_sf(root, out);
    cr_expect_str_eq(out, "ABCD");
    for (int i = 0; i < 4; i++) free(mats[i]);
}

Test(student_test_1, large_set_sorted) {
    bst_sf *root = NULL;
    char names[] = "PKZMAQBRCNDS";
    int n = strlen(names);
    matrix_sf *mats[12];
    for (int i = 0; i < n; i++) {
        mats[i] = malloc(sizeof(matrix_sf));
        mats[i]->name = names[i];
        root = insert_bst_sf(mats[i], root);
    }
    char out[13] = {0};
    inorder_sf(root, out);
    sort_string_sf(names);
    cr_expect_arr_eq(out, names, n);
    for (int i = 0; i < n; i++) free(mats[i]);
}

Test(student_test_1, ascending_right) {
    bst_sf *root = NULL;
    char names[] = "ABCDE";
    matrix_sf *mats[5];
    for (int i = 0; i < 5; i++) {
        mats[i] = malloc(sizeof(matrix_sf));
        mats[i]->name = names[i];
        root = insert_bst_sf(mats[i], root);
    }
    cr_expect_eq(root->mat->name, 'A');
    cr_expect_null(root->left_child);
    for (int i = 0; i < 5; i++) free(mats[i]);
}

Test(student_test_1, descending_left) {
    bst_sf *root = NULL;
    char names[] = "EDCBA";
    matrix_sf *mats[5];
    for (int i = 0; i < 5; i++) {
        mats[i] = malloc(sizeof(matrix_sf));
        mats[i]->name = names[i];
        root = insert_bst_sf(mats[i], root);
    }
    cr_expect_eq(root->mat->name, 'E');
    cr_expect_null(root->right_child);
    for (int i = 0; i < 5; i++) free(mats[i]);
}

Test(student_test_1, root_unchanged) {
    bst_sf *root = NULL;
    char names[] = "MFPAS";
    matrix_sf *mats[5];
    for (int i = 0; i < 5; i++) {
        mats[i] = malloc(sizeof(matrix_sf));
        mats[i]->name = names[i];
        root = insert_bst_sf(mats[i], root);
    }
    cr_expect_eq(root->mat->name, 'M');
    for (int i = 0; i < 5; i++) free(mats[i]);
}

Test(student_test_1, two_node_children_null) {
    bst_sf *root = NULL;
    matrix_sf *m1 = malloc(sizeof(matrix_sf)); m1->name = 'N';
    matrix_sf *m2 = malloc(sizeof(matrix_sf)); m2->name = 'Y';
    root = insert_bst_sf(m1, root);
    root = insert_bst_sf(m2, root);
    cr_expect_null(root->left_child);
    cr_expect_not_null(root->right_child);
    cr_expect_null(root->right_child->left_child);
    cr_expect_null(root->right_child->right_child);
    free(m1); free(m2);
    free(root->right_child); free(root);
}

Test(student_test_2, find_root) {
    bst_sf *root = NULL;
    matrix_sf *m = malloc(sizeof(matrix_sf)); m->name = 'G';
    root = insert_bst_sf(m, root);
    matrix_sf *found = find_bst_sf('G', root);
    cr_expect_not_null(found);
    cr_expect_eq(found->name, 'G');
    free(m); free(root);
}

Test(student_test_2, find_left_child) {
    bst_sf *root = NULL;
    matrix_sf *m1 = malloc(sizeof(matrix_sf)); m1->name = 'M';
    matrix_sf *m2 = malloc(sizeof(matrix_sf)); m2->name = 'B';
    root = insert_bst_sf(m1, root);
    root = insert_bst_sf(m2, root);
    cr_expect_eq(find_bst_sf('B', root)->name, 'B');
    free(m1); free(m2);
    free(root->left_child); free(root);
}

Test(student_test_2, find_right_child) {
    bst_sf *root = NULL;
    matrix_sf *m1 = malloc(sizeof(matrix_sf)); m1->name = 'M';
    matrix_sf *m2 = malloc(sizeof(matrix_sf)); m2->name = 'Z';
    root = insert_bst_sf(m1, root);
    root = insert_bst_sf(m2, root);
    cr_expect_eq(find_bst_sf('Z', root)->name, 'Z');
    free(m1); free(m2);
    free(root->right_child); free(root);
}

Test(student_test_2, find_missing) {
    bst_sf *root = NULL;
    matrix_sf *m = malloc(sizeof(matrix_sf)); m->name = 'A';
    root = insert_bst_sf(m, root);
    cr_expect_null(find_bst_sf('Z', root));
    free(m); free(root);
}

Test(student_test_2, find_empty) {
    cr_expect_null(find_bst_sf('A', NULL));
}

Test(student_test_2, find_deep) {
    bst_sf *root = NULL;
    char names[] = "MFAD";
    matrix_sf *mats[4];
    for (int i = 0; i < 4; i++) {
        mats[i] = malloc(sizeof(matrix_sf));
        mats[i]->name = names[i];
        root = insert_bst_sf(mats[i], root);
    }
    cr_expect_eq(find_bst_sf('D', root)->name, 'D');
    for (int i = 0; i < 4; i++) free(mats[i]);
}

Test(student_test_2, find_multiple) {
    bst_sf *root = NULL;
    char names[] = "NGLQC";
    matrix_sf *mats[5];
    for (int i = 0; i < 5; i++) {
        mats[i] = malloc(sizeof(matrix_sf));
        mats[i]->name = names[i];
        root = insert_bst_sf(mats[i], root);
    }
    cr_expect_eq(find_bst_sf('G', root)->name, 'G');
    cr_expect_eq(find_bst_sf('L', root)->name, 'L');
    cr_expect_eq(find_bst_sf('C', root)->name, 'C');
    for (int i = 0; i < 5; i++) free(mats[i]);
}

Test(student_test_2, find_nonexistent) {
    bst_sf *root = NULL;
    char names[] = "PKZMA";
    matrix_sf *mats[5];
    for (int i = 0; i < 5; i++) {
        mats[i] = malloc(sizeof(matrix_sf));
        mats[i]->name = names[i];
        root = insert_bst_sf(mats[i], root);
    }
    cr_expect_null(find_bst_sf('X', root));
    cr_expect_null(find_bst_sf('B', root));
    for (int i = 0; i < 5; i++) free(mats[i]);
}

Test(student_test_2, find_exact_pointer) {
    bst_sf *root = NULL;
    matrix_sf *m = malloc(sizeof(matrix_sf)); m->name = 'T';
    root = insert_bst_sf(m, root);
    cr_expect_eq(find_bst_sf('T', root), m);
    free(m); free(root);
}

Test(student_test_2, find_all_nodes) {
    bst_sf *root = NULL;
    char names[] = "MFPBHJQS";
    int n = strlen(names);
    matrix_sf *mats[8];
    for (int i = 0; i < n; i++) {
        mats[i] = malloc(sizeof(matrix_sf));
        mats[i]->name = names[i];
        root = insert_bst_sf(mats[i], root);
    }
    for (int i = 0; i < n; i++) {
        matrix_sf *found = find_bst_sf(names[i], root);
        cr_expect_not_null(found);
        cr_expect_eq(found->name, names[i]);
    }
    for (int i = 0; i < n; i++) free(mats[i]);
}

Test(student_test_3, free_single_node) {
    expect_no_valgrind_errors(run_with_valgrind("free_bst01"));
}

Test(student_test_3, free_left_skew) {
    expect_no_valgrind_errors(run_with_valgrind("free_bst02"));
}

Test(student_test_3, free_right_skew) {
    expect_no_valgrind_errors(run_with_valgrind("free_bst03"));
}

Test(student_test_3, free_two_nodes) {
    bst_sf *root = NULL;
    matrix_sf *m1 = malloc(sizeof(matrix_sf)); m1->name = 'M';
    matrix_sf *m2 = malloc(sizeof(matrix_sf)); m2->name = 'A';
    root = insert_bst_sf(m1, root);
    root = insert_bst_sf(m2, root);
    free_bst_sf(root);
}

Test(student_test_3, free_null) {
    free_bst_sf(NULL);
}

Test(student_test_3, free_three_nodes) {
    bst_sf *root = NULL;
    matrix_sf *mats[3];
    char names[] = "MAZ";
    for (int i = 0; i < 3; i++) {
        mats[i] = malloc(sizeof(matrix_sf));
        mats[i]->name = names[i];
        root = insert_bst_sf(mats[i], root);
    }
    free_bst_sf(root);
}

Test(student_test_3, free_six_nodes) {
    bst_sf *root = NULL;
    char names[] = "NFPBGQ";
    matrix_sf *mats[6];
    for (int i = 0; i < 6; i++) {
        mats[i] = malloc(sizeof(matrix_sf));
        mats[i]->name = names[i];
        root = insert_bst_sf(mats[i], root);
    }
    free_bst_sf(root);
}

Test(student_test_3, free_ten_nodes) {
    bst_sf *root = NULL;
    char names[] = "PKZMABRCTW";
    matrix_sf *mats[10];
    for (int i = 0; i < 10; i++) {
        mats[i] = malloc(sizeof(matrix_sf));
        mats[i]->name = names[i];
        root = insert_bst_sf(mats[i], root);
    }
    free_bst_sf(root);
}

Test(student_test_3, free_duplicate) {
    bst_sf *root = NULL;
    matrix_sf *m1 = malloc(sizeof(matrix_sf)); m1->name = 'K';
    matrix_sf *m2 = malloc(sizeof(matrix_sf)); m2->name = 'K';
    root = insert_bst_sf(m1, root);
    root = insert_bst_sf(m2, root);
    free(m1);
    free_bst_sf(root);
}

Test(student_test_3, free_rebuild) {
    for (int pass = 0; pass < 2; pass++) {
        bst_sf *root = NULL;
        char names[] = "MFPBHJ";
        matrix_sf *mats[6];
        for (int i = 0; i < 6; i++) {
            mats[i] = malloc(sizeof(matrix_sf));
            mats[i]->name = names[i];
            root = insert_bst_sf(mats[i], root);
        }
        free_bst_sf(root);
    }
}

Test(student_test_4, add_1x1) {
    matrix_sf *A = copy_matrix(1, 1, (int[]){5});
    matrix_sf *B = copy_matrix(1, 1, (int[]){-3});
    matrix_sf *C = add_mats_sf(A, B);
    expect_matrices_equal(C, 1, 1, (int[]){2});
    free(A); free(B); free(C);
}

Test(student_test_4, add_2x2) {
    matrix_sf *A = copy_matrix(2, 2, (int[]){1, 2, 3, 4});
    matrix_sf *B = copy_matrix(2, 2, (int[]){5, 6, 7, 8});
    matrix_sf *C = add_mats_sf(A, B);
    expect_matrices_equal(C, 2, 2, (int[]){6, 8, 10, 12});
    free(A); free(B); free(C);
}

Test(student_test_4, add_negative) {
    matrix_sf *A = copy_matrix(1, 3, (int[]){-1, -2, -3});
    matrix_sf *B = copy_matrix(1, 3, (int[]){1, 2, 3});
    matrix_sf *C = add_mats_sf(A, B);
    expect_matrices_equal(C, 1, 3, (int[]){0, 0, 0});
    free(A); free(B); free(C);
}

Test(student_test_4, add_zero_matrix) {
    matrix_sf *A = copy_matrix(2, 3, (int[]){10, 20, 30, 40, 50, 60});
    matrix_sf *B = copy_matrix(2, 3, (int[]){0, 0, 0, 0, 0, 0});
    matrix_sf *C = add_mats_sf(A, B);
    expect_matrices_equal(C, 2, 3, (int[]){10, 20, 30, 40, 50, 60});
    free(A); free(B); free(C);
}

Test(student_test_4, add_dimension_mismatch) {
    matrix_sf *A = copy_matrix(2, 3, (int[]){1, 2, 3, 4, 5, 6});
    matrix_sf *B = copy_matrix(3, 2, (int[]){1, 2, 3, 4, 5, 6});
    matrix_sf *C = add_mats_sf(A, B);
    cr_expect_null(C);
    free(A); free(B);
}

Test(student_test_4, add_row_mismatch) {
    matrix_sf *A = copy_matrix(1, 4, (int[]){1, 2, 3, 4});
    matrix_sf *B = copy_matrix(2, 4, (int[]){1, 2, 3, 4, 5, 6, 7, 8});
    cr_expect_null(add_mats_sf(A, B));
    free(A); free(B);
}

Test(student_test_4, add_col_mismatch) {
    matrix_sf *A = copy_matrix(2, 3, (int[]){1, 2, 3, 4, 5, 6});
    matrix_sf *B = copy_matrix(2, 4, (int[]){1, 2, 3, 4, 5, 6, 7, 8});
    cr_expect_null(add_mats_sf(A, B));
    free(A); free(B);
}

Test(student_test_4, add_large_values) {
    matrix_sf *A = copy_matrix(1, 2, (int[]){1000000, -1000000});
    matrix_sf *B = copy_matrix(1, 2, (int[]){1000000, -1000000});
    matrix_sf *C = add_mats_sf(A, B);
    expect_matrices_equal(C, 1, 2, (int[]){2000000, -2000000});
    free(A); free(B); free(C);
}

Test(student_test_4, add_3x3) {
    matrix_sf *A = copy_matrix(3, 3, (int[]){1, 0, 0, 0, 1, 0, 0, 0, 1});
    matrix_sf *B = copy_matrix(3, 3, (int[]){9, 8, 7, 6, 5, 4, 3, 2, 1});
    matrix_sf *C = add_mats_sf(A, B);
    expect_matrices_equal(C, 3, 3, (int[]){10, 8, 7, 6, 6, 4, 3, 2, 2});
    free(A); free(B); free(C);
}

Test(student_test_4, add_result_name) {
    matrix_sf *A = copy_matrix(1, 1, (int[]){1});
    matrix_sf *B = copy_matrix(1, 1, (int[]){2});
    matrix_sf *C = add_mats_sf(A, B);
    cr_expect_eq(C->name, '?');
    free(A); free(B); free(C);
}

Test(student_test_5, mult_1x1) {
    matrix_sf *A = copy_matrix(1, 1, (int[]){6});
    matrix_sf *B = copy_matrix(1, 1, (int[]){7});
    matrix_sf *C = mult_mats_sf(A, B);
    expect_matrices_equal(C, 1, 1, (int[]){42});
    free(A); free(B); free(C);
}

Test(student_test_5, mult_2x2) {
    matrix_sf *A = copy_matrix(2, 2, (int[]){1, 2, 3, 4});
    matrix_sf *B = copy_matrix(2, 2, (int[]){5, 6, 7, 8});
    matrix_sf *C = mult_mats_sf(A, B);
    expect_matrices_equal(C, 2, 2, (int[]){19, 22, 43, 50});
    free(A); free(B); free(C);
}

Test(student_test_5, mult_dot_product) {
    matrix_sf *A = copy_matrix(1, 3, (int[]){1, 2, 3});
    matrix_sf *B = copy_matrix(3, 1, (int[]){4, 5, 6});
    matrix_sf *C = mult_mats_sf(A, B);
    expect_matrices_equal(C, 1, 1, (int[]){32});
    free(A); free(B); free(C);
}

Test(student_test_5, mult_outer_product) {
    matrix_sf *A = copy_matrix(3, 1, (int[]){1, 2, 3});
    matrix_sf *B = copy_matrix(1, 3, (int[]){4, 5, 6});
    matrix_sf *C = mult_mats_sf(A, B);
    expect_matrices_equal(C, 3, 3, (int[]){4, 5, 6, 8, 10, 12, 12, 15, 18});
    free(A); free(B); free(C);
}

Test(student_test_5, mult_incompatible_dimensions) {
    matrix_sf *A = copy_matrix(2, 3, (int[]){1, 2, 3, 4, 5, 6});
    matrix_sf *B = copy_matrix(2, 3, (int[]){1, 2, 3, 4, 5, 6});
    cr_expect_null(mult_mats_sf(A, B));
    free(A); free(B);
}

Test(student_test_5, mult_by_zero) {
    matrix_sf *A = copy_matrix(2, 2, (int[]){1, 2, 3, 4});
    matrix_sf *B = copy_matrix(2, 2, (int[]){0, 0, 0, 0});
    matrix_sf *C = mult_mats_sf(A, B);
    expect_matrices_equal(C, 2, 2, (int[]){0, 0, 0, 0});
    free(A); free(B); free(C);
}

Test(student_test_5, mult_by_identity) {
    matrix_sf *A = copy_matrix(2, 2, (int[]){3, 7, 2, 5});
    matrix_sf *I = copy_matrix(2, 2, (int[]){1, 0, 0, 1});
    matrix_sf *C = mult_mats_sf(A, I);
    expect_matrices_equal(C, 2, 2, (int[]){3, 7, 2, 5});
    free(A); free(I); free(C);
}

Test(student_test_5, mult_2x3_3x4) {
    matrix_sf *A = copy_matrix(2, 3, (int[]){1, 2, 3, 4, 5, 6});
    matrix_sf *B = copy_matrix(3, 4, (int[]){7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18});
    matrix_sf *C = mult_mats_sf(A, B);
    expect_matrices_equal(C, 2, 4, (int[]){74, 80, 86, 92, 173, 188, 203, 218});
    free(A); free(B); free(C);
}

Test(student_test_5, mult_negative) {
    matrix_sf *A = copy_matrix(2, 2, (int[]){-1, 2, -3, 4});
    matrix_sf *B = copy_matrix(2, 2, (int[]){5, -6, 7, -8});
    matrix_sf *C = mult_mats_sf(A, B);
    expect_matrices_equal(C, 2, 2, (int[]){9, -10, 13, -14});
    free(A); free(B); free(C);
}

Test(student_test_5, mult_result_name) {
    matrix_sf *A = copy_matrix(1, 1, (int[]){2});
    matrix_sf *B = copy_matrix(1, 1, (int[]){3});
    matrix_sf *C = mult_mats_sf(A, B);
    cr_expect_eq(C->name, '?');
    free(A); free(B); free(C);
}

Test(student_test_6, trans_1x1) {
    matrix_sf *A = copy_matrix(1, 1, (int[]){42});
    matrix_sf *T = transpose_mat_sf(A);
    expect_matrices_equal(T, 1, 1, (int[]){42});
    free(A); free(T);
}

Test(student_test_6, trans_1x4) {
    matrix_sf *A = copy_matrix(1, 4, (int[]){1, 2, 3, 4});
    matrix_sf *T = transpose_mat_sf(A);
    expect_matrices_equal(T, 4, 1, (int[]){1, 2, 3, 4});
    free(A); free(T);
}

Test(student_test_6, trans_4x1) {
    matrix_sf *A = copy_matrix(4, 1, (int[]){5, 6, 7, 8});
    matrix_sf *T = transpose_mat_sf(A);
    expect_matrices_equal(T, 1, 4, (int[]){5, 6, 7, 8});
    free(A); free(T);
}

Test(student_test_6, trans_2x3) {
    matrix_sf *A = copy_matrix(2, 3, (int[]){1, 2, 3, 4, 5, 6});
    matrix_sf *T = transpose_mat_sf(A);
    expect_matrices_equal(T, 3, 2, (int[]){1, 4, 2, 5, 3, 6});
    free(A); free(T);
}

Test(student_test_6, trans_3x2) {
    matrix_sf *A = copy_matrix(3, 2, (int[]){1, 2, 3, 4, 5, 6});
    matrix_sf *T = transpose_mat_sf(A);
    expect_matrices_equal(T, 2, 3, (int[]){1, 3, 5, 2, 4, 6});
    free(A); free(T);
}

Test(student_test_6, trans_symmetric) {
    matrix_sf *A = copy_matrix(3, 3, (int[]){1, 2, 3, 2, 5, 6, 3, 6, 9});
    matrix_sf *T = transpose_mat_sf(A);
    expect_matrices_equal(T, 3, 3, (int[]){1, 2, 3, 2, 5, 6, 3, 6, 9});
    free(A); free(T);
}

Test(student_test_6, trans_double) {
    matrix_sf *A  = copy_matrix(2, 3, (int[]){1, 2, 3, 4, 5, 6});
    matrix_sf *T  = transpose_mat_sf(A);
    matrix_sf *TT = transpose_mat_sf(T);
    expect_matrices_equal(TT, 2, 3, (int[]){1, 2, 3, 4, 5, 6});
    free(A); free(T); free(TT);
}

Test(student_test_6, trans_negative) {
    matrix_sf *A = copy_matrix(2, 2, (int[]){-1, -2, -3, -4});
    matrix_sf *T = transpose_mat_sf(A);
    expect_matrices_equal(T, 2, 2, (int[]){-1, -3, -2, -4});
    free(A); free(T);
}

Test(student_test_6, trans_dimensions_swapped) {
    matrix_sf *A = copy_matrix(5, 3, (int[]){1,2,3,4,5,6,7,8,9,10,11,12,13,14,15});
    matrix_sf *T = transpose_mat_sf(A);
    cr_expect_eq(T->num_rows, 3u);
    cr_expect_eq(T->num_cols, 5u);
    free(A); free(T);
}

Test(student_test_6, trans_result_name) {
    matrix_sf *A = copy_matrix(1, 2, (int[]){1, 2});
    matrix_sf *T = transpose_mat_sf(A);
    cr_expect_eq(T->name, '?');
    free(A); free(T);
}

Test(student_test_7, create_1x1) {
    matrix_sf *m = create_matrix_sf('A', "1 1 [7 ;]");
    expect_matrices_equal(m, 1, 1, (int[]){7});
    cr_expect_eq(m->name, 'A');
    free(m);
}

Test(student_test_7, create_1x5) {
    matrix_sf *m = create_matrix_sf('R', "1 5 [10 20 30 40 50 ;]");
    expect_matrices_equal(m, 1, 5, (int[]){10, 20, 30, 40, 50});
    free(m);
}

Test(student_test_7, create_5x1) {
    matrix_sf *m = create_matrix_sf('C', "5 1 [1 ; 2 ; 3 ; 4 ; 5 ;]");
    expect_matrices_equal(m, 5, 1, (int[]){1, 2, 3, 4, 5});
    free(m);
}

Test(student_test_7, create_2x2) {
    matrix_sf *m = create_matrix_sf('B', "2 2 [1 2 ; 3 4 ;]");
    expect_matrices_equal(m, 2, 2, (int[]){1, 2, 3, 4});
    free(m);
}

Test(student_test_7, create_3x3_negative) {
    matrix_sf *m = create_matrix_sf('N', "3 3 [-1 -2 -3 ; -4 -5 -6 ; -7 -8 -9 ;]");
    expect_matrices_equal(m, 3, 3, (int[]){-1,-2,-3,-4,-5,-6,-7,-8,-9});
    free(m);
}

Test(student_test_7, create_2x4) {
    matrix_sf *m = create_matrix_sf('P', "2 4 [1 2 3 4 ; 5 6 7 8 ;]");
    expect_matrices_equal(m, 2, 4, (int[]){1,2,3,4,5,6,7,8});
    free(m);
}

Test(student_test_7, create_name_stored) {
    matrix_sf *m = create_matrix_sf('X', "1 1 [0 ;]");
    cr_expect_eq(m->name, 'X');
    free(m);
}

Test(student_test_7, create_dimensions_correct) {
    matrix_sf *m = create_matrix_sf('D', "4 3 [1 2 3 ; 4 5 6 ; 7 8 9 ; 10 11 12 ;]");
    cr_expect_eq(m->num_rows, 4u);
    cr_expect_eq(m->num_cols, 3u);
    free(m);
}

Test(student_test_7, create_zeros) {
    matrix_sf *m = create_matrix_sf('Z', "2 3 [0 0 0 ; 0 0 0 ;]");
    expect_matrices_equal(m, 2, 3, (int[]){0,0,0,0,0,0});
    free(m);
}

Test(student_test_7, create_mixed_signs) {
    matrix_sf *m = create_matrix_sf('M', "2 2 [100 -200 ; -300 400 ;]");
    expect_matrices_equal(m, 2, 2, (int[]){100,-200,-300,400});
    free(m);
}

Test(student_test_8, single_operand) {
    char *out = infix2postfix_sf("A");
    cr_expect_str_eq(out, "A");
    free(out);
}

Test(student_test_8, simple_add) {
    char *out = infix2postfix_sf("A+B");
    cr_expect_str_eq(out, "AB+");
    free(out);
}

Test(student_test_8, simple_mult) {
    char *out = infix2postfix_sf("A*B");
    cr_expect_str_eq(out, "AB*");
    free(out);
}

Test(student_test_8, transpose_only) {
    char *out = infix2postfix_sf("A'");
    cr_expect_str_eq(out, "A'");
    free(out);
}

Test(student_test_8, transpose_before_mult) {
    char *out = infix2postfix_sf("A'*B");
    cr_expect_str_eq(out, "A'B*");
    free(out);
}

Test(student_test_8, parens_override) {
    char *out = infix2postfix_sf("(A+B)*C");
    cr_expect_str_eq(out, "AB+C*");
    free(out);
}

Test(student_test_8, nested_parens) {
    char *out = infix2postfix_sf("((A+B)*C)");
    cr_expect_str_eq(out, "AB+C*");
    free(out);
}

Test(student_test_8, three_operands_mult) {
    char *out = infix2postfix_sf("A*B*C");
    cr_expect_str_eq(out, "AB*C*");
    free(out);
}

Test(student_test_8, spaces_ignored) {
    char *out = infix2postfix_sf("A + B * C");
    cr_expect_str_eq(out, "ABC*+");
    free(out);
}

Test(student_test_8, complex_expr) {
    char *out = infix2postfix_sf("(A+B)'*C+D'");
    cr_expect_str_eq(out, "AB+'C*D'+");
    free(out);
}

Test(student_test_9, eval_single_matrix) {
    bst_sf *root = build_bst();
    matrix_sf *result = evaluate_expr_sf('R', "C", root);
    cr_assert_not_null(result);
    expect_matrices_equal(result, 1, 4, (int[]){-123, 47, -4, 140});
    free_bst_sf(root);
    free(result);
}

Test(student_test_9, eval_add_CD) {
    bst_sf *root = build_bst();
    matrix_sf *result = evaluate_expr_sf('R', "C + D", root);
    expect_matrices_equal(result, 1, 4, (int[]){-139, 169, 131, 247});
    free_bst_sf(root);
    free(result);
}

Test(student_test_9, eval_transpose_H) {
    bst_sf *root = build_bst();
    matrix_sf *result = evaluate_expr_sf('R', "H'", root);
    expect_matrices_equal(result, 5, 1, (int[]){52, 65, -94, -73, -48});
    free_bst_sf(root);
    free(result);
}

Test(student_test_9, eval_add_AB) {
    bst_sf *root = build_bst();
    matrix_sf *result = evaluate_expr_sf('R', "A + B", root);
    expect_matrices_equal(result, 3, 5, (int[]){6, 27, 4, -26, 32, 30, 39, 20, 93, -47, -88, 24, 21, 16, -18});
    free_bst_sf(root);
    free(result);
}

Test(student_test_9, eval_mult_GC) {
    bst_sf *root = build_bst();
    matrix_sf *result = evaluate_expr_sf('R', "G * C", root);
    cr_assert_not_null(result);
    cr_expect_eq(result->num_rows, 7u);
    cr_expect_eq(result->num_cols, 4u);
    free_bst_sf(root);
    free(result);
}

Test(student_test_9, eval_result_name) {
    bst_sf *root = build_bst();
    matrix_sf *result = evaluate_expr_sf('Q', "C + D", root);
    cr_expect_eq(result->name, 'Q');
    free_bst_sf(root);
    free(result);
}

Test(student_test_9, eval_unknown_var) {
    bst_sf *root = build_bst();
    matrix_sf *result = evaluate_expr_sf('R', "X", root);
    cr_expect_null(result);
    free_bst_sf(root);
}

Test(student_test_9, eval_double_transpose) {
    bst_sf *root = build_bst();
    matrix_sf *result = evaluate_expr_sf('R', "A''", root);
    expect_matrices_equal(result, 3, 5, (int[]){-4, 18, 6, 7, 10, -14, 29, 8, 21, -99, 0, 7, 5, 2, -9});
    free_bst_sf(root);
    free(result);
}

Test(student_test_9, eval_paren_add) {
    bst_sf *root = build_bst();
    matrix_sf *result = evaluate_expr_sf('R', "(A + B)", root);
    expect_matrices_equal(result, 3, 5, (int[]){6, 27, 4, -26, 32, 30, 39, 20, 93, -47, -88, 24, 21, 16, -18});
    free_bst_sf(root);
    free(result);
}

Test(student_test_9, eval_incompatible_mult) {
    bst_sf *root = build_bst();
    matrix_sf *result = evaluate_expr_sf('R', "A * B", root);
    cr_expect_null(result);
    free_bst_sf(root);
}

Test(student_test_10, exec_script01_correct) {
    run_script_without_valgrind("script01");
}

Test(student_test_10, exec_script02_correct) {
    run_script_without_valgrind("script02");
}

Test(student_test_10, exec_script03_correct) {
    run_script_without_valgrind("script03");
}

Test(student_test_10, exec_script07_correct) {
    run_script_without_valgrind("script07");
}

Test(student_test_10, exec_script09_correct) {
    run_script_without_valgrind("script09");
}

Test(student_test_10, exec_script04_valgrind) {
    expect_no_valgrind_errors(run_script_with_valgrind("script04"));
}

Test(student_test_10, exec_script05_valgrind) {
    expect_no_valgrind_errors(run_script_with_valgrind("script05"));
}

Test(student_test_10, exec_script10_valgrind) {
    expect_no_valgrind_errors(run_script_with_valgrind("script10"));
}

Test(student_test_10, exec_script14_valgrind) {
    expect_no_valgrind_errors(run_script_with_valgrind("script14"));
}

Test(student_test_10, exec_script18_valgrind) {
    expect_no_valgrind_errors(run_script_with_valgrind("script18"));
}


