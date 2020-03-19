import json
import Encoder

with open('dict.json') as json_file:
    dictionary = json.load(json_file)
json_file.close()

command = ''  # command user write
IS_RUN = True

print('\nlist of commands:\n'
      '1) decode - decode word from file \'encoded\' and write to file \'decoded\'\n'
      '2) encode < ENCODE TYPE > - encode, where type is in [caesar, vigenere, playfair]')
print('dictionary length =', len(dictionary), '\n')
while IS_RUN:
    command = input('#> ').strip()
    com_words = command.split(' ')

    if com_words[0] == 'decode':
        # decoded_file = open('decoded.txt', 'w')
        encoded_file = open('encoded.txt', 'r')
        dictionary_frequency = {}
        text_frequency = {}
        for word in dictionary:
            for letter in word:
                if letter.upper() in Encoder.alphabet:
                    if letter.upper() in dictionary_frequency.keys():
                        dictionary_frequency[letter.upper()] += 1
                    else:
                        dictionary_frequency[letter.upper()] = 1
        # print(dictionary_frequency)
        text = encoded_file.read()
        for letter in text:
            if letter.upper() in Encoder.alphabet:
                pass
        # todo make
        # try ceasar shifer

        print('\nDONE!\n')
        IS_RUN = False

    elif com_words[0] == 'encode':
        if len(com_words) >= 2:
            if com_words[1] == 'caesar':
                decoded_file = open('decoded.txt', 'r')
                encoded_file = open('encoded.txt', 'w')
                encoded_file.write(Encoder.caesar_encode(decoded_file.read()))
                print('\nDONE!\n')
                IS_RUN = False
            elif com_words[1] == 'vigenere':
                decoded_file = open('decoded.txt', 'r')
                encoded_file = open('encoded.txt', 'w')
                encoded_file.write(Encoder.vigenere_encode(decoded_file.read()))
                print('\nDONE!\n')
                IS_RUN = False
            elif com_words[1] == 'playfair':
                decoded_file = open('decoded.txt', 'r')
                encoded_file = open('encoded.txt', 'w')
                encoded_file.write(Encoder.playfair_encode(decoded_file.read()))
                print('\nDONE!\n')
                IS_RUN = False
            else:
                print('\nunknown encoder \'%s\'\n' % com_words[1])
        else:
            print('\nempty encoder type\n')
    else:
        print('\nunknown command \'%s\'\n' % com_words[0])
