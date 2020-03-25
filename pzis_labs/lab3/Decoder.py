import json
from Encoder import Encoder
from typing import Dict


class Decoder:
    alphabet = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'

    with open('dict.json') as json_file:
        dictionary = json.load(json_file)
    json_file.close()

    @staticmethod
    def decode(encoded_text: str) -> str:
        # todo
        #  - caesar сразу частотным анализом
        #  - vigenere сначала поиск биграмм, совпадающих на определённом расстоянии,
        #       после подбор ключа и выбор наиболее подходящего перевода
        #  - playfair сначала симуляция отжига для поиска ключа, после выбор наиболее подходящего перевода
        for i in range(len(Decoder.alphabet)):
            pass

        return 'lul'

    @staticmethod
    def similarity(text_1: str, text_2: str) -> float:
        summary = max(len(text_1), len(text_2))
        similarities = 0
        for i in range(min(len(text_1), len(text_2))):
            if text_1[i].upper() == text_2[i].upper():
                similarities += 1
        return similarities / summary

    @staticmethod
    def letter_frequency(text: str) -> Dict[str, float]:
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
