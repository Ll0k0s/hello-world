#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/kthread.h>
#include <linux/list.h>
#include <linux/slab.h>
#include <linux/timer.h>
#include <linux/workqueue.h>

struct result {
	struct list_head list;
	long int num;
	int count;
	bool work_run;
};

struct result res_list;
struct result *work_ptr = NULL;
struct task_struct **ptr_t = NULL;
struct delayed_work work;

static void list_print(struct list_head *name_list)
{
	struct result *temp;
	list_for_each_entry(temp, name_list, list) {
		printk(KERN_NOTICE "list_arg = %li", temp->num);
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
	if(res == NULL) {
		return;
	}
	res->num = arg;
	list_add(&res->list, list_name);		
}

void work_func(struct work_struct *data)
{
	res_list.count++;
	if (res_list.count > 20) {
		printk(KERN_INFO "Timer stopiing: %li", jiffies);
		res_list.work_run = 0;
	} else {
		list_add_arg(work_ptr, &res_list.list, jiffies);
		schedule_delayed_work(&work, 1);
	}
}

static int __init mod_init(void) 
{
	printk(KERN_INFO "$$$ Start $$$\n");

	INIT_LIST_HEAD(&res_list.list);
	res_list.work_run = 1;
	INIT_DELAYED_WORK(&work, work_func);
	schedule_delayed_work(&work, 1);

	return 0;		
}

static void __exit mod_exit(void) 
{ 
	printk(KERN_INFO "Work list:\n");
	list_print(&res_list.list);

	if (res_list.work_run) {
		res_list.work_run = 0;
		while (flush_delayed_work(&work));
	}

	list_destroy(&res_list.list);

	printk(KERN_INFO "$$$ Finish $$$\n");
}

module_init(mod_init);
module_exit(mod_exit);

