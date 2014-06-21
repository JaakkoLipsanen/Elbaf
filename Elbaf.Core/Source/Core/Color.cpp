#include <Core\Color.h>
#include <Math\FlaiMath.h>
#include <Math\Vector.h>

inline static uint8 ClampToByte(float value)
{
	return static_cast<uint8>(FlaiMath::Clamp(value, 0.0f, 255.0f));
}

Color::Color(uint32 packedValue)
{
	this->R = packedValue % 256; packedValue /= 256;
	this->G = packedValue % 256; packedValue /= 256;
	this->B = packedValue % 256; packedValue /= 256;
	this->A = packedValue % 256; /* dwColor /= 256; */
}


Color::Color(uint8 r, uint8 g, uint8 b) : R(r), G(g), B(b), A(255)
{
}

Vector3f Color::ToVector3f() const
{
	return Vector3f(this->R / 255.0f, this->G / 255.0f, this->B / 255.0f);
}

Vector4f Color::ToVector4f() const
{
	return Vector4f(this->R / 255.0f, this->G / 255.0f, this->B / 255.0f, this->A / 255.0f);
}

Color::Color(uint8 r, uint8 g, uint8 b, uint8 a) : R(r), G(g), B(b), A(a)
{
}

Color Color::operator*(float multiplier) const
{
	return Color(this->R, this->G, this->B, ClampToByte(this->A * multiplier));
}

Color Color::Lerp(const Color& from, const Color& to, float amount)
{
	amount = FlaiMath::Clamp(amount, 0.0f, 1.0f);
	return Color(
		uint8(from.R + (to.R - from.R) * amount),
		uint8(from.G + (to.G - from.G) * amount),
		uint8(from.B + (to.B - from.B) * amount),
		uint8(from.A + (to.A - from.A) * amount));
}

// from XNA. Wrote a nice script that converted C# to C++ :)
Color const Color::Transparent = Color(0u);
Color const Color::AliceBlue = Color(4294965488u);
Color const Color::AntiqueWhite = Color(4292340730u);
Color const Color::Aqua = Color(4294967040u);
Color const Color::Aquamarine = Color(4292149119u);
Color const Color::Azure = Color(4294967280u);
Color const Color::Beige = Color(4292670965u);
Color const Color::Bisque = Color(4291093759u);
Color const Color::Black = Color(4278190080u);
Color const Color::BlanchedAlmond = Color(4291685375u);
Color const Color::Blue = Color(4294901760u);
Color const Color::BlueViolet = Color(4293012362u);
Color const Color::Brown = Color(4280953509u);
Color const Color::BurlyWood = Color(4287084766u);
Color const Color::CadetBlue = Color(4288716383u);
Color const Color::Chartreuse = Color(4278255487u);
Color const Color::Chocolate = Color(4280183250u);
Color const Color::Coral = Color(4283465727u);
Color const Color::CornflowerBlue = Color(4293760356u);
Color const Color::Cornsilk = Color(4292671743u);
Color const Color::Crimson = Color(4282127580u);
Color const Color::Cyan = Color(4294967040u);
Color const Color::DarkBlue = Color(4287299584u);
Color const Color::DarkCyan = Color(4287335168u);
Color const Color::DarkGoldenrod = Color(4278945464u);
Color const Color::DarkGray = Color(4289309097u);
Color const Color::DarkGreen = Color(4278215680u);
Color const Color::DarkKhaki = Color(4285249469u);
Color const Color::DarkMagenta = Color(4287299723u);
Color const Color::DarkOliveGreen = Color(4281297749u);
Color const Color::DarkOrange = Color(4278226175u);
Color const Color::DarkOrchid = Color(4291572377u);
Color const Color::DarkRed = Color(4278190219u);
Color const Color::DarkSalmon = Color(4286224105u);
Color const Color::DarkSeaGreen = Color(4287347855u);
Color const Color::DarkSlateBlue = Color(4287315272u);
Color const Color::DarkSlateGray = Color(4283387695u);
Color const Color::DarkTurquoise = Color(4291939840u);
Color const Color::DarkViolet = Color(4292018324u);
Color const Color::DeepPink = Color(4287829247u);
Color const Color::DeepSkyBlue = Color(4294950656u);
Color const Color::DimGray = Color(4285098345u);
Color const Color::DodgerBlue = Color(4294938654u);
Color const Color::Firebrick = Color(4280427186u);
Color const Color::FloralWhite = Color(4293982975u);
Color const Color::ForestGreen = Color(4280453922u);
Color const Color::Fuchsia = Color(4294902015u);
Color const Color::Gainsboro = Color(4292664540u);
Color const Color::GhostWhite = Color(4294965496u);
Color const Color::Gold = Color(4278245375u);
Color const Color::Goldenrod = Color(4280329690u);
Color const Color::Gray = Color(4286611584u);
Color const Color::Green = Color(4278222848u);
Color const Color::GreenYellow = Color(4281335725u);
Color const Color::Honeydew = Color(4293984240u);
Color const Color::HotPink = Color(4290013695u);
Color const Color::IndianRed = Color(4284243149u);
Color const Color::Indigo = Color(4286709835u);
Color const Color::Ivory = Color(4293984255u);
Color const Color::Khaki = Color(4287424240u);
Color const Color::Lavender = Color(4294633190u);
Color const Color::LavenderBlush = Color(4294308095u);
Color const Color::LawnGreen = Color(4278254716u);
Color const Color::LemonChiffon = Color(4291689215u);
Color const Color::LightBlue = Color(4293318829u);
Color const Color::LightCoral = Color(4286611696u);
Color const Color::LightCyan = Color(4294967264u);
Color const Color::LightGoldenrodYellow = Color(4292016890u);
Color const Color::LightGreen = Color(4287688336u);
Color const Color::LightGray = Color(4292072403u);
Color const Color::LightPink = Color(4290885375u);
Color const Color::LightSalmon = Color(4286226687u);
Color const Color::LightSeaGreen = Color(4289376800u);
Color const Color::LightSkyBlue = Color(4294626951u);
Color const Color::LightSlateGray = Color(4288252023u);
Color const Color::LightSteelBlue = Color(4292789424u);
Color const Color::LightYellow = Color(4292935679u);
Color const Color::Lime = Color(4278255360u);
Color const Color::LimeGreen = Color(4281519410u);
Color const Color::Linen = Color(4293325050u);
Color const Color::Magenta = Color(4294902015u);
Color const Color::Maroon = Color(4278190208u);
Color const Color::MediumAquamarine = Color(4289383782u);
Color const Color::MediumBlue = Color(4291624960u);
Color const Color::MediumOrchid = Color(4292040122u);
Color const Color::MediumPurple = Color(4292571283u);
Color const Color::MediumSeaGreen = Color(4285641532u);
Color const Color::MediumSlateBlue = Color(4293814395u);
Color const Color::MediumSpringGreen = Color(4288346624u);
Color const Color::MediumTurquoise = Color(4291613000u);
Color const Color::MediumVioletRed = Color(4286911943u);
Color const Color::MidnightBlue = Color(4285536537u);
Color const Color::MintCream = Color(4294639605u);
Color const Color::MistyRose = Color(4292994303u);
Color const Color::Moccasin = Color(4290110719u);
Color const Color::NavajoWhite = Color(4289584895u);
Color const Color::Navy = Color(4286578688u);
Color const Color::OldLace = Color(4293326333u);
Color const Color::Olive = Color(4278222976u);
Color const Color::OliveDrab = Color(4280520299u);
Color const Color::Orange = Color(4278232575u);
Color const Color::OrangeRed = Color(4278207999u);
Color const Color::Orchid = Color(4292243674u);
Color const Color::PaleGoldenrod = Color(4289390830u);
Color const Color::PaleGreen = Color(4288215960u);
Color const Color::PaleTurquoise = Color(4293848751u);
Color const Color::PaleVioletRed = Color(4287852763u);
Color const Color::PapayaWhip = Color(4292210687u);
Color const Color::PeachPuff = Color(4290370303u);
Color const Color::Peru = Color(4282353101u);
Color const Color::Pink = Color(4291543295u);
Color const Color::Plum = Color(4292714717u);
Color const Color::PowderBlue = Color(4293320880u);
Color const Color::Purple = Color(4286578816u);
Color const Color::Red = Color(4278190335u);
Color const Color::RosyBrown = Color(4287598524u);
Color const Color::RoyalBlue = Color(4292962625u);
Color const Color::SaddleBrown = Color(4279453067u);
Color const Color::Salmon = Color(4285694202u);
Color const Color::SandyBrown = Color(4284523764u);
Color const Color::SeaGreen = Color(4283927342u);
Color const Color::SeaShell = Color(4293850623u);
Color const Color::Sienna = Color(4281160352u);
Color const Color::Silver = Color(4290822336u);
Color const Color::SkyBlue = Color(4293643911u);
Color const Color::SlateBlue = Color(4291648106u);
Color const Color::SlateGray = Color(4287660144u);
Color const Color::Snow = Color(4294638335u);
Color const Color::SpringGreen = Color(4286578432u);
Color const Color::SteelBlue = Color(4290019910u);
Color const Color::Tan = Color(4287411410u);
Color const Color::Teal = Color(4286611456u);
Color const Color::Thistle = Color(4292394968u);
Color const Color::Tomato = Color(4282868735u);
Color const Color::Turquoise = Color(4291878976u);
Color const Color::Violet = Color(4293821166u);
Color const Color::Wheat = Color(4289978101u);
Color const Color::White = Color(4294967295u);
Color const Color::WhiteSmoke = Color(4294309365u);
Color const Color::Yellow = Color(4278255615u);
Color const Color::YellowGreen = Color(4281519514u);