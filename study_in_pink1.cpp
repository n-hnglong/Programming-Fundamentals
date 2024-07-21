#include "study_in_pink1.h"

bool readFile(
        const string & filename,
        int & HP1,
        int & HP2,
        int & EXP1,
        int & EXP2,
        int & M1,
        int & M2,
        int & E1,
        int & E2,
        int & E3
) {
    // This function is used to read the input file,
    // DO NOT MODIFY THIS FUNTION
    ifstream ifs(filename);
    if (ifs.is_open()) {
        ifs >> HP1 >> HP2
            >> EXP1 >> EXP2
            >> M1 >> M2
            >> E1 >> E2 >> E3;
        return true;
    }
    else {
        cerr << "The file is not found" << endl;
        return false;
    }
}

////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
/// Complete the following functions
/// DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////


int checkEXP (int & exp){
    if (exp > 600) return 600;
    else if (exp < 0) return 0;
    else return exp;
}
int checkHP (int & hp){
    if (hp > 666) return 666;
    else if (hp < 0) return 0;
    else return hp;
}
int checkM (int & m){
    if (m > 3000) return 3000;
    else if (m < 0) return 0;
    else return m;
}

// Task 1

void firstMeet_1(int & exp1, int & exp2, int e1){
    exp1 = checkEXP(exp1);
    exp2 = checkEXP(exp2);
    switch(e1){
        case 0:
            exp2 = exp2 + 29;
            exp2 = checkEXP(exp2);
            break;
        case 1:
            exp2 = exp2 + 45;
            exp2 = checkEXP(exp2);
            break;
        case 2:
            exp2 = exp2 + 75;
            exp2 = checkEXP(exp2);
            break;
        default:
            exp2 = exp2 + 29 + 45 + 75;
            exp2 = checkEXP(exp2);
            break;
    }
    int d = e1 * 3 + exp1 * 7;
    if ((d % 2) == 0) exp1 = exp1 + d/200.0 + 0.999;
    else exp1 = exp1 - d/100.0 + 0.999;
    exp1 = checkEXP(exp1);
    
}

void firstMeet_2(int & exp1, int & exp2, int e1){
    exp1 = checkEXP(exp1);
    exp2 = checkEXP(exp2);
    if (e1 >= 4 && e1 <= 19) {
        exp2 = exp2 + e1/4.0 + 19 + 0.999;
        exp2 = checkEXP(exp2);
        }
    else if (e1 >= 20 && e1 <= 49) {
        exp2 = exp2 + e1/9.0 + 21 + 0.999;
        exp2 = checkEXP(exp2);
        }
    else if (e1 >= 50 && e1 <= 65) {
        exp2 = exp2 + e1/16.0 + 17 + 0.999;
        exp2 = checkEXP(exp2);
    }
    else if (e1 >= 66 && e1 <= 79) {
        exp2 = exp2 + e1/4.0 + 19 + 0.999;
        if (exp2 > 200) exp2 = exp2 + e1/9.0 + 21 + 0.999;
        exp2 = checkEXP(exp2);
    }
    else {
        exp2 = exp2 + e1/4.0 + 19 + 0.999;
        exp2 = exp2 + e1/9.0 + 21 + 0.999;
        if (exp2 > 400) {
            exp2 = exp2 + e1/16.0 + 17 + 0.999;
            exp2 = exp2 * 1.15 + 0.999;
        }
        exp2 = checkEXP(exp2);
    }
    exp1 = exp1 - e1;
    exp1 = checkEXP(exp1);
}

int firstMeet(int & exp1, int & exp2, int e1) {
    // TODO: Complete this function
    
    if (e1 >= 0 && e1 <= 3) {
        firstMeet_1(exp1, exp2, e1);
        return exp1 + exp2;
    }
    else if (e1 >= 4 && e1 <= 99) {
        firstMeet_2(exp1, exp2, e1);
        return exp1 + exp2;
    }
    else return -99;   
}

// Task 2

double traceLuggage_1(int & exp1){
    exp1 = checkEXP(exp1);
    int s = round(sqrt(exp1*1.0)) * round(sqrt(exp1*1.0));
    if (exp1 >= s) return 1;
    else return (exp1*1.0/s + 80)/123.0;
}

double traceLuggage_2(int & hp1, int & exp1, int & m1, int e2){
    hp1 = checkHP(hp1);
    exp1 = checkEXP(exp1);
    m1 = checkM(m1);
    int used = 0;
    double used_max = m1 *0.5;
    do{
        if (e2 % 2 == 0){
            if (m1 == 0) break;
        }
        else {
            if (used > used_max || m1 == 0) break;
        }
        if (hp1 < 200) {
            hp1 = hp1 * 1.3 + 0.999;
            m1 = m1 - 150;
            used = used + 150;
        }
        else {
            hp1 = hp1 * 1.1 + 0.999;
            m1 = m1 - 70;
            used = used + 70;
        }
        hp1 = checkHP(hp1);
        m1 = checkM(m1);
        if (e2 % 2 == 0){
            if (m1 == 0) break;
        }
        else {
            if (used > used_max || m1 == 0) break;
        }
        if (exp1 < 400){
            m1 = m1 - 200;
            used = used + 200;
        }
        else {
            m1 = m1 - 120;
            used = used + 120;
        }
        exp1 = exp1 * 1.13 + 0.999;
        exp1 = checkEXP(exp1);
        m1 = checkM(m1);
        if (e2 % 2 == 0){
            if (m1 == 0) break;
        }
        else {
            if (used > used_max || m1 == 0) break;
        }
        if (exp1 < 300) {
            m1 = m1 - 100;
            used = used + 100;
        }
        else {
            m1 = m1 - 120;
            used = used + 120;
        }
        exp1 = exp1 * 0.9 + 0.999;
        exp1 = checkEXP(exp1);
        m1 = checkM(m1);
        if (e2 % 2 == 0){
            if (m1 == 0) break;
        }
        else {
            if (used > used_max || m1 == 0) break;
        }
    }while (e2 % 2 != 0);
    exp1 = exp1 * 1.17 + 0.999;
    hp1 = hp1 * 0.83 + 0.999;
    hp1 = checkHP(hp1);
    exp1 = checkEXP(exp1);
    return traceLuggage_1 (exp1);
}

double traceLuggage_3(int & e2){
    int p[10] = {32, 47, 28, 79, 100, 50, 22, 83, 64, 11};
    if (e2 < 10) return p[e2]/100.0;
    else return p[((e2 % 10) + (e2 / 10)) % 10]/100.0;
}

int traceLuggage(int & HP1, int & EXP1, int & M1, int E2) {
    // TODO: Complete this function
    if (E2 < 0 || E2 > 99) return -99;
    else {
        
        double p1 = traceLuggage_1(EXP1), p2 = traceLuggage_2(HP1, EXP1, M1, E2), p3 = traceLuggage_3(E2);
        if ((p1 + p2 + p3)/3 < 0.5){
            HP1 = HP1 * 0.85 + 0.999;
            EXP1 = EXP1 * 1.15 + 0.999;
        }
        else {
            if ((p1 + p2 + p3)/3 == 1) EXP1 = EXP1 * 0.75 + 0.999;
            else {
                HP1 = HP1 * 0.9 + 0.999;
                EXP1 = EXP1 * 1.2 + 0.999;
            }
        }
        HP1 = checkHP(HP1);
        EXP1 = checkEXP(EXP1);
        M1 = checkM(M1);
        return HP1 + EXP1 + M1;
    }
}

// Task 3

int findTaxi(int & n){
    int s = 0;
    while(n > 0){
        s = s + n%10;
        n = n / 10;
    }
    return s;
}

int chaseTaxi(int & HP1, int & EXP1, int & HP2, int & EXP2, int E3) {
    // TODO: Complete this function
    
    if (E3 < 0 || E3 > 99) return -99;
    else{
    EXP1 = checkEXP(EXP1);
    EXP2 = checkEXP(EXP2);
    HP1 = checkHP(HP1);
    HP2 = checkHP(HP2);
    int matrix[10][10];
    int x = 0, y = 0;
    for (int i = 0; i < 10; i++){
        for (int j = 0; j < 10; j++){
            matrix[i][j] = ((E3*j) + (i*2)) * (i-j);
            if (matrix[i][j] > (E3*2)) x++;
            if (matrix[i][j] < (-E3)) y++;
        }
    }
    x = findTaxi(x);
    y = findTaxi(y);

    x = findTaxi(x);
    y = findTaxi(y);

    int scoreSW = INT_MIN, scoreTaxi = matrix[x][y];
    int score_array[10][10] = {};
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if ((i - x == j - y) || (i - x == -(j - y))) {
                score_array[i][j] = matrix[i][j];
            } 
        }
    }
    for (int i = 0; i < 10; i++){
        for (int j = 0; j < 10; j++){
            if (scoreSW < score_array[i][j]) scoreSW = score_array[i][j];
        }
    }
    if (abs(scoreSW) >= abs(scoreTaxi)) {
        HP1 = HP1 * 1.1 + 0.999;
        EXP1 = EXP1 * 1.12 + 0.999;

        HP2 = HP2 * 1.1 + 0.999;
        EXP2 = EXP2 * 1.12 + 0.999;

        HP1 = checkHP(HP1);
        HP2 = checkHP(HP2);
        EXP1 = checkEXP(EXP1);
        EXP2 = checkEXP(EXP2);
        return scoreSW;
    }
    else{
        HP1 = HP1 * 0.9 + 0.999;
        EXP1 = EXP1 * 0.88 + 0.999;

        HP2 = HP2 * 0.9 + 0.999;
        EXP2 = EXP2 * 0.88 + 0.999;
    
        HP1 = checkHP(HP1);
        HP2 = checkHP(HP2);
        EXP1 = checkEXP(EXP1);
        EXP2 = checkEXP(EXP2);
        return scoreTaxi;
    }
}
}

// Task 4
int checkDoubleChars(const char * s){
    for (int i = 0; i < strlen(s); i++){
        if (s[i] == s[i+1] && s[i] == s[i+2]) return i;
    }
    return -1;
}
bool checkSpecialChars(const char * s){
    char spec[5] = {'@', '#', '%', '$', '!'};
    for (int i = 0; i < strlen(s); i++){
        for (int j = 0; j < 5; j++){
            if (s[i] == spec[j]) return true;
        }
    }
    return false;
}
int checkChars(const char * s){
    for (int i = 0; i < strlen(s); i++){
        if (!(s[i] >= 'a' && s[i] <= 'z') && !(s[i] >= 'A' && s[i] <= 'Z') && !(s[i] >= '0' && s[i] <= '9') && !(s[i] == '@') && !(s[i] == '#') && !(s[i] == '!') && !(s[i] == '$') && !(s[i] == '%')) return i;
    }
    return -1;
}
int checkPassword(const char * s, const char * email) {
    // TODO: Complete this function
    char se[100];
    const char *a_symbol = strchr(email, '@');
    int length = a_symbol - email;
    strncpy(se, email, length);
    se[length] = '\0';

    const char *res = strstr(s, se);
    if (strlen(s) < 8) return -1;
    else if (strlen(s) > 20) return -2;
    else if (res != NULL) return -(300 + int(res - s));
    else if (checkDoubleChars(s) != -1) return -(400 + checkDoubleChars(s));
    else if (checkSpecialChars(s) == false) return -5;
    else if (checkChars(s) != -1) return checkChars(s);
    else return -10;
}

// Task 5
int findCorrectPassword(const char * arr_pwds[], int num_pwds) {
    // TODO: Complete this function
    int maxFre = 0, maxLen = 0, result = -1;
    for (int i = 0; i < num_pwds; i++) {
        int fre = 0;
        int length = strlen(arr_pwds[i]);
        for (int j = 0; j < num_pwds; j++) {
            if (strcmp(arr_pwds[i], arr_pwds[j]) ==0) fre++;
        }
        if (fre > maxFre || (fre == maxFre && maxLen < length)) {
            maxFre = fre;
            maxLen = length;
            result = i;
        }
    }
    return result;
}

////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////