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

protected:
    enum class node_type { node_red, node_black};  

    static char& Color(node_ptr node) { return node->color; }
    static node_ptr& Left(node_ptr node) { return node->left; }
    static node_ptr& Parent(node_ptr node) { return node->parent; }
    static node_ptr& Right(node_ptr node) { return node->right; }
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

private:
    void add(bool add_left, node_ptr where_node, const T& value)
    {
        node_ptr new_node = add_node(value, node_type::node_red);
        size_++;

        if (where_node == head_)
        {
            head_ = new_node;
            Left(head_) = new_node, Right(head_) = new_node;
        }
        else if (add_left)
        {
            Left(where_node) = new_node;
        }
        else
        {
            Right(where_node) = new_node;
        }
        
        // 父节点为黑直接插入子节点
        for (node_ptr node = new_node; node_type::node_red == Color(Parent(new_node)))
        {
            //叔节点不存在 
            if (Parent(node) == Left(Parent(Parent(node))))
            {
                // 右旋
            }
            //叔节点存在
            else
            {
            }
        }
        
        // 根节点必须为黑色
        Color(head_) = node_type::node_black;
        return ;
    }

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
#include <map>
std::map<int,int> a;