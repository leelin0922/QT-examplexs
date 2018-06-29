#ifndef _I2C_H_
#define _I2C_H_

#include <stdio.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

int i2c_set(int fd, unsigned int timeout, unsigned int retry);

int i2c_byte_write(int fd, unsigned char addr, unsigned char reg, unsigned char val);

int i2c_nbytes_write(int fd, unsigned char addr, unsigned char reg, unsigned char *val, int len);

int i2c_byte_read(int fd, unsigned char addr, unsigned char *val);

int i2c_nbytes_read(int fd, unsigned char addr, unsigned char reg, unsigned char *val, int len);

#endif
