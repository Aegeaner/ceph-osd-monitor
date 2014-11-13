#include <rados/librados.hpp>
#include "helper.h"

int main()
{
    librados::Rados cluster;

    std::string err = connect_cluster_pp(cluster);
    if(err.length())
	    std::cerr << err << std::endl;
}
