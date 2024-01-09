#pragma once
#include <cstdint>

namespace DataBase{

template<typename T>
struct rbtree_node
{
    using node_ptr = rbtree_node*;
    using value_type = T;

    rbtree_node* left;
    rbtree_node* parent;
    rbtree_node* right;
    T value;
    char color; 
    char nil;

    //rbtree_node() = delete;
    //rbtree_node(const rbtree_node& node) = delete;
    //rbtree_node& operator=(const rbtree_node& node) = delete;
};

template<typename T>
class rbtree
{
protected:
    enum class node_type { node_red, node_black};  
    using node_ptr = rbtree_node<T>*;

    static char& Color(node_ptr node) { return node->color; }
    static node_ptr& Left(node_ptr node) { return node->left; }
    static node_ptr& Parent(node_ptr node) { return node->parent; }
    static node_ptr& Right(node_ptr node) { return node->right; }
public:
    
    void Add(const T& value)
    {
        node_ptr pnode = head_;
        node_ptr where_node = head_;
        bool add_left = false;
        while (pnode->nil)
        {
            where_node = pnode;
            add_left = value <= pnode->value;
            pnode = add_left ? pnode->left : pnode->right;
        }
        
        InsertNode(add_left, where_node, value);
    }

private:
    void InsertNode(bool add_left, node_ptr where_node, const T& value);

    node_ptr NewNode(const T& value, char crg);
private:
    node_ptr head_;
    uint32_t size_;
};
};