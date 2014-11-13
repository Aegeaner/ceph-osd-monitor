#include <sstream>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include "helper.h"

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

std::string create_one_pool_pp(const std::string &pool_name, Rados &cluster)
{
  std::string err = connect_cluster_pp(cluster);
  if(err.length())
    return err;
  int ret = cluster.pool_create(pool_name.c_str());
  if(ret) {
    cluster.shutdown();
    std::ostringstream oss;
    oss << "cluster.pool_create(" << pool_name << ") failed with error " << ret;
    return oss.str();
  }
  
  return "";
}

static int get_features(bool *old_format, uint64_t *features)
{
  const char *c = getenv("RBD_FEATURES");
  if (c) {
    std::stringstream ss;
    ss << c;
    ss >> *features;
    if (ss.fail())
      return -EINVAL;
    *old_format = false;
    std::cout << "using new format!" << std::endl;
  } else {
    *old_format = true;
    std::cout << "using old format" << std::endl;
  }

  return 0;
}

int create_image_pp(librbd::RBD &rbd,
                           librados::IoCtx &ioctx,
                           const char *name,
                           uint64_t size, int *order) {
  bool old_format;
  uint64_t features;
  int r = get_features(&old_format, &features);
  if (r < 0)
    return r;
  if (old_format) {
    return rbd.create(ioctx, name, size, order);
  } else {
    return rbd.create2(ioctx, name, size, features, order);
  }
}
