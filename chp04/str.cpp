#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef struct {
    char data[MAX_SIZE];
    int length;
} SqString;


// assign 拷贝str到字符串s中
void assign(SqString &s, char str[]) {
    int i = 0;
    while (str[i] != '\0') {
        s.data[i] = str[i];
        i++;
    }
    s.length = i;
}

void destroyStr(SqString s) {
    
}

// strCopy 拷贝字符串
void strCopy(SqString &s, SqString t) {
    int i;
    for (i = 0; i < t.length; i++) {
        s.data[i] = t.data[i];
    }
    s.length = t.length;
}

// strLength 求字符串长度
int strLength(SqString s) {
    return s.length;
}

// strEqual 判断两个字符串是否相同
int strEqual(SqString s, SqString t) {
    if (s.length != t.length) {
        return 0;
    }
    for (int i = 0; i < s.length; i++) {
        if (s.data[i] != t.data[i]) {
            return 0;
        }
    }
    return 1;
}


// concat 将s和t两个字符串拼接而成
SqString concat(SqString s, SqString t) {
    SqString r; 
    r.length = s.length + t.length;
    for (int i = 0; i < s.length; i++) {
        r.data[i] = s.data[i];
    }
    for (int j = 0; j < t.length; j++) {
        r.data[s.length + j] = t.data[j];
    }
    return r;
}

// subStr 返回字符串s,从第i个位置开始的j个字符串
SqString subStr(SqString s, int i, int j) {
    SqString t;
    if (i < 1 || i > s.length || j < 1 || i + j > s.length + 1) {
        t.length = 0;
        return t;
    }
    for (int k = i-1; k < i+j-1; k++) {
        t.data[k-i+1] = s.data[k];
    }
    t.length = j;
    return t;
}

// todo: