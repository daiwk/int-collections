class Solution {
public:
    void replaceSpace(char *str,int length) {
        if (str == NULL || length <= 0) {
            return;
        }
        int old_len = 0;
        int new_len = 0;
        int space_cnt = 0;
        while (str[old_len] != '\0') {
            if (str[old_len] == ' ') space_cnt++;
            old_len++;
        }
        new_len = old_len + 2 * space_cnt;
        if (new_len > length) {
            return;
        }
        int pOldlength = old_len; //注意不要减一因为隐藏个‘\0’也要算里
        int pNewlength = new_len;
        while (pOldlength >= 0 && pNewlength > pOldlength) {
             if (str[pOldlength] == ' ') {
                 str[pNewlength--]='0';
                 str[pNewlength--]='2';
                 str[pNewlength--]='%';
                 } else {//不是空格就把pOldlength指向的字符装入pNewlength指向的位置
                     str[pNewlength--]=str[pOldlength];
                 }
                 pOldlength--; //不管是if还是else都要把pOldlength前移      
          }       

    }
};
