#pragma once
#include <cstdint>

class smap
{
    enum class node_type { node_red, node_black};   

    struct map_node
    {
        void* value;
        node_type type;
    };

private:
    map_node* new_node(void* value)
    {
        map_node* tmp = new map_node;    
        tmp->type = node_type::node_black;
        tmp->value = value;
        return tmp;
    }
    
private:
    map_node* head;
    uint32_t size;
    uint32_t capatity;
};