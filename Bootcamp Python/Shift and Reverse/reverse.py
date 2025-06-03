## Melissa Martinez mmart213 D4E3E5
 
## Variable and array initialization
alp = 'abcdefghijklmnopqrstuvwxyz '
rev = 'zyxwvutsrqponmlkjihgfedcba '
out = 'The plaintext message is: '
punct = '''!#$%"&'()*+,-./:;<=>?@[\]^_`{|}~'''
 
## Prompting user for input
encrypted = input("Enter the encrypted message: ");
 
## Creating the decrypted string
for i in encrypted:
    if(i in punct):
        out += i
    else:
        out += rev[alp.find(i)]

## Outputting the message
print (out);
     

