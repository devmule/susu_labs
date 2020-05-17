import json
from Encoder import Encoder
from typing import Dict


class Decoder:
    alphabet = Encoder.alphabet

    with open('dict.json') as json_file:
        dictionary = json.load(json_file)
    json_file.close()

    @staticmethod
    def decode(encoded_text: str) -> str:
        caesar_key, caesar_frequency = Decoder.decode_caesar(encoded_text)
        print('caesar:', '\nkey: ', caesar_key, '\nfrequency: ', caesar_frequency, '\n')
        return Encoder.caesar_decode(encoded_text, caesar_key)
        """vigenere_key, vigenere_frequency = Decoder.decode_vigenere(encoded_text)
        print('vigenere:', '\nkey: ', vigenere_key, '\nfrequency: ', vigenere_frequency, '\n',
              Encoder.vigenere_decode(encoded_text, vigenere_key))"""

    @staticmethod
    def decode_caesar(encoded_text: str, min_frequency: float = .9):
        best_key = 0
        best_frequency = 0
        for key in range(len(Decoder.alphabet)):
            print('try key', key, end='')
            decoded = Encoder.caesar_decode(encoded_text, key).split(' ')
            frequency_sum = 0
            for word in decoded:
                for d in Decoder.dictionary:
                    if Decoder.similarity(word.upper(), d.upper()) > .75:
                        frequency_sum += 1
                        break
            frequency = frequency_sum / len(decoded)
            print(' frequency = ', frequency)
            if frequency > best_frequency:
                best_key = key
                best_frequency = frequency
            if frequency > min_frequency: break
        return best_key, best_frequency

    @staticmethod
    def decode_vigenere(encoded_text: str, min_frequency: float = .8):
        best_key = "A"
        best_frequency = 0
        for key in [x for x in Decoder.alphabet] + \
                   [x + y for x in Decoder.alphabet for y in Decoder.alphabet] + \
                   [x + y + z for x in Decoder.alphabet for y in Decoder.alphabet for z in Decoder.alphabet]:
            print('try key', key, end='')
            decoded = Encoder.vigenere_decode(encoded_text, key).split(' ')
            frequency_sum = 0
            for word in decoded:
                for d in Decoder.dictionary:
                    if Decoder.similarity(word.upper(), d.upper()) > .75:
                        frequency_sum += 1
                        break
            frequency = frequency_sum / len(decoded)
            print(' frequency = ', frequency)
            if frequency > best_frequency:
                best_key = key
                best_frequency = frequency
            if frequency > min_frequency: break
        return best_key, best_frequency

    @staticmethod
    def similarity(text_1: str, text_2: str) -> float:
        summary = max(len(text_1), len(text_2))
        similarities = 0
        for i in range(min(len(text_1), len(text_2))):
            if text_1[i].upper() == text_2[i].upper():
                similarities += 1
        return similarities / summary

    @staticmethod
    def letter_frequency(text: str) -> Dict[str, float]:  # deprecated
        frequency: Dict[str, float] = {}
        for letter in text:
            if letter.upper() in frequency.keys():
                frequency[letter.upper()] += 1
            else:
                frequency[letter.upper()] = 1
        return frequency


if __name__ == '__main__':
    print(Decoder.similarity('text_1', 'text_2'))  # = 0.83
    print(Decoder.similarity('text_1', 'text_1'))  # = 1
    print(Decoder.similarity('text', 'hi, world'))  # = 0
