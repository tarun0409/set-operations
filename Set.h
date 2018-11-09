#include<vector>
struct node
{
    int value;
    struct node * left_child;
    struct node * right_child;
    struct node * parent;
    int height;
    int balance_factor;
    int left_children;
    int right_children;
};

class Set
{
    private:

    struct node * root;
    int size;;

    struct node * create_node(int val);
    void init(struct node * new_root);
    void update_height(struct node * curr_node);
    void update_balance_factor(struct node * curr_node);
    void left_left_rotation(struct node * curr_node);
    void right_right_rotation(struct node * curr_node);
    void left_right_rotation(struct node * curr_node);
    void right_left_rotation(struct node * curr_node);
    int check_and_balance_tree(struct node * curr_node);
    struct node * find_predecessor(struct node * curr_node);
    int insert_node(struct node * curr_node, struct node * new_node);
    struct node * find_node(struct node * curr_node, int target);
    struct node * find(int target);
    int find_kth_smallest(struct node * curr_root, int k);
    std::vector<int> in_order_fill(struct node * curr_node, std::vector<int> arr);
    int fill_bbst(struct node * curr_node, std::vector<int> arr, int start_index, int end_index, int curr_pos);
    Set get_bbst_from_sorted_list(std::vector<int> arr);
    void in_order_print(struct node * curr_node);

    public:
    Set();
    int insert(int new_val);
    int remove(int val);
    int find_element(int k);
    int find_kth_smallest(int k);
    std::vector<int> get_elements();
    Set DIFFERENCE(Set tree2);
    Set INTERSECTION(Set tree2);
    Set UNION(Set tree2);
    void in_order_print();
    int get_size();
    
};