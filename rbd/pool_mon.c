#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <rados/librados.h>

char *APPNAME;

void error_print(int err, char *error, char* normal)
{
    if(err < 0) {
        fprintf(stderr, "[%s][WARN]: %s\n", APPNAME, strerror(-err));
        exit(EXIT_FAILURE);
    } else {
        printf("[%s]: %s\n", APPNAME, normal);
    }
}

void split_str(char *buf, int len)
{
    int i;
   
    for(i=0; i<len; i++)
    {
        if(i>1 && buf[i-1]=='\0' && buf[i-2]=='\0')
            buf[i] = -1;
    }
    
    for(i=0; i<len && buf[i]!=-1; i++)
    {
        if(buf[i] == '\0')
            buf[i] = ',';
    }
    buf[i-2] = '\0';
}

int main(int argc, char **argv)
{
    rados_t cluster;
    char cluster_name[] = "ceph";
    char user_name[] = "client.admin";
    APPNAME = &argv[0][2];
    uint64_t flags;
   
    int err;

    /* Initialize the cluster handle */
    //err = rados_create2(&cluster, cluster_name, user_name, flags);
    err - rados_create(&cluster, NULL);
    error_print(err, "Couldn't create the cluster handle!", "Created a cluster handle.");
    
    /* Read a Ceph configuration file to configure the cluster handle. */
    err = rados_conf_read_file(cluster, "/etc/ceph/ceph.conf");
    error_print(err, "Cannot read config file!", "Read the config file.");

    /* Connect to the cluster */
    err = rados_connect(cluster);
    error_print(err, "Cannot connect to cluster!", "Connected to the cluster.");

    /* List pools. */
    char buf[1024];
    err = rados_pool_list(cluster, buf, 1024);
    split_str(buf, 1024);
    error_print(err, "Cannot list pools!", buf);

/*    {
        printf("%s\n", poolname);
        poolname = strtok(NULL, "\0\n\t");
    }
*/
}
