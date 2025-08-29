//#pragma once
//#ifndef GENERAL_UTILS_H
//#endif
#include<cstdlib>
#include<pwd.h>
#include<unistd.h>
#include<iostream>
#include<linux/limits.h>
#include<errno.h>
#include<dirent.h>
using namespace std;

void get_user() {
    uid_t uid = geteuid();
    struct passwd *pw = getpwuid(uid);

    cout<<pw->pw_name<<endl;
}

void get_current_dir() {
    char cwd[PATH_MAX];
    getcwd(cwd, sizeof(cwd));
    cout<<cwd<<endl;
}

int get_current_dir_contents() {
    struct dirent **dir_entries;
    int n = scandir(".", &dir_entries, NULL, alphasort);

    if (n == -1) {
        perror("Error scanning the working tree");
    }

    for (int i=0; i<n; i++) {
        cout<<dir_entries[i]->d_name<<endl;
        free(dir_entries[i]);
    }
    free(dir_entries);
}

int main() {
    get_user();
    get_current_dir();
    get_current_dir_contents();
}