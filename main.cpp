#include <iostream>
#include "driver.hh"
#include "syntax_tree.hh"

driver ddriver;
CompUnit *root;

int main (int argc, char *argv[])
{
    std::cout << "start..." << std::endl;
    if(argc < 2){
        std::cout << "please enter a file: ./main test.sy" <<std::endl;
        exit(0);
    }
    root = ddriver.parse(argv[1]);
    root->visit(0);
    std::cout << "end..." <<std::endl;
    return 0;
}
