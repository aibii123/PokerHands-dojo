#include <iostream>

#ifndef UNIT_TEST
int main(int argc, char** argv)
#else
int ut_main(int argc, char** argv)
#endif
{
    std::cout << "We need a HERO to save dumplings !!!" << std::endl;

    return 0;
}
