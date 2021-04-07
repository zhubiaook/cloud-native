#include <linux/init.h>
#include <linux/module.h>

MODULE_AUTHOR("zhubiao");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("a simple hello world");
MODULE_ALIAS("simple module");

static int hello_init(void) {
	printk(KERN_INFO "hello world enter\n");
	return 0;
}


static void hello_exit(void) {
	printk(KERN_INFO "hello world exit\n");
}

module_init(hello_init);
module_exit(hello_exit);
