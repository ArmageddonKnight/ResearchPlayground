/**
 * https://linux.die.net/lkmpg/x769.html
 * https://stackoverflow.com/questions/29700466/create-proc-fs-dir-and-entry-under-a-already-existing-subdir-kernel-3-11-or-high
 * https://devarea.com/linux-kernel-development-creating-a-proc-file-and-interfacing-with-user-space/#.Y2EyotKZPbY
 */

#include <asm/uaccess.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/proc_fs.h>

#define C_NV_CAPTURE_NEXT_PMA_ALLOC_IND_PROC_BUFFER_MAX_SIZE 1024
#define C_NV_CAPTURE_NEXT_PMA_ALLOC_IND_PROC_FILENAME                          \
  "nv_capture_next_pma_alloc_ind"

static struct proc_dir_entry *NVCaptureNextPMAAllocIndFile;
static char NVCaptureNextPMAAllocIndKBuffer
    [C_NV_CAPTURE_NEXT_PMA_ALLOC_IND_PROC_BUFFER_MAX_SIZE];
static unsigned long NVCaptureNextPMAAllocIndKBufferSize = 0;

enum NVCaptureNextPMAAllocMode_t {
  kNVCaptureNextPMAAllocModeDefault = 0,
  kNVCaptureNextPMAAllocModeRecord = 1,
  kNVCaptureNextPMAAllocModeReplay = 2,
  kNVCaptureNextPMAAllocModeEnd = 3
};
static int NVCaptureNextPMAAllocMode = kNVCaptureNextPMAAllocModeDefault;

static ssize_t _nv_capture_next_pma_alloc_proc_file_read(struct file *file2read,
                                                         char __user *ubuf,
                                                         size_t count,
                                                         loff_t *offset) {
  int kbuf_len = 0;

  printk(KERN_INFO
         "Proc file read (/proc/" C_NV_CAPTURE_NEXT_PMA_ALLOC_IND_PROC_FILENAME
         ") called, with count=%ld and offset=%lld\n",
         count, *offset);
  // Since `count` is usually in the chunk of 128 KB, it is more than enough to
  // satisfy the requirements.
  if (*offset > 0 || count < NVCaptureNextPMAAllocIndKBufferSize) {
    return 0;
  }
  kbuf_len +=
      sprintf(NVCaptureNextPMAAllocIndKBuffer,
              "NVCaptureNextPMAAllocMode = %d\n", NVCaptureNextPMAAllocMode);
  if (copy_to_user(ubuf, NVCaptureNextPMAAllocIndKBuffer, kbuf_len)) {
    return -EFAULT;
  }
  *offset = kbuf_len;
  return kbuf_len;
}

static ssize_t
_nv_capture_next_pma_alloc_proc_file_write(struct file *file2write,
                                           const char __user *ubuf,
                                           size_t count, loff_t *offset) {
  printk(KERN_INFO
         "Proc file write (/proc/" C_NV_CAPTURE_NEXT_PMA_ALLOC_IND_PROC_FILENAME
         ") called, with count=%ld and offset=%lld\n",
         count, *offset);

  NVCaptureNextPMAAllocIndKBufferSize = count;
  if (*offset || count > C_NV_CAPTURE_NEXT_PMA_ALLOC_IND_PROC_BUFFER_MAX_SIZE) {
    return -EFAULT;
  }
  if (copy_from_user(NVCaptureNextPMAAllocIndKBuffer, ubuf, count)) {
    return -EFAULT;
  }

  if (sscanf(NVCaptureNextPMAAllocIndKBuffer, "%d",
             &NVCaptureNextPMAAllocMode) != 1) {
    return -EFAULT;
  }
  if (NVCaptureNextPMAAllocMode < kNVCaptureNextPMAAllocModeDefault ||
      NVCaptureNextPMAAllocMode >= kNVCaptureNextPMAAllocModeEnd) {
    return -EFAULT;
  }

  *offset = count;
  return count;
}

static struct proc_ops _nv_capture_next_pma_alloc_ind_proc_ops = {
    .proc_read = _nv_capture_next_pma_alloc_proc_file_read,
    .proc_write = _nv_capture_next_pma_alloc_proc_file_write};

int init_module() {
  NVCaptureNextPMAAllocIndFile =
      proc_create(C_NV_CAPTURE_NEXT_PMA_ALLOC_IND_PROC_FILENAME, 0666, NULL,
                  &_nv_capture_next_pma_alloc_ind_proc_ops);

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
