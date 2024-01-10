#pragma once
#include <cstdint>

namespace DataBase{

template<typename T>
struct rbtree_node
{
    using NodePtr = rbtree_node*;
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
    enum node_type { node_red, node_black};  
    using NodePtr = rbtree_node<T>*;

    static char& Color(NodePtr node) { return node->color; }
    static char& IsNil(NodePtr node) { return node->nil; }
    static NodePtr& Left(NodePtr node) { return node->left; }
    static NodePtr& Parent(NodePtr node) { return node->parent; }
    static NodePtr& Right(NodePtr node) { return node->right; }
    NodePtr& Root() { return Parent(Head_);}
public:
    rbtree()
    {
        Init();
    }

    void Add(const T& value)
    {
        NodePtr pNode = Root();
        NodePtr pWherenode = Head_;
        bool bAddLeft = true;
        while (!IsNil(pNode))
        {
            pWherenode = pNode;
            bAddLeft = value <= pNode->value;
            pNode = bAddLeft ? pNode->left : pNode->right;
        }
        
        InsertNode(bAddLeft, pWherenode, value);
    }

private:

    void RLeft(NodePtr WhereNode);
    void RRight(NodePtr WhereNode);

    NodePtr NewNode(const T& value, char crg)
    {
        NodePtr tmp = new rbtree_node<T>;
        tmp->color = crg;
        tmp->nil = false;
        tmp->value = value;
        tmp->left = nullptr;
        tmp->parent = nullptr;
        tmp->right = nullptr;
        return tmp;
    }

    void InsertNode(bool bAddLeft, NodePtr pWherenode, const T& value)
    {
        NodePtr new_node = NewNode(value, node_type::node_red);
        Size_++;

        if (pWherenode == Head_)
        {
            Root() = new_node;
            Left(Head_) = new_node, Right(Head_) = new_node;
        }
        else if (bAddLeft)
        {
            Left(pWherenode) = new_node;
        }
        else
        {
            Right(pWherenode) = new_node;
        }
        
        // 父节点为黑直接插入子节点
        for (NodePtr node = new_node; node_type::node_red == Color(Parent(new_node)); )
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
        Color(Head_) = node_type::node_black;
        //return ;
    }

    void Init()
    {
        Head_ = NewNode(T(), node_black);
        IsNil(Head_) = true;
        Root() = Head_;
        Left(Head_) = Head_, Right(Head_) = Head_;
        Size_ = 0;
    }
private:
    NodePtr Head_ = nullptr;
    uint32_t Size_ = 0;
};
};