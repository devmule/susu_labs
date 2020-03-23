import json
from Encoder import Encoder


class Decoder:
    alphabet = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'

    with open('dict.json') as json_file:
        dictionary = json.load(json_file)
    json_file.close()

    @staticmethod
    def decode(encoded_text: str) -> str:
        return 'lul'

    @staticmethod
    def similarity(text_1: str, text_2: str) -> float:
        summary = max(len(text_1), len(text_2))
        similarities = 0
        for i in range(min(len(text_1), len(text_2))):
            if text_1[i].upper() == text_2[i].upper():
                similarities += 1
        return similarities / summary


if __name__ == '__main__':
    print(Decoder.similarity('text_1', 'text_2'))  # = 0.83
    print(Decoder.similarity('text_1', 'text_1'))  # = 1
    print(Decoder.similarity('text', 'hi, world'))  # = 0
