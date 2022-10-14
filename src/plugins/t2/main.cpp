//
// Created by bismarck on 22-10-11.
//
//
// Created by bismarck on 22-10-11.
//

#include <iostream>
#include "node.h"
#include <boost/dll.hpp>

#define API extern "C" BOOST_SYMBOL_EXPORT

API node& getInstance() {
    return node::get_mutable_instance();
}

API void test() {
    std::cout << "In plugin: " << node::get_const_instance().it << std::endl;
}
