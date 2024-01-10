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

    rbtree_node(NodePtr Larg, NodePtr Parg, NodePtr Rarg, 
        const T& value, char crg)
        :left(Larg),right(Parg),value(value),color(crg),nil(false)
    {

    }
    //rbtree_node(const rbtree_node& node) = delete;
    //rbtree_node& operator=(const rbtree_node& node) = delete;
};

template<typename T>
class rbtree
{
protected:
    enum node_type { node_red, node_black};  
    typedef typename rbtree_node<T>::NodePtr NodePtr;

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

    void InsertNode(bool bAddLeft, NodePtr pWherenode, const T& value)
    {
        NodePtr Newnode = BuyNode(Head_, pWherenode, Head_, value, node_type::node_red);
        Size_++;

        if (pWherenode == Head_)
        {
            Root() = Newnode;
            Left(Head_) = Newnode, Right(Head_) = Newnode;
        }
        else if (bAddLeft)
        {
            Left(pWherenode) = Newnode;
        }
        else
        {
            Right(pWherenode) = Newnode;
        }
        
        // 父节点为黑直接插入子节点
        for (NodePtr pNode = Newnode; node_type::node_red == Color(Parent(pNode)); )
        {
            //叔节点不存在 
            if (Parent(pNode) == Left(Parent(Parent(pNode))))
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

    NodePtr BuyNode(NodePtr Larg, NodePtr Parg, NodePtr Rarg, 
        const T& value, char crg)
    {
        NodePtr Wherenode = new rbtree_node<T>(Larg, Parg, Rarg, value, crg);
        return Wherenode;
    }

    NodePtr BuyNode()
    {
        NodePtr Wherenode = new rbtree_node<T>(
            nullptr, nullptr, nullptr, T(), node_type::node_black
        );
        return Wherenode;
    }

    void Init()
    {
        Head_ = nullptr;//BuyNode();
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