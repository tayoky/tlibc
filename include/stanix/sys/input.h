#ifndef _SYS_INPUT_H
#define _SYS_INPUT_H

#include <sys/time.h>

struct input_event {
    struct timeval timestamp;
    unsigned long ie_class;
    unsigned long ie_subclass;
    unsigned long ie_type;
    union {
        struct {
            unsigned long axis;
            long x;
            long y;
        } ie_move;
        struct {
            unsigned long key;
            unsigned long scancode;
            unsigned long flags;
        } ie_key;
        char ie_string[24];
    };
};

struct input_info {
    unsigned long if_class;
    unsigned long if_subclass;
};

struct input_request {
    unsigned long ir_type;
    unsigned long ir_arg;
};

// non device specific
#define IR_INFO_REQUEST 0x01
#define IR_VENDOR_REQUEST 0x02
#define IR_NAME_REQUEST 0x03
#define IR_RESET_REQUEST 0x04

// device specific
#define IR_SET_LED_REQUEST 0x05
#define IR_SET_LAYOUT_REQUEST 0x06

// event types
#define IE_UNKOW_EVENT 0x00
#define IE_ACK_EVENT 0x01
#define IE_MOVE_EVENT 0x02
#define IE_KEY_EVENT 0x03

// class
#define IE_CLASS_UNKNOW 0x00
#define IE_CLASS_KEYBOARD 0x01
#define IE_CLASS_MOUSE 0x02
#define IE_CLASS_JOYSTICK 0x03

// subclass
#define IE_SUBCLASS_UNKNOW 0x00

// keyboard subclass
#define IE_SUBCLASS_USB_KBD 0x01
#define IE_SUBCLASS_PS2_KBD 0x02
#define IE_SUBCALSS_VIRT_KBD 0x03

// mouse subclass
#define IE_SUBCLASS_USB_MOUSE 0x01
#define IE_SUBCLASS_PS2_MOUSE 0x02
#define IE_SUBCLASS_VIRT_MOUSE 0x03
#define IE_SUBCLASS_PS2_TRACKPAD 0x04

// key event flags
#define IE_KEY_PRESS 0x01
#define IE_KEY_RELEASE 0x02
#define IE_KEY_HOLD 0x03
#define IE_KEY_GRAPH 0x04  // printable key
#define IE_KEY_GRPAH IE_KEY_GRAPH  //conserved 

//ioctl
#define I_INPUT_GET_CONTROL  1001
#define I_INPUT_DROP_CONTROL 1002
#define I_INPUT_GET_INFO     1003
#define I_INPUT_SET_LAYOUT   1004
#define I_INPUT_GET_LAYOUT   1005

#define INPUT_LAYOUT_SIZE 64

#define INPUT_KEY_FIRST        17000000
#define INPUT_KEY_MOUSE_LEFT   17000000
#define INPUT_KEY_MOUSE_MIDDLE 17000001
#define INPUT_KEY_MOUSE_RIGHT  17000002
#define INPUT_KEY_ESC          17000051
#define INPUT_KEY_TAB          17000052
#define INPUT_KEY_BACKSPACE    17000053
#define INPUT_KEY_ENTER        17000054
#define INPUT_KEY_DELETE       17000055
#define INPUT_KEY_INSERT       17000056
#define INPUT_KEY_HOME         17000057
#define INPUT_KEY_END          17000058
#define INPUT_KEY_ARROW_UP     17000059
#define INPUT_KEY_ARROW_DOWN   17000060
#define INPUT_KEY_ARROW_DOWN   17000061
#define INPUT_KEY_ARROW_LEFT   17000062
#define INPUT_KEY_ARROW_RIGHT  17000063
#define INPUT_KEY_PAGE_UP      17000064
#define INPUT_KEY_PAGE_DOWN    17000065
#define INPUT_KEY_LSHIFT       17000066
#define INPUT_KEY_RSHIFT       17000067
#define INPUT_KEY_LCRTL        17000068
#define INPUT_KEY_RCRTL        17000069
#define INPUT_KEY_LALT         17000070
#define INPUT_KEY_RALT         17000071
#define INPUT_KEY_ALTGR        17000072
#define INPUT_KEY_NUM_LOCK     17000073
#define INPUT_KEY_SCROLL_LOCK  17000074
#define INPUT_KEY_CAPS_LOCK    17000075
#define INPUT_KEY_F1           17000076
#define INPUT_KEY_F2           17000077
#define INPUT_KEY_F3           17000078
#define INPUT_KEY_F4           17000079
#define INPUT_KEY_F5           17000080
#define INPUT_KEY_F6           17000081
#define INPUT_KEY_F7           17000082
#define INPUT_KEY_F8           17000083
#define INPUT_KEY_F9           17000084
#define INPUT_KEY_F10          17000085
#define INPUT_KEY_F11          17000086
#define INPUT_KEY_F12          17000087
#define INPUT_KEY_GUI          17000088
#define INPUT_KEY_VOLUME_UP    17000089
#define INPUT_KEY_VOLUME_DOWN  17000090
#define INPUT_KEY_LAST         17000090

#define INPUT_KEY_SPACE ' '

#endif
