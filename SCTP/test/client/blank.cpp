#include "blank.h"

blank::blank(int _offset, int _length, string _name):offset(_offset), length(_length) {
	name = string(_name.c_str());
}
