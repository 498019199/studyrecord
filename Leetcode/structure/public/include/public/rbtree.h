#pragma once
#include <cstdint>

namespace DataBase{

template<typename T>
struct rbtree_node
{
    using NodePtr = rbtree_node*;
    using value_type = T;

    rbtree_node* Left_;
    rbtree_node* Parent_;
    rbtree_node* Right_;
    T Value_;
    char Color_; 
    char Nil_;

    rbtree_node(NodePtr Larg, NodePtr Parg, NodePtr Rarg, 
        const T& value, char crg)
        :Left_(Larg), Parent_(Parg), Right_(Rarg), Value_(value), Color_(crg), Nil_(false)
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

    static char& Color(NodePtr node) { return node->Color_; }
    static char& IsNil(NodePtr node) { return node->Nil_; }
    static T& MyVal(NodePtr node) { return node->Value_; }
    static NodePtr& Left(NodePtr node) { return node->Left_; }
    static NodePtr& Parent(NodePtr node) { return node->Parent_; }
    static NodePtr& Right(NodePtr node) { return node->Right_; }

    NodePtr& Root() { return Parent(Head_);}
public:
    rbtree()
    {
        Init();
    }

    ~rbtree()
    {
        Tidy();
    }

    void Add(const T& Val)
    {
        NodePtr pNode = Root();
        NodePtr pWherenode = Head_;
        bool bAddLeft = true;
        while (!IsNil(pNode))
        {
            pWherenode = pNode;
            bAddLeft = Val < MyVal(pNode);
            pNode = bAddLeft ? Left(pNode) : Right(pNode);
        }
        
        InsertNode(bAddLeft, pWherenode, Val);
    }

private:

    void InsertNode(bool bAddLeft, NodePtr pWherenode, const T& Val)
    {
        NodePtr Newnode = BuyNode(Head_, pWherenode, Head_, Val, node_type::node_red);
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
            if (Parent(pNode) == Left(Parent(Parent(pNode)))) // 查看是否存在节点的叔父节点
            {
                //叔节点不存在
                pWherenode/*祖父节点*/ = Right(Parent(Parent(pNode)));
                if (Color(pWherenode) == node_type::node_red) // *祖父父节点为红
                {
                    // wiki/红黑树#插入##情形3
                    Color(pNode) = node_type::node_black;
                    Color(pWherenode) = node_type::node_black;
                    Color(Parent(pNode)) = node_type::node_red;
                }
                else // *祖父父节点为黑
                {
                    // 右旋
                }
            }
            else
            {
                //叔节点存在
                pWherenode/*叔父节点*/ = Left(Parent(Parent(pNode)));
                if (Color(pWherenode) == node_type::node_red) // *叔父父节点为红
                {}
                else
                {
                    Color(Parent(pNode)) = node_type::node_black;
                    Color(Parent(Parent(pNode))) = node_type::node_red;
                    Lrotate(Parent(Parent(pNode)));
                }
            }
        }
        
        // 根节点必须为黑色
        Color(Root()) = node_type::node_black;
    }

    void Lrotate(NodePtr pWhereNode)
    {
        NodePtr pNode = Right(pWhereNode);
        Right(pWhereNode) = Left(pNode);
        Left(pNode) = pWhereNode;

        if (Root() == pWhereNode)
        {
            Root() = pNode;
        } 
    }

    void Rrotate(NodePtr WhereNode)
    {}

    NodePtr BuyNode(NodePtr Larg, NodePtr Parg, NodePtr Rarg, 
        const T& value, char crg)
    {
        NodePtr Wherenode = new rbtree_node<T>(Larg, Parg, Rarg, value, crg);
#ifdef _DEBUG
    printf("new node address: %p   %d\n", Wherenode, value);
#endif//_DEBUG
        return Wherenode;
    }

    NodePtr BuyNode()
    {
        NodePtr Wherenode = new rbtree_node<T>(
            nullptr, nullptr, nullptr, T(), node_type::node_black
        );
#ifdef _DEBUG
    printf("head node address: %p\n", Wherenode);
#endif//_DEBUG
        return Wherenode;
    }

    void Init()
    {
        Head_ = BuyNode();
        IsNil(Head_) = true;
        Root() = Head_;
        Left(Head_) = Head_, Right(Head_) = Head_;
        Size_ = 0;
    }

    void Tidy()
    {

    }
private:
    NodePtr Head_ = nullptr;
    uint32_t Size_ = 0;
};


};