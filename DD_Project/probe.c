
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/i2c.h>


#define	I2C_BUS_MAX	4


static const unsigned short probe_i2c_addrs[] = I2C_ADDRS(0x76, 0x77);

static struct i2c_board_info bmp085_i2c_info[] = {

	{ I2C_BOARD_INFO("bmp085", 0x77), }
};

static int __init bmp085_probe_init(void)
{
	int n;

	for(n =0; n < I2C_BUS_MAX; n++) {

		struct i2c_adapter * adap = i2c_get_adapter(n);
		if(adap) {
			i2c_new_probed_device(adap, bmp085_i2c_info, probe_i2c_addrs, NULL);
		}
	}
	return 0;
}

static void __exit bmp085_probe_exit(void)
{
	printk(KERN_ALERT "In EXIT Function");
}

module_init(bmp085_probe_init);
module_exit(bmp085_probe_exit);

MODULE_AUTHOR("Dilip reddy chandrashekar, anurag");
MODULE_DESCRIPTION("bmp085/18x init");
MODULE_LICENSE("GPL");
