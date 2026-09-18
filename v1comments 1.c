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
    printf(                                                                    \
        "\n _                _              _       \n| |  ___    __ _ (_)  "  \
        "___  __ _ | |    ___ \n| | / _ \\  / _` || | / __|/ _` || |   / "     \
        "__|\n| || (_) || (_| || || (__| (_| || | _| (__ \n|_| \\___/  "       \
        "\\__, ||_| \\___|\\__,_||_|(_)\\___|\n           |___/ \n")
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
    // removes space
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
    // removes \n to \0
    int i;
    for (i = 0; a[i] != '\0'; i++)
        if (a[i] == '\n')
            a[i] = '\0';
}

void format(char a[], int *m) {
    int n = 32, i, j, k, l, p, q, r, x, y, z, f;
    char b[512], *pos, *t;
    // d is basically the funtions that - these needs * on their left but not
    // right . c is things like ! and ) that can have * on their left. pos and t
    // are pointers to be used t is basically just a and pos is the position
    // that strstr returns.
    char *d[32] = {
        "sin", "cos", "tan",  "csc",  "sec",  "cot", "csc", "sec",
        "cot", "cbr", "sini", "cosi", "tani", "log", "ln",  "pi",
        "(",   "log", "ln",   "e",    "f",    "g",   "h",
    };

    char *c[32] = {")", "!"};
    // avoids placing * after ) or ! if theres ) or ! after them or they have c
    // that is for comnbination and p that is for permutation, needs to spacifiy
    // so it dosent pick up csc cos cot cbr and pi, t goes from left to right if
    // they find someone they can update their position to a + p + strlen which
    // looks dumb now we could write pos+1. b updates with new a. str cpy
    // basicaly copy pastes sstring after placing the *. the also check for any
    // arithmatic like + - * / etc
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
        // pretty much same stuff with less complication and this time * sits
        // before the funtion if theres a number usually
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

    // since pi and e needs * on both sides but not when they r places in
    // funtions e is making sure hes not part of sec , also checks for
    // aryhtmatics
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
    // counts brackets, if 0 straight to calc , if not check if they equal and
    // actually ends with a closing braket and if we have any equal sign cuz
    // they cant detect that out of a number. sends to brakcet at last
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

    // bracket checks if the bracket count is 0 because it recurses until it is
    for (i = 0; a[i] != '\0'; i++)
        if (a[i] == '(') {
            p = i;
            c++;
        }

    if (c == 0)
        calc(a, m);

    else {
        // finds the inner most brakcets with with previously last record of we
        // finding '(' in p postion . and we check for the closing bracket for
        // this on starting from p. then we strip the brakcets and send to calc,
        // replace the whole thing with new value string
        f = 1;
        for (i = p + 1; a[i] != '\0'; i++)
            if (a[i] == ')' && i != p + 1) {
                f = 0;
                break;
            }

        if (f == 1)
            *m = 1;

        if (*m != 1) {
            // strips the brakcets basically
            q = i;
            strcpy(t, a);
            strncpy(b, a + p + 1, q - p - 1);
            b[q - p - 1] = '\0';
            // sends to calc
            calc(b, m);
            if (*m != 1) {
                // places the string back in place. p is where it starts and q
                // is where it so after the new b lenth+p we place back the rest
                // from position q.
                strcpy(a + p, b);
                strcpy(a + p + strlen(b), t + q + 1);
                bracket(a, m);
            }
        }
    }
}

void calc(char a[], int *m) {
    // f1 is both sided funtions . f2 only looks at right and we handle !
    // sepratly cuz its the only left sided funtion.
    char b[512], *pos, *t;
    char *f1[32] = {"^", "c", "p"};
    char *f2[32] = {"sini", "cosi", "tani", "csci", "seci", "coti", "sin",
                    "cos",  "tan",  "csc",  "sec",  "cot",  "sqr",  "cbr",
                    "log",  "ln",   "f",    "g",    "h"};
    int n = 32, i, j, k, l, p, q, r, c, x, y, z, flag1, flag2;

    // this one goes from left to right - if it sees a factorial it looks for
    // number on its left
    for (i = 0; i <= strlen(a) - 1 && *m != 1; i++)
        if (a[i] == '!') {
            FACTORIAL(a, i, m);
            i = 0;
        }

    // this one starts from right to left , these ones only funtion with numbers
    // both side first it checks if we looking for an empty string , this it
    // looks if the are in the whole string in the first place , if yes it
    // starts looking. gets back pos as its positon pointer we minus a to get
    // the nth index. if we find something flag becomes 1.
    t = a + strlen(a) - 1;
    while (t >= a) {
        flag1 = 0;
        for (i = 0; i < 3; i++) {
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
                        }
                        t = a + strlen(a) - 1;
                        if (*m == 1)
                            break;
                    }
            if (*m == 1)
                break;
        }

        // this one starts from right to left so it always sees the number
        // infront of any function first in instances of sinsin30 that way sin30
        // gets calculated and gets turned into a number before we gettting to
        // 2nd sin. first it checks if we looking for an empty string , this it
        // looks if there in the whole string in the first place , if yes it
        // starts looking. gets back pos as its positon pointer we minus a to
        // get the nth index. if we find something this flag becomes 1.
        flag2 = 0;
        for (i = 0; i < 20; i++) {
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
                        }
                        t = a + strlen(a) - 1;
                        if (*m == 1)
                            break;
                    }
            if (*m == 1)
                break;
        }
        // if both flat is 0 then in found nothing it simply decreements , if
        // they found something the update their loop with new lenth value
        // coming from newly replaced strings from all the funtions and it
        // starts from very right again
        if (*m == 1)
            break;
        if (flag1 == 0 && flag2 == 0)
            t--;
    }
    // when all done it only leaves out + - * / which gets handled here
    ARITHMETICS(a, m);
}

void right(char a[], char b[], double *v, int n, int *m) {
    int p = n + 1, q, r, x, y, z, t, i, j, k;
    // this checks for number of right of postion n. by chekcing if they start
    // with . or - or normally and covers every scenrio and copies it until it
    // reaches an end with hitting something other than digits, checks error by
    // looking at multiple '.' but copies it puts it in string b from the whole
    // string a , makes it a number too and gives the number back in double
    // named v, m is for error
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
    // same as right but just for left . - marks the end of any number on left
    // as it confirms its starting . etc..
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
    // converts from degree to rad if user using degree so we can put in math.h
    // funtions they use rad
    if (uid[current].set[0] == 2)
        return v * PI / 180;
    return v;
}

double radian(double v) {
    // converts from rad to degree on trig inverse funtion out puts if user
    // using degree cuz math.h returns in rad.
    if (uid[current].set[0] == 2)
        return v * 180 / PI;
    return v;
}

void trim(char a[]) {
    // trims the useless 0 on decimal or .0 if its a integer
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
    // checks if the f funtion of user has anything in their uid , if not wrong
    // input. if yes they replace all the x with users value on right of f then
    // sends it to calc to get calculated normally
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
    // same as f funtion but for g
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
    // same as f and g but just with h.
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
    // copies the user equation for function and sends here then keeps taking
    // values and keeps rlacing x with that value out putting outputs
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
    // sin cos cosec sec all works the same . sends in the value since they all
    // 3 letters long the postion thry need to look for number is the postion
    // sin was found in aka n + 2 so it starts looking from last chars right ,
    // right returns value , gets turned into radian if its not radian already
    // by user preferance and gets calculated. if theres a parameter that needs
    // to be checked on and if user is using radian we use deg and w variable to
    // separatly turn it into segree and compare it to the 90 formats invalid
    // parameters cuz we dont know shit about radian parameters.
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

// if user using deg they get back degree value or they get back degree format
// after getting radian in the first place from math.h same for everyone and we
// check the parameters first. same for inverse for other trig functions
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
    // pretty staright forward picks up the right number and rejects below 0.
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
    // same like sqrt withought parameters
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
    // does stardard 10 base log
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
    // does similar e base log
    // strcpy(a + n, c);
    // strcpy(a + n + strlen(c), t + n + 2 + strlen(b));
    // this is basically just strcpy the answer then measure it and place the
    // previous strings everything after the funtion thus the funtion lenthgh ln
    // is 2 + the strlen(b) aka the number that was input, n the postion we
    // found it in , t is the prev a copy so we can retain a's old data to copy
    // later case in point here.
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
// factorial looks at left instead and also checks if integer. math h funtion is
// basically for n! we need to do tgamma(n+1).
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

        else { // minus factorial gets handled by just norally calculated after
               // made postitive and then turned back negetibve again
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
    // uses pow funtion avoids power over 25 we got lazy we could setup proper
    // parameter calcing how much each number can have power by deviding log(c
    // max number)/log(n) if n negetaive and power is even aka output is
    // positive it prints out a + for the number if we have things on left of
    // the number . we check it by subtracting the numbers lenthh with b . if
    // its bigger rhan 0 that means there is more than number.
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
    // simple n c r, takes both right and left input . checks if they all
    // integer and postive. first checks if its not any of the other funtion
    // containing c.
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
            // first pastes it on the place where first number starts . then
            // after the new numbers length it pastes from where the last number
            // stops.
            strcpy(a + n - strlen(b), c);
            strcpy(a + n - strlen(b) + strlen(c), t + n + 1 + strlen(d));
        }
    }
}

void NPR(char a[], int n, int *m) {
    // very similar to ncr
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
    // replaces the "pi" with pi's value
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
    // same as pi but first checks if its sec or seci
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
    // simple . if both negetive it places a + if theres other stuff on left of
    // the left number . srring copy works same as ncr npr and will be same for
    // multiply and add. checks if its being divided by 0
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
    // similar to divide
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
    // adds... nothing much
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

    // first it replaces all the - with +- to make them go in add mode as
    // negative numbers if unless theres nothing on left of -. also makes any --
    // ,+
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
    // if user set[1] is 16 that means scintific or semiscientific using %g . if
    // not 1-15 is the number of digits in decimal. also checks if valid number.
    // trim cuts the extra 0. in case of negative 0 we make it just 0.
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
    // replaces pi and e with value by sending them to their funtions.
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
    // tries to open file to see if it exits
    data = fopen(file, "rb");
    if (data == NULL) {
        // opens a new file if it dosent exit in write mode and fills it with
        // struct with all 0 and '\0'
        data = fopen(file, "wb");
        if (data != NULL) {
            fwrite(uid, sizeof(user), 64, data);
            fclose(data);
            data = NULL;
            usernumb = 0;
        }
    } else {
        // sends to load file if file already exits.
        fclose(data);
        data = NULL;
        lfile();
    }
}

void lfile() {
    // opens file in read mode and pastes everything in uid.
    int i, j, k, l, m, n, p, q, r;
    data = fopen(file, "rb");
    if (data != NULL) {
        fread(uid, sizeof(user), 64, data);
        fclose(data);
        data = NULL;
    }
    usernumb = 0;
    // increments user number if their id isnt 0 which indicates empty user.
    for (i = 0; i < 64; i++)
        if (uid[i].id != 0)
            usernumb++;
}

void wfile() {
    // basically repastes struct into file every time there is an update to uid.
    data = fopen(file, "wb");
    if (data != NULL) {
        fwrite(uid, sizeof(user), 64, data);
        fclose(data);
        data = NULL;
        lfile();
    }
}

int chkspc(char a[]) {
    // returns 1 if there is space in string. used while setting new password.
    for (int i = 0; a[i] != '\0'; i++)
        if (a[i] == ' ')
            return 1;
    return 0;
}

void lcase(char a[]) {
    // pastes anythings lower case version to string named low for matching with
    // exit or home or back.
    strcpy(low, a);
    for (int i = 0; low[i]; i++)
        low[i] = tolower(low[i]);
}

void mask(char a[]) {
    int i = 0;
    char c;
    // 13 is enter so it takes input until enter.
    //_getch dosent show input being put on screen unlike getchar.
    while ((c = _getch()) != 13) {
        // 8 is backspace .
        //\b takes the curser one place back. ' ' replaces the letter with space
        // thus deleteing the astrisk. \b again to go back from that space
        // again. thus "\b \b"
        if (c == 8 && i > 0) {
            i--;
            printf("\b \b");
        }
        // takes input as long as its asci char over 64 and isnt backspace
        else if (c != 8 && i < 64) {
            a[i++] = c;
            printf("*");
        }
    }
    // prints a \0 to mark the end and \n to replicate hiiting enter.
    a[i] = '\0';
    printf("\n");
}

int match(char a[]) {
    // used for user name login. usernumb is number of currenet valid user. name
    // is the user name. returns one if matched fully. othewrwise 0.
    int i, j, k;
    // strcpr checks if the string is fully identical.
    for (i = 0; i < usernumb; i++)
        if (!strcmp(a, uid[i].name))
            return 1;
    return 0;
}

void search(char a[]) {
    // strstr partially searches. returns null if it dosent find anything so it
    // dosent return null aka. if input matches with anything partially of those
    // valid users. i incriments. for first user it asks do u mean : [username]
    // and then from after it says or - [username]... and goes on. %-15s makes
    // it so the names look aligned after 15 allocated place for do u mean and
    // or -to print. the - makes it so they r printed on right side of the
    // allocated space.
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
    // found basically comes if matches returns 1 , aka matches tell us if we
    // actually have someone of that name and if we do we run found to find the
    // index of that matching name from uid-s 64 array. using strcmp to find the
    // identical name in the users.
    int i, j, k, l, m, n, p, q, r;
    for (i = 0; i < usernumb; i++)
        if (!(strcmp(uid[i].name, a)))
            return i;
}

void Home() {
    // clear is defined as printf("\033[2J\033[1;1H") \033[2J clears screen and
    // the 1;1H means replace curser at 1 row and 1 collumn basically at top.
    // logicalc prints the logo
    // home prints that boxed cool home for title
    // u get to inpput choice ,a loop runs if u give wrong input asking u to try
    // again until u input something valid .
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
    // whats new - register prints the resiter title in a box as its defined,
    // button prints that intruction that u can just write home or back or exit
    // etc. if someone taps enter without a name aka a[0]='\0' or matches name
    // with other users aka match(a),,, it keeps asking u to tryz
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
        button;
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
        // after naming procress it checks for password while showing u the
        // name. mask takes the string as input u wanna store a password into
        // and does its thing.
        clear;
        logicalc;
        REGISTER;
        button;
        printf("\n%-15s: %s", "Name", a);
        printf("\n%-15s: ", "Password");
        mask(b);
        ntrim(b);

        // check space tells if it has space by returning 1 so as long as u put
        // space in or just hit enter without pass it keeps asking u to try
        // again
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

        // again check if user if trying to exit or go back
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
            // if not we ask to confirm password
            clear;
            logicalc;
            REGISTER;
            button;
            printf("\n%-18s: %s", "Name", a);
            printf("\n%-18s: ", "Confirm password");
            mask(c);
            ntrim(c);
            // b is original pass word, c is the password we recoived while
            // telling them to confirm , we macth them if they dont match we
            // tell the to try again.
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
            // if the passwords match your id gets saved is this section
            // simple explaination is user id 1 lives at the struct index 0.
            // thus when when theres n number of users already we have to add
            // one for the first user. we incriment user numb after getting  a
            // new user .. duh. wfile to save it all into file right away.
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
        printf(
            "There is no registered user.\nPress any key to get redirected to "
            "Home...");
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
        // checks if intput is not matching nor home or exit ot back or user
        // just hit enter with nothing.
        while (a[0] == '\0' ||
               (!match(a) && strcmp(low, "home") != 0 &&
                strcmp(low, "back") != 0 && strcmp(low, "exit") != 0)) {
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
            // found returns an index to where it found the name the string
            // named a carries.
            f = found(a);
            clear;
            logicalc;
            DELETE;
            button;
            printf("\n%-12s: %s", "Name", a);
            printf("\n%-12s: ", "Password: ");
            mask(b);
            ntrim(b);
            // again matches with the buttons , and checks if the password
            // matches with the current user we r trying to delete thats on f
            // index. so if dosent match checks buttons , if they dont match
            // they ask u to retry cuz wrong password
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
            // loop breaks if u give the correct password
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
                // user f = mem which is empty,,, thus deleting user index
                // number f. if theres 10 users and i delete index number f user
                // suppose 5 . then it firstly deleltes the index 5 aka 6th
                // user. then to fill the empty spot it goes to usernumber - 1
                // slot aka 9th index aka 10th and last user  copies it , pastes
                // into the currently deleted empty slot at 5th index place.
                // then sicne last user got pastes to the currently deleted slot
                // we remove the last users old slot with mem making that all 0.
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
                       "continue to "
                       "home page...",
                       a);
                if (getchar())
                    Home();
            }
        }
    }
}

void Exit() {
    // basically takes y or n input , if y it goes saves all file with wfile and
    // then then uses exit(0) to exit.
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
        printf(
            "There is no registered user.\nPress any key to get redirected to "
            "Home...");
        if (getchar())
            Home();
    }

    else {
        // very similar to the delete funtion.
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
            // current is basically global varaible that stores the currently
            // logged in users index.
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
    // HEAD is header(head) and head is currently User: basically it makes it so
    // je we get back User: [Current user name] with a cool box around it.
    printf("\n[1]Calculator\n[2]History\n[3]Setup "
           "Function\n[4]Settings\n[5]Back\n[6]Home\n[7]Exit\n\nInput your "
           "choice number: ");
    scanf("%d", &o);
    while (getchar() != '\n')
        ;
    // typical try again until valid input part that will reoccur in every
    // funtion that you come accross.
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
        // saves the p which is 1 rad or 2 degree into settings index[0] of
        // current user.wfile to save the new data.
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
            printf(
                "\nInvalid choice input...\n[1]Scintific or [2]Fixed Notation "
                "?\n\nChoose again (1/2): ");
            scanf("%d", &q);
            buffer;
        }
        // if you dont input 0 to go back and you select 1 aka scintific it sets
        // the set[1] to 16 which indicates that you use scientific .
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
                       "between "
                       "(1-15): ");
                scanf("%d", &q);
                buffer;
                while (q < 0 || q > 15) {
                    clear;
                    logicalc;
                    HEAD;
                    printf(p == 1 ? "Rad/Deg: Radians\n" : "Rad/Deg: Degree\n");
                    printf("\nInvalid choice input for decimal "
                           "precision...\n\nChoose "
                           "again between (1-15): ");
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
    // basically header makes it so u if head = "user:" this header funtion
    // strcats aka adds current users name after it making the string user
    // :[name] and the puts it in a cool box like design.
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
    // like other selection menu. just like register or logged.
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
        // if current users input[0][0] int '\0' that means history is available
        // int that case we print that users in[0] and out[0] on the history
        // tab, if not available we say not available .
        if (uid[current].in[0][0] != '\0')
            printf("\n[HISTORY]\n\n  %s\n  = %s\n", uid[current].in[0],
                   uid[current].out[0]);
        else
            printf("\n[HISTORY]\n\n  No hitory available...\n\n");
        printf("\n\n[INPUT]\n\n  ");
        m = 0;
        // takes input- removes space - check if user wants to exit or something
        // - if not we format it and keep a copy of that on string b. and the we
        // do constant validate and output and if the final output dosent say
        // invalid which btw we determine by passing a flag around that is m=0,
        // if m becomes 1 it means invalid. if m isnt 1 it gets saved in histry
        // by being passed to update.
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
    // basically it moves back everything to make space for the newly done math
    // to be added in history. also adds a [D] or [R] to mark which mode it got
    // calculated in
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
    printf(
        "\nHaving wrong syntanx in equation & \nInput outside parameters will "
        "result in Invalid Input while usage.\nOnly use x for the "
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

    // for different case they get saved into their respective slot in
    // uid[current]. wfile to save everything. key press to recurision for
    // further changes on custom function if needed.
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

        // takes the funtion with x. saves it in a , formats it and removes
        // space. if its not exit or one of those buttons , it carries on.
        printf("\nf(x) = ?\n");
        fgets(a, 512, stdin);
        n = 0;
        space(a, &n);

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
            if (n != 1)
                format(a, &n);
            strcpy(c, a);
            // copies the equation. takes input of numbers as string so u can
            // still take exit n stuff as inputs.
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
                    // similar ritual to calculator we set it up for calculation
                    // then it sends to the calc_funtion with the number and the
                    // string with x that is the equation. atof turns it into
                    // number new inputs that is . calc takes b to get modified
                    // and return as output.
                    if (n != 1)
                        format(a, &n);
                    constant(a, &m);
                    if (m != 1)
                        validate(a, &m);
                    if (m != 1) {
                        v = atof(a);
                        strcpy(b, c);
                        CALC_FUNCTION(b, v, &m);
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
    // turns radian to degree for funciton like tan cot csc to compare it to
    // their degree equivalent of parameters like for tan its 90. if user
    // settings is degree in the first place then changes nothing.
    if (uid[current].set[0] == 1)
        return v * PI / 180;
    return v;
}