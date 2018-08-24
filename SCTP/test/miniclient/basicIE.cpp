#include "basicIE.h"
basicIE::basicIE(string _basic) {
	basicString = string(_basic);
}
basicIE::basicIE(char* _basic) {
	basicString = string(_basic);
}
basicIE::~basicIE() {};
bool basicIE::changeBlank(string name, string content) {
	for(list<blank>::iterator iter=blankList.begin(); iter != blankList.end(); iter ++) {
		if(iter->name == name) {
			if(content.length() <= iter->length) {
				int i;
				for(i = 0;i < content.length();i ++)
					workspace[i + iter->offset] = content[i];
				for(;i < iter->length;i ++)
					workspace[i + iter->offset] = 0x00;
				return true;
			}
			else 
				return false;
		}
	}
	return false;
}

string basicIE::getWorkspace() {
	return workspace;
}

void basicIE::resetWorkspace() {
	workspace = string(basicString.c_str());
}

void basicIE::addBlank(string name, int offset, int length) {
	blankList.push_back(blank(offset, length, name));
}
