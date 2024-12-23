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

// index 查找串t在串s中的位置
int index(SqString s, SqString t) {
    int i = 0;
    int j = 0;
    while (i < s.length && j < t.length) {
        if (s.data[i] == t.data[j]) {
            i++;
            j++;
            continue;
        }
        i = i - j + 1; // i回退到原i的下一个位置
        j = 0;
    }
    if (j < t.length) {
        return 0;
    }
    return i - t.length + 1;
}

// insStr 子串插入运算算法
int insStr(SqString &s, int i, SqString t) {
    // 判断位置参数i输入的正确性
    if (i < 1 || i > s.length + 1 || s.length == MAX_SIZE) {
        return 0;
    }
    // 将s.data[i-1...s.length-1] 往后顺移t.length个位置
    for (int j = s.length - 1; j >= i - 1; j--) {
        s.data[j+t.length] = s.data[j];
    }
    // 最后把t子串插入到原来的主串中
    for (int j = 0; j < t.length; j++) {
        s.data[i+j-1] = t.data[j];
    }
    // 更新串的长度
    s.length += t.length;
    return 1;
}

int delStr(SqString &s, int i , int j) {
    if (i < 1 || i > s.length || j < 1 || i+j > s.length + 1) {
        return 0;
    }
    // 将s的第i+j位置之后的字符串往前移动j位置
    // [i - 1 + j, s.length-1] <- 往前移动j个位置 [i-1, s.length-1-j]
    for (int k = i+j-1; k < s.length; k++) {
        s.data[k-j] = s.data[k];
    }
    s.length -= j; // 更新串的长度
    return 1;
}

// repStrAll 把字符串s中的s1均替换成s2
SqString repStrAll(SqString &s, SqString s1, SqString s2) {
    int i = index(s, s1);
    while (i > 0) {
        delStr(s, i, s1.length);
        insStr(s, i, s2);
        i = index(s, s1);
    }
    return s;
}

// dispStr 输出串
void dispStr(SqString s) {
    for (int i = 0; i < s.length; i++) {
        printf("%c ", s.data[i]);
    }
    printf("\n");
}


void runStr() {
    SqString s1,s2,s3,s4,s5,s6,s7;

    assign(s1, "abcd");
    printf("s1:");
    dispStr(s1);
    printf("s1的长度:%d\n", strLength(s1));

    printf("s1=>s2\n");
    strCopy(s2, s1);
    printf("s2:");
    dispStr(s2);

    printf("s1和s2%s\n", (strEqual(s1, s2) == 1 ? "相同" : "不相同"));
    
    assign(s3, "12345678");
    printf("s3:");
    dispStr(s3);

    printf("s1和s3连接 => s4\n");
    s4 = concat(s1, s3);
    printf("s4:");
    dispStr(s4);

    printf("s3[2..5] => s5\n");
    s5 = subStr(s3, 2, 4);
    printf("s5:");
    dispStr(s5);

    assign(s6, "567");
    printf("s6:");
    dispStr(s6);

    printf("s6 在 s3中的位置:%d\n", index(s3, s6));
    printf("从s3中删除s3[3..6]字符\n");
    delStr(s3, 3, 4);
    printf("s3: ");
    dispStr(s3);

    printf("从s4中将s6替换成s1 => s7\n");
    s7 = repStrAll(s4, s6, s1);
    printf("s7: ");
    dispStr(s7);

    // 清空内存
    destroyStr(s1);
    destroyStr(s2);
    destroyStr(s3);
    destroyStr(s4);
    destroyStr(s5);
    destroyStr(s6);
    destroyStr(s7);

}


// strCmp 字符串比较函数
int strCmp(SqString s, SqString t) {
    int comlen;
    if (s.length < t.length) {
        comlen = s.length;
    } else {
        comlen = t.length;
    }
    for (int i = 0; i < comlen; i++) {
        if (s.data[i] > t.data[i]) {
            return 1;
        } else if (s.data[i] < t.data[i]) {
            return -1;
        }
    }
    if (s.length == t.length) {
        return 0;
    } else if (s.length > t.length) {
        return 1;
    } else {
        return -1;
    }
}

// count 求串t在串s中出现的次数
int count(SqString s, SqString t) {
    int cnt = 0; // 累加值
    int i = 0;
    while (i <= s.length - t.length) {
        int k = 0;
        int j = 0;
        while (j < t.length && s.data[k] == t.data[k]) {
            k++;
            j++;
        }
        if (j == t.length) {
            cnt++;
            i += t.length;
        } else {
            i++;
        }
    }
    return cnt;
}