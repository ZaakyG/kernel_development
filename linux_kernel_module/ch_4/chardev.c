/*
 * chardev.c: Creates a read-only char device that says how many times
 * you've read from the dev file 
*/

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <asm/uacces.h> /* for put_user */

/*
 * Prototypes - this would normally go in an .h file
*/

init init_module(void);
void cleanup_module(void);
static int device_open(struct inode *, struct file *);
static int device_release(struct inode *, struct file *);
static ssize_t device_read(struct file *, char *, size)t, loff_t *);
static ssize_t devece_write(struct file *, const char *, size_t, loff_t *);

#define SUCCESS 0
#define DEVICE_NAME "chardev" // Dev name as it appears in /proc/devices
#define BUF_LEN 80 	      // Max length of the message from the device

/*
 * Global variables are declared as static, so are global within the file.
 */
static int Major; 
static int Device_Open = 0;

static char msg[BUF_LEN];
static char * msg_ptr;

statuc struct file_operations fops = {
	.read = device_read;
	.write = device_write;
	.open = device_open;
	.release = device_release
};

/*
 * This function is called when the module is loaded
 */
int init_module(void){
	Major = register_chrdev(0, DEVICE_NAME, &fops);
	if (Major < 0){
		print(KERN_ALER "Registering char device failed with %d\n", Major);
		return Major;
	}
	printk(KERN_INFO "I WAS ASSIGNED MAJOR NUMBER %d . Talk to \n", Major);
	printk(KERN_INFO "the driver, create a dev file with\n");
	printk(KERN_INFO "'mknod /dev/%s c %d 0' .\n", DEVICE_NAME, Major);
	printk(KERN_INFO "Try various minor numbers. Try to cat and echo to\n");
	printk(KERN_INFO "the device file.\n");
	printk(KERN_INFO "Remove the device file and module when done\n");

}
