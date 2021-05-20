#include <iostream>
#include <string>
#include "../interface/mini_analyzer.h"

# ifndef __CINT__
int main(int argc, char * argv[])
{
    if(argc != 5){
        std::cout << "did not provide correct arguments: ./executable input_filename max_entries partition partitionjobnumber" << std::endl;
        return 1;
    }

    mini_analyzer mini(argv[1]);
    double max_entries      = atof(argv[2]);
    int partition           = atoi(argv[3]);
    int partitionjobnumber  = atoi(argv[4]);
    mini.analyze(max_entries, partition, partitionjobnumber);
}
#endif
