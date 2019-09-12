#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/syscalls.h>
#include "sleepInfo.h"
    
asmlinkage long sys_listSleepInfo(const long __user *buf, int size) {
	struct task_struct *proces;
  	unsigned long kbuf[256];
  	int bufsz;
  	int ret;
	int index = 0;
  
  	/* Find the process */
  	for_each_process(proces) {
  		if( (long) proces->state != TASK_RUNNING){
			kbuf[index] = (long) task_pid_nr(process);
			index++;
  		}
  	}

	bufsz = (index-1) * sizeof(long);

	/* User buffer is too small */
	if(bufsz > size){
		return -1;
	}

	/* success */
	ret = copy_to_user((void*)buf, (void*)kbuf, bufsz);

	return bufsz - ret;
  
  }
