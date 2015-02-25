# -*- coding: utf-8 -*-
import MeCab
from gensim import corpora
mecab = MeCab.Tagger('mecabrc')


def main():
    text = "すもももももももものうち"
    node = mecab.parseToNode(text)
    while node:
        print node.surface , node.feature
        node = node.next


if __name__ == "__main__":
    main()
