#pragma once
#include <cstdint>

template<typename T>
class smap
{
    enum class node_type { node_red, node_black};   

    struct rbtree_node
    {
        T value;
        node_type type;
        rbtree_node* left;
        rbtree_node* right;
    };
    using node_ptr = *rbtree_node;
public:
    void add(const T& value)
    {
        if (nullptr == head)
        {
            head = new_node(value);
            return ;
        }
        
        
    }

private:
    node_ptr find(const T& key)
    {
        node_ptr pnode = head;
        node_ptr where_node = head;
        while (pnode)
        {
            if (pnode->value < key)
            {
                pnode = pnode->right;
            }
            else
            {
                pnode = pnode->left;
                where_node = pnode;
            }
        }

        return where_node;
    }

    rbtree_node* new_node(const T& value)
    {
        rbtree_node* tmp = new rbtree_node;    
        tmp->type = node_type::node_black;
        tmp->value = std::move(value);
        tmp->left = nullptr;
        tmp->right = nullptr;
        return tmp;
    }
    
private:
    rbtree_node* head;
    uint32_t size;
    uint32_t capatity;
};