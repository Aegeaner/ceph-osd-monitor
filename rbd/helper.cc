#include <rados/librados.h>
#include <rados/librados.hpp>
#include "helper.h"

#include <sstream>
#include <stdlib.h>
#include <string>
#include <unistd.h>

using namespace librados;

std::string connect_cluster_pp(Rados &cluster)
{
    char *id = getenv("CEPH_CLIENT_ID");
    if(id)
        std::cerr << "Client id is: " << id << std::endl;

    int ret;
    ret = cluster.init(id);
    if(ret) {
        std::ostringstream oss;
        oss << "cluster init failed with error " << ret;
        return oss.str();
    }

    ret = cluster.conf_read_file(NULL);
    if(ret) {
      cluster.shutdown();
      std::ostringstream oss;
      oss << "cluster.conf_read_file failed with error " << ret;
      return oss.str();
    }

    cluster.conf_parse_env(NULL);
    ret = cluster.connect();
    if(ret) {
      cluster.shutdown();
      std::ostringstream oss;
      oss << "cluster.connect failed with error " << ret;
      return oss.str();
    }
    
    return "";
}
