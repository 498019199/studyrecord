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
};

template<typename T>
class rbtree
{
protected:
    enum RBNodeType { _Red, _Black};  
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
        NodePtr Newnode = BuyNode(Head_, pWherenode, Head_, Val, RBNodeType::_Red);
        Size_++;

        // 维护_Head 指向节点
        if (pWherenode == Head_)
        {
            // 情形1：新节点N位于树的根上，没有父节点。
            Root() = Newnode;
            Left(Head_) = Newnode, Right(Head_) = Newnode;
        }
        else if (bAddLeft)
        {
            Left(pWherenode) = Newnode;
            // maintain leftmost pointing to min node
            if (pWherenode == Head_->Left_) 
                Left(Head_) = Newnode;
        }
        else
        {
            Right(pWherenode) = Newnode;
            // maintain rightmost pointing to max node
            if (pWherenode == Head_->Right_) 
                Right(Head_) = Newnode;
        }
        
        // rebalance                  // 情形2:新节点的父节点P是黑色,直接插入
        for (NodePtr pNode = Newnode; RBNodeType::_Red == Color(Parent(pNode)); ) 
        {
            if (Parent(pNode) == Left(Parent(Parent(pNode)))) // 查看是否存在节点的叔父节点
            {
                //叔节点存在
                pWherenode/*祖父节点*/ = Right(Parent(Parent(pNode)));
                // if (Color(pWherenode) == RBNodeType::_Red) // *祖父父节点为红
                // {
                //     // 情形3：父节点为红色，叔父节点为红色
                //     Color(pNode) = RBNodeType::_Black;
                //     Color(pWherenode) = RBNodeType::_Black;
                //     Color(Parent(pNode)) = RBNodeType::_Red;
                //     pNode = Parent(Parent(pNode));
                // }
                // else // *祖父父节点为黑
                // {
                //     // 右旋
                // }
            }
            else
            {
                pWherenode/*叔父节点*/ = Left(Parent(Parent(pNode)));
                if (Color(pWherenode) == RBNodeType::_Red) // *叔父父节点为红
                {
                    // 情形3：父节点为红色，叔父节点为红色
                    Color(pNode) = RBNodeType::_Black;
                    Color(pWherenode) = RBNodeType::_Black;
                    Color(Parent(pNode)) = RBNodeType::_Red;
                    pNode = Parent(Parent(pNode));
                }
                else
                {
                    if (pWherenode == Left(Parent(pWherenode)))
                    {
                        // 情形4 父节点P是红色而叔父节点U是黑色
                        pNode = Parent(pNode);
                        Rrotate(pNode);
                    }
                    // 情形5
                    Color(Parent(pNode)) = RBNodeType::_Black;
                    Color(Parent(Parent(pNode))) = RBNodeType::_Red;
                    Lrotate(Parent(Parent(pNode)));
                }
            }
        }
        
        // 根节点必须为黑色
        Color(Root()) = RBNodeType::_Black;
    }

    void Lrotate(NodePtr pWhereNode)
    {
        // 旋转pWhereNode，pNode(pWhereNode的右孩子)
        NodePtr pNode = Right(pWhereNode);
        // pNode替换pWhereNode的位置，pNode右孩子是pWhereNode。
        Right(pWhereNode) = Left(pNode);
        // 需要修改pNode右孩子
        if (!IsNil(Left(pNode)))
            Parent(Left(pNode)) = pWhereNode;
        Parent(pNode) = Parent(pWhereNode);

        if (Root() == pWhereNode) //pWhereNode is root
            Root() = pNode;
        else if (pWhereNode == Left(Parent(pWhereNode))) // pWhereNode is left child
            Left(Parent(pWhereNode)) = pWhereNode;
        else 
            Left(Parent(pWhereNode)) = pWhereNode;
        
        // pWhereNode成为pNode右孩子，pWhereNode右孩子是原来pWhereNode左孩子
        Left(pNode) = pWhereNode;
        Parent(pWhereNode) = pNode;
    }

    // pWhereNode节点P, pWhereNode的左孩子节点N
    void Rrotate(NodePtr pWhereNode)
    {
        // 获取pWhereNode的左孩子N
        NodePtr pNode = Left(pWhereNode);

        // p.Left 互指 N.Rihgt
        Left(pWhereNode) = Right(pNode);        // P左子树改为N的右子树
        if (!IsNil(Right(pNode)))               
            Parent(Right(pNode)) = pWhereNode;  // 改N的右子树父节点为P

        // 修改P的父节点
        Parent(pNode) = Parent(pWhereNode);     // P父节点改为N父节点
        if (Root() == pWhereNode) 
            Root() = pNode;// 情况1：如果P的父亲根节点，则将N设为根节点
        // 修改N的父节点
        else if (pWhereNode == Right(Parent(pWhereNode)))
            Right(Parent(pWhereNode)) = pNode;//情况2：如果P是它父节点的左孩子，则将N设为P的父节点的左孩子
        else 
            Left(Parent(pWhereNode)) = pNode;
        
        Right(pNode) = pWhereNode;
        Parent(pWhereNode) = pNode;
    }

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
            nullptr, nullptr, nullptr, T(), RBNodeType::_Black
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