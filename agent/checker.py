from utils import PipeCmd
import re

def get_devices():
    lines = PipeCmd("mount", "grep ceph").strip().split('\n')
    for line in lines:
        fields = line.split()
        dev_prefix = re.compile('\/dev\/')
        osd_prefix = re.compile('\/var\/lib\/ceph\/osd\/ceph-')
        print dev_prefix.sub('', fields[0]),  \
              osd_prefix.sub('', fields[2])
    return lines 
