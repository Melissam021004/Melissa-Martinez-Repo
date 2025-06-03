## Melissa Martinez mmart213 D4E3E5


## Open Pride and Prejudice file, shortened to pp
pp_file = open('pride_prejudice.txt', 'r', encoding='utf-8-sig')


## Declaring alphabet and freq list
alp = 'abcdefghijklmnopqrstuvwxyz'
freq = []
chi_vals = []
freq_enc = []


## Setting all character counts to 0
for x in range(26):
    freq.append(0)
    chi_vals.append(0);
    freq_enc.append(0);


## Iterate through each line in pp_file while counting appearances of letters and total number of characters
count = 0;
for line in pp_file:
    for ch in line:
        if ch.isalpha():
            freq[alp.find(ch)] += 1
            count = count + 1
pp_file.close()


## Calculating the frequency of the letters of the alphabet
for x in range(26):
    freq[x] = freq[x]/count


## Prompting user for input
encrypted = input("Enter the encrypted message: ");

## Length of the encrypted message
n = len(encrypted)

## Times each letter appears in the encrypted message
for ch in encrypted:
    if(ch.isalpha()):
        freq_enc[alp.find(ch)] += 1

## Length of the encrypted message
n = len(encrypted)

## Calculating all chi values for all shifts
shift = 1
while(shift < 26):
    alp = alp[25] + alp[0:25]
    freq_enc.insert(0,freq_enc.pop())
    for x in range(26):
        chi_vals[26-shift] = chi_vals[26-shift] + ((freq_enc[x]-freq[x]*n)**2)/(freq[x]*n)
    shift = shift + 1


## Finding lowest chi value
## Popped last chi_vals because it was 0
shift_val = 1
chi_vals.pop(0)
lowest_chi = chi_vals[0]
for x in range(25):
    if(chi_vals[x] < lowest_chi):
        lowest_chi = chi_vals[x]
        shift_val = x + 1
    
## Creating the shifted alphabet and punctuation
punct = '''!#$%"&'()*+,-./:;<=>?@[\]^_`{|}~'''
alp = 'abcdefghijklmnopqrstuvwxyz'
shift_alp = alp[(26-shift_val):] + alp[0:(26-shift_val)]

## Decyphering the encrypted message
out = 'The plaintext message is: '
for i in encrypted:
    if(i.isspace()):
        out += ' '
    elif(i in punct):
        out += i
    else:
        out += shift_alp[alp.find(i)]
    
print(out)