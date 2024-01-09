#pragma once
#include <cstdint>

namespace DataBase{

template<typename T>
class rbtree_node: public T
{
protected:
    struct node;
    using node_ptr = node*;
    using value_type = T::value_type;

    struct node
    {
        rbtree_node* left;
        rbtree_node* parent;
        rbtree_node* right;
        T value;
        char color; 
        char nil;
    };
private:
    node_ptr alnod;
};

template<typename T>
class rbtree:
    public: rbtree_node<T>
{

protected:
    enum class node_type { node_red, node_black};  

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
            where_node = node;
            add_left = value <= node->value;
            pnode = add_left ? node->left : node->right;
        }
        
        InsertNode(add_left, where_node, value);
    }

private:
    void InsertNode(bool add_left, node_ptr where_node, const T& value);

    rbtree_node* NewNode(const T& value, char crg);
    
private:
    rbtree_node* head_;
    uint32_t size_;
};
};