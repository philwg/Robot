#ifndef _TextureCoord_h_
#define _TextureCoord_h_

class TextureCoord
{
public:
	float u, v;

	TextureCoord() {}
	TextureCoord(float u, float v) : u(u), v(v) {}

	TextureCoord operator+(TextureCoord t) {
		return TextureCoord(u+t.u, v+t.v);
	}

	TextureCoord operator-(TextureCoord t) {
		return TextureCoord(u-t.u, v-t.v);
	}

	TextureCoord operator*(float c) {
		return TextureCoord(u*c, v*c);
	}

	TextureCoord operator/(float c) {
		return TextureCoord(u/c, v/c);
	}

	inline friend TextureCoord operator*(float v, TextureCoord t);
};

inline TextureCoord operator*(float v, TextureCoord t)
{
	return t*v;
}

#endif
