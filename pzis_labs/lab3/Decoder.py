import json
import math

from Encoder import Encoder
from typing import Dict, Tuple
import difflib  # для проверки похожести
import random  # для метода иммитации обжига (с постоянной температурой)


class Decoder:
    """Этот модуль содержит в себе метод дешифровки
    путём подбора ключа методом иммитации отжига
    и проверки с помощью метода частотного анализа"""
    alphabet = Encoder.alphabet

    with open('dict.json') as json_file:
        dictionary = json.load(json_file)
    json_file.close()

    @staticmethod
    def decode(encoded_text: str, min_frequency: float = 0.3, max_iteration: int = 1000) -> str:
        cache: Dict[str, float] = {}
        best_frequency = 0
        best_key = ""
        best_text = ""

        # добавляется случайный знак из алфавита
        best_key += Decoder.alphabet[random.randint(0, len(Decoder.alphabet) - 1)]
        iteration = 0
        # пока не достигли требуемой частоты или не прошли максимальное количество итераций
        while best_frequency < min_frequency and iteration < max_iteration:

            # создаётся ключ - мутант. чем больше разница, тем сильнее мутация
            new_key = best_key
            mutations = math.ceil((min_frequency - best_frequency) * 10)
            for i in range(mutations): new_key = Decoder.mutate_key(new_key)

            # если такой был - продолжаем, не теряем на него времени
            if new_key in cache.keys(): continue
            iteration += 1

            # иначе - декодируем методы Виженера и Плейфера
            # метод Виженера с одной буквой в качестве ключа всё равно что метод цезаря
            for decoded in [Encoder.vigenere_decode(encoded_text, new_key),
                            Encoder.playfair_decode(encoded_text, new_key)]:

                f = Decoder.text_frequency(decoded)  # частота
                # новый ключ, чтобы не повторять его в следующий раз
                cache[new_key] = f
                print(iteration, new_key, f, best_key)

                if f > best_frequency:
                    # если мутант лучше чем предыдущий ключ, то мы идём в правильном направлении,
                    # записываем мутанта как лучший ключ на данный момент
                    best_frequency = f
                    best_key = new_key
                    best_text = decoded

        return best_text

    @staticmethod
    def mutate_key(key: str) -> str:
        """функция рандомизации ключа"""
        if random.random() > .9:  # с шансом 1/10 добавляется случайная буква
            r = random.randint(0, len(key))
            return key[:r] + Decoder.alphabet[random.randint(0, len(Decoder.alphabet) - 1)] + key[r:]
        elif random.random() > .8 and len(key) > 1:  # с шансом 1/10 удаляется случайная буква
            r = random.randint(0, len(key) - 1)
            return key[:r] + key[r - 1:]
        elif random.random() > .7 and len(key) > 1:  # с шансом 1/10 перемешивается
            l = list(key)
            random.shuffle(l)
            return ''.join(l)
        else:  # иначе меняется случайная буква
            k = list(key)
            k[random.randint(0, len(key) - 1)] = Decoder.alphabet[random.randint(0, len(Decoder.alphabet) - 1)]
            return "".join(k)

    @staticmethod
    def text_frequency(text: str, return_in_zero: int = 10) -> float:
        """return_in_zero - количество слов, при проверке которых,
        если ни одно не было опознано, прекращается опознание"""
        frequency_sum = 0
        text = text.split(" ")
        for word in text:
            if frequency_sum >= return_in_zero and frequency_sum == 0: break
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
