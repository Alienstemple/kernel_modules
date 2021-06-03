#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/cdev.h>

static char *kbuf;
static dev_t first;
static unsigned int count = 1;
static int my_major = 700, my_minor = 0;
static struct cdev *my_cdev;

#define MY_DEV_NAME "simplecdev"
#define KBUF_SIZE size_t ((10) * PAGE_SIZE)   // slab.h

static int __init init_chrdev(void)
{
 printk( KERN_INFO "Hello from simple char driver! ");
 kbuf = kmalloc(KBUF_SIZE,GFP_KERNEL);

 first = MKDEV (my_major,my_minor); // create node in devfs
 register_chrdev_region(first,count,MYDEV_NAME);   
// region - set of id's for our module

 my_cdev = cdev_alloc();

 cdev_init(my_cdev, &my_cdev_fops);
 cdev_add(my_cdev,first,count); 

 return 0;
}

static int mychrdev_open(struct inode *inode, struct file *file)
{
 printk( KERN_INFO "Opening device %s \n\n", MYDEV_NAME);
 return 0;
}

static int mychrdev_release(struct inode *inode, struct file *file)
{
 printk( KERN_INFO "Leaving \n", MYDEV_NAME);
 return 0;
}

static ssize_t mychrdev_read(struct file *file, char __user *buf, size_t lbuf, loff_t *ppos)  
// __user - mark as from userspace
{
 printk( KERN_INFO "Reading device %s \n\n", MYDEV_NAME);
 return 0;
}

static ssize_t mychrdev_write(struct file *file, const char __user *buf, ssize_t lbuf, loff_t ppos)
{
 printk( KERN_INFO "Writing device %s \n\n", MYDEV_NAME);
 return 0;
}

static void __exit cleanup_chrdev(void)
{
 printk( KERN_INFO "Bye!" );
}

module_init (init_chrdev);
module_exit (cleanup_chrdev);

MODULE_LICENSE("GPL");
