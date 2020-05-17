import json
from Encoder import Encoder
from typing import Dict, Tuple
import difflib  # для проверки похожести
import random  # для метода симуляции обжига


class Decoder:
    alphabet = Encoder.alphabet

    with open('dict.json') as json_file:
        dictionary = json.load(json_file)
    json_file.close()

    @staticmethod
    def decode(encoded_text: str, min_frequency: float = 0.2, max_iteration: int = 9000) -> str:
        cache: Dict[str, float] = {}
        best_frequency = 0
        best_key = ""
        best_text = ""

        # метод Виженера с одной буквой в качестве ключа всё равно что метод цезаря
        '''for i in range(len(Decoder.alphabet)):  # len 1
            for decoded in [Encoder.caesar_decode(encoded_text, i),
                            Encoder.playfair_decode(encoded_text, Decoder.alphabet[i])]:
                f = Decoder.text_frequency(decoded)
                if f > best_frequency:
                    best_frequency = f
                    best_key = Decoder.alphabet[i]
                if f > min_frequency:
                    return decoded'''

        # len > 1
        best_key += Decoder.alphabet[random.randint(0, len(Decoder.alphabet) - 1)]
        for i in range(max_iteration):
            # добавляется случайный знак из алфавита
            key = best_key
            for new_key in [Decoder.mutate_key(key) for x in range(3)]:
                if new_key in cache.keys(): continue
                for decoded in [Encoder.vigenere_decode(encoded_text, new_key),
                                Encoder.playfair_decode(encoded_text, new_key)]:
                    f = Decoder.text_frequency(decoded)
                    cache[new_key] = f
                    print(i, new_key, f, best_key)
                    if f > best_frequency:
                        best_frequency = f
                        best_key = new_key
                        best_text = decoded
                    if f > min_frequency:
                        return decoded
        return best_text

    @staticmethod
    def mutate_key(key: str) -> str:
        if random.random() > .9 and len(key) > 1:  # с шансом 1/10 удаляется случайная буква
            r = random.randint(0, len(key) - 1)
            return key[:r] + key[r - 1:]
        if random.random() < .1:  # с шансом 1/10 добавляется случайная буква
            r = random.randint(0, len(key))
            return key[:r] + Decoder.alphabet[random.randint(0, len(Decoder.alphabet) - 1)] + key[r:]
        else:  # иначе меняется случайная буква
            k = list(key)
            k[random.randint(0, len(key) - 1)] = Decoder.alphabet[random.randint(0, len(Decoder.alphabet) - 1)]
            return "".join(k)

    @staticmethod
    def text_frequency(text: str) -> float:
        frequency_sum = 0
        text = text.split(" ")
        for word in text:
            for d in Decoder.dictionary:
                if Decoder.similarity(word.upper(), d.upper()) > .75:
                    frequency_sum += 1
        return frequency_sum / len(text)

    @staticmethod
    def similarity(text_1: str, text_2: str) -> float:
        normalized1 = text_1.lower()
        normalized2 = text_2.lower()
        matcher = difflib.SequenceMatcher(None, normalized1, normalized2)
        return matcher.ratio()


if __name__ == '__main__':
    print(Decoder.similarity('text_1', 'text_2'))  # = 0.8333333333333334
    print(Decoder.similarity('text_1', 'text_1'))  # = 1
    print(Decoder.similarity('text', 'hi, world'))  # = 0
    Decoder.decode("123123")
