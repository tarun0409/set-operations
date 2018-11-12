#include "set.h"
#include <iostream>
#include <stdio.h>
#include <vector>
#include <set>
#include <fstream>
#include <unistd.h>
#include <algorithm>
#include <stdio.h>
using namespace std;


string output1="";

struct node
{
    int value;
    struct node *left_child;
    struct node *right_child;
    struct node *parent;
    int height;
    int balance_factor;
    int left_children;
    int right_children;
};

class AVLTree
{
  public:
    struct node *root = NULL;
    int size = 0;

    struct node *create_node(int val)
    {
        struct node *new_node = (struct node *)malloc(sizeof(struct node));
        new_node->value = val;
        new_node->left_child = NULL;
        new_node->right_child = NULL;
        new_node->parent = NULL;
        new_node->height = 1;
        new_node->balance_factor = 0;
        new_node->left_children = 0;
        new_node->right_children = 0;
        return new_node;
    }

    void init(struct node *new_root)
    {
        root = new_root;
    }
    void update_height(struct node *curr_node)
    {
        int max_h = -1;
        if (curr_node->left_child != NULL)
        {
            if ((curr_node->left_child->height) > max_h)
            {
                max_h = curr_node->left_child->height;
            }
        }
        if (curr_node->right_child != NULL)
        {
            if ((curr_node->right_child->height) > max_h)
            {
                max_h = curr_node->right_child->height;
            }
        }
        if (max_h > -1)
        {
            curr_node->height = (max_h + 1);
        }
        else if (max_h == -1)
        {
            curr_node->height = 1;
        }
    }

    void update_balance_factor(struct node *curr_node)
    {
        int l_h = 0;
        int r_h = 0;
        if (curr_node->value == 4)
        {
            int x = 0;
            x++;
        }
        if (curr_node->left_child != NULL)
        {
            l_h = curr_node->left_child->height;
        }
        if (curr_node->right_child != NULL)
        {
            r_h = curr_node->right_child->height;
        }
        curr_node->balance_factor = (l_h - r_h);
    }

    void left_left_rotation(struct node *curr_node)
    {
        struct node *temp = curr_node->right_child;
        curr_node->right_child = curr_node->parent;
        int p_n = (curr_node->parent->right_children) + (curr_node->right_children);
        int c_n = curr_node->right_children;
        curr_node->right_children = p_n + 1;
        curr_node->parent->left_child = temp;
        curr_node->parent->left_children = c_n;
        if (temp != NULL)
        {
            temp->parent = curr_node->parent;
        }
        if (curr_node->parent == root)
        {
            root = curr_node;
            curr_node->parent->parent = curr_node;
            curr_node->parent = NULL;
        }
        else
        {
            if ((curr_node->parent->parent->value) > (curr_node->parent->value))
            {
                curr_node->parent->parent->left_child = curr_node;
            }
            else
            {
                curr_node->parent->parent->right_child = curr_node;
            }
            struct node *temp_parent = curr_node->parent;
            curr_node->parent = curr_node->parent->parent;
            temp_parent->parent = curr_node;
        }
    }

    void right_right_rotation(struct node *curr_node)
    {
        struct node *temp = curr_node->left_child;
        curr_node->left_child = curr_node->parent;
        int p_n = (curr_node->parent->left_children) + (curr_node->left_children);
        int c_n = curr_node->left_children;
        curr_node->left_children = p_n + 1;
        curr_node->parent->right_child = temp;
        curr_node->parent->right_children = c_n;
        if (temp != NULL)
        {
            temp->parent = curr_node->parent;
        }
        if (curr_node->parent == root)
        {
            root = curr_node;
            curr_node->parent->parent = curr_node;
            curr_node->parent = NULL;
        }
        else
        {
            if ((curr_node->parent->parent->value) > (curr_node->parent->value))
            {
                curr_node->parent->parent->left_child = curr_node;
            }
            else
            {
                curr_node->parent->parent->right_child = curr_node;
            }
            struct node *temp_parent = curr_node->parent;
            curr_node->parent = curr_node->parent->parent;
            temp_parent->parent = curr_node;
        }
    }
    void left_right_rotation(struct node *curr_node)
    {
        struct node *temp1 = curr_node->left_child;
        curr_node->left_child = curr_node->parent;
        curr_node->parent->right_child = temp1;
        int p_n = (curr_node->parent->left_children) + (curr_node->left_children);
        int c_n = curr_node->left_children;
        curr_node->left_children = p_n + 1;
        curr_node->parent->right_children = c_n;
        if (temp1 != NULL)
        {
            temp1->parent = curr_node->parent;
        }
        curr_node->parent->parent->left_child = curr_node;
        curr_node->parent->parent->left_children = (curr_node->left_children + curr_node->right_children);
        struct node *temp2 = curr_node->parent;
        curr_node->parent = curr_node->parent->parent;
        temp2->parent = curr_node;
    }

    void right_left_rotation(struct node *curr_node)
    {
        struct node *temp1 = curr_node->right_child;
        curr_node->right_child = curr_node->parent;
        curr_node->parent->left_child = temp1;
        int p_n = (curr_node->parent->right_children) + (curr_node->right_children);
        int c_n = curr_node->right_children;
        curr_node->right_children = p_n + 1;
        curr_node->parent->left_children = c_n;
        if (temp1 != NULL)
        {
            temp1->parent = curr_node->parent;
        }
        curr_node->parent->parent->right_child = curr_node;
        curr_node->parent->parent->right_children = (curr_node->left_children + curr_node->right_children);
        struct node *temp2 = curr_node->parent;
        curr_node->parent = curr_node->parent->parent;
        temp2->parent = curr_node;
    }

    int check_and_balance_tree(struct node *curr_node)
    {
        int change = 0;
        if (curr_node == NULL)
        {
            return change;
        }
        if (curr_node->balance_factor > 1)
        {
            if (curr_node->left_child->balance_factor > 0)
            {
                struct node *temp_curr = curr_node->left_child;
                left_left_rotation(curr_node->left_child);
                change = 1;
                if (temp_curr->left_child != NULL)
                {
                    update_height(temp_curr->left_child);
                    update_balance_factor(temp_curr->left_child);
                }
                if (temp_curr->right_child != NULL)
                {
                    update_height(temp_curr->right_child);
                    update_balance_factor(temp_curr->right_child);
                }
                update_height(temp_curr);
                update_balance_factor(temp_curr);
            }
            else if (curr_node->left_child->balance_factor < 0)
            {
                left_right_rotation(curr_node->left_child->right_child);
                struct node *temp_curr = curr_node->left_child;
                left_left_rotation(curr_node->left_child);
                change = 1;
                if (temp_curr->left_child != NULL)
                {
                    update_height(temp_curr->left_child);
                    update_balance_factor(temp_curr->left_child);
                }
                if (temp_curr->right_child != NULL)
                {
                    update_height(temp_curr->right_child);
                    update_balance_factor(temp_curr->right_child);
                }
                update_height(temp_curr);
                update_balance_factor(temp_curr);
            }
        }
        else if (curr_node->balance_factor < -1)
        {
            if (curr_node->right_child->balance_factor < 0)
            {
                struct node *temp_curr = curr_node->right_child;
                right_right_rotation(curr_node->right_child);
                change = 1;
                if (temp_curr->left_child != NULL)
                {
                    update_height(temp_curr->left_child);
                    update_balance_factor(temp_curr->left_child);
                }
                if (temp_curr->right_child != NULL)
                {
                    update_height(temp_curr->right_child);
                    update_balance_factor(temp_curr->right_child);
                }
                update_height(temp_curr);
                update_balance_factor(temp_curr);
            }
            else if (curr_node->right_child->balance_factor > 0)
            {
                right_left_rotation(curr_node->right_child->left_child);
                struct node *temp_curr = curr_node->right_child;
                right_right_rotation(curr_node->right_child);
                change = 1;
                if (temp_curr->left_child != NULL)
                {
                    update_height(temp_curr->left_child);
                    update_balance_factor(temp_curr->left_child);
                }
                if (temp_curr->right_child != NULL)
                {
                    update_height(temp_curr->right_child);
                    update_balance_factor(temp_curr->right_child);
                }
                update_height(temp_curr);
                update_balance_factor(temp_curr);
            }
        }
        return change;
    }

    struct node *find_predecessor(struct node *curr_node)
    {
        if (curr_node == NULL)
        {
            return NULL;
        }
        if (curr_node->left_child == NULL)
        {
            return curr_node;
        }
        struct node *temp = curr_node->left_child;
        while (temp->right_child != NULL)
        {
            temp = temp->right_child;
        }
        return temp;
    }

    int insert_node(struct node *curr_node, struct node *new_node)
    {
        int status;
        if (root == NULL)
        {
            root = new_node;
            return 1;
        }
        if ((new_node->value) == (curr_node->value))
        {
            return 0;
        }
        if ((new_node->value) < (curr_node->value))
        {
            if (curr_node->left_child == NULL)
            {
                curr_node->left_child = new_node;
                new_node->parent = curr_node;
                update_height(curr_node);
                update_balance_factor(curr_node);
                (curr_node->left_children)++;
                return 1;
            }
            else
            {
                status = insert_node((curr_node->left_child), new_node);
                if (status)
                {
                    update_height(curr_node);
                    update_balance_factor(curr_node);
                    int change = check_and_balance_tree(curr_node);
                    if (!change)
                    {
                        (curr_node->left_children)++;
                    }
                }
            }
        }
        else if ((new_node->value) > (curr_node->value))
        {
            if (curr_node->right_child == NULL)
            {
                curr_node->right_child = new_node;
                new_node->parent = curr_node;
                update_height(curr_node);
                update_balance_factor(curr_node);
                (curr_node->right_children)++;
                return 1;
            }
            else
            {
                status = insert_node((curr_node->right_child), new_node);
                if (status)
                {
                    update_height(curr_node);
                    update_balance_factor(curr_node);
                    int change = check_and_balance_tree(curr_node);
                    if (!change)
                    {
                        (curr_node->right_children)++;
                    }
                }
            }
        }
        return status;
    }

    int insert(int new_val)
    {
        struct node *new_node = create_node(new_val);
        int success = insert_node(root, new_node);
        if (success)
        {
            size++;
        }
        return success;
    }

    struct node *find_node(struct node *curr_node, int target)
    {
        struct node *dest = NULL;
        if (root == NULL)
        {
            return NULL;
        }
        if ((curr_node->value) == target)
        {
            return curr_node;
        }
        else if (((curr_node->value) > target) && curr_node->left_child != NULL)
        {
            dest = find_node(curr_node->left_child, target);
        }
        else if (((curr_node->value) < target) && curr_node->right_child != NULL)
        {
            dest = find_node(curr_node->right_child, target);
        }
        return dest;
    }

    struct node *find(int target)
    {
        return find_node(root, target);
    }

    int remove(int val)
    {
        struct node *curr_node = find(val);
        if (curr_node == NULL)
        {
            return 0;
        }
        if (curr_node->left_child == NULL)
        {
            if (curr_node == root)
            {
                root = curr_node->right_child;
                if (curr_node->right_child != NULL)
                {
                    curr_node->right_child->parent = NULL;
                }
            }
            else
            {
                if (curr_node->parent->left_child == curr_node)
                {
                    curr_node->parent->left_child = curr_node->right_child;
                    if (curr_node->right_child != NULL)
                    {
                        curr_node->parent->left_children--;
                    }
                    else
                    {
                        curr_node->parent->left_children = 0;
                    }
                }
                else if (curr_node->parent->right_child == curr_node)
                {
                    curr_node->parent->right_child = curr_node->right_child;
                    if (curr_node->right_child != NULL)
                    {
                        curr_node->parent->right_children--;
                    }
                    else
                    {
                        curr_node->parent->right_children = 0;
                    }
                }
                if (curr_node->right_child != NULL)
                {
                    curr_node->right_child->parent = curr_node->parent;
                }
            }
            curr_node = curr_node->parent;
        }
        else
        {
            struct node *pred = find_predecessor(curr_node);
            curr_node->value = pred->value;

            if (pred->parent->left_child == pred)
            {
                pred->parent->left_child = pred->left_child;
                if (pred->left_child != NULL)
                {
                    pred->parent->left_children--;
                }
                else
                {
                    pred->parent->left_children = 0;
                }
            }
            else if (pred->parent->right_child == pred)
            {
                pred->parent->right_child = pred->left_child;
                if (pred->left_child != NULL)
                {
                    pred->parent->right_children--;
                }
                else
                {
                    pred->parent->right_children = 0;
                }
            }
            if (pred->left_child != NULL)
            {
                pred->left_child->parent = pred->parent;
            }
            curr_node = pred->parent;
        }

        while (curr_node != NULL)
        {
            update_height(curr_node);
            update_balance_factor(curr_node);
            check_and_balance_tree(curr_node);
            if (curr_node->left_child != NULL)
            {
                curr_node->left_children = (curr_node->left_child->left_children + curr_node->left_child->right_children + 1);
            }
            else
            {
                curr_node->left_children = 0;
            }
            if (curr_node->right_child != NULL)
            {
                curr_node->right_children = (curr_node->right_child->left_children) + (curr_node->right_child->right_children + 1);
            }
            else
            {
                curr_node->right_children = 0;
            }
            curr_node = curr_node->parent;
        }
        size--;
        return 1;
    }

    int find_kth_smallest(struct node *curr_root, int k)
    {
        if (curr_root == NULL || k == 0)
        {
            //cout<<"\n\nRoot is null\n\n";
            //exit(1);
            return 0;
        }
        int n = curr_root->left_children;
        if (k == (n + 1))
        {
            return curr_root->value;
        }
        else
        {
            if (k <= n)
            {
                return find_kth_smallest(curr_root->left_child, k);
            }
            else
            {
                return find_kth_smallest(curr_root->right_child, (k - n - 1));
            }
        }
        return 0;
    }

    int find_kth_smallest(int k)
    {
        return find_kth_smallest(root, k);
    }

    vector<int> in_order_fill(struct node *curr_node, vector<int> arr)
    {
        if (curr_node == NULL)
        {
            return arr;
        }
        arr = in_order_fill(curr_node->left_child, arr);
        arr.push_back(curr_node->value);
        arr = in_order_fill(curr_node->right_child, arr);
        return arr;
    }

    vector<int> get_elements()
    {
        vector<int> arr;
        arr = in_order_fill(root, arr);
        return arr;
    }

    int fill_bbst(struct node *curr_node, vector<int> arr, int start_index, int end_index, int curr_pos)
    {
        if (end_index < start_index)
        {
            return 1;
        }
        int mid = (start_index + end_index) / 2;

        int value = arr[mid];
        struct node *new_node = create_node(value);
        //new_node->height = height;
        if (start_index != end_index)
        {
            new_node->left_children = (mid - start_index);
            new_node->right_children = (end_index - mid);
        }
        if (curr_pos == 0)
        {
            curr_node->left_child = new_node;
        }
        else if (curr_pos == 1)
        {
            curr_node->right_child = new_node;
        }
        int h1 = fill_bbst(new_node, arr, start_index, (mid - 1), 0);
        int h2 = fill_bbst(new_node, arr, (mid + 1), end_index, 1);
        int height = (h1 > h2 ? h1 : h2);
        new_node->height = height;
        int bf = h1 - h2;
        new_node->balance_factor = bf;
        return (height + 1);
    }

    AVLTree get_bbst_from_sorted_list(vector<int> arr)
    {
        int start_index = 0;
        int end_index = arr.size() - 1;
        if (end_index < start_index)
        {
            AVLTree empty;
            return empty;
        }
        int mid = (start_index + end_index) / 2;
        int value = arr[mid];
        struct node *new_node = create_node(value);
        if (start_index != end_index)
        {
            new_node->left_children = mid;
            new_node->right_children = (end_index - start_index) - mid;
        }
        struct node *new_root = new_node;
        int h1 = fill_bbst(new_node, arr, start_index, (mid - 1), 0);
        int h2 = fill_bbst(new_node, arr, (mid + 1), end_index, 1);
        int height = (h1 > h2 ? h1 : h2);
        new_node->height = height;
        new_node->balance_factor = (h1 - h2);
        AVLTree bbst;
        bbst.init(new_root);
        return bbst;
    }

    AVLTree DIFFERENCE(AVLTree tree2)
    {
        vector<int> set1 = get_elements();
        vector<int> set2 = tree2.get_elements();
        vector<int> diff_set;
        int i = 0, j = 0;
        while (i < set1.size() && j < set2.size())
        {
            if (set1[i] < set2[j])
            {
                diff_set.push_back(set1[i]);
                i++;
            }
            else if (set1[i] > set2[j])
            {
                j++;
            }
            else
            {
                i++;
                j++;
            }
        }
        while (i < set1.size())
        {
            diff_set.push_back(set1[i]);
            i++;
        }
        AVLTree bbst = get_bbst_from_sorted_list(diff_set);
        return bbst;
    }

    AVLTree INTERSECTION(AVLTree tree2)
    {
        vector<int> set1 = get_elements();
        vector<int> set2 = tree2.get_elements();
        vector<int> inter_set;
        int i = 0, j = 0;
        while (i < set1.size() && j < set2.size())
        {
            if (set1[i] < set2[j])
            {
                i++;
            }
            else if (set1[i] > set2[j])
            {
                j++;
            }
            else
            {
                inter_set.push_back(set1[i]);
                i++;
                j++;
            }
        }
        AVLTree bbst = get_bbst_from_sorted_list(inter_set);
        return bbst;
        // return ;
    }

    AVLTree UNION(AVLTree tree2)
    {
        vector<int> set1 = get_elements();
        vector<int> set2 = tree2.get_elements();
        vector<int> union_set;
        int i = 0, j = 0;
        while (i < set1.size() && j < set2.size())
        {
            int s = union_set.size();
            s--;
            if (s >= 0 && union_set[s] == set1[i])
            {
                i++;
            }
            if (s >= 0 && union_set[s] == set2[j])
            {
                j++;
            }
            if (i < set1.size() && set1[i] <= set2[j])
            {
                union_set.push_back(set1[i]);
                i++;
            }
            else if (j < set2.size())
            {
                union_set.push_back(set2[j]);
                j++;
            }
        }
        if (i < set1.size())
        {
            while (i < set1.size())
            {
                union_set.push_back(set1[i]);
                i++;
            }
        }
        else if (j < set2.size())
        {
            while (j < set2.size())
            {
                union_set.push_back(set2[j]);
                j++;
            }
        }
        AVLTree bbst = get_bbst_from_sorted_list(union_set);
        return bbst;
    }

    void in_order_print(struct node *curr_node)
    {
        if (curr_node == NULL)
        {
            return;
        }
        in_order_print(curr_node->left_child);
        //cout << "(" << curr_node->value << "," << curr_node->height << ")";
        // cout << curr_node->value << " ";
        output1 = output1 + to_string(curr_node->value) + " ";
        in_order_print(curr_node->right_child);
    }
    void in_order_print()
    {
        if (root == NULL)
        {
            printf("\nTree is empty!\n");
            return;
        }
        // cout << endl;
        in_order_print(root);
        // cout << endl;
    }
};

int randomNumber(int start, int end)
{
    double r = (double)rand() / RAND_MAX;
    int i = start + r * (end - start);
    return i;
}

int *randomArr(int n, int min, int max)
{
    int *array = (int *)malloc(sizeof(int) * n);

    for (int i = 0; i < n; i++)
    {
        array[i] = randomNumber(min, max);
    }
    return array;
}

//stores output in myImplementation.txt and in STl.txt
void insertionOutputGeneration()
{

    srand(200);

    int *arr;
    FILE *fptr = fopen("myImplementation.txt", "w");
    FILE *fptr1 = fopen("STL.txt", "w");

    for (int i = 100; i < 100000; i += 1000)
    {

        // n=i;
        // nToFind = randomNumber(0,n); //random k

        arr = randomArr(i, 0, 100000);

        AVLTree test;

        auto start = chrono::high_resolution_clock::now();
        // qS(0,n-1, ans);
        for (int j = 0; j < i; j++)
        {
            test.insert(arr[j]);
        }
        auto stop = chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed = stop - start;
        cout << endl;
        cout << " Size = " << i << endl;
        cout << "Our Implementation | Time taken : " << elapsed.count() << " ms to insert " << i << " elements" << endl;

        fprintf(fptr, "%d %f\n", i, elapsed.count());

        set<int> s;
        start = chrono::high_resolution_clock::now();
        // nth_element(arr1,arr1+nToFind,arr1+n-1);
        for (int j = 0; j < i; j++)
        {
            s.insert(arr[j]);
        }

        stop = chrono::high_resolution_clock::now();
        elapsed = stop - start;
        cout << "STL set function | Time taken : " << elapsed.count() << " ms  to insert " << i << " elements" << endl;

        fprintf(fptr1, "%f\n", elapsed.count());
    }

    fclose(fptr);
    fclose(fptr1);
}

//stores output in myImplementation.txt and in STl.txt
void unionOutputGeneration()
{

    int *arr1, *arr2;
    FILE *fptr1 = fopen("myImplementation.txt", "w");
    FILE *fptr2 = fopen("STL.txt", "w");

    for (int i = 100; i <= 1000; i += 100)
    {
        // n=i;
        // nToFind = randomNumber(0,n); //random k

        arr1 = randomArr(i, 0, 100000);
        arr2 = randomArr(i, 0, 100000);

        AVLTree test1;
        AVLTree test2;

        // qS(0,n-1, ans);
        for (int j = 0; j < i; j++)
        {
            test1.insert(arr1[j]);
        }

        for (int j = 0; j < i; j++)
        {
            test2.insert(arr2[j]);
        }

        auto start = chrono::high_resolution_clock::now();
        test1.UNION(test2);
        auto stop = chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed = stop - start;
        cout << endl;
        cout << "Input Size = " << i << endl;
        cout << "Time taken : " << elapsed.count() << " ms to union " << i << " elements" << endl;
        cout << " T(n)/n : " << (double)elapsed.count() / i << endl;

        fprintf(fptr1, "%d %lf\n", i, (double)(elapsed.count() / i));
        free(arr1);
        free(arr2);
    }

    fclose(fptr1);
    fclose(fptr2);
}

void intersectionOutputGeneration()
{

    int *arr1, *arr2;
    FILE *fptr = fopen("myImplementation.txt", "w");
    FILE *fptr1 = fopen("STL.txt", "w");

    for (int i = 100; i <= 1000; i += 100)
    {

        // n=i;
        // nToFind = randomNumber(0,n); //random k

        arr1 = randomArr(i, 0, 100000);
        arr2 = randomArr(i, 0, 100000);

        AVLTree test1;
        AVLTree test2;

        // qS(0,n-1, ans);
        for (int j = 0; j < i; j++)
        {
            test1.insert(arr1[j]);
        }

        for (int j = 0; j < i; j++)
        {
            test2.insert(arr2[j]);
        }

        auto start = chrono::high_resolution_clock::now();

        test1.INTERSECTION(test2);
        auto stop = chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed = stop - start;
        cout << endl;
        cout << "Input Size = " << i << endl;
        cout << "Time taken : " << elapsed.count() << " ms to union " << i << " elements" << endl;
        cout << " T(n)/n : " << (double)elapsed.count() / i << endl;

        fprintf(fptr, "%d %f\n", i, (double)(elapsed.count() / i));
        free(arr1);
        free(arr2);
    }

    fclose(fptr);
    fclose(fptr1);
}

void differenceOutputGeneration()
{

    int *arr1, *arr2;
    FILE *fptr1 = fopen("myImplementation.txt", "w");
    FILE *fptr2 = fopen("STL.txt", "w");

    for (int i = 100; i <= 1000; i += 100)
    {
        // n=i;
        // nToFind = randomNumber(0,n); //random k

        arr1 = randomArr(i, 0, 100000);
        arr2 = randomArr(i, 0, 100000);

        AVLTree test1;
        AVLTree test2;

        // qS(0,n-1, ans);
        for (int j = 0; j < i; j++)
        {
            test1.insert(arr1[j]);
        }

        for (int j = 0; j < i; j++)
        {
            test2.insert(arr2[j]);
        }

        auto start = chrono::high_resolution_clock::now();
        test1.DIFFERENCE(test2);
        auto stop = chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed = stop - start;
        cout << endl;
        cout << "Input Size = " << i << endl;
        cout << "Time taken : " << elapsed.count() << " ms to union " << i << " elements" << endl;
        cout << " T(n)/n : " << (double)elapsed.count() / i << endl;

        fprintf(fptr1, "%d %lf\n", i, (double)(elapsed.count() / i));
        free(arr1);
        free(arr2);
    }

    fclose(fptr1);
    fclose(fptr2);
}


void testCase1()
{
    cout << "Inserting few elements and comparing output with STL set" << endl;

    set<int> s;
    s.insert(6);
    s.insert(5);
    s.insert(11);
    s.insert(4);
    s.insert(9);
    s.insert(7);
    // s.insert(12);
    // f = freopen("STL.txt","w",stdout);
    string output2="";
    for(auto i:s)
    {
        output2  = output2 + to_string(i)+ " ";
    }

    AVLTree tree1;
    tree1.insert(6);
    tree1.insert(5);
    tree1.insert(11);
    tree1.insert(4);
    tree1.insert(9);
    tree1.insert(7);

    
    tree1.in_order_print();
    // cout << output1 << endl;
    cout<<endl;
    // cout << output2 <<endl;

    if(output1.compare(output2)==0)
        cout << "__________________________Test case passed!__________________________" << endl;
    else
        cout<< "__________________________Test case failed.__________________________" <<endl;
}


void testCase2()
{
    int * arr1,*arr2;
    cout << "Inserting random elements then performing union" << endl;

    // for (int i = 100; i <= 200; i += 100)
    // {
        // n=i;
        // nToFind = randomNumber(0,n); //random k

        arr1 = randomArr(100, 0, 100);
        arr2 = randomArr(100, 0, 100);

        AVLTree test1;
        AVLTree test2;

        int i =100;

        // qS(0,n-1, ans);
        for (int j = 0; j < 100; j++)
        {
            test1.insert(arr1[j]);
        }

        for (int j = 0; j < i; j++)
        {
            test2.insert(arr2[j]);
        }

        
        AVLTree test3 = test1.UNION(test2);

        output1="";
        test3.in_order_print();
        cout << endl;


        set<int> s1;
        set<int> s2;


          for (int j = 0; j < i; j++)
        {
            s1.insert(arr1[j]);
        }

        for (int j = 0; j < i; j++)
        {
            s2.insert(arr2[j]);
        }

        // insert
        set<int> s3;

        set_union(s1.begin(), s1.end() , s2.begin(), s2.end(), inserter(s3,s3.begin()));

        string output2="";
        for(auto i:s3)
        {
            output2  = output2 + to_string(i)+ " ";
        }

        // cout << output2 <<endl;

        if(output1.compare(output2)==0)
            cout << "__________________________Test passed__________________________" <<endl;
        else
            cout << "__________________________Test failed__________________________" << endl;

        
        // cout << "Input Size = " << i << endl;
        // cout << "Time taken : " << elapsed.count() << " ms to union " << i << " elements" << endl;
        // cout << " T(n)/n : " << (double)elapsed.count() / i << endl;

        // fprintf(fptr1, "%d %lf\n", i, (double)(elapsed.count() / i));
        free(arr1);
        free(arr2);
    // }



}



void testCase3()
{
    int * arr1,*arr2;
    cout << "Inserting 100 random elements each in two sets then performing intersection" << endl;

    // for (int i = 100; i <= 200; i += 100)
    // {
        // n=i;
        // nToFind = randomNumber(0,n); //random k

        arr1 = randomArr(100, 0, 50);
        arr2 = randomArr(100, 0, 50);

        AVLTree test1;
        AVLTree test2;

        int i =100;

        // qS(0,n-1, ans);
        for (int j = 0; j < 100; j++)
        {
            test1.insert(arr1[j]);
        }

        for (int j = 0; j < i; j++)
        {
            test2.insert(arr2[j]);
        }

        
        AVLTree test3 = test1.INTERSECTION(test2);

        output1="";
        test3.in_order_print();
        cout << endl;


        set<int> s1;
        set<int> s2;


          for (int j = 0; j < i; j++)
        {
            s1.insert(arr1[j]);
        }

        for (int j = 0; j < i; j++)
        {
            s2.insert(arr2[j]);
        }

        // insert
        set<int> s3;

        set_intersection(s1.begin(), s1.end() , s2.begin(), s2.end(), inserter(s3,s3.begin()));

        string output2="";
        for(auto i:s3)
        {
            output2  = output2 + to_string(i)+ " ";
        }

        // cout << output2 <<endl;

        if(output1.compare(output2)==0)
            cout << "__________________________Test passed__________________________" <<endl;
        else
            cout << "__________________________Test failed__________________________" << endl;

        
        // cout << "Input Size = " << i << endl;
        // cout << "Time taken : " << elapsed.count() << " ms to union " << i << " elements" << endl;
        // cout << " T(n)/n : " << (double)elapsed.count() / i << endl;

        // fprintf(fptr1, "%d %lf\n", i, (double)(elapsed.count() / i));
        free(arr1);
        free(arr2);
    // }



}



void testCase4()
{
    int * arr1,*arr2;
    cout << "Inserting 100 random elements each in two sets then performing difference" << endl;

    // for (int i = 100; i <= 200; i += 100)
    // {
        // n=i;
        // nToFind = randomNumber(0,n); //random k

        arr1 = randomArr(100, 0, 50);
        arr2 = randomArr(100, 0, 50);

        AVLTree test1;
        AVLTree test2;

        int i =100;

        // qS(0,n-1, ans);
        for (int j = 0; j < 100; j++)
        {
            test1.insert(arr1[j]);
        }

        for (int j = 0; j < i; j++)
        {
            test2.insert(arr2[j]);
        }

        
        AVLTree test3 = test1.DIFFERENCE(test2);

        output1="";
        test3.in_order_print();
        cout << endl;


        set<int> s1;
        set<int> s2;


          for (int j = 0; j < i; j++)
        {
            s1.insert(arr1[j]);
        }

        for (int j = 0; j < i; j++)
        {
            s2.insert(arr2[j]);
        }

        // insert
        set<int> s3;

        set_difference(s1.begin(), s1.end() , s2.begin(), s2.end(), inserter(s3,s3.begin()));

        string output2="";
        for(auto i:s3)
        {
            output2  = output2 + to_string(i)+ " ";
        }

        // cout << output2 <<endl;

        if(output1.compare(output2)==0)
            cout << "__________________________Test passed__________________________" <<endl;
        else
            cout << "__________________________Test failed__________________________" << endl;

    
        delete(arr1);
        delete(arr2);
}

