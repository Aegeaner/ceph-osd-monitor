#include <rados/librados.h>
#include <rados/librados.hpp>
#include <rbd/librbd.hpp>

#include <string>

#ifndef CEPH_RADOS_API_HELPER_H
#define CEPH_RADOS_API_HELPER_H

std::string connect_cluster_pp(librados::Rados &cluster);
std::string create_one_pool_pp(const std::string &pool_name, librados::Rados &cluster);
int create_image_pp(librbd::RBD &rbd, librados::IoCtx &ioctx, const char *name, uint64_t size, int *order);

#endif
