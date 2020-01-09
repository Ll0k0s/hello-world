#include <linux/build-salt.h>
#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x9cbc70c9, "module_layout" },
	{ 0x8d41732f, "param_ops_charp" },
	{ 0xab9e5ae3, "param_ops_int" },
	{ 0x15ba50a6, "jiffies" },
	{ 0x12677859, "device_create" },
	{ 0xb1ce3d68, "__class_create" },
	{ 0x426e9832, "cdev_add" },
	{ 0x20c3ef79, "cdev_init" },
	{ 0x3fd78f3b, "register_chrdev_region" },
	{ 0xe3ec2f2b, "alloc_chrdev_region" },
	{ 0xa5526619, "rb_insert_color" },
	{ 0x6202efec, "kmem_cache_alloc_trace" },
	{ 0xd1e83caf, "kmalloc_caches" },
	{ 0xb44ad4b3, "_copy_to_user" },
	{ 0x362ef408, "_copy_from_user" },
	{ 0x88db9f48, "__check_object_size" },
	{ 0xd2b09ce5, "__kmalloc" },
	{ 0x7c32d0f0, "printk" },
	{ 0x449ad0a7, "memcmp" },
	{ 0xca9360b5, "rb_next" },
	{ 0x37a0cba, "kfree" },
	{ 0x4d9b652b, "rb_erase" },
	{ 0xdf2c2742, "rb_last" },
	{ 0xece784c2, "rb_first" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0x11270350, "cdev_del" },
	{ 0x74533ae0, "class_destroy" },
	{ 0x6fbf480b, "class_unregister" },
	{ 0x25de6d8d, "device_destroy" },
	{ 0xbdfb6dbb, "__fentry__" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "B6B491974AF8BA2BF15DF4E");
