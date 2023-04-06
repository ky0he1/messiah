// int sum(int a, int b) {
//     int sum = 0;
//     goto cond;
// loop:
//     sum += a;
//     a++;
// cond:
//     if (a <= b) {
//         goto loop;
//     }
//     return sum;
// }

// int main(void) { return sum(1, 10); }

int sum(int a, int b) {
    int sum;
    sum = 0;
    while (a <= b) {
        sum += a;
        a++;
    }
    return sum;
}

int main(void) { return sum(1, 10); }
