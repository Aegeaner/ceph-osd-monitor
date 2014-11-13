#include <rados/librados.h>
#include <rados/librados.hpp>

#include <string>
#include <unistd.h>

#ifndef CEPH_RADOS_API_HELPER_H
#define CEPH_RADOS_API_HELPER_H

std::string connect_cluster_pp(librados::Rados &cluster);

#endif
