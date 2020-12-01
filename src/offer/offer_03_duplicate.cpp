bool duplicate(int numbers[], int length, int* duplication) {
    if (numbers == nullptr || length <= 0) {
        return false;
    }
    for (int i = 0; i < length; ++i) {
        if (numbers[i] < 0 || numbers[i] > length - 1) {
            return false;
        }
    }
    for (int i = 0; i < length; ++i) {
        while (numbers[i] != i) { //当前数不在他的位置上,那就把这个数放到他应该去的numbers[numbers[i]]上
            if (numbers[i] == numbers[numbers[i]]) {
                *duplication = numbers[i];
                return true;
            }
            int tmp = numbers[i];
            numbers[i] = numbers[numbers[i]];
            numbers[tmp] = tmp;
        }
    }
    return false;
}
