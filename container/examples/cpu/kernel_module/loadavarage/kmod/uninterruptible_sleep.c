#include <linux/module.h>
#include <linux/init.h>
#include <linux/uaccess.h>
#include <linux/proc_fs.h>
#include <linux/kernel.h>
#include <linux/delay.h>
#define BUFSIZE 100



MODULE_LICENSE("GPL");

static struct proc_dir_entry *ent;
static char data[BUFSIZE];


static ssize_t myread(struct file *file, char __user *ubuf, size_t count, loff_t *ppos) {
    printk(KERN_INFO "mydev read start\n");
    msleep(100000);
    printk(KERN_INFO "mydev read exit\n");
    return 0;
}

static ssize_t mywrite(struct file *file, const char __user *ubuf, size_t count, loff_t *ppos) {
    int len;
    char buf[BUFSIZE];

    printk(KERN_INFO "mydev write\n"); 
    copy_from_user(buf, ubuf, count);
    len = sscanf(buf, "%s", data);
    return len;
}


static struct file_operations myops = {
    .owner = THIS_MODULE,
    .read = myread,
    .write = mywrite,
};

static int simple_init(void) {
  ent = proc_create("mydev", 0660, NULL, &myops); 
  return 0;
}

static void simple_cleanup(void) {
  proc_remove(ent); 
}


module_init(simple_init);
module_exit(simple_cleanup);
