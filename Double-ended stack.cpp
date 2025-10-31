#include <stdio.h>
typedef int SElemType;
typedef struct{
	int top[2],bot[2];
	SElemType *V;
	int m; 
}DblStack;
void InitDblStack(DblStack *S, int maxSize) {    //初始化
    S.m = maxSize;
    S.V = new SElemType[maxSize];
    S.top[0] = -1;
    S.bot[0] = 0;
    S.top[1] = maxSize;
    S.bot[1] = maxSize - 1;
}
bool IsEmpty(DblStack *S, int stackNo) {        //判断栈空
    if (stackNo == 0) {
        return S.top[0] == -1;
    } else {
        return S.top[1] == S.m;
    }
}
bool IsFull(DblStack *S) {
    return S.top[0] + 1 == S.top[1];           //判断栈满
}
bool Push(DblStack *S, SElemType e, int stackNo) {
    if (IsFull(S)) {                           //进栈
        return false; // 栈满，进栈失败
    }
    if (stackNo == 0) {
        S.V[++S.top[0]] = e;
    } else {
        S.V[--S.top[1]] = e;
    }
    return true;
}
bool Pop(DblStack *S, SElemType e, int stackNo) {
    if (IsEmpty(S, stackNo)) {                 //出栈
        return false; // 栈空，出栈失败
    }
    if (stackNo == 0) {
        e = S.V[S.top[0]--];
    } else {
        e = S.V[S.top[1]++];
    }
    return true;
}
int main(){
	DblStack Stack;
	InitDblStack(&Stack,10);
	Push(&Stack, SElemType e,10);
}






















#include <stdio.h>
#include <stdlib.h>

// 定义栈元素类型为整型
typedef int SElemType;

// 双栈结构定义
typedef struct {
    SElemType *V;        // 存储两个栈的数组
    int top[2];          // top[0]和top[1]分别是两个栈的栈顶指针
    int m;               // 数组的总容量
} DblStack;

// 1. 初始化双栈
void InitDblStack(DblStack *S, int maxSize) {
    S->m = maxSize;
    S->V = (SElemType *)malloc(maxSize * sizeof(SElemType));
    if (S->V == NULL) {
        printf("内存分配失败！\n");
        exit(1); // 分配失败则退出程序
    }
    S->top[0] = -1;      // 栈0的栈顶指针初始化为-1，表示为空
    S->top[1] = maxSize; // 栈1的栈顶指针初始化为maxSize，表示为空
}

// 2. 判断指定栈是否为空
int IsEmpty(DblStack S, int stackNo) {
    if (stackNo == 0) {
        return S.top[0] == -1;
    } else {
        return S.top[1] == S.m;
    }
}

// 3. 判断双栈是否已满
int IsFull(DblStack S) {
    // 当两个栈的栈顶指针相邻时，表示栈已满
    return S.top[0] + 1 == S.top[1];
}

// 4. 进栈操作
int Push(DblStack *S, SElemType e, int stackNo) {
    if (IsFull(*S)) {
        printf("双栈已满，无法将元素 %d 压入栈 %d！\n", e, stackNo);
        return 0; // 进栈失败
    }
    if (stackNo == 0) {
        // 栈0从左向右增长
        S->V[++(S->top[0])] = e;
    } else {
        // 栈1从右向左增长
        S->V[--(S->top[1])] = e;
    }
    return 1; // 进栈成功
}

// 5. 出栈操作
int Pop(DblStack *S, SElemType *e, int stackNo) {
    if (IsEmpty(*S, stackNo)) {
        printf("栈 %d 为空，无法出栈！\n", stackNo);
        return 0; // 出栈失败
    }
    if (stackNo == 0) {
        *e = S->V[(S->top[0])--];
    } else {
        *e = S->V[(S->top[1])++];
    }
    return 1; // 出栈成功
}

// 辅助函数：打印双栈当前状态
void PrintStacks(DblStack S) {
    printf("\n当前双栈状态:\n");
    printf("栈0 (底 -> 顶): ");
    if (IsEmpty(S, 0)) {
        printf("(空)");
    } else {
        for (int i = 0; i <= S.top[0]; i++) {
            printf("%d ", S.V[i]);
        }
    }
    printf("\n栈1 (底 -> 顶): ");
    if (IsEmpty(S, 1)) {
        printf("(空)");
    } else {
        for (int i = S.m - 1; i >= S.top[1]; i--) {
            printf("%d ", S.V[i]);
        }
    }
    printf("\n\n");
}


int main() {
    DblStack myDblStack;
    int maxSize = 20; // 设定足够大的容量以避免栈满
    InitDblStack(&myDblStack, maxSize);

    SElemType pushNums[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    SElemType poppedValue;

    // --- 进栈操作 ---
    printf("--- 开始进栈 10 个元素 ---\n");
    for (int i = 0; i < 10; i++) {
        int stackNo = (i < 5) ? 0 : 1; // 前5个进栈0，后5个进栈1
        Push(&myDblStack, pushNums[i], stackNo);
        printf("已将元素 %d 压入栈 %d\n", pushNums[i], stackNo);
    }
    
    // 打印进栈后的状态
    PrintStacks(myDblStack);

    // --- 出栈操作 ---
    printf("--- 开始出栈 4 个元素 ---\n");
    // 从栈0出栈2个
    for (int i = 0; i < 2; i++) {
        if (Pop(&myDblStack, &poppedValue, 0)) {
            printf("从栈 0 弹出元素: %d\n", poppedValue);
        }
    }
    // 从栈1出栈2个
    for (int i = 0; i < 2; i++) {
        if (Pop(&myDblStack, &poppedValue, 1)) {
            printf("从栈 1 弹出元素: %d\n", poppedValue);
        }
    }

    // 打印出栈后的最终状态
    PrintStacks(myDblStack);

    // 释放动态分配的内存
    free(myDblStack.V);

    return 0;

}
