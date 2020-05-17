import json
from Encoder import Encoder
from Decoder import Decoder

command = ''  # command user write
IS_RUN = True

print('\nlist of commands:\n'
      '1) decode - decode word from file \'encoded\' and write to file \'decoded\'\n'
      '2) encode < ENCODE TYPE > - encode, where type is in [caesar, vigenere, playfair]')
print('dictionary length =', len(Decoder.dictionary), '\n')
while IS_RUN:
    command = input('#> ').strip()
    com_words = command.split(' ')

    if com_words[0].lower() == 'decode':
        # decoded_file = open('decoded.txt', 'w')
        encoded_file = open('encoded.txt', 'r')
        print(Decoder.decode(encoded_file.read()))
        print('\nDONE!\n')
        IS_RUN = False

    elif com_words[0].lower() == 'encode':
        if len(com_words) >= 2:
            if com_words[1].lower() == 'caesar':
                print("enter key (spaces are symbols too), or press enter for default")
                key = input('# key > ')
                if len(key) > 0: key = int(key)
                else: key = None
                decoded_file = open('decoded.txt', 'r')
                encoded_file = open('encoded.txt', 'w')
                encoded_file.write(Encoder.caesar_encode(decoded_file.read(), key or 3))
                print('\nDONE!\n')
                IS_RUN = False
            elif com_words[1].lower() == 'vigenere':
                print("enter key (spaces are symbols too), or press enter for default")
                key = input('# key > ')
                if len(key) > 0: key = key.strip()
                else: key = None
                decoded_file = open('decoded.txt', 'r')
                encoded_file = open('encoded.txt', 'w')
                encoded_file.write(Encoder.vigenere_encode(decoded_file.read(), key or "KEY"))
                print('\nDONE!\n')
                IS_RUN = False
            elif com_words[1].lower() == 'playfair':
                print("enter key (spaces are symbols too), or press enter for default")
                key = input('# key > ')
                if len(key) > 0: key = key.strip()
                else: key = None
                decoded_file = open('decoded.txt', 'r')
                encoded_file = open('encoded.txt', 'w')
                encoded_file.write(Encoder.playfair_encode(decoded_file.read(), key or "KEY"))
                print('\nDONE!\n')
                IS_RUN = False
            else:
                print('\nunknown encoder \'%s\'\n' % com_words[1])
        else:
            print('\nempty encoder type\n')
    else:
        print('\nunknown command \'%s\'\n' % com_words[0])
