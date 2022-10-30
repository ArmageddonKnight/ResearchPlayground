/**
 * https://linux.die.net/lkmpg/x769.html
 */

#include <asm/uaccess.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/proc_fs.h>

#define C_PROC_BUFFER_MAX_SIZE 1024
#define C_PROC_FILENAME "buffer1k"

static struct proc_dir_entry *MyProcFile;
static char MyProcBuffer[C_PROC_BUFFER_MAX_SIZE];
static unsigned long MyProcBufferSize = 0;

static int _proc_file_read(char *buffer, char **buffer_location, off_t offset,
                           int buffer_length, int *eof, void *data) {
  int ret;

  printk(KERN_INFO "Proc file read (/proc/" C_PROC_FILENAME ") called\n");

  if (offset > 0) {
    ret = 0;
  } else {
    memcpy(buffer, MyProcBuffer, MyProcBufferSize);
    ret = MyProcBufferSize;
  }
  return ret;
}

static int _proc_file_write(struct file *file, const char *buffer,
                            unsigned long count, void *data) {
  MyProcBufferSize = count;
  if (MyProcBufferSize > C_PROC_BUFFER_MAX_SIZE) {
    MyProcBufferSize = C_PROC_BUFFER_MAX_SIZE;
  }

  if (copy_from_user(MyProcBuffer, buffer, C_PROC_BUFFER_MAX_SIZE)) {
    return -EFAULT;
  }

  return MyProcBufferSize;
}

int init_module() {
  MyProcFile = create_proc_entry(C_PROC_FILENAME, 0644, NULL);

  if (MyProcFile == NULL) {
    remove_proc_entry(C_PROC_FILENAME, &proc_root);
    printk(KERN_ALERT "Error: Could not initialize /proc/" C_PROC_FILENAME
                      "\n");
    return -ENOMEM;
  }

  MyProcFile->read_proc = _proc_file_read;
  MyProcFile->write_proc = _proc_file_write;
  MyProcFile->owner = THIS_MODULE;
  MyProcFile->mode = S_IFREG | S_IRUGO;
  MyProcFile->uid = 0;
  MyProcFile->gid = 0;
  MyProcFile->size = 37;

  printk(KERN_INFO "/proc/" C_PROC_FILENAME " created\n");
  return 0;
}

void cleanup_module() {
  remove_proc_entry(C_PROC_FILENAME, &proc_root);
  printk(KERN_INFO "/proc/" C_PROC_FILENAME " removed\n");
}
