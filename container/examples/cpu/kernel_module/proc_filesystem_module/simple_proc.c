#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>   
#include <linux/proc_fs.h>
#include <linux/uaccess.h>
#define BUFSIZE 100

MODULE_LICENSE("GPL");


static struct proc_dir_entry *ent;
static int data;

static ssize_t myread(struct file *file, char __user *ubuf, size_t count, loff_t *ppos) {
  int len = 0;
  char buf[BUFSIZE];

  len = sprintf(buf, "%d", data);
  copy_to_user(ubuf,buf,len);
  return len;
}

static ssize_t mywrite(struct file *file, const char __user *ubuf, size_t count, loff_t *ppos) {
  int num, c;
  char buf[BUFSIZE]; 

  copy_from_user(buf, ubuf, count);
  sscanf(buf, "%d", &num);
  c = strlen(buf);
  data = num;
  return c;
}


static struct file_operations myops = {
  .owner = THIS_MODULE,
  .read = myread,
  .write = mywrite,
};

static int simple_init(void) {
  ent = proc_create("yourdev", 0660, NULL, &myops);  
  printk(KERN_INFO "proc_simple enter\n");
  return 0;
}

static void simple_cleanup(void) {
  proc_remove(ent);
  printk(KERN_INFO "proc_simple exit\n");
}

module_init(simple_init);
module_exit(simple_cleanup);
