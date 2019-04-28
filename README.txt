
*Build
------
$ make 
$ sudo make install 
$ sudo depmod -a



*Config
-------
$ sudo nano /etc/modprobe.d/raspi-blacklist.conf
Uncoment the following lines
#blacklist i2c-bcm2708


 
$ sudo nano /etc/modules 
Add lines as follow
bmp085
bmp085-i2c
bmp085-probe

*Test:
-------
$ sudo modprobe bmp085 bmp085-i2c bmp085-probe 

$ cat /sys/bus/i2c/drivers/bmp085/1-0077/temp0_input
$ cat /sys/bus/i2c/drivers/bmp085/1-0077/pressure0_input
