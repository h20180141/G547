


#include <linux/module.h>
#include <linux/i2c.h>
#include <linux/err.h>
#define BMP085_NAME		"bmp085"
#include <linux/regmap.h>
#define BMP085_I2C_ADDRESS	0x77


 int bmp085_probe(struct device *dev, struct regmap *regmap, int irq);
 int bmp085_remove(struct device *dev);
 int bmp085_detect(struct device *dev);




struct regmap_config bmp085_regmap_config;

static const unsigned short normal_i2c[] = { BMP085_I2C_ADDRESS,
							I2C_CLIENT_END };

static int bmp085_i2c_detect(struct i2c_client *client,
			     struct i2c_board_info *info)
{
	if (client->addr != BMP085_I2C_ADDRESS)
		return -ENODEV;

	return bmp085_detect(&client->dev);
}

static int bmp085_i2c_probe(struct i2c_client *client,
				      const struct i2c_device_id *id)
{
	int err;
	struct regmap *regmap = devm_regmap_init_i2c(client,
						     &bmp085_regmap_config);

	if (IS_ERR(regmap)) {
		err = PTR_ERR(regmap);
		dev_err(&client->dev, "Failed to init regmap: %d\n", err);
		return err;
	}

	return bmp085_probe(&client->dev, regmap, client->irq);
}

static int bmp085_i2c_remove(struct i2c_client *client)
{
	return bmp085_remove(&client->dev);
}

static const struct i2c_device_id bmp085_id[] = {
	{ BMP085_NAME, 0 },
	{ "bmp180", 0 },
	{ }
};
MODULE_DEVICE_TABLE(i2c, bmp085_id);

static struct i2c_driver i2c_driver_fun = {
	.driver = {
		.name	= BMP085_NAME,
	},
	.id_table	= bmp085_id,
	.probe		= bmp085_i2c_probe,
	.remove		= bmp085_i2c_remove,

	.detect		= bmp085_i2c_detect,
	.address_list	= normal_i2c
};

module_i2c_driver(i2c_driver_fun);

MODULE_AUTHOR("Dilip Reddy, Kunreddy Chandrashekar reddy, Anurag");
MODULE_DESCRIPTION("BMP085 I2C bus driver");
MODULE_LICENSE("GPL");
