#include <iostream>
#include "TemplateMetaprog.h"

using namespace std;


int main() {
	cout << metaprog::d << endl;
	cout << metaprog::factorial<4>::result << endl;
	metaprog::If< (2 > 1) >::f();

	system("pause"); 
	return 0;
}