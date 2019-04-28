.>>>>>>>>>>>>>>>>Block Device Driver<<<<<<<<<<<<<<<<
....................................................



step 1: Go to the directory and give the command $ make all

step 2: insert the module using sudo insmod main.ko

step 3: check whether module is loaded using lsmod command

step 4: for the partition information using cat /proc/partitions also check using ls -l /dev/mydisk* or sudo fdisk -l

step 5: we have created 2 logical Parititions of the Device (mydisk1 and mydisk2 each of 255.5KB and 256KB)

step 6: for root access using sudo -s command 

step 7: to write into disk use cat > /dev/mydisk ,type something & press enter
to read back from the disk on command line use command xxd /dev/mydisk | less


step 8: remove the module using sudo rmmod main.ko



