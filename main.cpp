#include<bits/stdc++.h>
#include"aux.h"
using namespace std;
namespace fs = std::filesystem;
using namespace std;

void RePL() {
    string input;

    while (true) {
        cout<<"Katana> ";
        getline(cin, input);
        if (input=="exit 0") return;
        else if (input.find("echo") !=std::string::npos) cout<<input.substr(5)<<endl;
        else cout<<input<<": invalid command"<<endl;
    }
}

int main() {
    cout<<std::unitbuf;
    cerr<<std::unitbuf;

    drawLogo();

    RePL();

    main();
}