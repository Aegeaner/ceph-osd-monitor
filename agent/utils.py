from subprocess import Popen, PIPE

def Cmd(*args):
    process = Popen(args, stderr=PIPE,stdout=PIPE)
    stdout, stderr = process.communicate()
    if process.returncode == 0:
        return stdout
    else:
        return stderr


def PipeCmd(*args):
        prev = None
        for arg in args:
            if prev is None:
                prev = Popen(arg.split(), stdout=PIPE)
            else:
                cur = Popen(arg.split(), stdin=prev.stdout, stdout=PIPE)
                prev.stdout.close()
                prev = cur
	stdout, stderr = cur.communicate()
	if cur.returncode == 0:
	        return stdout
    	else:
        	return stderr

