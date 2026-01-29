#include <stdio.h>

int sumDigits(int num)
{
    int sum = 0;
    if (num < 0) {
        num = -num;
    }
    while (num > 0) {
        sum += num % 10;
        num /= 10;
    }
    return sum;
}

const char* getOrdinalSuffix(int n)
{
    if (n % 100 >= 11 && n % 100 <= 13) {
        return "th";
    }
    switch (n % 10) {
        case 1: return "st";
        case 2: return "nd";
        case 3: return "rd";
        default: return "th";
    }
}

int main()
{
    int count = 1;
    int value;
    double sum_even = 0, sum_odd = 0;
    int count_even = 0, count_odd = 0;
    int digit_sum;

    printf("Enter the %d%s value: ", count, getOrdinalSuffix(count));
    scanf("%d", &value);

    if (value == 0) {
        printf("There is no average to compute.\n");
        return 0;
    }

    while (value != 0) {
        digit_sum = sumDigits(value);
        if (digit_sum % 2 == 0) {
            sum_even += value;
            count_even++;
        } else {
            sum_odd += value;
            count_odd++;
        }

        count++;
        printf("Enter the %d%s value: ", count, getOrdinalSuffix(count));
        scanf("%d", &value);
    }

    if (count_even > 0 && count_odd > 0) {
        printf("Average of input values whose digits sum up to an even number: %.2f\n", sum_even / count_even);
        printf("Average of input values whose digits sum up to an odd number: %.2f\n", sum_odd / count_odd);
    } else if (count_even > 0) {
        printf("Average of input values whose digits sum up to an even number: %.2f\n", sum_even / count_even);
    } else if (count_odd > 0) {
        printf("Average of inputs whose digits sum up to an odd number: %.2f\n", sum_odd / count_odd);
    }

    return 0;
}
