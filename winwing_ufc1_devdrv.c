#include <linux/module.h>
#include <linux/init.h>
#include <linux/usb.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Giorgos Makris");
MODULE_DESCRIPTION("Driver for the WinWing UFC1");

#define VENDOR_ID 0x4098
#define PRODUCT_ID 0xbed0

static struct usb_device_id usb_table[] = {
  {USB_DEVICE(VENDOR_ID, PRODUCT_ID)},
  {},
};

MODULE_DEVICE_TABLE(usb, usb_table);

static int probe(struct usb_interface *intf, const struct usb_device_id *id) {
  printk("winwing_ufc1_devdrv - Probed\n");
  return 0;
}

static void disconnect(struct usb_interface *intf){
  printk("winwing_ufc1_devdrv - Disconnected\n");
}

static struct usb_driver driver = {
  .name = "winwing_ufc1_devdrv",
  .id_table = usb_table,
  .probe = probe,
  .disconnect = disconnect
};

static int __init ww_ufc_init(void) {
  int registered = usb_register(&driver);

  if (registered) {
    printk("winwing_ufc1_devdrv - Error: could not register driver!\n");
    return -registered;
  }
  printk("winwing_ufc1_devdrv - Initialized driver\n");
  return 0;
}

static void __exit ww_ufc_exit(void) {
  usb_deregister(&driver);
  printk("winwing_ufc1_devdrv - Unloaded driver\n");
}

module_init(ww_ufc_init);
module_exit(ww_ufc_exit);
