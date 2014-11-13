#include <rados/librados.hpp>
#include "helper.h"

void err_print(int ret, const char *error, const char *normal)
{
  if(ret < 0) {
    std::cerr << error << ": " << ret << std::endl;
    exit(EXIT_FAILURE);
  } else {
    std::cout << normal << std::endl;
  }
}
    

int main()
{
    librados::Rados cluster;
    librados::IoCtx ioctx;
    std::string pool_name = "rbd_demo";
    std::string image_name = "test_image";
    std::string err;
    int ret;

    err = connect_cluster_pp(cluster);
	  err_print(err.length(), err.c_str(), "Cluster connected.");

    err = create_one_pool_pp(pool_name, cluster);
    err_print(err.length(), err.c_str(), "Created one pool.");

    ret = cluster.ioctx_create(pool_name.c_str(), ioctx);
    err_print(ret, "Failed to create IO context", "Created IO context.");

    {
      librbd::RBD rbd;
      librbd::image_info_t info;
      librbd::Image image;
      int order = 0;
      uint64_t size = 2 << 20;

      ret = create_image_pp(rbd, ioctx, image_name.c_str(), size, &order);
      err_print(ret, "Failed to create image", "Created image.");

      ret = rbd.open(ioctx, image, image_name.c_str());
      err_print(ret, "Failed to open RBD image", "Opened RBD image.");

      ret = image.stat(info, size);
      err_print(ret, "Failed to stat RBD image", "Stated RBD image.");

      std::cout << "Image has size " << info.size << " and order " << info.order << std::endl;
    }

    ioctx.close();
    std::cout << "IO context shut down." << std::endl;
}
