/**
 * https://linux.die.net/lkmpg/x769.html
 * https://stackoverflow.com/questions/29700466/create-proc-fs-dir-and-entry-under-a-already-existing-subdir-kernel-3-11-or-high
 */

#include <asm/uaccess.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/proc_fs.h>

#define C_PROC_BUFFER_MAX_SIZE 1024
#define C_PROC_FILENAME "buffer1k"

static struct proc_dir_entry *MyProcFile;
static char *MyProcBuffer = NULL;
static unsigned long MyProcBufferSize = 0, MyProcBufferTemp = 0;

static ssize_t _proc_file_read(struct file *file2read, char *buffer,
                               size_t count, loff_t *offset) {
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
  MyProcBufferTemp = MyProcBufferTemp - count;
  if (copy_to_user(buffer, MyProcBuffer, count)) {
    return -EFAULT;
  }
  if (count == 0) {
    MyProcBufferTemp = MyProcBufferSize;
  }

  return count;
}

static ssize_t _proc_file_write(struct file *file2write, const char *buffer,
                                size_t count, loff_t *offset) {
  printk(KERN_INFO "Proc file write (/proc/" C_PROC_FILENAME ") called\n");

  // MyProcBufferSize = count;
  // if (MyProcBufferSize > C_PROC_BUFFER_MAX_SIZE) {
  //   MyProcBufferSize = C_PROC_BUFFER_MAX_SIZE;
  // }
  // if (copy_from_user(MyProcBuffer, buffer, C_PROC_BUFFER_MAX_SIZE)) {
  //   return -EFAULT;
  // }

  // printk(KERN_INFO "Received msg=%s of len=%ld from the user space\n",
  //        MyProcBuffer, MyProcBufferSize);

  // return MyProcBufferSize;
  // return 0;
  // MyProcBufferSize = count;
  // if (MyProcBufferSize > C_PROC_BUFFER_MAX_SIZE) {
  //   MyProcBufferSize = C_PROC_BUFFER_MAX_SIZE;
  // }
  MyProcBufferSize = count;
  if (MyProcBufferSize > C_PROC_BUFFER_MAX_SIZE) {
    MyProcBufferSize = C_PROC_BUFFER_MAX_SIZE;
  }
  MyProcBufferTemp = MyProcBufferSize;

  if (copy_from_user(MyProcBuffer, buffer, count)) {
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

  MyProcFile = proc_create(/*name=*/C_PROC_FILENAME, /*mode=*/0644,
                           /*parent=*/NULL, /*proc_ops=*/&my_proc_ops);

  if (MyProcFile == NULL) {
    remove_proc_entry(C_PROC_FILENAME, NULL);
    printk(KERN_ALERT "Error: Could not initialize /proc/" C_PROC_FILENAME
                      "\n");
    return -ENOMEM;
  }
  printk(KERN_INFO "/proc/" C_PROC_FILENAME " created\n");
  MyProcBuffer = kmalloc(1024 * sizeof(char), GFP_KERNEL);
  return 0;
}

void cleanup_module() {
  remove_proc_entry(C_PROC_FILENAME, NULL);
  kfree(MyProcBuffer);
  printk(KERN_INFO "/proc/" C_PROC_FILENAME " removed\n");
}

MODULE_LICENSE("GPL");
