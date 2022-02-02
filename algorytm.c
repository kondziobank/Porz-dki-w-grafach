#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct node
{
    int data; //node will store an integer
    struct node *right_child; // right child
    struct node *left_child; // left child
};

//function to find the minimum value in a node
struct node* find_minimum(struct node *root)
{
    if(root == NULL)
        return NULL;
    else if(root->left_child != NULL) // node with minimum value will have no left child
        return find_minimum(root->left_child); // left most element will be minimum
    return root;
}


int minValue(struct node* root) 
{ 
    printf("->");
    if (root->left_child == NULL) {
    } 
    printf(" %d ", root->data);
    return minValue(root->left_child); 
} 

int maxValue(struct node* root) 
{ 
    printf("->");
    if (root->right_child == NULL){
    }
    printf(" %d ", root->data);
    return maxValue(root->right_child); 
} 

//function to create a node
struct node* new_node(int x)
{
    struct node *p;
    p = malloc(sizeof(struct node));
    p->data = x;
    p->left_child = NULL;
    p->right_child = NULL;

    return p;
}

struct node* insert(struct node *root, int x)
{
    //searching for the place to insert
    if(root==NULL)
        return new_node(x);
    else if(x>root->data) // x is greater. Should be inserted to right
        root->right_child = insert(root->right_child, x);
    else // x is smaller should be inserted to left
        root->left_child = insert(root->left_child,x);
    return root;
}

// funnction to delete a node
struct node* delete(struct node *root, int x)
{
    //searching for the item to be deleted
    if(root==NULL)
        return NULL;
    if (x>root->data)
        root->right_child = delete(root->right_child, x);
    else if(x<root->data)
        root->left_child = delete(root->left_child, x);
    else
    {
        //No Children
        if(root->left_child==NULL && root->right_child==NULL)
        {
            free(root);
            return NULL;
        }

        //One Child
        else if(root->left_child==NULL || root->right_child==NULL)
        {
            struct node *temp;
            if(root->left_child==NULL)
                temp = root->right_child;
            else
                temp = root->left_child;
            free(root);
            return temp;
        }

        //Two Children
        else
        {
            struct node *temp = find_minimum(root->right_child);
            root->data = temp->data;
            root->right_child = delete(root->right_child, temp->data);
        }
    }
    return root;
}

void deleteTree(struct node* root)  
{ 
    if (root == NULL) return; 
  
    /* first delete both subtrees */
    deleteTree(root->left_child); 
    deleteTree(root->right_child); 
    
    /* then delete the node */
    printf("\n Usuwam wezel: %d", root->data); 
    free(root); 
}  

void inorder(struct node *root)
{
    if(root!=NULL) // checking if the root is not null
    {
        inorder(root->left_child); // visiting left child
        printf(" %d ", root->data); // printing data at root
        inorder(root->right_child);// visiting right child
    }
}

void preorder(struct node *root)
{
    if(root!=NULL)
    {
        printf(" %d ", root->data);
        preorder(root->left_child);
        preorder(root->right_child);
    }
}

void postorder(struct node *root)
{
    if(root!=NULL)
    {
        postorder(root->left_child);
        postorder(root->right_child);
        printf(" %d ", root->data);
    }
}


int main()
{
    struct node *root;
    int number ,var=100000;
    int* table_of_elements;

    root = new_node(500);
    
    printf("Wpisz ile liczb chcesz miec w drzewie: ");
    scanf("%d", &number);
    table_of_elements = (int*)malloc(sizeof(int)*number);

    for(int j=0; j<number; j++){
        table_of_elements[j]= var;
        var = var-2;
    }
    printf("\n");
                            
    for(int i=0; i<number; i++){
        root = insert(root, table_of_elements[i]);
        printf(" %d ", table_of_elements[i]);
    }

    printf("\n\n");
    srand(time(NULL));
    clock_t start = clock();
    find_minimum(root);
    printf("\n\n");
    printf("Min: %lu ms\n", clock() - start);
    return 0;
}