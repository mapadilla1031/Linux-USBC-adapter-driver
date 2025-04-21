#include <linux/init.h>
#include <linux/module.h>
#include <linux/usb.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Marko Padilla");
MODULE_DESCRIPTION("Basic USB-C to HDMI Linux Driver");

//  actual USB-C to HDMI adapter's IDs (use lsusb)
#define USB_VENDOR_ID    0x1234
#define USB_PRODUCT_ID   0x5678

// Supported device table
static struct usb_device_id usbc_hdmi_table[] = {
    { USB_DEVICE(USB_VENDOR_ID, USB_PRODUCT_ID) },
    {} // Termination entry
};
MODULE_DEVICE_TABLE(usb, usbc_hdmi_table);

// Called when the device is plugged in
static int usbc_hdmi_probe(struct usb_interface *interface, const struct usb_device_id *id) {
    printk(KERN_INFO "[usbc_hdmi_driver] USB-C HDMI adapter connected (VID:PID = %04X:%04X)\n",
           id->idVendor, id->idProduct);
    return 0;
}

// Called when the device is unplugged
static void usbc_hdmi_disconnect(struct usb_interface *interface) {
    printk(KERN_INFO "[usbc_hdmi_driver] USB-C HDMI adapter disconnected\n");
}

// USB driver struct
static struct usb_driver usbc_hdmi_driver = {
    .name = "usbc_hdmi_driver",
    .id_table = usbc_hdmi_table,
    .probe = usbc_hdmi_probe,
    .disconnect = usbc_hdmi_disconnect,
};

// Register/unregister driver
static int __init usbc_hdmi_init(void) {
    return usb_register(&usbc_hdmi_driver);
}

static void __exit usbc_hdmi_exit(void) {
    usb_deregister(&usbc_hdmi_driver);
}

module_init(usbc_hdmi_init);
module_exit(usbc_hdmi_exit);






// obj-m += usbc_hdmi_driver.o

// all:
// 	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

// clean:
// 	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
