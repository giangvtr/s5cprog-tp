
#include "myDoubleTree.h"
#include <float.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


/*!
* \brief Allocate memory for the node element and initialize the structure members
* \param[in] v the double for the value member
* \param[in] l the address of the left child
* \param[in] r the address of the right child
* \return DNode* the address of the new tree element
*/
DNode * initNode(double v, DNode * l, DNode * r)
{
    DNode * new = (DNode*) malloc(sizeof(DNode));
    if(new == NULL)
        return NULL;
    new->value = v;
    new->left = l;
    new->right = r;
    return new;
}

/*!
* \brief Desallocate memory associated to a node
* \param[in] n the address of the  data element to be freed
*/
static void freeNode(DNode * n)
{
    free((void*) n);
}


/*!
* \brief Suppress all elements from a tree
* \param[in] t the tree to be emptied
*/
void freeTree(DTree t)
{
    if(t!=NULL)
    {
        if(t->right != NULL)
            freeTree(t->right);

        if(t->left != NULL)
            freeTree(t->left);

        freeNode(t);
    }
}


/*!
* \brief Initialize an empty tree
* \param[out] t the tree to be initialized
*/
void initTree(DTree * t)
{
    *t = NULL;
}


/*!
* \brief Tests if it is an empty tree
* \param[in] t the tree to be tested
* \return int 1 if empty, 0 otherwise
*/
int isEmpty(DTree t)
{
    return t == NULL;
}

/*!
* \brief Tests if it is a leaf
* \param[in] t the tree to be tested
* \return int 1 if it is a leaf, 0 otherwise
*/
int isLeaf(DTree t)
{
    return t->left == NULL && t->right == NULL ;
}

/*!
* \brief Insert a new element containing the double value given as a parameter to get a sorted tree
* \param[in,out] t the tree
* \param[in] v the value to be inserted
* \return int 1 if everything was OK, 0 otherwise
*/
DTree addDouble(DTree  t, double v)
{
    if(isEmpty(t))
        t = initNode(v,NULL,NULL);
    else
    {
        double current_val = t->value;
        if(current_val == v)
            return t; /*already in the tree*/
        else
            if(current_val > v)
                t->left = addDouble(t->left,v);
            else
                t->right = addDouble(t->right,v);
    }
    return t;
}

/*!
* \brief Build a sorted tree from a sorted array
* \param[in] a the array of sorted values
* \param[in] n the number of values in the array
* \return DTree the new tree
*/
DTree buildBalancedTreeFromSortedArray(double * a, int n)
{
    if(n!=0)
        return initNode(a[n/2],buildBalancedTreeFromSortedArray(a,n/2),buildBalancedTreeFromSortedArray(a + n/2 + 1,(n-1)/2));
    return NULL;
}



/*!
* \brief Print the content of the current node of the tree
* \param[in] t the node to be displayed
* \param[in] depth its depth in the tree
*/
static void printTreeRec(DTree t, int depth)
{
	if(!isEmpty(t))
	{
        int i;
        printTreeRec(t->left,depth+1);
        for(i = 0; i< depth ; i++)
            printf("\t");
        printf("%f\n",t->value);
        printTreeRec(t->right,depth+1);
	}
}

/*!
* \brief Print the content of the tree
* \param[in] t the tree to be displayed
*/
void printTree(DTree t)
{
	if(!isEmpty(t))
	{
        printf("--------- Printing tree : --------- \n");
        printTreeRec(t,0);
        printf("--------- End of printing tree --------- \n\n");
	}
	else
        printf("This tree is empty \n");
}

int getHeight(DTree t) {
    if (isEmpty(t)) return 0;
    if (isLeaf(t)) return 1;

    int left_height = getHeight(t->left);
    int right_height = getHeight(t->right);
    return left_height > right_height ? left_height + 1 : right_height + 1;
}

double findMax(DTree t) {
    if (isEmpty(t)) return 0;
    if (isLeaf(t)) return t->value;

    double res = t->value;
    double leftMax = findMax(t->left);
    double rightMax = findMax(t->right);
    if (leftMax > res) res = leftMax;
    if (rightMax > res) res = rightMax;

    return res;
}

int isUnbalancedTree(DTree t) {
    return (getHeight(t->left) - getHeight(t->right) > 1
        || getHeight(t->right) - getHeight(t->left) > 1);
}


DTree rightRotation(DTree t) {
    if (isLeaf(t) || isEmpty(t)) return t;

    //Name some things
    DNode * Q = t; //current root
    DNode * P = t->left;
    DNode * B = P->right;

    //Do a rotation
    Q->left = B;
    P->right = Q;

    return P;
}

DTree leftRotation(DTree t) {
    DNode * P = t;
    DNode * Q = t->right;
    DNode * B = Q->left;

    //Do a left rotation

    Q->left = P;
    P->right = B;

    return Q;
}

DTree reBalance(DTree t) {
    if (isEmpty(t)||isLeaf(t)) return t;

    //if not, do something
    int balanceFactor = getHeight(t->left) - getHeight(t->right);

    // Perform rotations if the tree is unbalanced
    if (balanceFactor > 1) {
        // Left-heavy tree
        t = rightRotation(t);
    } else if (balanceFactor < -1) {
    // Right-heavy tree
        t = leftRotation(t);
    } else return t;

    // Recursively rebalance left and right subtrees
    t->left = reBalance(t->left);
    t->right = reBalance(t->right);

    return t;
}

DTree removeNode(DTree t, double value) {
    if (isEmpty(t)) return t;  // Return if the tree is empty

    if (value < t->value) {
        t->left = removeNode(t->left, value);  // Search in the left subtree
    } else if (value > t->value) {
        t->right = removeNode(t->right, value); // Search in the right subtree
    } else { // value == t->value
        // If the node is a leaf
        if (isLeaf(t)) {
            freeNode(t);
            return NULL;
        }
        // If the node has only one child
        else if (t->left == NULL) {
            DNode * temp = t;
            t = t->right;
            freeNode(temp);
            return t;
        } else if (t->right == NULL) {
            DNode * temp = t;
            t = t->left;
            freeNode(temp);
            return t;
        }
        // If the node has two children
        else {
            int max = findMax(t->left);
            t->value = max;  // Replace with max from left subtree
            t->left = removeNode(t->left, max);  // Recursively remove the max node
        }
    }

    return t;
}

int compare(const void *a, const void *b) {
    double arg1 = *(double*)a;
    double arg2 = *(double*)b;
    return (arg1 > arg2) - (arg1 < arg2);  // Return 1 if arg1 > arg2, -1 if arg1 < arg2, 0 if equal
}

// Function to build a balanced tree from unsorted array
DTree buildBalancedTreeFromUnsortedArray(double *data, int n) {
    qsort(data, n, sizeof(double), compare);  // Sort the array
    return buildBalancedTreeFromSortedArray(data, n);  // Build the balanced tree
}

// Function to read data from a binary file and return an array of doubles
double* readArrayFromFile(char *s, int *nb) {
    FILE *file = fopen(s, "rb");
    if (!file) {
        fprintf(stderr, "Error opening file %s\n", s);
        return NULL;
    }

    //find file size
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    rewind(file);

    *nb = fileSize / sizeof(double);  // Calculate the number of doubles in the file
    double *data = (double *)malloc(*nb * sizeof(double));
    if (!data) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(file);
        return NULL;
    }

    fread(data, sizeof(double), *nb, file);  // Read the data into the array
    fclose(file);
    return data;  // Return the array of doubles
}

DTree readDTreeFromFile(char *s) {
    int n;
    double *data = readArrayFromFile(s, &n);  // Read data from the file
    if (!data) return NULL;

    DTree tree = buildBalancedTreeFromUnsortedArray(data, n);  // Build balanced tree
    free(data);  // Free the allocated memory for data
    return tree;
}










