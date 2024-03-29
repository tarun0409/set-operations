#include <iostream>
#include "Set.h"

using namespace std;

Set::Set()
{
    root = NULL;
    size = 0;
}

struct node * Set::create_node(int val)
{
    struct node * new_node = (struct node *)malloc(sizeof(struct node));
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

void Set::init(struct node * new_root)
{
    root = new_root;
}

void Set::update_height(struct node * curr_node)
{
    int max_h = -1;
    if(curr_node->left_child!=NULL)
    {
        if((curr_node->left_child->height) > max_h)
        {
            max_h = curr_node->left_child->height;
        }
    }
    if(curr_node->right_child!=NULL)
    {
        if((curr_node->right_child->height) > max_h)
        {
            max_h = curr_node->right_child->height;
        }
    }
    if(max_h>-1)
    {
        curr_node->height = (max_h+1);
    }
    else if(max_h==-1)
    {
        curr_node->height = 1;
    }
}

void Set::update_balance_factor(struct node * curr_node)
{
    int l_h = 0;
    int r_h = 0;
    if(curr_node->value == 4)
    {
        int x = 0;
        x++;
    }
    if(curr_node->left_child!=NULL)
    {
        l_h = curr_node->left_child->height;
    }
    if(curr_node->right_child!=NULL)
    {
        r_h = curr_node->right_child->height;
    }
    curr_node->balance_factor = (l_h-r_h);
}

void Set::left_left_rotation(struct node * curr_node)
{
    struct node * temp = curr_node ->right_child;
    curr_node->right_child = curr_node->parent;
    int p_n = (curr_node->parent->right_children) + (curr_node->right_children);
    int c_n = curr_node->right_children;
    curr_node->right_children = p_n+1;
    curr_node->parent->left_child = temp;
    curr_node->parent->left_children = c_n;
    if(temp!=NULL)
    {
        temp->parent = curr_node->parent;
    }
    if(curr_node->parent == root)
    {
        root = curr_node;
        curr_node->parent->parent = curr_node;
        curr_node->parent = NULL;
    }
    else
    {
        if((curr_node->parent->parent->value) > (curr_node->parent->value))
        {
            curr_node->parent->parent->left_child = curr_node;
        }
        else
        {
            curr_node->parent->parent->right_child = curr_node;
        }
        struct node * temp_parent = curr_node->parent;
        curr_node->parent = curr_node->parent->parent;
        temp_parent->parent = curr_node;
    }
}

void Set::right_right_rotation(struct node * curr_node)
{
    struct node * temp = curr_node->left_child;
    curr_node->left_child = curr_node->parent;
    int p_n = (curr_node->parent->left_children) + (curr_node->left_children);
    int c_n = curr_node->left_children;
    curr_node->left_children = p_n+1;
    curr_node->parent->right_child = temp;
    curr_node->parent->right_children = c_n;
    if(temp!=NULL)
    {
        temp->parent = curr_node->parent;
    }
    if(curr_node->parent==root)
    {
        root = curr_node;
        curr_node->parent->parent = curr_node;
        curr_node->parent = NULL;
    }
    else
    {
        if((curr_node->parent->parent->value) > (curr_node->parent->value))
        {
            curr_node->parent->parent->left_child = curr_node;
        }
        else
        {
            curr_node->parent->parent->right_child = curr_node;
        }
        struct node * temp_parent = curr_node->parent;
        curr_node->parent = curr_node->parent->parent;
        temp_parent->parent = curr_node;
    }
}

void Set::left_right_rotation(struct node * curr_node)
{
    struct node * temp1 = curr_node->left_child;
    curr_node->left_child = curr_node->parent;
    curr_node->parent->right_child = temp1;
    int p_n = (curr_node->parent->left_children) + (curr_node->left_children);
    int c_n = curr_node->left_children;
    curr_node->left_children = p_n+1;
    curr_node->parent->right_children = c_n;
    if(temp1!=NULL)
    {
        temp1->parent = curr_node->parent;
    }
    curr_node->parent->parent->left_child = curr_node;
    curr_node->parent->parent->left_children = (curr_node->left_children + curr_node->right_children);
    struct node * temp2 = curr_node->parent;
    curr_node->parent = curr_node->parent->parent;
    temp2->parent = curr_node;
}

void Set::right_left_rotation(struct node * curr_node)
{
    struct node * temp1 = curr_node->right_child;
    curr_node->right_child = curr_node->parent;
    curr_node->parent->left_child = temp1;
    int p_n = (curr_node->parent->right_children) + (curr_node->right_children);
    int c_n = curr_node->right_children;
    curr_node->right_children = p_n+1;
    curr_node->parent->left_children = c_n;
    if(temp1!=NULL)
    {
        temp1->parent = curr_node->parent;
    }
    curr_node->parent->parent->right_child = curr_node;
    curr_node->parent->parent->right_children = (curr_node->left_children + curr_node->right_children);
    struct node * temp2 = curr_node->parent;
    curr_node->parent = curr_node->parent->parent;
    temp2->parent  = curr_node;
}

int Set::check_and_balance_tree(struct node * curr_node)
{
    int change = 0;
    if(curr_node==NULL)
    {
        return change;
    }
    if(curr_node->balance_factor>1)
    {
        if(curr_node->left_child->balance_factor > 0)
        {
            struct node * temp_curr = curr_node->left_child;
            left_left_rotation(curr_node->left_child);
            change = 1;
            if(temp_curr->left_child!=NULL)
            {
                update_height(temp_curr->left_child);
                update_balance_factor(temp_curr->left_child);
            }
            if(temp_curr->right_child!=NULL)
            {
                update_height(temp_curr->right_child);
                update_balance_factor(temp_curr->right_child);
            }
            update_height(temp_curr);
            update_balance_factor(temp_curr);
        }
        else if(curr_node->left_child->balance_factor<0)
        {
            left_right_rotation(curr_node->left_child->right_child);
            struct node * temp_curr = curr_node->left_child;
            left_left_rotation(curr_node->left_child);
            change = 1;
            if(temp_curr->left_child!=NULL)
            {
                update_height(temp_curr->left_child);
                update_balance_factor(temp_curr->left_child);
            }
            if(temp_curr->right_child!=NULL)
            {
                update_height(temp_curr->right_child);
                update_balance_factor(temp_curr->right_child);
            }
            update_height(temp_curr);
            update_balance_factor(temp_curr);
        }
    }
    else if(curr_node->balance_factor<-1)
    {
        if(curr_node->right_child->balance_factor < 0)
        {
            struct node * temp_curr = curr_node->right_child;
            right_right_rotation(curr_node->right_child);
            change = 1;
            if(temp_curr->left_child!=NULL)
            {
                update_height(temp_curr->left_child);
                update_balance_factor(temp_curr->left_child);
            }
            if(temp_curr->right_child!=NULL)
            {
                update_height(temp_curr->right_child);
                update_balance_factor(temp_curr->right_child);
            }
            update_height(temp_curr);
            update_balance_factor(temp_curr);
        }
        else if(curr_node->right_child->balance_factor>0)
        {
            right_left_rotation(curr_node->right_child->left_child);
            struct node * temp_curr = curr_node->right_child;
            right_right_rotation(curr_node->right_child);
            change = 1;
            if(temp_curr->left_child!=NULL)
            {
                update_height(temp_curr->left_child);
                update_balance_factor(temp_curr->left_child);
            }
            if(temp_curr->right_child!=NULL)
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

struct node * Set::find_predecessor(struct node * curr_node)
{
    if(curr_node==NULL)
    {
        return NULL;
    }
    if(curr_node->left_child == NULL)
    {
        return curr_node;
    }
    struct node * temp = curr_node->left_child;
    while(temp->right_child!=NULL)
    {
        temp = temp->right_child;
    }
    return temp;
}

int Set::insert_node(struct node * curr_node, struct node * new_node)
{
    int status;
    if(root==NULL)
    {
        root = new_node;
        return 1;
    }
    if((new_node->value) == (curr_node->value))
    {
        return 0;
    }
    if((new_node->value) < (curr_node->value))
    {
        if(curr_node->left_child==NULL)
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
            status = insert_node((curr_node->left_child) , new_node);
            if(status)
            {
                update_height(curr_node);
                update_balance_factor(curr_node);
                int change = check_and_balance_tree(curr_node);
                if(!change)
                {
                    (curr_node->left_children)++;
                }
            }
        }
    }
    else if((new_node->value) > (curr_node->value))
    {
        if(curr_node->right_child==NULL)
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
            status =  insert_node((curr_node->right_child), new_node);
            if(status)
            {
                update_height(curr_node);
                update_balance_factor(curr_node);
                int change = check_and_balance_tree(curr_node);
                if(!change)
                {
                    (curr_node->right_children)++;
                }
            }
        }
    }
    return status;
}

int Set::insert(int new_val)
{
    struct node * new_node = create_node(new_val);
    int success = insert_node(root,new_node);
    if(success)
    {
        size++;
    }
    return success;
}

struct node * Set::find_node(struct node * curr_node, int target)
{
    struct node * dest = NULL;
    if(root==NULL)
    {
        return NULL;
    }
    if((curr_node->value) == target)
    {
        return curr_node;
    }
    else if(((curr_node->value) > target) && curr_node->left_child!=NULL)
    {
        dest = find_node(curr_node->left_child, target);
    }
    else if(((curr_node->value)<target) && curr_node->right_child!=NULL)
    {
        dest = find_node(curr_node->right_child, target);
    }
    return dest;
}

struct node * Set::find(int target)
{
    return find_node(root,target);
}

int Set::find_element(int k)
{
    struct node * n = find_node(root, k);
    if(n==NULL)
    {
        return 0;
    }
    return 1;
}

int Set::remove(int val)
{
    struct node * curr_node = find(val);
    if(curr_node==NULL)
    {
        return 0;
    }
    if(curr_node->left_child==NULL)
    {
        if(curr_node==root)
        {
            root = curr_node->right_child;
            if(curr_node->right_child!=NULL)
            {
                curr_node->right_child->parent = NULL;
            }
        }
        else
        {
            if(curr_node->parent->left_child == curr_node)
            {
                curr_node->parent->left_child = curr_node->right_child;
                if(curr_node->right_child!=NULL)
                {
                        curr_node->parent->left_children--;
                }
                else
                {
                    curr_node->parent->left_children = 0;
                }
            }
            else if(curr_node->parent->right_child == curr_node)
            {
                curr_node->parent->right_child = curr_node->right_child;
                if(curr_node->right_child!=NULL)
                {
                    curr_node->parent->right_children--;
                }
                else
                {
                    curr_node->parent->right_children = 0;
                }
            }
            if(curr_node->right_child!=NULL)
            {
                curr_node->right_child->parent = curr_node->parent;
            }
        }
        curr_node = curr_node->parent;
    }
    else
    {
        struct node * pred = find_predecessor(curr_node);
        curr_node->value = pred->value;

        if(pred->parent->left_child == pred)
        {
            pred->parent->left_child = pred->left_child;
            if(pred->left_child!=NULL)
            {
                pred->parent->left_children--;
            }
            else
            {
                pred->parent->left_children = 0;
            }
        }
        else if(pred->parent->right_child == pred)
        {
            pred->parent->right_child = pred->left_child;
            if(pred->left_child!=NULL)
            {
                pred->parent->right_children--;
            }
            else
            {
                pred->parent->right_children = 0;
            }
        }
        if(pred->left_child!=NULL)
        {
            pred->left_child->parent = pred->parent;
        }
        curr_node = pred->parent;
    }

    while(curr_node!=NULL)
    {
        update_height(curr_node);
        update_balance_factor(curr_node);
        check_and_balance_tree(curr_node);
        if(curr_node->left_child!=NULL)
        {
            curr_node->left_children = (curr_node->left_child->left_children + curr_node->left_child->right_children + 1);
        }
        else
        {
            curr_node->left_children = 0;
        }
        if(curr_node->right_child!=NULL)
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

int Set::find_kth_smallest(struct node * curr_root, int k)
{
    if(curr_root==NULL || k==0)
    {
        //cout<<"\n\nRoot is null\n\n";
        //exit(1);
        return 0;
    }
    int n = curr_root->left_children;
    if(k==(n+1))
    {
        return curr_root->value;
    }
    else
    {
        if(k<=n)
        {
            return find_kth_smallest(curr_root->left_child, k);
        }
        else
        {
            return find_kth_smallest(curr_root->right_child,(k-n-1));
        }
    }
    return 0;
}

int Set::find_kth_smallest(int k)
{
    return find_kth_smallest(root,k);
}

vector<int> Set::in_order_fill(struct node * curr_node, vector<int> arr)
{
    if(curr_node==NULL)
    {
        return arr;
    }
    arr = in_order_fill(curr_node->left_child,arr);
    arr.push_back(curr_node->value);
    arr = in_order_fill(curr_node->right_child,arr);
    return arr;
}

vector<int> Set::get_elements()
{
    vector<int> arr;
    arr = in_order_fill(root,arr);
    return arr;
}

int Set::fill_bbst(struct node * curr_node, vector<int> arr, int start_index, int end_index, int curr_pos)
{
    if(end_index<start_index)
    {
        return 1;
    }
    int mid = (start_index+end_index)/2;

    int value = arr[mid];
    struct node * new_node = create_node(value);
    //new_node->height = height;
    if(start_index!=end_index)
    {
        new_node->left_children = (mid-start_index);
        new_node->right_children = (end_index-mid);
    }
    if(curr_pos==0)
    {
        curr_node->left_child = new_node;
    }
    else if(curr_pos==1)
    {
        curr_node->right_child = new_node;
    }
    int h1 = fill_bbst(new_node, arr, start_index, (mid-1),0);
    int h2 = fill_bbst(new_node, arr, (mid+1), end_index,1);
    int height = (h1>h2?h1:h2);
    new_node->height = height;
    int bf = h1-h2;
    new_node->balance_factor = bf;
    return (height+1);
}

Set Set::get_bbst_from_sorted_list(vector<int> arr)
{
    int start_index = 0;
    int end_index = arr.size() - 1;
    if(end_index<start_index)
    {
        Set empty;
        return empty;
    }
    int mid = (start_index+end_index)/2;
    int value = arr[mid];
    struct node * new_node = create_node(value);
    if(start_index!=end_index)
    {
        new_node->left_children = mid;
        new_node->right_children = (end_index-start_index) - mid;
    }
    struct node * new_root = new_node;
    int h1 = fill_bbst(new_node, arr, start_index, (mid-1),0);
    int h2 = fill_bbst(new_node, arr, (mid+1), end_index,1);
    int height = (h1>h2?h1:h2);
    new_node->height = height;
    new_node->balance_factor = (h1-h2);
    Set bbst;
    bbst.init(new_root);
    return bbst;
}

Set Set::DIFFERENCE(Set tree2)
{
    vector<int> set1 = get_elements();
    vector<int> set2 = tree2.get_elements();
    vector<int> diff_set;
    int i=0,j=0;
    while(i<set1.size() && j<set2.size())
    {
        if(set1[i]<set2[j])
        {
            diff_set.push_back(set1[i]);
            i++;
        }
        else if(set1[i]>set2[j])
        {
            j++;
        }
        else
        {
            i++;
            j++;
        }
    }
    while(i<set1.size())
    {
        diff_set.push_back(set1[i]);
        i++;
    }
    Set bbst = get_bbst_from_sorted_list(diff_set);
    return bbst;
}

Set Set::INTERSECTION(Set tree2)
{
    vector<int> set1 = get_elements();
    vector<int> set2 = tree2.get_elements();
    vector<int> inter_set;
    int i=0, j=0;
    while(i<set1.size() && j<set2.size())
    {
        if(set1[i]<set2[j])
        {
            i++;
        }
        else if(set1[i]>set2[j])
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
    Set bbst = get_bbst_from_sorted_list(inter_set);
    return bbst;
}

Set Set::UNION(Set tree2)
{
    vector<int> set1 = get_elements();
    vector<int> set2 = tree2.get_elements();
    vector<int> union_set;
    int i=0, j=0;
    while(i<set1.size() && j<set2.size())
    {
        int s = union_set.size();
        s--;
        if(s>=0 && union_set[s]==set1[i])
        {
            i++;
        }
        if(s>=0 && union_set[s]==set2[j])
        {
            j++;
        }
        if(i<set1.size() && set1[i]<=set2[j])
        {
            union_set.push_back(set1[i]);
            i++;
        }
        else if(j<set2.size())
        {
            union_set.push_back(set2[j]);
            j++;
        }
    }
    if(i<set1.size())
    {
        while(i<set1.size())
        {
            union_set.push_back(set1[i]);
            i++;
        }
    }
    else if(j<set2.size())
    {
        while(j<set2.size())
        {
            union_set.push_back(set2[j]);
            j++;
        }
    }
    Set bbst = get_bbst_from_sorted_list(union_set);
    return bbst;
}

void Set::in_order_print(struct node * curr_node)
{
    if(curr_node==NULL)
    {
        return;
    }
    in_order_print(curr_node->left_child);
    cout<<"("<<curr_node->value<<","<<curr_node->height<<")";
    in_order_print(curr_node->right_child);
}

void Set::in_order_print()
{
    if(root==NULL)
    {
        printf("\nTree is empty!\n");
        return;
    }
    cout<<endl;
    in_order_print(root);
    cout<<endl;
}

int Set::get_size()
{
    return size;
}