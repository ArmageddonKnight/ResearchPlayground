/**
 * https://linux.die.net/lkmpg/x769.html
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/proc_fs.h>

#define C_PROC_BUFFER_MAX_SIZE 1024
#define C_PROC_FILENAME "buffer1k"

static struct proc_dir_entry *MyProcFile;
static char MyProcBuffer[C_PROC_BUFFER_MAX_SIZE];
static unsigned long MyProcBufferSize = 0;

static ssize_t _proc_file_read(struct file *file2read, char *buffer,
                               size_t count, loff_t *offset) {
  int ret;

  printk(KERN_INFO "Proc file write (/proc/" C_PROC_FILENAME ") called\n");

  if (*offset > 0) {
    ret = 0;
  } else {
    memcpy(buffer, MyProcBuffer, MyProcBufferSize);
    ret = MyProcBufferSize;
  }
  return ret;
}

static ssize_t _proc_file_write(struct file *file2write, const char *buffer,
                                size_t count, loff_t *offset) {
  printk(KERN_INFO "Proc file write (/proc/" C_PROC_FILENAME ") called\n");

  MyProcBufferSize = count;
  if (MyProcBufferSize > C_PROC_BUFFER_MAX_SIZE) {
    MyProcBufferSize = C_PROC_BUFFER_MAX_SIZE;
  }
  if (copy_from_user(MyProcBuffer, buffer, C_PROC_BUFFER_MAX_SIZE)) {
    return -EFAULT;
  }

  printk(KERN_INFO "Received msg=%s of len=%ld from the user space\n",
         MyProcBuffer, MyProcBufferSize);

  return MyProcBufferSize;
}

int init_module() {

  struct proc_ops my_proc_ops;
  my_proc_ops.proc_read = _proc_file_read;
  my_proc_ops.proc_write = _proc_file_write;

  MyProcFile = proc_create(/*name=*/C_PROC_FILENAME, /*mode=*/0,
                           /*parent=*/NULL, /*proc_ops=*/&my_proc_ops);

  if (MyProcFile == NULL) {
    proc_remove(MyProcFile);
    printk(KERN_ALERT "Error: Could not initialize /proc/" C_PROC_FILENAME
                      "\n");
    return -ENOMEM;
  }

  proc_set_size(MyProcFile, 37);

  printk(KERN_INFO "/proc/" C_PROC_FILENAME " created\n");
  return 0;
}

void cleanup_module() {
  proc_remove(MyProcFile);
  printk(KERN_INFO "/proc/" C_PROC_FILENAME " removed\n");
}

MODULE_LICENSE("GPL");
