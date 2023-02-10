#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
int my_strlen(char* str) {
    int count = 0;
    for (int i = 0; str[i]; i++) {
        count++;
    }
    return count;
}

char* rev_str(char* str) {
    char* str1 = malloc(sizeof(char) *my_strlen(str));
    int ind = 0;
    for (int i = my_strlen(str) - 1; i != -1; i--) {
        str1[ind] = str[i];
        ind++; 
    } 
    return str1;
}

int print_char_p(char* param_1) {
    write(1, param_1, my_strlen(param_1));
    int length_of_str = my_strlen(param_1);
    return length_of_str;
}
int print_decimal(int dec) {
    int number = dec;
    int flag = 0;
    int length = 0;
    char* str = malloc(sizeof(char)*10);
    if (number == 0) {
        str[0] = number + '0';
        write(1, &str[0], 1);
        return length += 1;
    }
    else if (number < 0) {
        number = number * -1;
        flag = 1;
    }
    if (number > 0) {
        for (int i = 0; number != 0 ; i++) {
            str[i] = number % 10 + '0';
            number = number / 10;
        }
    }  
    if (flag == 1) {
        str[my_strlen(str)] = '-';
    }  
    char* reversed = rev_str(str);

    length = print_char_p(reversed);
    return length;
}

int dec_to_hdec(long x) {
    char* hdec = malloc(sizeof(char) *20);
    int i = 0, temp;
    while (x != 0) {
        temp = x % 16;
        if (temp < 10) {
            hdec[i] = temp + 48;
            i++;
        }
        else {
            hdec[i] = temp + 87;
            i++;
        }
        x = x / 16;
    }
    char* str = rev_str(hdec);
    write(1, str, my_strlen(str));
    return my_strlen(str);
}
int dec_to_hex(int x) {
    char* hdec = malloc(sizeof(char) *20);
    int i = 0, temp;
    while (x != 0) {
        temp = x % 16;
        if (temp < 10) {
            hdec[i] = temp + 48;
            i++;
        }
        else {
            hdec[i] = temp + 55;
            i++;
        }
        x = x / 16;
    }
    char* str = rev_str(hdec);
    write(1, str, my_strlen(str));
    return my_strlen(str);
}

int convert_octal(int octal){
    int octalnum = 0, temp = 1, count = 0;

    while (octal != 0)
    {
        count++;
    	octalnum = octalnum + (octal % 8) * temp;
    	octal = octal / 8;
        temp = temp * 10;
    }
    char* str = malloc(sizeof(char) *count) ;
    for(int in = 0; octalnum != 0; in++){
        str[in] = (octalnum % 10) + '0';
        octalnum = octalnum / 10;
    }
    char* reversed = rev_str(str);
    int length = print_char_p(reversed);
    return length;
}
int un_int_print(int un_int) {
    char* str = malloc(sizeof(char)* 10);
    if (un_int < 0) {
        un_int = un_int * -1;
    }
     if (un_int > 0) {
        for (int i = 0; un_int != 0 ; i++) {
            str[i] = un_int % 10 + '0';
            un_int = un_int / 10;
        }
    }  
    char* reversed = rev_str(str);
    return print_char_p(reversed);
}
int my_printf(char* format, ...) {
    int length_of_content = 0;
    va_list list_of_var;
    va_start(list_of_var, format);
    for (int i = 0; format[i]; i++) {
        if (format[i] == '%' && format[i + 1] == 's') {
            char* str = va_arg(list_of_var, char*);
            if(str == NULL){
                str = "(null)";
            }
            length_of_content += print_char_p(str);
            i++;
        }
        else if (format[i] == '%' && format[i + 1] == 'c') {
            char c = va_arg(list_of_var, int);
            write(1, &c, 1);
            length_of_content++;
            i++;
        }
        else if (format[i] == '%' && format[i + 1] == 'd') {
            int dec = va_arg(list_of_var, int);
            length_of_content += print_decimal(dec);
            i++;
        }
        else if (format[i] == '%' && format[i + 1] == 'x') {
            int hdex = va_arg(list_of_var, int);
            length_of_content += dec_to_hex(hdex);
            i++;
        }
        else if (format[i] == '%' && format[i + 1] == 'o') {
            int octal = va_arg(list_of_var, int);
            length_of_content += convert_octal(octal); 
            i++;
        }
        else if (format[i] == '%' && format[i + 1] == 'u') {
            int un_int = va_arg(list_of_var, int);
            length_of_content += un_int_print(un_int);
            i++;
        }
        else if (format[i] == '%' && format[i + 1] == 'p') {
            unsigned long v = (unsigned long)va_arg(list_of_var, void*);
            write(1, "0x", 2);
            length_of_content+=2;
            length_of_content += dec_to_hdec(v);
            i++;
        }
        else {
            write(1, &format[i], 1);
            length_of_content++;
        }
    }
    return length_of_content;
}

// int main() {                                                                                                                                                  
//     int x = my_printf("1337!\n");    
//     printf("%d\n", x);                                                                                                                                  
//     return 0;                                                                                                                                           
// }