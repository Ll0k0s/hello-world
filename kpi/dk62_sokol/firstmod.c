// Based on https://bit.ly/2kLBtD9 made by thodnev.
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/list.h>
#include <linux/slab.h>
#include <linux/kthread.h>
#include <asm/atomic.h>
#include <linux/jiffies.h>
#include <linux/timer.h>

#include <linux/interrupt.h>
#include <linux/workqueue.h>
#include <linux/semaphore.h>
#include <linux/delay.h>

MODULE_DESCRIPTION("Basic module demo: init, deinit, printk, jiffies");
MODULE_AUTHOR("Yaroslav Sokol");
MODULE_VERSION("0.3.1");
MODULE_LICENSE("Dual MIT/GPL");

struct struct_result {
	struct list_head list;
	long int n;
};

struct struct_flags {
	bool ena_timer;
	bool ena_work;
};

struct struct_result res_list1, res_list2, *ptr_res = NULL;
struct task_struct **t = NULL;
struct list_head *iter, *iter_safe;
struct struct_flags flags;
struct timer_list timer;

//list functions(list_print, list_delete,list_add_arg)
static void list_print(struct list_head *name_list)
{
	struct struct_result *temp;
	list_for_each_entry(temp, name_list, list) {
		printk(KERN_NOTICE "list_num = %li", temp->n);
	}
}
static void list_destroy(struct list_head *name_list)
{
	struct struct_result *cursor, *tmp;
	list_for_each_entry_safe(cursor, tmp, name_list, list) {
		list_del(&cursor->list);
		kfree(cursor);
	}
}
static void list_add_arg(bool num_struct, long int arg)
{
	ptr_res = kmalloc(sizeof(*ptr_res), GFP_KERNEL);
	ptr_res->n = arg;
	if(num_struct) {
		list_add(&ptr_res->list, &res_list2.list);
	} else {
		list_add(&ptr_res->list, &res_list1.list);		
	}
}
static void timer_func(struct timer_list *data)
{
	printk(KERN_INFO "$$$timer func$$$\n");
	while(flags.ena_timer == 1) {
		if(jiffies % 11 ==  0) {
			list_add_arg(0, jiffies);
			flags.ena_timer = 0;
			flags.ena_work = 0;
			kthread_stop(t[0]);
			kthread_stop(t[1]);
		} else {
			mod_timer(&timer, jiffies + 17);

		}
	}
}

static int thread_func_1(void *arg)
{
	while(flags.ena_timer) {
		//schedule();
	}
	return 0;
}

static int thread_func_2(void *arg)
{
	while(flags.ena_work) {
		schedule();
	}
	return 0;
}

static int __init mod_init(void)
{
	printk(KERN_INFO "$$$ Start $$$\n");

	INIT_LIST_HEAD(&res_list1.list);
	//INIT_LIST_HEAD(&res_list2.list);

	t = kmalloc(sizeof(*t), GFP_KERNEL);

	flags.ena_timer = 1;
	t[0] = kthread_run(&thread_func_1, NULL, "_thread[0]_");
	timer_setup(&timer, &timer_func, 0);
	mod_timer(&timer, jiffies + 1);

//	flags.ena_work = 1;
//	t[1] = kthread_run(&thread_func_2, NULL, "_thread[1]_");


	printk(KERN_INFO "$$$init finish$$$\n");
	return 0;
}


static void __exit mod_exit(void)
{
	if(flags.ena_timer) {
		flags.ena_timer = 0;
		kthread_stop(t[0]);
	}
/*	if(flags.ena_work) {
		flags.ena_work = 0;
		kthread_stop(t[1]);
	}
*/

	del_timer_sync(&timer);

	printk(KERN_INFO "List 1:\n");
	list_print(&res_list1.list);
	printk(KERN_INFO "List 2:\n");
	//list_print(&res_list2.list);

	list_destroy(&res_list1.list);
	//list_destroy(&res_list2.list);


	kfree(t);


	printk(KERN_INFO "$$$ Finish $$$\n");
}

module_init(mod_init);
module_exit(mod_exit);

