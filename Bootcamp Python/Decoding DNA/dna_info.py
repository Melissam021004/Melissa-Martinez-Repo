# Melissa Martinez D4E3E5 mmart213
import random

def encode_sequence(word):
    """
    Function: encode_sequence: encodes the parameter "word" by first turning into ASCII, then binary, and then into DNA nucleotides

    Parameters
    ----------
    word : Word(s) that must be encoded

    Returns
    -------
    encoded : The encoded version of the inputted text

    """
    encoded = ""
    
    for char in word:
        bi = bin(ord(char)).replace('b', '')
        for i in range(4):
            if bi.find('00', 2*i, 2*i+2) != -1:
                encoded += 'A'
            elif bi.find('01', 2*i, 2*i+2) != -1:
                encoded += 'T'
            elif bi.find('10', 2*i, 2*i+2) != -1:
                encoded += 'C'
            elif bi.find('11', 2*i, 2*i+2) != -1:
                encoded += 'G'
    
    return encoded
    
def decode_sequence (encoded):
    
    """
    Function: decode_sequence: takes the encoded parameter, "encoded", and turns the DNA nucleotide into its corresponding binary, and then ASCII, and then alphanumeric version

    Parameters
    ----------
    encoded: The encoded message

    Returns
    -------
    word : The decoded message

    """
    word = ""
    bins = [''];
    loc = 0
    num = 0
    for char in encoded:
        match char:
            case 'A':
                bins[loc] += '00'
            case 'T':
                bins[loc] += '01'
            case 'C':
                bins[loc] += '10'
            case 'G':
                bins[loc] += '11'
            case _:
                print("Not valid")
        num += 1
        if num == 4:
            loc += 1
            num = 0
            bins.append('')
            
    bins.pop()
    for i in bins:
        word += chr(int(i, 2))

    return word
    
def encrypt_decrypt (word, key = "CAT"):
    """
    Function: encrypt_decrypt: Encodes the parameter "word" by using the exclusive or function to compare to the key

    Parameters
    ----------
    word : the word that needs to be encoded
    (optional) key: series of letters to which the letters in word will be compared to using exclusive or

    Returns
    -------
    out: the original word encoded using the key

    """
    encoded = []
    for x in word:
        encoded.append(x);
    num = 0
    xor = {'AA':'A', 'AT':'T', 'TA':'T', 'AC':'C', 'CA':'C', 'AG':'G', 'GA':'G', 'TT':'A', 'TC':'G', 'CT':'G', 'TG':'C', 'GT':'C', 'CC':'A', 'CG':'T', 'GC':'T', 'GG':'A'}
    for a in key:
        for b in encoded:
            encoded[num] = xor[a+b]
            num += 1
        num = 0
        
    out = (' '.join([str(elem) for elem in encoded])).replace(" ", "")
    return out
    
def synthesizer (sequence):
    """
    Function: synthesizer: Returns a sequence possibly produced by a robot given the error probabilities

    Parameters
    ----------
    sequence : the sequence given to the robot to encode

    Returns
    -------
    synth: a possible synthesized sequence by the robot

    """
    synth = ""
    for char in sequence:
        a = random.randint(1,100)
        match char:
            case 'A':
                synth += 'A'
            case 'T':
                if a <= 90:
                    synth += 'T'
                elif a <= 95:
                    synth += 'A'
                elif a <= 98:
                    synth += 'C'
                else:
                    synth += 'G'
            case 'G':
                if a <= 95:
                    synth += 'G'
                elif a <= 97:
                    synth += 'T'
                elif a <= 99:
                    synth += 'C'
                else:
                    synth += 'A'
            case 'C':
                if a <= 97:
                    synth += 'C'
                elif a <= 98:
                    synth += 'A'
                elif a <= 99:
                    synth += 'T'
                else:
                    synth += 'G'
    return synth
                
    
def error_count(a, b):
    """
    Function: error_count: counts how many differences there are between the two parameter strings

    Parameters
    ----------
    a : first string to compare
    b : second string to compare

    Returns
    -------
    mismatches: total number of character differences between the strings a and b

    """
    mismatches = 0
    for i in range(len(a) - 1):
        if a[i] != b[i]:
            mismatches += 1
            
    return mismatches
    
def redundancy(num, syn):
    """
    Function: redundancy: calls the synthesis function n number of times and returns the most likely series of nucleotides

    Parameters
    ----------
    num : number of times to run the synthesis function
    syn : the series of nucleotides to input in the synthesis function

    Returns
    -------
    out: the most probable series of nucleotides 

    """
    counter = [[0 for i in range(len(syn))] for j in range(4)]
    for n in range(num):
        number = 0
        for char in synthesizer(syn):
            match char:
                case 'A':
                    counter[0][number] += 1
                case 'T':
                    counter[1][number] += 1
                case 'C':
                    counter[2][number] += 1
                case 'G':
                    counter[3][number] += 1
            number += 1
            
    
    bases = ['A', 'T', 'C', 'G']
    out = ''
    for i in range(len(syn)):
        max = counter[0][i]
        base = bases[0]
        for b in range (1,4):
            if counter[b][i] > max:
                max = counter[b][i]
                base = bases[b]
        out += base
    
    return out
        