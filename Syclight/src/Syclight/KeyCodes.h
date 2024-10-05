#pragma once
#define SYC_KEY_UNKNOWN            -1

// 复制于glfw3.h
/*! @} */

/*! @defgroup keys Keyboard key tokens
 *  @brief Keyboard key tokens.
 *
 *  See [key input](@ref input_key) for how these are used.
 *
 *  These key codes are inspired by the _USB HID Usage Tables v1.12_ (p. 53-60),
 *  but re-arranged to map to 7-bit ASCII for printable keys (function keys are
 *  put in the 256+ range).
 *
 *  The naming of the key codes follow these rules:
 *   - The US keyboard layout is used
 *   - Names of printable alphanumeric characters are used (e.g. "A", "R",
 *     "3", etc.)
 *   - For non-alphanumeric characters, Unicode:ish names are used (e.g.
 *     "COMMA", "LEFT_SQUARE_BRACKET", etc.). Note that some names do not
 *     correspond to the Unicode standard (usually for brevity)
 *   - Keys that lack a clear US mapping are named "WORLD_x"
 *   - For non-printable keys, custom names are used (e.g. "F4",
 *     "BACKSPACE", etc.)
 *
 *  @ingroup input
 *  @{
 */

 /* Printable keys */
#define SYC_KEY_SPACE              32
#define SYC_KEY_APOSTROPHE         39  /* ' */
#define SYC_KEY_COMMA              44  /* , */
#define SYC_KEY_MINUS              45  /* - */
#define SYC_KEY_PERIOD             46  /* . */
#define SYC_KEY_SLASH              47  /* / */
#define SYC_KEY_0                  48
#define SYC_KEY_1                  49
#define SYC_KEY_2                  50
#define SYC_KEY_3                  51
#define SYC_KEY_4                  52
#define SYC_KEY_5                  53
#define SYC_KEY_6                  54
#define SYC_KEY_7                  55
#define SYC_KEY_8                  56
#define SYC_KEY_9                  57
#define SYC_KEY_SEMICOLON          59  /* ; */
#define SYC_KEY_EQUAL              61  /* = */
#define SYC_KEY_A                  65
#define SYC_KEY_B                  66
#define SYC_KEY_C                  67
#define SYC_KEY_D                  68
#define SYC_KEY_E                  69
#define SYC_KEY_F                  70
#define SYC_KEY_G                  71
#define SYC_KEY_H                  72
#define SYC_KEY_I                  73
#define SYC_KEY_J                  74
#define SYC_KEY_K                  75
#define SYC_KEY_L                  76
#define SYC_KEY_M                  77
#define SYC_KEY_N                  78
#define SYC_KEY_O                  79
#define SYC_KEY_P                  80
#define SYC_KEY_Q                  81
#define SYC_KEY_R                  82
#define SYC_KEY_S                  83
#define SYC_KEY_T                  84
#define SYC_KEY_U                  85
#define SYC_KEY_V                  86
#define SYC_KEY_W                  87
#define SYC_KEY_X                  88
#define SYC_KEY_Y                  89
#define SYC_KEY_Z                  90
#define SYC_KEY_LEFT_BRACKET       91  /* [ */
#define SYC_KEY_BACKSLASH          92  /* \ */
#define SYC_KEY_RIGHT_BRACKET      93  /* ] */
#define SYC_KEY_GRAVE_ACCENT       96  /* ` */
#define SYC_KEY_WORLD_1            161 /* non-US #1 */
#define SYC_KEY_WORLD_2            162 /* non-US #2 */

/* Function keys */
#define SYC_KEY_ESCAPE             256
#define SYC_KEY_ENTER              257
#define SYC_KEY_TAB                258
#define SYC_KEY_BACKSPACE          259
#define SYC_KEY_INSERT             260
#define SYC_KEY_DELETE             261
#define SYC_KEY_RIGHT              262
#define SYC_KEY_LEFT               263
#define SYC_KEY_DOWN               264
#define SYC_KEY_UP                 265
#define SYC_KEY_PAGE_UP            266
#define SYC_KEY_PAGE_DOWN          267
#define SYC_KEY_HOME               268
#define SYC_KEY_END                269
#define SYC_KEY_CAPS_LOCK          280
#define SYC_KEY_SCROLL_LOCK        281
#define SYC_KEY_NUM_LOCK           282
#define SYC_KEY_PRINT_SCREEN       283
#define SYC_KEY_PAUSE              284
#define SYC_KEY_F1                 290
#define SYC_KEY_F2                 291
#define SYC_KEY_F3                 292
#define SYC_KEY_F4                 293
#define SYC_KEY_F5                 294
#define SYC_KEY_F6                 295
#define SYC_KEY_F7                 296
#define SYC_KEY_F8                 297
#define SYC_KEY_F9                 298
#define SYC_KEY_F10                299
#define SYC_KEY_F11                300
#define SYC_KEY_F12                301
#define SYC_KEY_F13                302
#define SYC_KEY_F14                303
#define SYC_KEY_F15                304
#define SYC_KEY_F16                305
#define SYC_KEY_F17                306
#define SYC_KEY_F18                307
#define SYC_KEY_F19                308
#define SYC_KEY_F20                309
#define SYC_KEY_F21                310
#define SYC_KEY_F22                311
#define SYC_KEY_F23                312
#define SYC_KEY_F24                313
#define SYC_KEY_F25                314
#define SYC_KEY_KP_0               320
#define SYC_KEY_KP_1               321
#define SYC_KEY_KP_2               322
#define SYC_KEY_KP_3               323
#define SYC_KEY_KP_4               324
#define SYC_KEY_KP_5               325
#define SYC_KEY_KP_6               326
#define SYC_KEY_KP_7               327
#define SYC_KEY_KP_8               328
#define SYC_KEY_KP_9               329
#define SYC_KEY_KP_DECIMAL         330
#define SYC_KEY_KP_DIVIDE          331
#define SYC_KEY_KP_MULTIPLY        332
#define SYC_KEY_KP_SUBTRACT        333
#define SYC_KEY_KP_ADD             334
#define SYC_KEY_KP_ENTER           335
#define SYC_KEY_KP_EQUAL           336
#define SYC_KEY_LEFT_SHIFT         340
#define SYC_KEY_LEFT_CONTROL       341
#define SYC_KEY_LEFT_ALT           342
#define SYC_KEY_LEFT_SUPER         343
#define SYC_KEY_RIGHT_SHIFT        344
#define SYC_KEY_RIGHT_CONTROL      345
#define SYC_KEY_RIGHT_ALT          346
#define SYC_KEY_RIGHT_SUPER        347
#define SYC_KEY_MENU               348

#define SYC_KEY_LAST               SYC_KEY_MENU