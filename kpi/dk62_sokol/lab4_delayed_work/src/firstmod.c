#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/kthread.h>
#include <linux/list.h>
#include <linux/slab.h>
#include <linux/timer.h>
#include <linux/workqueue.h>

MODULE_DESCRIPTION("Basic module demo: init, deinit, printk, jiffies");
MODULE_AUTHOR("Yaroslav Sokol");
MODULE_VERSION("0.3.1");
MODULE_LICENSE("Dual MIT/GPL");

struct result {
	struct list_head list;
	long int num;
};

struct st_flags {
	bool timer_run;
	bool work_run;
};

struct result res_list1, res_list2;
struct result *work_func_st_p = NULL;
struct result *timer_func_st_p = NULL;
struct st_flags flags;
struct task_struct **ptr_t = NULL;
struct delayed_work work;
struct timer_list timer;

static void list_print(struct list_head *name_list)
{
	struct result *temp;
	list_for_each_entry(temp, name_list, list) {
		printk(KERN_NOTICE "list_arg = %li (%li)", temp->num, temp->num % 11);
	}
}

static void list_destroy(struct list_head *name_list)
{
	struct result *cursor, *tmp;
	list_for_each_entry_safe(cursor, tmp, name_list, list) {
		list_del(&cursor->list);
		kfree(cursor);
	}
}

static void list_add_arg(struct result *res, struct list_head *list_name, long int arg)
{
	res = kmalloc(sizeof(*res), GFP_ATOMIC);
	res->num = arg;
	list_add(&res->list, list_name);		
}

void work_func(struct work_struct *data)
{
	if ((jiffies % 11) == 0) {
		printk(KERN_INFO "Timer stopiing: %li (%li)\n", jiffies, jiffies % 11);
		flags.work_run = 0;		
	} else {
		list_add_arg(work_func_st_p, &res_list1.list, jiffies);
		schedule_delayed_work(&work, 17);
	}
}

void timer_func(struct timer_list *data)
{
	if ((jiffies % 11) == 0) {
		printk(KERN_INFO "Work stopping:  %li (%li)\n", jiffies, jiffies % 11);
		flags.timer_run = 0;
	} else {
		list_add_arg(timer_func_st_p, &res_list2.list, jiffies);
		mod_timer(&timer, jiffies + 17);
	}
}

int first_th_func(void *data)
{	
	while (flags.timer_run) {
		schedule();
	}
	return 0;
}

int second_th_func(void *data)
{
	while (flags.work_run) {
		schedule();
	}
	return 0;
}

static int __init mod_init(void) 
{
	printk(KERN_INFO "$$$ Start $$$\n");

	INIT_LIST_HEAD(&res_list1.list);
	INIT_LIST_HEAD(&res_list2.list);

	ptr_t = kmalloc(sizeof(*ptr_t) * 2, GFP_KERNEL);	

	flags.work_run = 1;
	ptr_t[1] = kthread_run(&second_th_func, NULL, "thread_1");
	INIT_DELAYED_WORK(&work, work_func);
	schedule_delayed_work(&work, 17);

	flags.timer_run = 1;
	ptr_t[0] = kthread_run(&first_th_func, NULL, "thread_0");
	timer_setup(&timer, &timer_func, 0);
	mod_timer(&timer, jiffies + 1);

	return 0;		
}

static void __exit mod_exit(void) 
{ 
	printk(KERN_INFO "Timer list:\n");
	list_print(&res_list1.list);

	printk(KERN_INFO "Work list:\n");
	list_print(&res_list2.list);

	if (flags.work_run) {
		flags.work_run = 0;
		while (flush_delayed_work(&work));
	}

	if (flags.timer_run) {
		flags.timer_run = 0;
		del_timer_sync(&timer);
	}


	kfree(ptr_t);
	list_destroy(&res_list1.list);
	list_destroy(&res_list2.list);

	printk(KERN_INFO "$$$ Finish $$$\n");
}

module_init(mod_init);
module_exit(mod_exit);

