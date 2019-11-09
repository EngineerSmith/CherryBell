#pragma once

namespace CherryBell {
	enum class KeyCode
	{
		// Codes from glfw3.h
		KeySpace  			 = 32,
		KeyApostrophe  		 = 39, /* ' */
		KeyComma             = 44,  /* , */
		KeyMinus             = 45,  /* - */
		KeyPeriod            = 46,  /* . */
		KeySlash             = 47,  /* / */
		Key0                 = 48,
		Key1                 = 49,
		Key2                 = 50,
		Key3                 = 51,
		Key4                 = 52,
		Key5                 = 53,
		Key6                 = 54,
		Key7                 = 55,
		Key8                 = 56,
		Key9                 = 57,
		KeySemicolon         = 59,  /* ; */
		KeyEqual             = 61,  /*   */
		KeyA                 = 65,
		KeyB                 = 66,
		KeyC                 = 67,
		KeyD                 = 68,
		KeyE                 = 69,
		KeyF                 = 70,
		KeyG                 = 71,
		KeyH                 = 72,
		KeyI                 = 73,
		KeyJ                 = 74,
		KeyK                 = 75,
		KeyL                 = 76,
		KeyM                 = 77,
		KeyN                 = 78,
		KeyO                 = 79,
		KeyP                 = 80,
		KeyQ                 = 81,
		KeyR                 = 82,
		KeyS                 = 83,
		KeyT                 = 84,
		KeyU                 = 85,
		KeyV                 = 86,
		KeyW                 = 87,
		KeyX                 = 88,
		KeyY                 = 89,
		KeyZ                 = 90,
		KeyLeft_bracket      = 91,  /* [ */
		KeyBackslash         = 92,  /* \ */
		KeyRight_bracket     = 93,  /* ] */
		KeyGrave_accent      = 96,  /* ` */
		KeyWorld1            = 161, /* non-US #1 */
		KeyWorld2            = 162, /* non-US #2 */

	/* Function keys */
		KeyEscape            = 256,
		KeyEnter             = 257,
		KeyTab               = 258,
		KeyBackspace         = 259,
		KeyInsert            = 260,
		KeyDelete            = 261,
		KeyRight             = 262,
		KeyLeft              = 263,
		KeyDown              = 264,
		KeyUp                = 265,
		KeyPageUp            = 266,
		KeyPageDown          = 267,
		KeyHome              = 268,
		KeyEnd               = 269,
		KeyCapsLock          = 280,
		KeyScrollLock        = 281,
		KeyNumLock           = 282,
		KeyPrintScreen       = 283,
		KeyPause             = 284,
		KeyF1                = 290,
		KeyF2                = 291,
		KeyF3                = 292,
		KeyF4                = 293,
		KeyF5                = 294,
		KeyF6                = 295,
		KeyF7                = 296,
		KeyF8                = 297,
		KeyF9                = 298,
		KeyF10               = 299,
		KeyF11               = 300,
		KeyF12               = 301,
		KeyF13               = 302,
		KeyF14               = 303,
		KeyF15               = 304,
		KeyF16               = 305,
		KeyF17               = 306,
		KeyF18               = 307,
		KeyF19               = 308,
		KeyF20               = 309,
		KeyF21               = 310,
		KeyF22               = 311,
		KeyF23               = 312,
		KeyF24               = 313,
		KeyF25               = 314,
		KeyKp0               = 320,
		KeyKp1               = 321,
		KeyKp2               = 322,
		KeyKp3               = 323,
		KeyKp4               = 324,
		KeyKp5               = 325,
		KeyKp6               = 326,
		KeyKp7               = 327,
		KeyKp8               = 328,
		KeyKp9               = 329,
		KeyKpDecimal         = 330,
		KeyKpDivide          = 331,
		KeyKpMultiply        = 332,
		KeyKpSubtract        = 333,
		KeyKpAdd             = 334,
		KeyKpEnter           = 335,
		KeyKpEqual           = 336,
		KeyLeftShift         = 340,
		KeyLeftControl       = 341,
		KeyLeftAlt           = 342,
		KeyLeftSuper         = 343,
		KeyRightShift        = 344,
		KeyRightControl      = 345,
		KeyRightAlt          = 346,
		KeyRightSuper        = 347,
		KeyMenu              = 348
	};

	inline std::ostream& operator<<(std::ostream& os, KeyCode keyCode)
	{
		os << static_cast<int32_t>(keyCode);
		return os;
	}
}

#define CB_KEY_SPACE              ::CherryBell::KeyCode::KeySpace
#define CB_KEY_APOSTROPHE         ::CherryBell::KeyCode::KeyApostrophe 
#define CB_KEY_COMMA              ::CherryBell::KeyCode::KeyComma 
#define CB_KEY_MINUS              ::CherryBell::KeyCode::KeyMinus 
#define CB_KEY_PERIOD             ::CherryBell::KeyCode::KeyPeriod
#define CB_KEY_SLASH              ::CherryBell::KeyCode::KeySlash 
#define CB_KEY_0                  ::CherryBell::KeyCode::Key0
#define CB_KEY_1                  ::CherryBell::KeyCode::Key1
#define CB_KEY_2                  ::CherryBell::KeyCode::Key2
#define CB_KEY_3                  ::CherryBell::KeyCode::Key3
#define CB_KEY_4                  ::CherryBell::KeyCode::Key4
#define CB_KEY_5                  ::CherryBell::KeyCode::Key5
#define CB_KEY_6                  ::CherryBell::KeyCode::Key6
#define CB_KEY_7                  ::CherryBell::KeyCode::Key7
#define CB_KEY_8                  ::CherryBell::KeyCode::Key8
#define CB_KEY_9                  ::CherryBell::KeyCode::Key9
#define CB_KEY_SEMICOLON          ::CherryBell::KeyCode::KeySemicolon 
#define CB_KEY_EQUAL              ::CherryBell::KeyCode::KeyEqual 
#define CB_KEY_A                  ::CherryBell::KeyCode::KeyA            
#define CB_KEY_B                  ::CherryBell::KeyCode::KeyB            
#define CB_KEY_C                  ::CherryBell::KeyCode::KeyC            
#define CB_KEY_D                  ::CherryBell::KeyCode::KeyD            
#define CB_KEY_E                  ::CherryBell::KeyCode::KeyE            
#define CB_KEY_F                  ::CherryBell::KeyCode::KeyF            
#define CB_KEY_G                  ::CherryBell::KeyCode::KeyG            
#define CB_KEY_H                  ::CherryBell::KeyCode::KeyH            
#define CB_KEY_I                  ::CherryBell::KeyCode::KeyI            
#define CB_KEY_J                  ::CherryBell::KeyCode::KeyJ            
#define CB_KEY_K                  ::CherryBell::KeyCode::KeyK            
#define CB_KEY_L                  ::CherryBell::KeyCode::KeyL            
#define CB_KEY_M                  ::CherryBell::KeyCode::KeyM            
#define CB_KEY_N                  ::CherryBell::KeyCode::KeyN            
#define CB_KEY_O                  ::CherryBell::KeyCode::KeyO            
#define CB_KEY_P                  ::CherryBell::KeyCode::KeyP            
#define CB_KEY_Q                  ::CherryBell::KeyCode::KeyQ            
#define CB_KEY_R                  ::CherryBell::KeyCode::KeyR            
#define CB_KEY_S                  ::CherryBell::KeyCode::KeyS            
#define CB_KEY_T                  ::CherryBell::KeyCode::KeyT            
#define CB_KEY_U                  ::CherryBell::KeyCode::KeyU            
#define CB_KEY_V                  ::CherryBell::KeyCode::KeyV            
#define CB_KEY_W                  ::CherryBell::KeyCode::KeyW            
#define CB_KEY_X                  ::CherryBell::KeyCode::KeyX            
#define CB_KEY_Y                  ::CherryBell::KeyCode::KeyY            
#define CB_KEY_Z                  ::CherryBell::KeyCode::KeyZ            
#define CB_KEY_LEFT_BRACKET       ::CherryBell::KeyCode::KeyLeftBracket  
#define CB_KEY_BACKSLASH          ::CherryBell::KeyCode::KeyBackslash    
#define CB_KEY_RIGHT_BRACKET      ::CherryBell::KeyCode::KeyRightBracket 
#define CB_KEY_GRAVE_ACCENT       ::CherryBell::KeyCode::KeyGraveAccent  
#define CB_KEY_WORLD_1            ::CherryBell::KeyCode::KeyWorld1       
#define CB_KEY_WORLD_2            ::CherryBell::KeyCode::KeyWorld2       

/* Function keys */				  
#define CB_KEY_ESCAPE             ::CherryBell::KeyCode::KeyEscape       
#define CB_KEY_ENTER              ::CherryBell::KeyCode::KeyEnter        
#define CB_KEY_TAB                ::CherryBell::KeyCode::KeyTab          
#define CB_KEY_BACKSPACE          ::CherryBell::KeyCode::KeyBackspace    
#define CB_KEY_INSERT             ::CherryBell::KeyCode::KeyInsert       
#define CB_KEY_DELETE             ::CherryBell::KeyCode::KeyDelete       
#define CB_KEY_RIGHT              ::CherryBell::KeyCode::KeyRight        
#define CB_KEY_LEFT               ::CherryBell::KeyCode::KeyLeft         
#define CB_KEY_DOWN               ::CherryBell::KeyCode::KeyDown         
#define CB_KEY_UP                 ::CherryBell::KeyCode::KeyUp           
#define CB_KEY_PAGE_UP            ::CherryBell::KeyCode::KeyPageUp      
#define CB_KEY_PAGE_DOWN          ::CherryBell::KeyCode::KeyPageDown    
#define CB_KEY_HOME               ::CherryBell::KeyCode::KeyHome         
#define CB_KEY_END                ::CherryBell::KeyCode::KeyEnd          
#define CB_KEY_CAPS_LOCK          ::CherryBell::KeyCode::KeyCapsLock    
#define CB_KEY_SCROLL_LOCK        ::CherryBell::KeyCode::KeyScrollLock  
#define CB_KEY_NUM_LOCK           ::CherryBell::KeyCode::KeyNumLock     
#define CB_KEY_PRINT_SCREEN       ::CherryBell::KeyCode::KeyPrintScreen 
#define CB_KEY_PAUSE              ::CherryBell::KeyCode::KeyPause        
#define CB_KEY_F1                 ::CherryBell::KeyCode::KeyF1           
#define CB_KEY_F2                 ::CherryBell::KeyCode::KeyF2           
#define CB_KEY_F3                 ::CherryBell::KeyCode::KeyF3           
#define CB_KEY_F4                 ::CherryBell::KeyCode::KeyF4           
#define CB_KEY_F5                 ::CherryBell::KeyCode::KeyF5           
#define CB_KEY_F6                 ::CherryBell::KeyCode::KeyF6           
#define CB_KEY_F7                 ::CherryBell::KeyCode::KeyF7           
#define CB_KEY_F8                 ::CherryBell::KeyCode::KeyF8           
#define CB_KEY_F9                 ::CherryBell::KeyCode::KeyF9           
#define CB_KEY_F10                ::CherryBell::KeyCode::KeyF10          
#define CB_KEY_F11                ::CherryBell::KeyCode::KeyF11          
#define CB_KEY_F12                ::CherryBell::KeyCode::KeyF12          
#define CB_KEY_F13                ::CherryBell::KeyCode::KeyF13          
#define CB_KEY_F14                ::CherryBell::KeyCode::KeyF14          
#define CB_KEY_F15                ::CherryBell::KeyCode::KeyF15          
#define CB_KEY_F16                ::CherryBell::KeyCode::KeyF16          
#define CB_KEY_F17                ::CherryBell::KeyCode::KeyF17          
#define CB_KEY_F18                ::CherryBell::KeyCode::KeyF18          
#define CB_KEY_F19                ::CherryBell::KeyCode::KeyF19          
#define CB_KEY_F20                ::CherryBell::KeyCode::KeyF20          
#define CB_KEY_F21                ::CherryBell::KeyCode::KeyF21          
#define CB_KEY_F22                ::CherryBell::KeyCode::KeyF22          
#define CB_KEY_F23                ::CherryBell::KeyCode::KeyF23          
#define CB_KEY_F24                ::CherryBell::KeyCode::KeyF24          
#define CB_KEY_F25                ::CherryBell::KeyCode::KeyF25          
#define CB_KEY_KP_0               ::CherryBell::KeyCode::KeyKp0         
#define CB_KEY_KP_1               ::CherryBell::KeyCode::KeyKp1         
#define CB_KEY_KP_2               ::CherryBell::KeyCode::KeyKp2         
#define CB_KEY_KP_3               ::CherryBell::KeyCode::KeyKp3         
#define CB_KEY_KP_4               ::CherryBell::KeyCode::KeyKp4         
#define CB_KEY_KP_5               ::CherryBell::KeyCode::KeyKp5         
#define CB_KEY_KP_6               ::CherryBell::KeyCode::KeyKp6         
#define CB_KEY_KP_7               ::CherryBell::KeyCode::KeyKp7         
#define CB_KEY_KP_8               ::CherryBell::KeyCode::KeyKp8         
#define CB_KEY_KP_9               ::CherryBell::KeyCode::KeyKp9         
#define CB_KEY_KP_DECIMAL         ::CherryBell::KeyCode::KeyKpDecimal   
#define CB_KEY_KP_DIVIDE          ::CherryBell::KeyCode::KeyKpDivide    
#define CB_KEY_KP_MULTIPLY        ::CherryBell::KeyCode::KeyKpMultiply  
#define CB_KEY_KP_SUBTRACT        ::CherryBell::KeyCode::KeyKpSubtract  
#define CB_KEY_KP_ADD             ::CherryBell::KeyCode::KeyKpAdd       
#define CB_KEY_KP_ENTER           ::CherryBell::KeyCode::KeyKpEnter     
#define CB_KEY_KP_EQUAL           ::CherryBell::KeyCode::KeyKpEqual     
#define CB_KEY_LEFT_SHIFT         ::CherryBell::KeyCode::KeyLeftShift   
#define CB_KEY_LEFT_CONTROL       ::CherryBell::KeyCode::KeyLeftControl 
#define CB_KEY_LEFT_ALT           ::CherryBell::KeyCode::KeyLeftAlt     
#define CB_KEY_LEFT_SUPER         ::CherryBell::KeyCode::KeyLeftSuper   
#define CB_KEY_RIGHT_SHIFT        ::CherryBell::KeyCode::KeyRightShift  
#define CB_KEY_RIGHT_CONTROL      ::CherryBell::KeyCode::KeyRightControl
#define CB_KEY_RIGHT_ALT          ::CherryBell::KeyCode::KeyRightAlt    
#define CB_KEY_RIGHT_SUPER        ::CherryBell::KeyCode::KeyRightSuper  
#define CB_KEY_MENU               ::CherryBell::KeyCode::KeyMenu         
