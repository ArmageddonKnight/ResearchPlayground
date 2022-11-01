/**
 * https://linux.die.net/lkmpg/x769.html
 * https://stackoverflow.com/questions/29700466/create-proc-fs-dir-and-entry-under-a-already-existing-subdir-kernel-3-11-or-high
 */

#include <asm/uaccess.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/proc_fs.h>

#define C_NV_CAPTURE_NEXT_PMA_ALLOC_IND_PROC_BUFFER_MAX_SIZE 1024
#define C_NV_CAPTURE_NEXT_PMA_ALLOC_IND_PROC_FILENAME                          \
  "nv_capture_next_pma_alloc_ind"

static struct proc_dir_entry *NVCaptureNextPMAAllocIndFile;
static char NVCaptureNextPMAAllocIndKBuffer[C_PROC_BUFFER_MAX_SIZE];
static unsigned long NVCaptureNextPMAAllocIndKBufferSize = 0;

enum NVCaptureNextPMAAllocMode_t {
  kDefault = 0,
  kRecord = 1,
  kReplay = 2
} NVCaptureNextPMAAllocMode;

static ssize_t _nv_capture_next_pma_alloc_proc_file_read(struct file *file2read,
                                                         char *buffer,
                                                         size_t count,
                                                         loff_t *offset) {
  printk(KERN_INFO "Proc file read (/proc/" C_PROC_FILENAME ") called\n");

  // if (count > MyProcBufferSize) {
  //   count = MyProcBufferSize;
  // }
  // if (count == 0) {
  //   return 0;
  // }
  // if (copy_to_user(buffer, MyProcBuffer, count)) {
  //   return -EFAULT;
  // }

  // printk(KERN_INFO "Obtained msg=%s of len=%ld from the kernel space\n",
  // buffer,
  //        count);

  // return count;
  // return 0;

  if (count > MyProcBufferTemp) {
    count = MyProcBufferTemp;
  }
  if (copy_to_user(buffer, MyProcBuffer, count)) {
    return -EFAULT;
  }
  if (count == 0) {
    MyProcBufferTemp = MyProcBufferSize;
  }

  return count;
}

static ssize_t _nv_capture_next_pma_alloc_proc_file_write(
    struct file *file2write, const char *ubuf, size_t count, loff_t *offset) {
  printk(KERN_INFO
         "Proc file write (/proc/" C_NV_CAPTURE_NEXT_PMA_ALLOC_IND_PROC_FILENAME
         ") called\n");

  NVCaptureNextPMAAllocIndKBufferSize = count;
  if (*offset || count > C_NV_CAPTURE_NEXT_PMA_ALLOC_IND_PROC_BUFFER_MAX_SIZE) {
    return -EFAULT
  }
  if (copy_from_user(NVCaptureNextPMAAllocIndKBuffer, ubuf, count)) {
    return -EFAULT;
  }

  if (sscanf(NVCaptureNextPMAAllocIndKBuffer, "%d",
             NVCaptureNextPMAAllocMode) != 1) {
    return -EFAULT;
  }

  *offset = count;
  return count;
}

static struct proc_ops nv_capture_next_pma_alloc_ind_proc_ops {
  .proc_read = _nv_capture_next_pma_alloc_proc_file_read,
  .proc_write = _nv_capture_next_pma_alloc_proc_file_write
};

int init_module() {
  NVCaptureNextPMAAllocIndFile =
      proc_create(C_NV_CAPTURE_NEXT_PMA_ALLOC_IND_PROC_FILENAME, 0666, NULL,
                  nv_capture_next_pma_alloc_ind_proc_ops);

  if (NVCaptureNextPMAAllocIndFile == NULL) {
    proc_remove(NVCaptureNextPMAAllocIndFile);
    printk(KERN_ALERT "Error: Could not initialize "
                      "/proc/" C_NV_CAPTURE_NEXT_PMA_ALLOC_IND_PROC_FILENAME
                      "\n");
    return -ENOMEM;
  }
  printk(KERN_INFO "/proc/" C_NV_CAPTURE_NEXT_PMA_ALLOC_IND_PROC_FILENAME
                   " created\n");
  return 0;
}

void cleanup_module() {
  proc_remove(NVCaptureNextPMAAllocIndFile);
  printk(KERN_INFO "/proc/" C_NV_CAPTURE_NEXT_PMA_ALLOC_IND_PROC_FILENAME
                   " removed\n");
}

MODULE_LICENSE("GPL");

/*
#include <asm/uaccess.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/proc_fs.h>
#define BUFSIZE 100

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Liran B.H");

static struct proc_dir_entry *ent;

static int irq = 20;
module_param(irq, int, 0660);

static int mode = 1;
module_param(mode, int, 0660);

static char buf[BUFSIZE];

static ssize_t mywrite(struct file *file, const char __user *ubuf, size_t count,
                       loff_t *ppos) {
  int num, c, i, m;
  if (*ppos > 0 || count > BUFSIZE)
    return -EFAULT;
  if (copy_from_user(buf, ubuf, count))
    return -EFAULT;
  num = sscanf(buf, "%d %d", &i, &m);
  if (num != 2)
    return -EFAULT;
  irq = i;
  mode = m;
  c = strlen(buf);
  *ppos = c;
  return c;
}

static ssize_t myread(struct file *file, char __user *ubuf, size_t count,
                      loff_t *ppos) {
  int len = 0;
  printk(KERN_DEBUG "read handler\n");
  if (*ppos > 0 || count < BUFSIZE)
    return 0;
  len += sprintf(buf, "irq = %d\n", irq);
  len += sprintf(buf + len, "mode = %d\n", mode);

  if (copy_to_user(ubuf, buf, len))
    return -EFAULT;
  *ppos = len;
  return len;
}

static struct proc_ops myops = {
    .proc_read = myread,
    .proc_write = mywrite,
};

static int simple_init(void) {
  ent = proc_create("mydev", 0660, NULL, &myops);
  return 0;
}

static void simple_cleanup(void) { proc_remove(ent); }

module_init(simple_init);
module_exit(simple_cleanup);
 */