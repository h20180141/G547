#include<linux/init.h>
#include<linux/module.h>
#include<linux/version.h>
#include<linux/kernel.h>
#include<linux/types.h>
#include<linux/kdev_t.h>
#include<linux/cdev.h>
#include<linux/fs.h>
#include<linux/device.h>
#include <linux/types.h>
#include <linux/random.h>
#include <linux/uaccess.h>


static dev_t aclr;   // variable for device number

static struct cdev *x_dev;
static struct cdev *y_dev;
static struct cdev *z_dev;

static struct class *cls;

dev_t x,y,z;

uint16_t val;

// permissions
static int permission(struct device* dev,struct kobj_uevent_env* env)
{
  add_uevent_var(env,"DEVMODE=%#o",0777);
  return 0;
}



// Random Value generator for imitating Harware

uint16_t getrand(void)
{
	uint16_t retval;
	get_random_bytes(&retval, 2);
	return retval;
}


// STEP 4 : Driver Call back functions 

static int x_open(struct inode *i,struct file *f)
{
	printk(KERN_INFO "x:open()\n");
	return 0;
}
static int x_close(struct inode *i,struct file *f)
{
	printk(KERN_INFO "x:close()\n");
	return 0;
}
static ssize_t x_read(struct file *f,char __user *buf,size_t len,loff_t *off)
{
	printk(KERN_INFO "x:read()\n");
	val=getrand()&0x3ff;
	printk(KERN_INFO "%d\n",val);
	copy_to_user(buf, &val, 2);
	return 0;
}
static int y_open(struct inode *i,struct file *f)
{
	printk(KERN_INFO "y:open()\n");
	return 0;
}
static int y_close(struct inode *i,struct file *f)
{
	printk(KERN_INFO "y:close()\n");
	return 0;
}
static ssize_t y_read(struct file *f,char __user *buf,size_t len,loff_t *off)
{
	printk(KERN_INFO "y:read()\n");
	val=getrand()&0x3ff;
	printk(KERN_INFO "%d\n",val);
	copy_to_user(buf, &val, 2);
	return 0;
}
static int z_open(struct inode *i,struct file *f)
{
	printk(KERN_INFO "z:open()\n");
	return 0;
}
static int z_close(struct inode *i,struct file *f)
{
	printk(KERN_INFO "z:close()\n");
	return 0;
}
static ssize_t z_read(struct file *f,char __user *buf,size_t len,loff_t *off)
{
	printk(KERN_INFO "z:read()\n");
	val=getrand()&0x3ff;
	printk(KERN_INFO "%d\n",val);
	copy_to_user(buf, &val, 2);
	return 0;
}

// File operations to be performed on files 

static struct file_operations x_ops =
{
	.owner=THIS_MODULE,
	.open=x_open,
	.release=x_close,
	.read=x_read,
};
static struct file_operations y_ops =
{
	.owner=THIS_MODULE,
	.open=y_open,
	.release=y_close,
	.read=y_read,
};
static struct file_operations z_ops =
{
	.owner=THIS_MODULE,
	.open=z_open,
	.release=z_close,
	.read=z_read,
};


static __init int demo_init(void)
{
	
	
	printk(KERN_INFO "My character driver for Accelerometer registered\n\n");
	
	// STEP 1 : Reserving major and minor numbers

	if((alloc_chrdev_region(&aclr,0,3,"accelerometer"))<0) 
		{
			return -1;
		}

	// Allocating the major and minor numbers
	
	x=MKDEV(MAJOR(aclr), MINOR(aclr)+0);
	y=MKDEV(MAJOR(aclr), MINOR(aclr)+1);
	z=MKDEV(MAJOR(aclr), MINOR(aclr)+2);

	// STEP 2 : Creation of device file

	if((cls=class_create(THIS_MODULE,"accelerometer"))==NULL)
		{
			unregister_chrdev_region(aclr,3);
			return -1;
		}
	cls->dev_uevent = permission;

	// STEP 3 : Link fops and cdev to the device node

		
	x_dev = cdev_alloc(); // struct cdev is allocated dynamically and its pointer address stored in x_dev
					
	cdev_init(x_dev,&x_ops); // initialises the struct cdev with the defined file operations 

	device_create(cls,NULL,x,NULL,"x_axis"); // file 'x_axis' is ceated in /dev directory

	if(cdev_add(x_dev,x,1)<0)  // cdev_add() : it adds the charatcer device to the system, after successfull addition it returns 0 
		{
			class_destroy(cls);
			unregister_chrdev_region(aclr, 3);
			return -1;
		}

	
	y_dev = cdev_alloc();
	cdev_init(y_dev,&y_ops);
	device_create(cls,NULL,y,NULL,"y_axis");

	if(cdev_add(y_dev,y,1)<0)
		{
			cdev_del(x_dev);
			device_destroy(cls, y);
			device_destroy(cls, x);
			class_destroy(cls);
			unregister_chrdev_region(aclr, 3);
			return -1;
		}

	
	z_dev = cdev_alloc();
	cdev_init(z_dev,&z_ops);
	device_create(cls,NULL,z,NULL,"z_axis");

	if(cdev_add(z_dev,z,1)<0)
		{
			cdev_del(y_dev);
			cdev_del(x_dev);
			device_destroy(cls, z);
			device_destroy(cls, y);
			device_destroy(cls, x);
			class_destroy(cls);
			unregister_chrdev_region(aclr, 3);
			return -1;
		}
	
}
static __exit void demo_exit(void)
{
	//printk(KERN_ALERT "BYE WORLD\n");
	cdev_del(x_dev);
	cdev_del(y_dev);
	cdev_del(z_dev);
	device_destroy(cls,x);
	device_destroy(cls,y);
	device_destroy(cls,z);
	class_destroy(cls);
	unregister_chrdev_region(aclr,3);
	printk(KERN_INFO "Accelerometer unregistered\n\n");
}

module_init(demo_init);
module_exit(demo_exit);

MODULE_DESCRIPTION("Assignment 1");
MODULE_AUTHOR("K Chandrashekar Reddy");
MODULE_LICENSE("GPL");
