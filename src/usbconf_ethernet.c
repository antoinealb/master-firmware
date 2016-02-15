#include "usbconf_ethernet.h"

/*Endpoints to be used for USBD1.  */
#define USBD1_DATA_REQUEST_EP           1
#define USBD1_DATA_AVAILABLE_EP         1
#define USBD1_INTERRUPT_REQUEST_EP      2

/* USB Device Descriptor.  */
static const uint8_t vcom_device_descriptor_data[18] = {
    USB_DESC_DEVICE       (0x0110,        /* bcdUSB (1.1).                    */
            0x02,          /* bDeviceClass (CDC).              */
            0x06,          /* bDeviceSubClass.                 */
            0x00,          /* bDeviceProtocol.                 */
            0x40,          /* bMaxPacketSize.                  */
            0x0483,        /* idVendor (ST).                   */
            0x5740,        /* idProduct.                       */
            0x0200,        /* bcdDevice.                       */
            1,             /* iManufacturer.                   */
            2,             /* iProduct.                        */
            3,             /* iSerialNumber.                   */
            1)             /* bNumConfigurations.              */
};

/* Device Descriptor wrapper.  */
static const USBDescriptor vcom_device_descriptor = {
    sizeof vcom_device_descriptor_data,
    vcom_device_descriptor_data
};

/* Configuration Descriptor tree for a CDC.*/
static const uint8_t vcom_configuration_descriptor_data[70] = {
    /* Configuration Descriptor, 9 bytes*/
    USB_DESC_CONFIGURATION(70,            /* wTotalLength.                    */
            0x02,          /* bNumInterfaces.                  */
            0x01,          /* bConfigurationValue.             */
            0,             /* iConfiguration.                  */
            0xC0,          /* bmAttributes (self powered).     */
            50),           /* bMaxPower (100mA).               */
    /* Interface Descriptor., 9 bytes*/
    USB_DESC_INTERFACE    (0x00,          /* bInterfaceNumber.                */
            0x00,          /* bAlternateSetting.               */
            0x01,          /* bNumEndpoints.                   */
            0x02,          /* bInterfaceClass (Communications
                              Interface Class, CDC section
                              4.2).                            */
            0x06,          /* bInterfaceSubClass (Ethernet networking control model, CDC section 4.3).   */
            0x00,          /* bInterfaceProtocol (none, CDC section 4.4).                */
            0),            /* iInterface.                      */
    /* Header Functional Descriptor (CDC section 5.2.3).*/
    USB_DESC_BYTE         (5),            /* bLength.                         */
    USB_DESC_BYTE         (0x24),         /* bDescriptorType (CS_INTERFACE).  */
    USB_DESC_BYTE         (0x00),         /* bDescriptorSubtype (Header
                                             Functional Descriptor.           */
    USB_DESC_BCD          (0x0110),       /* bcdCDC.                          */
    /* Ethernet networking functional descriptor */
    USB_DESC_BYTE         (12), /* Length */
    USB_DESC_BYTE         (0xf),         /* Ethernet func desc */
    USB_DESC_BYTE         (4),         /*  Mac address pointer */
    USB_DESC_BYTE         (0),         /*  Statistics */
    USB_DESC_BYTE         (0),
    USB_DESC_BYTE         (0),
    USB_DESC_BYTE         (0),
    USB_DESC_WORD         (1514),   /* MTU */
    USB_DESC_WORD         (0x00),   /* No multicast support */
    USB_DESC_BYTE         (0),

    /* Union Functional Descriptor.*/
    USB_DESC_BYTE         (5),            /* bFunctionLength.                 */
    USB_DESC_BYTE         (0x24),         /* bDescriptorType (CS_INTERFACE).  */
    USB_DESC_BYTE         (0x06),         /* bDescriptorSubtype (Union
                                             Functional Descriptor).          */
    USB_DESC_BYTE         (0x00),         /* bMasterInterface (Communication
                                             Class Interface).                */
    USB_DESC_BYTE         (0x01),         /* bSlaveInterface0 (Data Class
                                             Interface).                      */
    /* Endpoint 2 Descriptor., 7 bytes*/
    USB_DESC_ENDPOINT     (USBD1_INTERRUPT_REQUEST_EP|0x80,
            0x03,          /* bmAttributes (Interrupt).        */
            0x0008,        /* wMaxPacketSize.                  */
            0xFF),         /* bInterval.                       */
    /* Interface Descriptor., 9 bytes*/
    USB_DESC_INTERFACE    (0x01,          /* bInterfaceNumber.                */
            0x00,          /* bAlternateSetting.               */
            0x02,          /* bNumEndpoints.                   */
            0x0A,          /* bInterfaceClass (Data Class
                              Interface, CDC section 4.5).     */
            0x00,          /* bInterfaceSubClass (CDC section
                              4.6).                            */
            0x00,          /* bInterfaceProtocol (CDC section
                              4.7).                            */
            0x00),         /* iInterface.                      */
    /* Endpoint 3 Descriptor.*/
    USB_DESC_ENDPOINT     (USBD1_DATA_AVAILABLE_EP,       /* bEndpointAddress.*/
            0x02,          /* bmAttributes (Bulk).             */
            0x0040,        /* wMaxPacketSize.                  */
            0x00),         /* bInterval.                       */
    /* Endpoint 1 Descriptor.*/
    USB_DESC_ENDPOINT     (USBD1_DATA_REQUEST_EP|0x80,    /* bEndpointAddress.*/
            0x02,          /* bmAttributes (Bulk).             */
            0x0040,        /* wMaxPacketSize.                  */
            0x00)          /* bInterval.                       */
};

/* Configuration Descriptor wrapper.  */
static const USBDescriptor vcom_configuration_descriptor = {
    sizeof vcom_configuration_descriptor_data,
    vcom_configuration_descriptor_data
};

/* U.S. English language identifier.  */
static const uint8_t vcom_string0[] = {
    USB_DESC_BYTE(4),                     /* bLength.                         */
    USB_DESC_BYTE(USB_DESCRIPTOR_STRING), /* bDescriptorType.                 */
    USB_DESC_WORD(0x0409)                 /* wLANGID (U.S. English).          */
};

/* Vendor string.  */
static const uint8_t vcom_string1[] = {
    USB_DESC_BYTE(38),                    /* bLength.                         */
    USB_DESC_BYTE(USB_DESCRIPTOR_STRING), /* bDescriptorType.                 */
    'C', 0, 'V', 0, 'R', 0, 'A', 0,
};

/* Device Description string.  */
static const uint8_t vcom_string2[] = {
    USB_DESC_BYTE(60),                    /* bLength.                         */
    USB_DESC_BYTE(USB_DESCRIPTOR_STRING), /* bDescriptorType.                 */
    'C', 0, 'h', 0, 'i', 0, 'b', 0, 'i', 0, 'O', 0, 'S', 0, '/', 0,
    'R', 0, 'T', 0, ' ', 0, 'E', 0, 't', 0, 'h', 0, 'e', 0, 'r', 0, 'n', 0, 'e', 0,
    't', 0, ' ', 0, 'a', 0, 'd', 0, 'a', 0, 'p', 0, 't', 0, 'e', 0, 'r',
};

/* Serial Number string.  */
static const uint8_t vcom_string3[] = {
    USB_DESC_BYTE(8),                     /* bLength.                         */
    USB_DESC_BYTE(USB_DESCRIPTOR_STRING), /* bDescriptorType.                 */
    '0' + CH_KERNEL_MAJOR, 0,
    '0' + CH_KERNEL_MINOR, 0,
    '1' + CH_KERNEL_PATCH, 0
};

static const uint8_t vcom_string4[] = {
    USB_DESC_BYTE(26),                     /* bLength.                         */
    USB_DESC_BYTE(USB_DESCRIPTOR_STRING), /* bDescriptorType.                 */
    'd', 0, 'e', 0, 'a', 0, 'd', 0,
    'b', 0, 'e', 0, 'e', 0, 'f', 0,
    'b', 0, 'a', 0, 'b', 0, 'e', 0,
};

/* Strings wrappers array.  */
static const USBDescriptor vcom_strings[] = {
    {sizeof vcom_string0, vcom_string0},
    {sizeof vcom_string1, vcom_string1},
    {sizeof vcom_string2, vcom_string2},
    {sizeof vcom_string3, vcom_string3},
    {sizeof vcom_string4, vcom_string4},
};

/* Handles the GET_DESCRIPTOR callback. All required descriptors must be
 * handled here.  */
static const USBDescriptor *get_descriptor(USBDriver *usbp,
        uint8_t dtype,
        uint8_t dindex,
        uint16_t lang) {

    (void)usbp;
    (void)lang;
    switch (dtype) {
        case USB_DESCRIPTOR_DEVICE:
            return &vcom_device_descriptor;
        case USB_DESCRIPTOR_CONFIGURATION:
            return &vcom_configuration_descriptor;
        case USB_DESCRIPTOR_STRING:
            if (dindex < 5)
                return &vcom_strings[dindex];
    }
    return NULL;
}

static USBInEndpointState ep1instate;
static USBOutEndpointState ep1outstate;

/** @brief   EP1 initialization structure (both IN and OUT).  */
static const USBEndpointConfig ep1config = {
    USB_EP_MODE_TYPE_BULK,
    NULL,
    sduDataTransmitted,
    sduDataReceived,
    0x0040,
    0x0040,
    &ep1instate,
    &ep1outstate,
    2,
    NULL
};

static USBInEndpointState ep2instate;

static const USBEndpointConfig ep2config = {
    USB_EP_MODE_TYPE_INTR,
    NULL,
    sduInterruptTransmitted,
    NULL,
    0x0010,
    0x0000,
    &ep2instate,
    NULL,
    1,
    NULL
};

/** Handles the USB driver global events.  */
static void usb_event(USBDriver *usbp, usbevent_t event) {

    switch (event) {
        case USB_EVENT_RESET:
            return;
        case USB_EVENT_ADDRESS:
            return;
        case USB_EVENT_CONFIGURED:
            chSysLockFromISR();

            usbInitEndpointI(usbp, USBD1_DATA_REQUEST_EP, &ep1config);
            usbInitEndpointI(usbp, USBD1_INTERRUPT_REQUEST_EP, &ep2config);

            /* Resetting the state of the CDC subsystem.*/
            /* TODO */

            chSysUnlockFromISR();
            return;
        case USB_EVENT_SUSPEND:
            return;
        case USB_EVENT_WAKEUP:
            return;
        case USB_EVENT_STALLED:
            return;
    }
    return;
}

/** USB driver configuration.  */
const USBConfig ethernet_usbcfg = {
    usb_event,
    get_descriptor,
    sduRequestsHook,
    NULL
};
