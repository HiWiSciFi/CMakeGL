#pragma once
#include <inttypes.h>
#include <string>

namespace Junia
{
	enum class MouseButton : uint8_t
	{
		Left = 0,
		Right = 1,
		Middle = 2
	};

	enum class KeyCode : uint8_t
	{
		HOME           = 2, /* POS1 | HOME */
		END            = 3,
		PRINT_SCREEN   = 4,
		NUM_LOCK       = 5,
		CAPS_LOCK      = 6,
		SCROLL_LOCK    = 7,
		BACKSPACE      = 8,
		TAB            = 9,
		ENTER          = 10,
		MENU           = 12,
		PAGE_UP        = 14,
		PAGE_DOWN      = 15,
		PAUSE          = 22,
		INSERT         = 26,
		ESCAPE         = 27,

		SPACE          = 32,

		APOSTROPHE     = 39,  /* ' */
		COMMA          = 44,  /* , */
		MINUS          = 45,  /* - */
		PERIOD         = 46,  /* . */
		SLASH          = 47,  /* / */

		KEY_0          = 48,
		KEY_1          = 49,
		KEY_2          = 50,
		KEY_3          = 51,
		KEY_4          = 52,
		KEY_5          = 53,
		KEY_6          = 54,
		KEY_7          = 55,
		KEY_8          = 56,
		KEY_9          = 57,

		SEMICOLON      = 59,  /* ; */
		EQUAL          = 61,  /* = */

		A              = 65,
		B              = 66,
		C              = 67,
		D              = 68,
		E              = 69,
		F              = 70,
		G              = 71,
		H              = 72,
		I              = 73,
		J              = 74,
		K              = 75,
		L              = 76,
		M              = 77,
		N              = 78,
		O              = 79,
		P              = 80,
		Q              = 81,
		R              = 82,
		S              = 83,
		T              = 84,
		U              = 85,
		V              = 86,
		W              = 87,
		X              = 88,
		Y              = 89,
		Z              = 90,

		LEFT_BRACKET   = 91,  /* [ */
		BACKSLASH      = 92,  /* \ */
		RIGHT_BRACKET  = 93,  /* ] */
		GRAVE_ACCENT   = 96,  /* ^ */

		ARROW_LEFT     = 97,  /* <- */
		ARROW_UP       = 98,  /* /\ */
		ARROW_RIGHT    = 99,  /* -> */
		ARROW_DOWN     = 100, /* \/ */

		F1             = 101,
		F2             = 102,
		F3             = 103,
		F4             = 104,
		F5             = 105,
		F6             = 106,
		F7             = 107,
		F8             = 108,
		F9             = 109,
		F10            = 110,
		F11            = 111,
		F12            = 112,
		F13            = 113,
		F14            = 114,
		F15            = 115,
		F16            = 116,
		F17            = 117,
		F18            = 118,
		F19            = 119,
		F20            = 120,
		F21            = 121,
		F22            = 122,
		F23            = 123,
		F24            = 124,
		F25            = 125,

		DELETE         = 127, /* DEL */

		LEFT_SHIFT     = 128,
		RIGHT_SHIFT    = 129,
		LEFT_CONTROL   = 130,
		RIGHT_CONTROL  = 131,
		LEFT_ALT       = 132,
		RIGHT_ALT      = 133,
		LEFT_SUPER     = 134, /* left Windows Key / platform equivalent */
		RIGHT_SUPER    = 135, /* right Windows Key / platform equivalent */

		NUM_ENTER      = 202, /* 0xa | 192 */
		NUM_MULTIPLY   = 234, /* '*' | 192 */
		NUM_ADD        = 235, /* '+' | 192 */
		NUM_SUBTRACT   = 237, /* '-' | 192 */
		NUM_DECIMAL    = 238, /* '.' | 192 */
		NUM_DIVIDE     = 239, /* '/' | 192 */
		NUM_0          = 240, /* '0' | 192 */
		NUM_1          = 241, /* '1' | 192 */
		NUM_2          = 242, /* '2' | 192 */
		NUM_3          = 243, /* '3' | 192 */
		NUM_4          = 244, /* '4' | 192 */
		NUM_5          = 245, /* '5' | 192 */
		NUM_6          = 246, /* '6' | 192 */
		NUM_7          = 247, /* '7' | 192 */
		NUM_8          = 248, /* '8' | 192 */
		NUM_9          = 249, /* '9' | 192 */
		NUM_EQUAL      = 253  /* '=' | 192 */
	};

	static std::string KeyToString(KeyCode keycode)
	{
		std::stringstream ss;
		if (keycode >= 202) // NUMPAD
		{
			ss << "NUM ";
			if ((keycode >= 237 && keycode <= 249) || keycode == 234 || keycode == 235 || keycode == 253) ss << static_cast<char>(keycode & ~192);
			else if (keycode == 202) ss << "Enter";
			else return "Unknown Key";
		}
		else if (keycode >= 101 && keycode <= 125) // F-Keys
		{
			ss << "F" << static_cast<int>(keycode - 100);
		}
		else if (keycode == 32 || keycode == 39 || (keycode >= 44 && keycode <= 57) || keycode == 59 || keycode == 61 || (keycode >= 65 && keycode <= 93) || keycode == 96) // Number keys
		{
			ss << static_cast<char>(keycode);
		}
		else
		{
			switch (keycode)
			{
				case 0:
				default:
					return "Unknown Key";
			}
		}
		return ss.str();
	}
}
