#pragma once
#include <cstdint>

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
class smap:public: rbtree_node<T>
{
    enum class node_type { node_red, node_black};  
protected:

public:
    void add(const T& value)
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
        
        add(add_left, where_node, value);
    }

    void add(bool add_left, node_ptr where_node, const T& value)
    {
        node_ptr new_node = add_node(value, node_type::node_red);
        size_++;

        if (where_node == head_)
        {
            head_ = new_node;
            head_->left = new_node, head_->right = new_node;
        }
        else if (add_left)
        {
            head_->left = new_node;
        }
        else
        {
            head_->right = new_node;
        }

        for ()
        {
            /* code */
        }
        
        head_->type = node_type::node_black;
        return ;
    }
private:
    rbtree_node* add_node(const T& value, char crg)
    {
        rbtree_node* tmp = new rbtree_node;    
        tmp->type = crg;
        tmp->nil = false;
        tmp->value = std::move(value);
        tmp->left = nullptr;
        tmp->parent = nullptr;
        tmp->right = nullptr;
        return tmp;
    }
private:
    rbtree_node* head_;
    uint32_t size_;
};