#include <public/rbtree.h>
namespace DataBase{

void rbtree::InsertNode(bool add_left, node_ptr where_node, const T& value)
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

rbtree_node* rbtree::NewNode(const T& value, char crg)
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
};