#import <cs50.h>
#import <stdio.h>
#import <math.h>

bool lunh(int csum);
long long sum(long long card);
long long firstdigs(long long ccard);
long long expon(int x, int y);

int carddigits = 1;
//main has the big daddy if-else branch that checks to see if the card number matches all the criteria for the different types of cards. 
//fxns to obtain the first 1 or 2 digits of the card based on length as well as luhn's algo is called by main.
int main(void) 
{
    int sumresult = 0;

    long long cardnum = get_long_long ("Enter a credit card number: ");

    sumresult = sum(cardnum);

    if(carddigits - 1 == 15 && (firstdigs(cardnum) == 34 || firstdigs(cardnum) == 37) && lunh(sumresult))
    {
        printf("AMEX\n");
    }
    else if((carddigits - 1 == 13 || carddigits - 1 == 16) && firstdigs(cardnum) == 4 && lunh(sumresult))
    {
        printf("VISA\n");
    }
    else if (carddigits - 1 == 16 && (firstdigs(cardnum) >= 51 && firstdigs(cardnum) <= 55) && lunh(sumresult))
    {
        printf("MASTERCARD\n");
    }
    else
    {
        printf("INVALID\n");
    }
}

//this is the actual fxn doing the heavy lifting for the luhn algo, the luhn fxn is just a boolean to check fi the result of the sum fxn ends in a 0
long long sum(long long card)
{
    int even=0;
    int evensum=0;
    int odd=0;
    int result=0;
    carddigits = 1;
    do
    {
        if (carddigits % 2 == 0)
        {
            even = (2 * (card % 10));
             do
            {
                evensum = evensum + (even % 10);
                even = even/10;
            }
            while(even);
        }
        else
        {
             odd = odd + (card % 10);
        }

        card = card/10;
        carddigits ++;
    }
    while(card);

    do
    {
        evensum = evensum + (even % 10);
        even = even/10;
    }
    while(even);

    result = evensum + odd;
    //printf ("the total sum is %i\n", result);

    return (result);
}

long long firstdigs(long long ccard) //fxn to find the first 2 digits of the card number based on the carddigits global variable
{
    long long fdigs = 0;
    long long digit = 0;
    long long denom = 10;

    denom = expon(10, carddigits - 2);
    digit = ccard / denom;

    if(digit == 3 || digit == 5)
    {
        denom = expon(10, carddigits - 3);
        fdigs = ccard /denom;
    }
    else
    {
        denom = expon(10, carddigits - 2);
        fdigs = ccard / denom;
    }
    return fdigs;
}

long long expon(int x, int y) //raises integer x to the power of integer y
{
    long result = 1;
    for(int i = 0; i < y; i++)
    {
        result *= x;
    }
    return result;
}

bool lunh(int csum)
{
    if(csum%10 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
