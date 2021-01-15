#pragma once
enum Compare {EQUALS, MORE, LESS};
Compare StrCompare(char* fir, char* sec) {
    int i = 0;
    while (fir[i] != '\0' && sec[i] != '\0') {
        if (fir[i] > sec[i]) {
            return MORE;
        }
        else if (fir[i] < sec[i]) {
            return LESS;
        }
        ++i;
    }
    if (fir[i] != '\0') {
        return MORE;
    }
    else if (sec[i] != '\0') {
        return LESS;
    }
    else {
        return EQUALS;
    }
}
void Convert(char* str) {
    for (int i = 0; str[i] != '\0'; ++i) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] = str[i] - 'A' + 'a';
        }
    }
}
void Assign(char* fir, char* sec) {
    int i;
    for (i = 0; sec[i] != '\0'; ++i) {
        fir[i] = sec[i];
    }
    fir[i] = sec[i];
}
