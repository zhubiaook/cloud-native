#include <linux/init.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");

static int irq = 10;
module_param(irq, int, 0660);

static int debug = 0;
module_param(debug, int, 0660);

static char *name = "mydev";
module_param(name, charp, 0660);

static int simple_init(void) {
  printk(KERN_INFO "hello enter: irq=%d, debug=%d, name=%s\n", irq, debug, name);
  return 0;
}

static void simple_cleanup(void) {
  printk(KERN_INFO "hello exit: irq=%d, debug=%d, name=%s\n", irq, debug, name);
}

module_init(simple_init);
module_exit(simple_cleanup);
