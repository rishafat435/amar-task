#include <conio.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>

#define PI 3.14159265358979323846
#define E 2.71828182845904523536
#define file "userdata.bin"
#define clear printf("\033[2J\033[1;1H")
#define logicalc                                                               \
    printf("\n _                _              _       \n| |  ___    __ _ "    \
           "(_)  ___  __ _ | |    ___ \n| | / _ \\  / _` || | / __|/ _` || | " \
           "  / __|\n| || (_) || (_| || || (__| (_| || | _| (__ \n|_| \\___/ " \
           " \\__, ||_| \\___|\\__,_||_|(_)\\___|\n           |___/ \n")
#define HOME                                                                   \
    printf("\n+------------+\n|%12s|\n|    %-8s|\n|%12s|\n+------------+\n",   \
           "", "HOME", "")
#define LOGIN                                                                  \
    printf("\n+-------------+\n|%13s|\n|    %-9s|\n|%13s|\n+-------------+\n", \
           "", "LOGIN", "")
#define DELETE                                                                 \
    printf("\n+------------------------+\n|%24s|\n|    "                       \
           "%-20s|\n|%24s|\n+------------------------+\n",                     \
           "", "ACCOUNT DELETION", "")
#define REGISTER                                                               \
    printf("\n+------------------------+\n|%24s|\n|    "                       \
           "%-20s|\n|%24s|\n+------------------------+\n",                     \
           "", "ACCOUNT REGISTER", "")
#define EXIT                                                                   \
    printf("\n+------------+\n|%12s|\n|    %-8s|\n|%12s|\n+------------+\n",   \
           "", "EXIT", "")
#define buffer while (getchar() != '\n')
#define button                                                                 \
    printf("\nType 'back' or 'home' or 'exit' at any point to cancel \nand "   \
           "return previous page or to go back home page or to exit.\n")
#define HEAD header(head)
#define INSTRUCTIONS Instructions()

typedef struct {
    int id;
    char name[128];
    char pass[64];
    int set[2];
    char in[10][512];
    char out[10][128];
    char f[128];
    char g[128];
    char h[128];
} user;

user uid[64] = {0};
user mem = {0};
int current;
FILE *data = NULL;
int usernumb = 0;
char low[128];
char head[128];

void space(char a[], int *m);
void ntrim(char a[]);
void format(char a[], int *m);
void constant(char a[], int *m);
void validate(char a[], int *m);
void bracket(char a[], int *m);
void calc(char a[], int *m);
void right(char a[], char b[], double *v, int n, int *m);
void left(char a[], char b[], double *v, int n, int *m);
double degree(double v);
double radian(double v);
void trim(char a[]);
void F(char a[], int n, int *m);
void G(char a[], int n, int *m);
void H(char a[], int n, int *m);
void CALC_FUNCTION(char a[], float v, int *m);
void SIN(char a[], int n, int *m);
void COS(char a[], int n, int *m);
void TAN(char a[], int n, int *m);
void CSC(char a[], int n, int *m);
void SEC(char a[], int n, int *m);
void COT(char a[], int n, int *m);
void ASIN(char a[], int n, int *m);
void ACOS(char a[], int n, int *m);
void ATAN(char a[], int n, int *m);
void ACSC(char a[], int n, int *m);
void ASEC(char a[], int n, int *m);
void ACOT(char a[], int n, int *m);
void SQROOT(char a[], int n, int *m);
void CBROOT(char a[], int n, int *m);
void LOG(char a[], int n, int *m);
void LN(char a[], int n, int *m);
void FACTORIAL(char a[], int n, int *m);
void POWER(char a[], int n, int *m);
void NCR(char a[], int n, int *m);
void NPR(char a[], int n, int *m);
void C_PI(char a[], int n, int *m);
void C_E(char a[], int n, int *m);
void DIVIDE(char a[], int n, int *m);
void MULTIPLY(char a[], int n, int *m);
void ADD(char a[], int n, int *m);
void ARITHMETICS(char a[], int *m);
void OUTPUT(char a[], int *m);
void nfile();
void lfile();
void wfile();
void Home();
void Exit();
void Register();
void Delete();
void Login();
void Logged();
void Settings();
int match(char a[]);
void search(char a[]);
int found(char a[]);
int chkspc(char a[]);
void lcase(char a[]);
void mask(char a[]);
void header(char a[]);
void Calculator();
void Sci_Calc();
void Instructions();
void Update(char a[], char b[]);
void History();
void Function();
void Evaluate();
double deg(double v);

void main() {
    nfile();
    Home();
}

void space(char a[], int *m) {
    int i, j = 0;
    for (i = 0; a[i] != '\0'; i++)
        if (a[i] != ' ')
            a[j++] = a[i];
    a[j] = '\0';
    if (a[1] == '\0')
        *m = 1;
    ntrim(a);
}

void ntrim(char a[]) {
    int i;
    for (i = 0; a[i] != '\0'; i++)
        if (a[i] == '\n')
            a[i] = '\0';
}

void format(char a[], int *m) {
    int n = 32, i, j, k, l, p, q, r, x, y, z, f;
    char b[512], *pos, *t;
    char *d[32] = {
        "sin", "cos", "tan",  "csc",  "sec",  "cot", "csc", "sec",
        "cot", "cbr", "sini", "cosi", "tani", "log", "ln",  "pi",
        "(",   "log", "ln",   "e",    "f",    "g",   "h",
    };

    char *c[32] = {")", "!"};

    for (i = 0; i < 2; i++)
        if (c[i] != NULL) {
            t = a;
            strcpy(b, a);
            while ((pos = strstr(t, c[i])) != NULL && c[i] != NULL) {
                if (a[(p = pos - a) + 2] != '\0' &&
                    !(strchr("!)-+*/^", a[p + 1])) &&
                    !(a[p + 1] == 'c' && (a[p + 2] != 'o' && a[p + 2] != 's' &&
                                          a[p + 2] != 'b')) &&
                    (a[p + 1] != 'p' || (a[p + 1] == 'p' && a[p + 2] == 'i'))) {
                    a[p + 1] = '*';
                    strcpy(a + p + 2, b + p + 1);
                    t = a + p + strlen(c[i]);
                    strcpy(b, a);
                } else
                    t++;
            }
        }

    for (i = 0; i < n; i++)
        if (d[i] != NULL) {
            t = a;
            strcpy(b, a);
            while ((pos = strstr(t, d[i])) != NULL && d[i] != NULL) {
                if (isdigit(a[(p = pos - a) - 1])) {
                    a[p] = '*';
                    strcpy(a + p + 1, b + p);
                    t = a + p + strlen(d[i]);
                    strcpy(b, a);
                } else
                    t++;
            }
        }

    for (i = 0; a[i] != '\0'; i++) {
        strcpy(b, a);
        if (((i > 0 && a[i] == 'i' && a[i - 1] == 'p') ||
             (a[i] == 'e' && a[i - 1] != 's' && a[i + 1] != 'c')) &&
            a[i + 1] != '\0' && !(strchr("!)-+*/^", a[i + 1])) &&
            (a[p + 1] != 'p' || (a[p + 1] == 'p' && a[p + 2] == 'i'))) {
            a[i + 1] = '*';
            strcpy(a + i + 2, b + i + 1);
            t = a + p + strlen(c[i]);
            strcpy(b, a);
        }
    }
}

void validate(char a[], int *m) {
    int i, j, k, p = 0, q = 0, r, f, x = 0, y = 0;
    char b[512];

    for (i = 0; a[i] != '\0'; i++) {
        if (a[i] == '(') {
            p++;
            x = i;
        }
        if (a[i] == ')') {
            q++;
            y = i;
        }
    }

    if (p == 0 && q == 0)
        calc(a, m);

    else if (p != q || x > y)
        *m = 1;

    for (i = 0; a[i]; i++)
        if (a[i] == '=')
            *m = 1;

        else if (*m != 1)
            bracket(a, m);
}

void bracket(char a[], int *m) {
    char b[512], t[512];
    int i, j, k, p = 0, q = 0, r, f, x, y, c = 0;

    for (i = 0; a[i] != '\0'; i++)
        if (a[i] == '(') {
            p = i;
            c++;
        }

    if (c == 0)
        calc(a, m);

    else {
        f = 1;
        for (i = p + 1; a[i] != '\0'; i++)
            if (a[i] == ')' && i != p + 1) {
                f = 0;
                break;
            }

        if (f == 1)
            *m = 1;

        if (*m != 1) {
            q = i;
            strcpy(t, a);
            strncpy(b, a + p + 1, q - p - 1);
            b[q - p - 1] = '\0';
            calc(b, m);
            if (*m != 1) {
                strcpy(a + p, b);
                strcpy(a + p + strlen(b), t + q + 1);
                bracket(a, m);
            }
        }
    }
}

void calc(char a[], int *m) {
    char b[512], *pos, *t;
    char *f1[32] = {"^", "c", "p"};
    char *f2[32] = {"sini", "cosi", "tani", "csci", "seci", "coti", "sin",
                    "cos",  "tan",  "csc",  "sec",  "cot",  "sqr",  "cbr",
                    "log",  "ln",   "f",    "g",    "h"};
    int n = 32, i, j, k, l, p, q, r, c, x, y, z, flag1, flag2;

    for (i = 0; i <= strlen(a) - 1 && *m != 1; i++)
        if (a[i] == '!') {
            FACTORIAL(a, i, m);
            i = 0;
        }

    t = a + strlen(a) - 1;
    while (t >= a) {
        flag1 = 0;
        for (i = 0; i < n; i++) {
            if (f1[i] != NULL)
                if (strstr(a, f1[i]) != NULL)
                    if ((pos = strstr(t, f1[i])) != NULL) {
                        flag1 = 1;
                        p = pos - a;
                        switch (i) {
                        case 0:
                            POWER(a, p, m);
                            break;
                        case 1:
                            NCR(a, p, m);
                            break;
                        case 2:
                            NPR(a, p, m);
                            break;
                        case 3:
                            break;
                        case 4:
                            break;
                        case 5:
                            break;
                        case 6:
                            break;
                        case 7:
                            break;
                        case 8:
                            break;
                        case 9:
                            break;
                        case 10:
                        default:
                            break;
                        }
                        t = a + strlen(a) - 1;
                        if (*m == 1)
                            break;
                    }
            if (*m == 1)
                break;
        }

        flag2 = 0;
        for (i = 0; i < n; i++) {
            if (f2[i] != NULL)
                if (strstr(a, f2[i]) != NULL)
                    if ((pos = strstr(t, f2[i])) != NULL) {
                        flag2 = 1;
                        p = pos - a;
                        switch (i) {
                        case 0:
                            ASIN(a, p, m);
                            break;
                        case 1:
                            ACOS(a, p, m);
                            break;
                        case 2:
                            ATAN(a, p, m);
                            break;
                        case 3:
                            ACSC(a, p, m);
                            break;
                        case 4:
                            ASEC(a, p, m);
                            break;
                        case 5:
                            ACOT(a, p, m);
                            break;
                        case 6:
                            SIN(a, p, m);
                            break;
                        case 7:
                            COS(a, p, m);
                            break;
                        case 8:
                            TAN(a, p, m);
                            break;
                        case 9:
                            CSC(a, p, m);
                            break;
                        case 10:
                            SEC(a, p, m);
                            break;
                        case 11:
                            COT(a, p, m);
                            break;
                        case 12:
                            SQROOT(a, p, m);
                            break;
                        case 13:
                            CBROOT(a, p, m);
                            break;
                        case 14:
                            LOG(a, p, m);
                            break;
                        case 15:
                            LN(a, p, m);
                            break;
                        case 16:
                            F(a, p, m);
                            break;
                        case 17:
                            G(a, p, m);
                            break;
                        case 18:
                            H(a, p, m);
                            break;
                        case 19:
                            break;
                        case 20:
                            break;
                        case 21:
                            break;
                        case 22:
                            break;
                        case 23:
                            break;
                        case 24:
                            break;
                        case 25:
                            break;
                        case 26:
                            break;
                        case 27:
                            break;
                        case 28:
                            break;
                        case 29:
                            break;
                        case 30:
                            break;
                        case 31:
                            break;
                        default:
                            break;
                        }
                        t = a + strlen(a) - 1;
                        if (*m == 1)
                            break;
                    }
            if (*m == 1)
                break;
        }

        if (*m == 1)
            break;
        if (flag1 == 0 && flag2 == 0)
            t--;
    }
    ARITHMETICS(a, m);
}

void right(char a[], char b[], double *v, int n, int *m) {
    int p = n + 1, q, r, x, y, z, t, i, j, k;

    if (a[n + 1] == '-') {
        for (i = n + 2; isdigit(a[i]); i++)
            p = i;
        if (a[p + 1] == '.')
            for (i = p + 2; isdigit(a[i]); i++)
                p = i;
        if (a[i] == '.')
            *m = 1;
        if (*m != 1) {
            strncpy(b, a + n + 1, p - n);
            b[p - n] = '\0';
            *v = atof(b);
        }
    }

    else if (a[n + 1] == '.') {
        for (i = n + 2; isdigit(a[i]); i++)
            p = i;
        if (a[i] == '.')
            *m = 1;
        if (*m != 1) {
            strncpy(b, a + n + 1, p - n);
            b[p - n] = '\0';
            *v = atof(b);
        }
    }

    else if (isdigit(a[n + 1])) {

        for (i = n + 2; isdigit(a[i]); i++)
            p = i;

        if (a[p + 1] == '.')
            for (i = p + 2; isdigit(a[i]); i++)
                p = i;

        if (a[i] == '.')
            *m = 1;

        if (*m != 1) {
            strncpy(b, a + n + 1, p - n);
            b[p - n] = '\0';
            *v = atof(b);
        }
    }

    else
        *m = 1;
}

void left(char a[], char b[], double *v, int n, int *m) {
    int p = n - 1, q, r, x, y, z, t, i, j, k;

    if (isdigit(a[n - 1])) {
        for (i = n - 2; isdigit(a[i]); i--)
            p = i;
        if (a[p - 1] == '.')
            for (i = p - 2; isdigit(a[i]); i--)
                p = i;
        if (a[p - 1] == '.')
            *m = 1;
        if (a[p - 1] == '-' && *m != 1)
            p = p - 1;
        if (a[i] == '.')
            *m = 1;
        if (*m != 1) {
            strncpy(b, a + p, n - p);
            b[n - p] = '\0';
            *v = atof(b);
        }
    }

    else
        *m = 1;
}

double degree(double v) {
    if (uid[current].set[0] == 2)
        return v * PI / 180;
    return v;
}

double radian(double v) {
    if (uid[current].set[0] == 2)
        return v * 180 / PI;
    return v;
}

void trim(char a[]) {
    int i, j, k;
    for (i = 0; a[i]; i++)
        if (a[i] == '.')
            break;
    if (a[i] != '\0') {
        i = strlen(a) - 1;
        while (a[i] == '0' && i > 0)
            i--;
        if (a[i] == '.')
            i--;
        a[i + 1] = '\0';
    }
}

void F(char a[], int n, int *m) {
    int p, q, i, j, k;
    double v, r;
    char b[512], t[512], c[512], d[512];
    if (uid[current].f[0] == '\0')
        *m = 1;
    else {
        strcpy(t, a);
        right(a, b, &v, n, m);

        j = 0;
        for (i = 0; uid[current].f[i]; i++) {
            if (uid[current].f[i] == 'x')
                for (k = 0; b[k]; k++)
                    c[j++] = b[k];
            else
                c[j++] = uid[current].f[i];
        }
        c[j] = '\0';

        calc(c, m);
        if (*m != 1) {
            trim(c);
            strcpy(a + n, c);
            strcpy(a + n + strlen(c), t + n + 1 + strlen(b));
        }
    }
}

void G(char a[], int n, int *m) {
    if (a[n - 1] == 'o' && a[n - 2] == 'l')
        LOG(a, n - 2, m);
    else {
        int p, q, i, j, k;
        double v, r;
        char b[512], t[512], c[512], d[512];
        if (uid[current].g[0] == '\0')
            *m = 1;
        else {
            strcpy(t, a);
            right(a, b, &v, n, m);

            j = 0;
            for (i = 0; uid[current].g[i]; i++) {
                if (uid[current].g[i] == 'x')
                    for (k = 0; b[k]; k++)
                        c[j++] = b[k];
                else
                    c[j++] = uid[current].g[i];
            }
            c[j] = '\0';

            calc(c, m);
            if (*m != 1) {
                trim(c);
                strcpy(a + n, c);
                strcpy(a + n + strlen(c), t + n + 1 + strlen(b));
            }
        }
    }
}

void H(char a[], int n, int *m) {
    int p, q, i, j, k;
    double v, r;
    char b[512], t[512], c[512], d[512];
    if (uid[current].h[0] == '\0')
        *m = 1;
    else {
        strcpy(t, a);
        right(a, b, &v, n, m);

        j = 0;
        for (i = 0; uid[current].h[i]; i++) {
            if (uid[current].h[i] == 'x')
                for (k = 0; b[k]; k++)
                    c[j++] = b[k];
            else
                c[j++] = uid[current].h[i];
        }
        c[j] = '\0';

        calc(c, m);
        if (*m != 1) {
            trim(c);
            strcpy(a + n, c);
            strcpy(a + n + strlen(c), t + n + 1 + strlen(b));
        }
    }
}

void CALC_FUNCTION(char a[], float v, int *m) {
    int p, q, i, j, k, n;
    char b[512], t[512], c[512], d[512];
    sprintf(b, "%.15f", v);
    trim(b);

    j = 0;
    for (i = 0; a[i]; i++) {
        if (a[i] == 'x')
            for (k = 0; b[k]; k++)
                t[j++] = b[k];
        else
            t[j++] = a[i];
    }
    t[j] = '\0';
    strcpy(a, t);
    calc(a, m);
}

void SIN(char a[], int n, int *m) {
    int p, q;
    char b[512], t[512], c[512];
    strcpy(t, a);
    double v, r;
    right(a, b, &v, n + 2, m);
    if (*m != 1) {
        r = sin(degree(v));
        sprintf(c, "%.15lf", r);
        trim(c);
        strcpy(a + n, c);
        strcpy(a + n + strlen(c), t + n + 3 + strlen(b));
    }
}

void COS(char a[], int n, int *m) {
    int p, q;
    char b[512], t[512], c[512];
    strcpy(t, a);
    double v, r;
    right(a, b, &v, n + 2, m);
    if (*m != 1) {
        r = cos(degree(v));
        sprintf(c, "%.15lf", r);
        trim(c);
        strcpy(a + n, c);
        strcpy(a + n + strlen(c), t + n + 3 + strlen(b));
    }
}

void TAN(char a[], int n, int *m) {
    int p, q, w;
    char b[512], t[512], c[512];
    strcpy(t, a);
    double v, r;
    right(a, b, &v, n + 2, m);

    w = deg(v);
    if (w == (int)w && (int)w % 90 == 0)
        *m = 1;
    if (*m != 1) {
        r = tan(degree(v));
        sprintf(c, "%.15lf", r);
        trim(c);
        strcpy(a + n, c);
        strcpy(a + n + strlen(c), t + n + 3 + strlen(b));
    }
}

void CSC(char a[], int n, int *m) {
    int p, q;
    double w;
    char b[512], t[512], c[512];
    strcpy(t, a);
    double v, r;
    right(a, b, &v, n + 2, m);

    w = deg(v);
    if (w == (int)w && (int)w % 180 == 0)
        *m = 1;
    if (*m != 1) {
        r = 1 / (sin(degree(v)));
        sprintf(c, "%.15lf", r);
        trim(c);
        strcpy(a + n, c);
        strcpy(a + n + strlen(c), t + n + 3 + strlen(b));
    }
}

void SEC(char a[], int n, int *m) {
    int p, q;
    double w;
    char b[512], t[512], c[512];
    strcpy(t, a);
    double v, r;
    right(a, b, &v, n + 2, m);

    w = deg(v);
    if (w == (int)w && (int)w % 90 == 0 && ((int)w / 90) % 2 != 0)
        *m = 1;
    if (*m != 1) {
        r = 1 / (cos(degree(v)));
        sprintf(c, "%.15lf", r);
        trim(c);
        strcpy(a + n, c);
        strcpy(a + n + strlen(c), t + n + 3 + strlen(b));
    }
}

void COT(char a[], int n, int *m) {
    int p, q;
    double w;
    char b[512], t[512], c[512];
    strcpy(t, a);
    double v, r;
    right(a, b, &v, n + 2, m);

    w = deg(v);
    if (w == (int)w && (int)w % 180 == 0)
        *m = 1;
    if (*m != 1) {
        r = 1 / (tan(degree(v)));
        sprintf(c, "%.15lf", r);
        trim(c);
        strcpy(a + n, c);
        strcpy(a + n + strlen(c), t + n + 3 + strlen(b));
    }
}

void ASIN(char a[], int n, int *m) {
    int p, q;
    char b[512], t[512], c[512];
    strcpy(t, a);
    double v, r;
    right(a, b, &v, n + 3, m);
    if (v > 1 || v < -1)
        *m = 1;
    if (*m != 1) {
        r = asin(v);
        r = radian(r);
        sprintf(c, "%.15lf", r);
        trim(c);
        strcpy(a + n, c);
        strcpy(a + n + strlen(c), t + n + 4 + strlen(b));
    }
}

void ACOS(char a[], int n, int *m) {
    int p, q;
    char b[512], t[512], c[512];
    strcpy(t, a);
    double v, r;
    right(a, b, &v, n + 3, m);
    if (v > 1 || v < -1)
        *m = 1;
    if (*m != 1) {
        r = acos(v);
        r = radian(r);
        sprintf(c, "%.15lf", r);
        trim(c);
        strcpy(a + n, c);
        strcpy(a + n + strlen(c), t + n + 4 + strlen(b));
    }
}

void ATAN(char a[], int n, int *m) {
    int p, q;
    char b[512], t[512], c[512];
    strcpy(t, a);
    double v, r;
    right(a, b, &v, n + 3, m);
    if (*m != 1) {
        r = atan(v);
        r = radian(r);
        sprintf(c, "%.15lf", r);
        trim(c);
        strcpy(a + n, c);
        strcpy(a + n + strlen(c), t + n + 4 + strlen(b));
    }
}

void ACSC(char a[], int n, int *m) {
    int p, q;
    char b[512], t[512], c[512];
    strcpy(t, a);
    double v, r;
    right(a, b, &v, n + 3, m);
    if (v < 1 && v > -1)
        *m = 1;
    if (*m != 1) {
        r = asin(1 / v);
        r = radian(r);
        sprintf(c, "%.15lf", r);
        trim(c);
        strcpy(a + n, c);
        strcpy(a + n + strlen(c), t + n + 4 + strlen(b));
    }
}

void ASEC(char a[], int n, int *m) {
    int p, q;
    char b[512], t[512], c[512];
    strcpy(t, a);
    double v, r;
    right(a, b, &v, n + 3, m);
    if (v < 1 && v > -1)
        *m = 1;
    if (*m != 1) {
        r = acos(1 / v);
        r = radian(r);
        sprintf(c, "%.15lf", r);
        trim(c);
        strcpy(a + n, c);
        strcpy(a + n + strlen(c), t + n + 4 + strlen(b));
    }
}

void ACOT(char a[], int n, int *m) {
    int p, q;
    char b[512], t[512], c[512];
    strcpy(t, a);
    double v, r;
    right(a, b, &v, n + 3, m);
    if (*m != 1) {
        r = atan(1 / v);
        r = radian(r);
        sprintf(c, "%.15lf", r);
        trim(c);
        strcpy(a + n, c);
        strcpy(a + n + strlen(c), t + n + 4 + strlen(b));
    }
}

void SQROOT(char a[], int n, int *m) {
    int p, q;
    char b[512], t[512], c[512];
    strcpy(t, a);
    double v, r;
    right(a, b, &v, n + 2, m);
    if (v < 0)
        *m = 1;
    if (*m != 1) {
        r = sqrt(v);
        sprintf(c, "%.15lf", r);
        trim(c);
        strcpy(a + n, c);
        strcpy(a + n + strlen(c), t + n + 3 + strlen(b));
    }
}

void CBROOT(char a[], int n, int *m) {
    int p, q;
    char b[512], t[512], c[512];
    strcpy(t, a);
    double v, r;
    right(a, b, &v, n + 2, m);
    if (*m != 1) {
        r = cbrt(v);
        sprintf(c, "%.15lf", r);
        trim(c);
        strcpy(a + n, c);
        strcpy(a + n + strlen(c), t + n + 3 + strlen(b));
    }
}

void LOG(char a[], int n, int *m) {
    int p, q;
    char b[512], t[512], c[512];
    strcpy(t, a);
    double v, r;
    right(a, b, &v, n + 2, m);
    if (v <= 0)
        *m = 1;
    if (*m != 1) {
        r = log10(v);
        sprintf(c, "%.15lf", r);
        trim(c);
        strcpy(a + n, c);
        strcpy(a + n + strlen(c), t + n + 3 + strlen(b));
    }
}

void LN(char a[], int n, int *m) {
    int p, q;
    char b[512], t[512], c[512];
    strcpy(t, a);
    double v, r;
    right(a, b, &v, n + 1, m);
    if (v <= 0)
        *m = 1;
    if (*m != 1) {
        r = log(v);
        sprintf(c, "%.15lf", r);
        trim(c);
        strcpy(a + n, c);
        strcpy(a + n + strlen(c), t + n + 2 + strlen(b));
    }
}

void FACTORIAL(char a[], int n, int *m) {
    int p, q;
    char b[512], t[512], c[512];
    strcpy(t, a);
    double v, r;
    left(a, b, &v, n, m);
    if (v != (int)v || v > 25)
        *m = 1;

    if (*m != 1) {
        if (v >= 0) {
            r = tgamma(v + 1);
            sprintf(c, "%.15lf", r);
            trim(c);
            strcpy(a + n - strlen(b), c);
            strcpy(a + n + strlen(c) - strlen(b), t + n + 1);
        }

        else {
            {
                v = -1 * v;
                r = -1 * tgamma(v + 1);
                sprintf(c, "%.15lf", r);
                trim(c);
                strcpy(a + n - strlen(b), c);
                strcpy(a + n + strlen(c) - strlen(b), t + n + 1);
            }
        }
    }
}

void POWER(char a[], int n, int *m) {
    int p, q;
    char b[512], t[512], c[512], d[512];
    strcpy(t, a);
    double v, w, r;
    left(a, b, &v, n, m);
    right(a, d, &w, n, m);
    if (w > 25)
        *m = 1;
    if (*m != 1) {
        r = pow(v, w);
        if (n - strlen(b) != 0 && b[0] == '-' && r >= 0)
            sprintf(c, "+%.15lf", r);
        else
            sprintf(c, "%.15lf", r);
        trim(c);
        strcpy(a + n - strlen(b), c);
        strcpy(a + n - strlen(b) + strlen(c), t + n + 1 + strlen(d));
    }
}

void NCR(char a[], int n, int *m) {
    int p, q;
    char b[512], t[512], c[512], d[512];

    if (a[n + 1] == 'o' && a[n + 2] == 's' && a[n + 3] == 'i')
        ACOS(a, n, m);
    else if (a[n + 1] == 'o' && a[n + 2] == 't' && a[n + 3] == 'i')
        ACOT(a, n, m);
    else if (n >= 2 && a[n + 1] == 'i' && a[n - 1] == 's' && a[n - 2] == 'c')
        ACSC(a, n - 2, m);
    else if (n >= 2 && a[n + 1] == 'i' && a[n - 1] == 'e' && a[n - 2] == 's')
        ASEC(a, n - 2, m);
    else if (a[n + 1] == 'o' && a[n + 2] == 's')
        COS(a, n, m);
    else if (a[n + 1] == 'o' && a[n + 2] == 't')
        COT(a, n, m);
    else if (a[n - 1] == 's' && a[n - 2] == 'c')
        CSC(a, n - 2, m);
    else if (a[n - 1] == 'e' && a[n - 2] == 's')
        SEC(a, n - 2, m);
    else if (a[n + 1] == 'b' && a[n + 2] == 'r')
        CBROOT(a, n, m);

    else {
        strcpy(t, a);
        double v, w, r;
        left(a, b, &v, n, m);
        right(a, d, &w, n, m);
        if (w > 25 || v > 25 || v < 0 || w < 0 || v < w || v != (int)v ||
            w != (int)w)
            *m = 1;
        if (*m != 1) {
            r = tgamma(v + 1) / (tgamma(w + 1) * tgamma(v - w + 1));
            sprintf(c, "%.15lf", r);
            trim(c);
            strcpy(a + n - strlen(b), c);
            strcpy(a + n - strlen(b) + strlen(c), t + n + 1 + strlen(d));
        }
    }
}

void NPR(char a[], int n, int *m) {
    int p, q;
    char b[512], t[512], c[512], d[512];
    strcpy(t, a);
    double v, w, r;
    left(a, b, &v, n, m);
    right(a, d, &w, n, m);
    if (w > 25 || v > 25 || v < 0 || w < 0 || v < w || v != (int)v ||
        w != (int)w)
        *m = 1;
    if (*m != 1) {
        r = tgamma(v + 1) / tgamma(v - w + 1);
        sprintf(c, "%.15lf", r);
        trim(c);
        strcpy(a + n - strlen(b), c);
        strcpy(a + n - strlen(b) + strlen(c), t + n + 1 + strlen(d));
    }
}

void C_PI(char a[], int n, int *m) {
    int p, q;
    char b[512], t[512], c[512];
    strcpy(t, a);
    double v, r;
    if (m != 1) {
        r = PI;
        sprintf(c, "%.15lf", r);
        trim(c);
        strcpy(a + n, c);
        strcpy(a + n + strlen(c), t + n + 2);
    }
}

void C_E(char a[], int n, int *m) {
    if (n > 0 && a[n + 1] == 'c' && a[n + 2] == 'i' && a[n - 1] == 's')
        ASEC(a, n - 1, m);
    else if (n > 0 && a[n + 1] == 'c' && a[n - 1] == 's')
        SEC(a, n - 1, m);
    else {
        int p, q;
        char b[512], t[512], c[512];
        strcpy(t, a);
        double v, r;
        if (m != 1) {
            r = E;
            sprintf(c, "%.15lf", r);
            trim(c);
            strcpy(a + n, c);
            strcpy(a + n + strlen(c), t + n + 1);
        }
    }
}

void DIVIDE(char a[], int n, int *m) {
    int p, q;
    char b[512], t[512], c[512], d[512];
    strcpy(t, a);
    double v, w, r;
    left(a, b, &v, n, m);
    right(a, d, &w, n, m);
    if (w == 0)
        *m = 1;
    if (*m != 1) {
        r = v / w;
        if (n - strlen(b) != 0 && b[0] == '-' && d[0] == '-')
            sprintf(c, "+%.15lf", r);
        else
            sprintf(c, "%.15lf", r);
        trim(c);
        strcpy(a + n - strlen(b), c);
        strcpy(a + n - strlen(b) + strlen(c), t + n + 1 + strlen(d));
    }
}

void MULTIPLY(char a[], int n, int *m) {
    int p, q;
    char b[512], t[512], c[512], d[512];
    strcpy(t, a);
    double v, w, r;
    left(a, b, &v, n, m);
    right(a, d, &w, n, m);
    if (*m != 1) {
        r = v * w;
        if (n - strlen(b) != 0 && b[0] == '-' && d[0] == '-')
            sprintf(c, "+%.15lf", r);
        else
            sprintf(c, "%.15lf", r);
        trim(c);
        strcpy(a + n - strlen(b), c);
        strcpy(a + n - strlen(b) + strlen(c), t + n + 1 + strlen(d));
    }
}

void ADD(char a[], int n, int *m) {
    int p, q;
    char b[512], t[512], c[512], d[512];
    strcpy(t, a);
    double v, w, r;
    left(a, b, &v, n, m);
    right(a, d, &w, n, m);
    if (*m != 1) {
        r = v + w;
        sprintf(c, "%.15lf", r);
        trim(c);
        strcpy(a + n - strlen(b), c);
        strcpy(a + n - strlen(b) + strlen(c), t + n + 1 + strlen(d));
    }
}

void ARITHMETICS(char a[], int *m) {
    int i;
    char b[512];

    for (i = strlen(a) - 1; i >= 0 && *m != 1; i--)
        if (a[i] == '/') {
            DIVIDE(a, i, m);
            i = strlen(a);
        }

    for (i = strlen(a) - 1; i >= 0 && *m != 1; i--)
        if (a[i] == '*') {
            MULTIPLY(a, i, m);
            i = strlen(a);
        }

    strcpy(b, a);

    for (i = 0; a[i] != '\0'; i++)
        if (i > 0 && a[i] == '-' && a[i - 1] == '-') {
            a[i - 1] = '+';
            strcpy(a + i, b + i + 1);
            strcpy(b, a);
        }

    for (i = 0; a[i] != '\0'; i++)
        if (i > 0 && a[i] == '-' && a[i - 1] != '+') {
            a[i] = '+';
            strcpy(a + i + 1, b + i);
            strcpy(b, a);
        }

    for (i = strlen(a) - 1; i >= 0 && *m != 1; i--)
        if (a[i] == '+') {
            ADD(a, i, m);
            i = strlen(a);
        }
}

void OUTPUT(char a[], int *m) {
    int f = 0, i, n, c = 0;
    double d;
    for (i = 0; a[i] != '\0' && a[i] != '\n'; i++)
        if (a[i] == '.')
            c++;
    if (c > 1)
        *m = 1;

    if (*m != 1)
        for (i = 0; a[i] != '\0' && a[i] != '\n'; i++)
            if ((a[i] == '-' && i != 0) && !(isdigit(a[i])) && a[i] != '.')
                *m = 1;

    if (*m != 1) {

        d = atof(a);

        if (uid[current].set[1] == 16)
            sprintf(a, "%g", d);
        else {
            sprintf(a, "%.*f", uid[current].set[1], d);
            trim(a);
            ntrim(a);
        }
        if (a[0] == '-' && a[1] == '0' && a[2] == '\0')
            strcpy(a, "0");
    }
}

void constant(char a[], int *m) {
    char b[512];
    int i, j, k, n, p, q, r;
    for (i = 0; a[i] != '\0'; i++) {
        strcpy(b, a);
        if ((a[i] == 'p' && a[i + 1] == 'i') ||
            (a[i] == 'e' && a[i + 1] != 'c' && a[i - 1] != 's')) {
            if (a[i] == 'p')
                C_PI(a, i, m);
            if (a[i] == 'e')
                C_E(a, i, m);
        }
    }
}

void nfile() {
    data = fopen(file, "rb");
    if (data == NULL) {
        data = fopen(file, "wb");
        if (data != NULL) {
            fwrite(uid, sizeof(user), 64, data);
            fclose(data);
            data = NULL;
            usernumb = 0;
        }
    } else {
        fclose(data);
        data = NULL;
        lfile();
    }
}

void lfile() {
    int i, j, k, l, m, n, p, q, r;
    data = fopen(file, "rb");
    if (data != NULL) {
        fread(uid, sizeof(user), 64, data);
        fclose(data);
        data = NULL;
    }
    usernumb = 0;
    for (i = 0; i < 64; i++)
        if (uid[i].id != 0)
            usernumb++;
}

void wfile() {
    data = fopen(file, "wb");
    if (data != NULL) {
        fwrite(uid, sizeof(user), 64, data);
        fclose(data);
        data = NULL;
        lfile();
    }
}

int chkspc(char a[]) {
    for (int i = 0; a[i] != '\0'; i++)
        if (a[i] == ' ')
            return 1;
    return 0;
}

void lcase(char a[]) {
    strcpy(low, a);
    for (int i = 0; low[i]; i++)
        low[i] = tolower(low[i]);
}

void mask(char a[]) {
    int i = 0;
    char c;

    while ((c = _getch()) != 13) {
        if (c == 8 && i > 0) {
            i--;
            printf("\b \b");
        } else if (c != 8 && i < 64) {
            a[i++] = c;
            printf("*");
        }
    }

    a[i] = '\0';
    printf("\n");
}

int match(char a[]) {
    int i, j, k;
    for (i = 0; i < usernumb; i++)
        if (!strcmp(a, uid[i].name))
            return 1;
    return 0;
}

void search(char a[]) {
    int i, j, k, n = 0;
    ;
    for (i = 0; i < usernumb; i++)
        if (strstr(uid[i].name, a) != NULL) {
            n++;
            if (n == 1)
                printf("%-15s%s", "\nDo you mean?", uid[i].name);
            else
                printf("%-15s%s", "\nOr -", uid[i].name);
        }
}

int found(char a[]) {
    int i, j, k, l, m, n, p, q, r;
    for (i = 0; i < usernumb; i++)
        if (!(strcmp(uid[i].name, a)))
            return i;
}

void Home() {
    int i, j, k, o, p, q, r, n, x, y, z;

    clear;
    logicalc;
    HOME;
    printf("\n[1] Login\n[2] Register\n[3] Delete Account\n[4] Close "
           "Program\n\nInput choice number: ");
    scanf("%d", &o);
    while (getchar() != '\n')
        ;
    while (o < 1 || o > 4) {
        clear;
        logicalc;
        HOME;
        printf(
            "\n1. Login\n2. Register\n3. Delete Account\n4. Close Program\n");
        printf("\nInvalid choice...\nTry again: ");
        scanf("%d", &o);
        while (getchar() != '\n')
            ;
    }

    switch (o) {
    case 1:
        Login();
        break;

    case 2:
        Register();
        break;

    case 3:
        Delete();
        break;

    case 4:
        Exit();
        break;
    }
}

void Register() {
    int i, j, k, o, p, q, r, n, x, y, z;
    char a[128], b[64], c[64];

    clear;
    logicalc;
    REGISTER;
    button;
    printf("\nName: ");
    fgets(a, 127, stdin);
    ntrim(a);
    while (a[0] == '\0' || match(a)) {
        clear;
        logicalc;
        REGISTER;
        ;
        if (!a[0])
            printf("\nNo name detected...\nTry again: ");
        else
            printf(
                "\nSorry! User with same name already exists...\nTry again: ");
        fgets(a, 127, stdin);
        ntrim(a);
    }

    lcase(a);
    if (!strcmp(low, "back") || !strcmp(low, "home") || !strcmp(low, "exit")) {
        wfile();
        if (!strcmp(low, "exit"))
            Exit();
        if (!strcmp(low, "home"))
            Home();
        if (!strcmp(low, "back"))
            Home();
    } else {
        clear;
        logicalc;
        REGISTER;
        button;
        printf("\n%-15s: %s", "Name", a);
        printf("\n%-15s: ", "Password");
        mask(b);
        ntrim(b);
        if (chkspc(b) || b[0] == '\0') {
            clear;
            logicalc;
            REGISTER;
            button;
            printf("\n%-15s: %s", "Name", a);
            printf("\nInvalid password input...\n%-15s: ", "Try again");
            mask(b);
            ntrim(b);
        }

        lcase(b);
        if (!strcmp(low, "back") || !strcmp(low, "home") ||
            !strcmp(low, "exit")) {
            wfile();
            if (!strcmp(low, "exit"))
                Exit();
            if (!strcmp(low, "home"))
                Home();
            if (!strcmp(low, "back"))
                Register();
        } else {
            clear;
            logicalc;
            REGISTER;
            button;
            printf("\n%-18s: %s", "Name", a);
            printf("\n%-18s: ", "Confirm password");
            mask(c);
            ntrim(c);
            while (strcmp(c, b)) {
                lcase(c);
                if (!strcmp(low, "back") || !strcmp(low, "home") ||
                    !strcmp(low, "exit")) {
                    wfile();
                    if (!strcmp(low, "exit"))
                        Exit();
                    if (!strcmp(low, "home"))
                        Home();
                    if (!strcmp(low, "back"))
                        Register();
                } else {
                    clear;
                    logicalc;
                    REGISTER;
                    button;
                    printf("\n%-18s: %s", "Name", a);
                    printf("\nPasswords do not match...\n%-18s: ", "Try again");
                    mask(c);
                    ntrim(c);
                }
            }
            uid[usernumb].id = usernumb + 1;
            strcpy(uid[usernumb].name, a);
            strcpy(uid[usernumb].pass, b);
            usernumb++;
            wfile();
            clear;
            logicalc;
            REGISTER;
            printf("\nYour account succesfully have been created :>.\n");
            printf("\nPress any key to be redirected to home page...");
            if (getchar())
                Home();
        }
    }
}

void Delete() {
    if (usernumb == 0) {
        clear;
        printf("There is no registered user.\nPress any key to get redirected "
               "to Home...");
        if (getchar())
            Home();
    }

    else {
        int p, q, r, n, i, j, k, o, f;
        char a[128], b[64], c;
        clear;
        logicalc;
        DELETE;
        button;
        printf("Enter your ID name: ");
        fgets(a, 127, stdin);
        ntrim(a);
        lcase(a);
        while (a[0] == '\0' || (!match(a) && strcmp(low, "home") != 0 &&
                                strcmp(low, "back") != 0)) {
            clear;
            logicalc;
            DELETE;
            button;
            if (a[0] == '\0')
                printf("\nNo name detected...\nTry again: ");
            else {
                printf("\nUser not found...\n");
                search(a);
                printf("\nTry again: ");
            }
            fgets(a, 127, stdin);
            ntrim(a);
            lcase(a);
        }
        if (!strcmp(low, "back") || !strcmp(low, "home") ||
            !strcmp(low, "exit")) {
            wfile();
            if (!strcmp(low, "exit"))
                Exit();
            if (!strcmp(low, "home"))
                Home();
            if (!strcmp(low, "back"))
                Home();
        } else {
            f = found(a);
            clear;
            logicalc;
            DELETE;
            button;
            printf("\n%-12s: %s", "Name", a);
            printf("\n%-12s: ", "Password: ");
            mask(b);
            ntrim(b);
            while (strcmp(b, uid[f].pass)) {
                lcase(b);
                if (!strcmp(low, "back") || !strcmp(low, "home") ||
                    !strcmp(low, "exit")) {
                    wfile();
                    if (!strcmp(low, "exit"))
                        Exit();
                    if (!strcmp(low, "home"))
                        Home();
                    if (!strcmp(low, "back"))
                        Delete();
                }

                else {
                    clear;
                    logicalc;
                    DELETE;
                    button;
                    printf("\n%-12s: %s", "Name", a);
                    printf("\nWrong password...\n%-12s: ", "Try again");
                    mask(b);
                    ntrim(b);
                }
            }
            clear;
            logicalc;
            DELETE;
            printf("\nConfirm deletion (y/n): ");
            c = tolower(getchar());
            while (c != 'y' && c != 'n') {
                clear;
                logicalc;
                DELETE;
                printf("\nWrong input...\nTry again (y/n): ");
                c = tolower(getchar());
            }
            while (getchar() != '\n')
                ;
            if (c == 'n')
                Home();
            if (c == 'y') {
                uid[f] = mem;
                if (usernumb > 1) {
                    uid[f] = uid[usernumb - 1];
                    uid[f].id = f + 1;
                    uid[usernumb - 1] = mem;
                }
                usernumb--;
                wfile();
                clear;
                logicalc;
                DELETE;
                printf("\nUser '%s' has been deleted. \nPress any key to "
                       "continue to home page...",
                       a);
                if (getchar())
                    Home();
            }
        }
    }
}

void Exit() {
    char c;
    clear;
    logicalc;
    EXIT;
    printf("You sure you want to exit the program (y/n): ");
    c = tolower(getchar());
    buffer;
    while (c != 'y' && c != 'n') {
        clear;
        logicalc;
        DELETE;
        printf("\nWrong input...\nTry again (y/n): ");
        c = tolower(getchar());
        buffer;
    }
    if (c == 'n')
        Home();
    if (c == 'y') {
        wfile();
        exit(0);
    }
}

void Login() {
    if (usernumb == 0) {
        clear;
        printf("There is no registered user.\nPress any key to get redirected "
               "to Home...");
        if (getchar())
            Home();
    }

    else {
        int p, q, r, n, i, j, k, o, f;
        char a[128], b[64], c;
        clear;
        logicalc;
        LOGIN;
        button;
        printf("\nEnter your ID name: ");
        fgets(a, 127, stdin);
        ntrim(a);
        lcase(a);
        while (a[0] == '\0' ||
               (!match(a) && strcmp(low, "home") != 0 &&
                strcmp(low, "back") != 0 && strcmp(low, "exit") != 0)) {
            clear;
            logicalc;
            LOGIN;
            button;
            if (a[0] == '\0')
                printf("\nNo name detected...\nTry again: ");
            else {
                printf("\nUser not found...\n");
                search(a);
                printf("\nTry again: ");
            }
            fgets(a, 127, stdin);
            ntrim(a);
            lcase(a);
        }
        if (!strcmp(low, "back") || !strcmp(low, "home") ||
            !strcmp(low, "exit")) {
            wfile();
            if (!strcmp(low, "exit"))
                Exit();
            if (!strcmp(low, "home"))
                Home();
            if (!strcmp(low, "back"))
                Home();
        } else {
            f = found(a);
            clear;
            logicalc;
            LOGIN;
            button;
            printf("\n%-12s: %s", "Name", a);
            printf("\n%-12s: ", "Password: ");
            mask(b);
            ntrim(b);
            while (strcmp(b, uid[f].pass)) {
                lcase(b);
                if (!strcmp(low, "back") || !strcmp(low, "home") ||
                    !strcmp(low, "exit")) {
                    wfile();
                    if (!strcmp(low, "exit"))
                        Exit();
                    if (!strcmp(low, "home"))
                        Home();
                    if (!strcmp(low, "back"))
                        Login();
                }

                else {
                    clear;
                    logicalc;
                    LOGIN;
                    button;
                    printf("\n%-12s: %s", "Name", a);
                    printf("\nWrong password...\n%-12s: ", "Try again");
                    mask(b);
                    ntrim(b);
                }
            }
            current = f;
            Logged();
        }
    }
}

void Logged() {
    int i, j, k, o, p, q, r, n, x, y, z;
    if (uid[current].set[0] == 0 || uid[current].set[1] == 0)
        Settings();

    strcpy(head, "User: ");
    clear;
    logicalc;
    HEAD;
    printf("\n[1]Calculator\n[2]History\n[3]Setup "
           "Function\n[4]Settings\n[5]Back\n[6]Home\n[7]Exit\n\nInput your "
           "choice number: ");
    scanf("%d", &o);
    while (getchar() != '\n')
        ;
    while (o < 1 || o > 7) {
        clear;
        logicalc;
        HEAD;
        printf("\n[1]Calculator\n[2]History\n[3]Setup "
               "Function\n[4]Settings\n[5]Back\n[6]Home\n[7]Exit\n ");
        printf("\nInvalid choice...\nTry again: ");
        scanf("%d", &o);
        while (getchar() != '\n')
            ;
    }

    switch (o) {
    case 1:
        Calculator();
        break;

    case 2:
        History();
        break;

    case 3:
        Function();
        break;

    case 4:
        Settings();
        break;

    case 5:
        wfile();
        Login();
        break;

    case 6:
        wfile();
        Home();
        break;

    case 7:
        wfile();
        Exit();
    }
}

void Settings() {
    strcpy(head, "Settings \\\\ User: ");
    int i, j, k, l, m, n, p, q, r;
    clear;
    logicalc;
    HEAD;
    printf("\nInput 0 any time to go back to user page\n");
    printf("\nDo you prefer to use\n[1]Radians or [2]Degree\nfor your "
           "calculations?\n\nChoose (1/2): ");
    scanf("%d", &p);
    buffer;
    while (p != 0 && p != 1 && p != 2) {
        clear;
        logicalc;
        HEAD;
        printf("\nInvalid choice input...\n[1]Radians or [2]Degree ?\n\nChoose "
               "again (1/2): ");
        scanf("%d", &p);
        buffer;
    }

    if (p != 0) {
        uid[current].set[0] = p;
        wfile();
        clear;
        logicalc;
        HEAD;
        printf(p == 1 ? "Rad/Deg: Radians\n" : "Rad/Deg: Degree\n");
        printf("\nDo you want your results in \n[1]Scintific or [2]Fixed "
               "Notation\nfor your calculations?\n\nChoose (1/2): ");
        scanf("%d", &q);
        buffer;
        while (q != 0 && q != 1 && q != 2) {
            clear;
            logicalc;
            HEAD;
            printf(p == 1 ? "Rad/Deg: Radians\n" : "Rad/Deg: Degree\n");
            printf("\nInvalid choice input...\n[1]Scintific or [2]Fixed "
                   "Notation ?\n\nChoose again (1/2): ");
            scanf("%d", &q);
            buffer;
        }
        if (q != 0) {
            if (q == 1) {
                uid[current].set[1] = 16;
                wfile();
                printf("\nSettings updated successfully.");
                printf("\nPress any key to continue....");
                if (getchar())
                    Logged();
            }

            else {
                clear;
                logicalc;
                HEAD;
                printf(p == 1 ? "Rad/Deg: Radians\n" : "Rad/Deg: Degree\n");
                printf("\nDecimal precision for fixed notation ?\n\nChoose "
                       "between (1-15): ");
                scanf("%d", &q);
                buffer;
                while (q < 0 || q > 15) {
                    clear;
                    logicalc;
                    HEAD;
                    printf(p == 1 ? "Rad/Deg: Radians\n" : "Rad/Deg: Degree\n");
                    printf("\nInvalid choice input for decimal "
                           "precision...\n\nChoose again between (1-15): ");
                    scanf("%d", &q);
                    buffer;
                }
                if (q != 0) {
                    uid[current].set[1] = q;
                    wfile();
                    printf("\nSettings updated successfully.");
                    printf("\nPress any key to continue...");
                    if (getchar())
                        Logged();
                }
            }
        }
    }
    if (uid[current].set[0] == 0 || uid[current].set[1] == 0) {
        printf("\nYou have failed to configure all your settings properly.");
        printf("\nYou will be redirected to home page...\nPress any key to "
               "continue");
        if (getchar())
            Home();
    }
}

void header(char a[]) {
    int i, j, n;
    strcat(a, uid[current].name);
    n = strlen(a);
    printf("\n+");
    for (i = 0; i < n + 8; i++)
        printf("-");
    printf("+\n");
    printf("|%*s|\n", n + 8, "");
    printf("|%4s%s%4s|\n", "", a, "");
    printf("|%*s|\n", n + 8, "");
    printf("+");
    for (i = 0; i < n + 8; i++)
        printf("-");
    printf("+\n");
}

void Calculator() {
    strcpy(head, "Navigate Calculator \\\\ User: ");
    int i, j, k, o, p, q, r, n, x, y, z;
    clear;
    logicalc;
    HEAD;
    printf("\n[1]Scintific Calculator\n[2]Evaluate "
           "Function\n[3]Back\n[4]Home\n[5]Exit\n\nInput your choice number: ");
    scanf("%d", &o);
    while (getchar() != '\n')
        ;
    while (o < 1 || o > 5) {
        clear;
        logicalc;
        HEAD;
        printf(
            "\n[1]Scintific Calculator\n[2]Number Base Converter\n[3]Evaluate "
            "Function\n[4]Quadratic Equation\n[5]Back\n[6]Home\n[7]Exit ");
        printf("\n\nInvalid choice...\nTry again: ");
        scanf("%d", &o);
        while (getchar() != '\n')
            ;
    }

    switch (o) {
    case 1:
        Sci_Calc();
        break;
    case 2:
        Evaluate();
        break;

    case 3:
        wfile();
        Logged();
        break;

    case 4:
        wfile();
        Home();
        break;

    case 5:
        wfile();
        Exit();
        break;
    }
}

void Sci_Calc() {

    int i, j, k, o, p, q, r, n, x, y, z, m;
    char a[512], b[512], c;

    while (1) {
        strcpy(head, "Scientific Calculator \\\\ User: ");
        clear;
        logicalc;
        HEAD;
        button;
        INSTRUCTIONS;
        if (uid[current].in[0][0] != '\0')
            printf("\n[HISTORY]\n\n  %s\n  = %s\n", uid[current].in[0],
                   uid[current].out[0]);
        else
            printf("\n[HISTORY]\n\n  No hitory available...\n\n");
        printf("\n\n[INPUT]\n\n  ");
        m = 0;
        fgets(a, sizeof(a), stdin);
        space(a, &m);
        lcase(a);
        if (!strcmp(low, "back") || !strcmp(low, "home") ||
            !strcmp(low, "exit")) {
            wfile();
            if (!strcmp(low, "exit"))
                Exit();
            if (!strcmp(low, "home"))
                Home();
            if (!strcmp(low, "back"))
                Calculator();
        }
        if (m != 1)
            format(a, &m);
        strcpy(b, a);
        if (m != 1)
            constant(a, &m);
        if (m != 1)
            validate(a, &m);
        if (m != 1)
            OUTPUT(a, &m);
        printf("\n\n[FORMATTED INPUT AND OUTPUT]\n\n  %s\n", b);
        if (m != 1) {
            printf("  %s", a);
            Update(b, a);
        }
        if (m == 1)
            printf("  Invalid Input!!!");
        printf("\n\nTap [Enter] to continue...");
        if (getchar())
            ;
    }
}

void Instructions() {

    printf("\nSYNTAX AND INSTRUCTIONS:\n");
    printf("+");
    for (int i = 0; i < 95; i++)
        printf("-");
    printf("+");
    printf("\n|%15s|%15s|%15s|%15s|%15s|%15s|", "Sine: sin", "Cos: cos",
           "Tan: tan", "Cosec: csc", "Secant: sec", "Cot: cot");

    printf("\n|%15s|%15s|%15s|%15s|%15s|%15s|", "Arcsine: sini", "Arccos: cosi",
           "Arctan: tani", "Arccosec: csci", "Arcsecant: seci", "Arccot: coti");

    printf("\n|%15s|%15s|%15s|%15s|%15s|%15s|", "Root: sqr", "Cube root: cbr",
           "Power: ^", "Factorial: !", "e base log: ln", "10base log: log");

    printf("\n|%15s|%15s|%15s|%15s|%15s|%15s|", "Constant: pi", "Constant: e",
           "Add: +", "Subtract: -", "Multiply: *", "Divide: /");

    printf("\n|%15s|%15s|%15s|%47s|", "Function: f", "Function: g",
           "Function: h", "VALID SYNTAX & INPUT IS MANDITORY FOR RESULTS");
    printf("\n+");
    for (int i = 0; i < 95; i++)
        printf("-");
    printf("+");
}

void Update(char a[], char b[]) {
    int i;
    for (i = 9; i > 0; i--) {
        strcpy(uid[current].in[i], uid[current].in[i - 1]);
        strcpy(uid[current].out[i], uid[current].out[i - 1]);
    }

    if (uid[current].set[0] == 2)
        strcat(b, " [D]");
    else
        strcat(b, " [R]");
    strcpy(uid[current].in[0], a);
    strcpy(uid[current].out[0], b);
    wfile();
}

void History() {
    strcpy(head, "History \\\\ User: ");
    clear;
    logicalc;
    HEAD;
    printf("\n");
    for (int i = 0; i < 10; i++) {
        if (uid[current].in[i][0] != '\0')
            printf("\n%2d. %s\n    = %s", i + 1, uid[current].in[i],
                   uid[current].out[i]);
        else
            printf("\n%2d. -\n    = -", i + 1, uid[current].in[i],
                   uid[current].out[i]);
        printf("\n");
    }

    printf("\nPress any key to continue...");
    if (getchar())
        Logged();
}

void Function() {
    int i, j, k, c, n = 1;
    double v;
    char a[512];
    strcpy(head, "Add funtion \\\\ User :");
    clear;
    logicalc;
    HEAD;

    printf("\nCurrent state of funtions:\nf(x) = %s\ng(x) = %s\nh(x) = %s\n",
           uid[current].f, uid[current].g, uid[current].h);
    printf("\nYou can input 0 to go back");
    printf(
        "\nChoose a funtion to setup or rewrite \nbetween [1]f [2]g [3]h : ");
    scanf("%d", &c);
    buffer;
    while (c < 0 || c > 3) {
        strcpy(head, "Add funtion \\\\ User :");
        clear;
        logicalc;
        HEAD;
        printf("\nYou press input 0 to go back");
        printf("\nInvalid Input...\nChoose again, [1]f [2]g [3]h : ");
        scanf("%d", &c);
        buffer;
    }

    if (c == 0)
        Logged();

    clear;
    logicalc;
    HEAD;
    button;
    INSTRUCTIONS;
    printf("\nHaving wrong syntanx in equation & \nInput outside parameters "
           "will result in Invalid Input while usage.\nOnly use x for the "
           "equation.\nEnter nothing to clear a funtion.\n");
    switch (c) {
    case 1:
        printf("f(x) = ");
        break;
    case 2:
        printf("g(x) = ");
        break;
    case 3:
        printf("h(x) = ");
        break;
    }
    fgets(a, 512, stdin);
    space(a, &n);
    format(a, &n);
    lcase(a);

    if (!strcmp(low, "back") || !strcmp(low, "home") || !strcmp(low, "exit")) {
        wfile();
        if (!strcmp(low, "exit"))
            Exit();
        if (!strcmp(low, "home"))
            Home();
        if (!strcmp(low, "back"))
            Logged();
    }

    switch (c) {
    case 1:
        strcpy(uid[current].f, a);
        break;
    case 2:
        strcpy(uid[current].g, a);
        break;
    case 3:
        strcpy(uid[current].h, a);
        break;
    }
    wfile();
    printf("\n[SUCCESS]\nPress any key to continue...");
    if (getchar())
        Function();
}

void Evaluate() {
    int i, j, k, n, m;
    double v;
    char a[512], b[512], c[512];

    strcpy(head, "Evaluate Funtion \\\\ User :");
    clear;
    logicalc;
    HEAD;
    printf("\nInput your choice - [1]Setup Function [2]Back: ");
    scanf("%d", &n);
    buffer;

    while (n != 1 && n != 2) {
        printf("\nInvalid Input...\nTry again - [1]Setup Function [2]Back: ");
        scanf("%d", &n);
        buffer;
    }

    if (n == 2)
        Calculator();
    else {
        strcpy(head, "Evaluate Funtion \\\\ User :");
        clear;
        logicalc;
        HEAD;
        button;
        INSTRUCTIONS;
        printf("\nInvalid syntax & wrong parameters will result in error\n");

        printf("\nf(x) = ?\n");
        fgets(a, 512, stdin);
        n = 0;
        space(a, &n);
        if (n != 1)
            format(a, &n);

        lcase(a);
        if (!strcmp(low, "back") || !strcmp(low, "home") ||
            !strcmp(low, "exit")) {
            wfile();
            if (!strcmp(low, "exit"))
                Exit();
            if (!strcmp(low, "home"))
                Home();
            if (!strcmp(low, "back"))
                Calculator();
        } else {
            strcpy(c, a);

            while (1) {
                strcpy(head, "Evaluate Funtion \\\\ User :");
                clear;
                logicalc;
                HEAD;
                button;
                printf("\nType reset to reset the funtion\n");
                printf("\nf(x) = %s", c);
                printf("\nx = ?\n\nInput x: ");
                fgets(a, 512, stdin);

                n = 0;
                m = 0;
                space(a, &n);
                if (n != 1)
                    format(a, &n);

                lcase(a);
                if (!strcmp(low, "back") || !strcmp(low, "home") ||
                    !strcmp(low, "exit") || !strcmp(low, "reset")) {
                    wfile();
                    if (!strcmp(low, "exit"))
                        Exit();
                    if (!strcmp(low, "home"))
                        Home();
                    if (!strcmp(low, "back"))
                        Calculator();
                    if (!strcmp(low, "reset"))
                        Evaluate();
                } else {
                    constant(a, &m);
                    if (m != 1)
                        validate(a, &m);
                    if (m != 1) {
                        v = atof(a);
                        strcpy(b, c);
                        CALC_FUNCTION(b, (float)v, &m);
                    }

                    if (m != 1) {
                        trim(b);
                        printf("\nf(%.15lf) = %s", v, b);
                    } else
                        printf("\nInvalid Equation or Input.");

                    printf("\n\nPress any key to continue...");
                    if (getchar())
                        ;
                }
            }
        }
    }
}

double deg(double v) {
    if (uid[current].set[0] == 1)
        return v * PI / 180;
    return v;
}
