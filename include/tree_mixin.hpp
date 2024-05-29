#ifndef EV_TREE_MIXIN_HPP
#define EV_TREE_MIXIN_HPP

#include "avl_tree.hpp"
#include "binary_search_tree.h"
#include <type_traits>

template<typename StructureType> struct is_tree : public std::false_type
{
};

template<typename T> struct is_tree<ev::AVLTree<T>> : public std::true_type
{
};

template<typename T> struct is_tree<BinarySearchTree<T>> : public std::true_type
{
};

#endif
