// Send a fake keystroke event to an X window.
// A full list of available codes can be found in /usr/include/X11/keysymdef.h

// To compile it, you need to type this:
// g++ -o XFakeKey Send_a_fake_keystroke_event_to_an_X_window.cpp -L/usr/X11R6/lib -lX11

#include <X11/Xlib.h>
#include <X11/keysym.h>

// Function to create a keyboard event
XKeyEvent createKeyEvent(Display *display, Window &win,
                           Window &winRoot, bool press,
                           int keycode, int modifiers)
{
   XKeyEvent event;

   event.display     = display;
   event.window      = win;
   event.root        = winRoot;
   event.subwindow   = None;
   event.time        = CurrentTime;
   event.x           = 1;
   event.y           = 1;
   event.x_root      = 1;
   event.y_root      = 1;
   event.same_screen = True;
   event.keycode     = XKeysymToKeycode(display, keycode);
   event.state       = modifiers;

   if(press)
      event.type = KeyPress;
   else
      event.type = KeyRelease;

   return event;
}

main()
{
// Obtain the X11 display.
   Display *display = XOpenDisplay(0);
   if(display == NULL)
      return -1;

// Get the root window for the current display.
   Window winRoot = XDefaultRootWindow(display);

// Find the window which has the current keyboard focus.
   Window winFocus;
   int    revert;
   XGetInputFocus(display, &winFocus, &revert);

// Send a fake key press event to the window.
   XKeyEvent event = createKeyEvent(display, winFocus, winRoot, true, 0x76, ControlMask);
   XSendEvent(event.display, event.window, False, KeyPressMask, (XEvent *)&event);

// Send a fake key release event to the window.
   event = createKeyEvent(display, winFocus, winRoot, false, 0x76, ControlMask);
   XSendEvent(event.display, event.window, False, KeyReleaseMask, (XEvent *)&event);

// Done.
   XCloseDisplay(display);
   return 0;
}