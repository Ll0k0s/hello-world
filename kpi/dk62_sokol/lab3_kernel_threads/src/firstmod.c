#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/list.h>
#include <linux/slab.h>
#include <linux/kthread.h>
#include <asm/atomic.h>

MODULE_DESCRIPTION("Basic module demo: init, deinit, printk, jiffies");
MODULE_AUTHOR("Yaroslav Sokol");
MODULE_VERSION("0.1.2");
MODULE_LICENSE("Dual MIT/GPL");		// this affects the kernel behavior

static int N = 10;
static int M = 1000;


struct struct_result {
	struct list_head my_list;
	int n;
};

struct struct_result my_res, *ptr_res;

static int thread_func(int num)
{

	int i;
	for(i = 0; i < num; i++){
		printk(KERN_INFO "\t\ti = %i\n", i);
		
	}
	

	return 0;

//	printk(KERN_INFO "\t\t\tarray = %i\n", my_list[num].array);	

}




static int __init mod_init(void)
{
	printk(KERN_INFO "$$$ Hello $$$\n");

	struct task_struct *my_task_struct;
	INIT_LIST_HEAD(&my_res.my_list);

	list_add(&ptr_res->my_list, &my_res.my_list);

	thread_func(50);
	int i;
	for(i = 0; i < N; i++) {
		i++;
	}

	if(!kmalloc(sizeof(*ptr_res), GFP_KERNEL)) {
		goto Mem_Error;
	} else {
		goto Mem_nice;		
	}
	//return 0;

	
Mem_nice:
	printk(KERN_INFO "memory nice\n");
	return 0;
Mem_Error:
	printk(KERN_INFO "memory bad\n");
	return 0;



}
 
static void __exit mod_exit(void)
{
	printk(KERN_INFO "Long live the Kernel!\n");
}

 
module_init(mod_init);
module_exit(mod_exit);

