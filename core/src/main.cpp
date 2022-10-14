#include <iostream>

#include <boost/dll.hpp>

int main() {
    boost::dll::shared_library lib("/home/bismarck/mos/cmake-build-debug/plugins/t1/libtest1.so");
    boost::dll::shared_library lib2("/home/bismarck/mos/cmake-build-debug/plugins/t1/libtest2.so");
//    auto& nh = lib.get<node& (void)>("getInstance")();
//    std::cout << "In main 1: " << nh.it << std::endl;
//    nh.it = 12;
//    std::cout << "In main 2: " << nh.it << std::endl;
//    lib.get<void (void)>("test")();
//
//    auto& nh2 = lib2.get<node& (void)>("getInstance")();
//    std::cout << "In main 3: " << nh2.it << std::endl;
//    nh2.it = 13;
//    lib2.get<void (void)>("test")();
//
//    std::cout << "In main 4: " << node::get_const_instance().it << std::endl;
//    return 0;
}
