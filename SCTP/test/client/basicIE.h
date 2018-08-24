#include <list>
#include "blank.h"
class basicIE{
private:
		string basicString;
		std::list<blank> blankList;
		string workspace;
public:
		basicIE(string _basicString);
		basicIE(char* _basicString);
		~basicIE();
		bool changeBlank(string name, string content);
		string getWorkspace();
		void resetWorkspace();
		void addBlank(string name, int offset, int length);
};
