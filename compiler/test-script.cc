#include <iostream>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
	for (int i = 1; i < argc; ++i) {
		string c {argv[i]};
		cout << c << '\n';
	}
}
