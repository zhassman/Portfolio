class Trie:
    """
    Class for representing tries
    """

    def __init__(self, root):
        '''
        Constructor

        Parameters:
         root : str (a character, but Python does not have a "char" type)

        Initialize root to given char, empty dict of children, final to False.
        '''
        self.root = root
        self.children = {}
        self.final = False

    def insert(self, word):
        '''
        Insert the word into the trie.

        Parameters:
	     word : str

        Returns: (does not return a value)
        '''
        rest = word[1:]
        first = rest[:1]

        if len(word) == 1:
            self.final = True
        else:
            self.children[first] = self.children.get(first, Trie(first))
            self.children[first].insert(rest)

    def contains(self, word):
        '''
        Check presence of given word in the trie.

        Parameters:
         word : str

        Returns: boolean
        '''
        rest = word[1:]
        first = rest[:1]

        if len(word) == 1:
            return self.final
        elif first not in self.children:
            return False
        else:
            return self.children[first].contains(rest)


    def all_words(self):
        '''
        Return all the words in the trie. Returned list not guaranteed
        in any particular order.

        Parameters:
         none

        Returns: list[str]
        '''
        return self.completions("")


    def num_words(self):
        '''
        Return the number of words in the trie.

        Parameters:
          none

        Returns: int
        '''
        word_count = 0

        if self.final:
            word_count += 1

        if len(self.children) != 0:
            for child in self.children.values():
                word_count += child.num_words()

        return word_count


    def completions(self, prefix):
        '''
        Return all completions given prefix. The returned list is not
        guaranteed to be in any particular order.

        Parameters:
          prefix : str

        Returns: list[str]
        '''
        return self._compl(prefix, "")


    def _compl(self, prefix, acc):
        '''
        Private method. Return all completions given prefix. The
        variable acc stores the string seen thus far in traversal of
        the trie. The returned list is not guaranteed to be in any
        particular order.

        Parameters:
          prefix : str
          acc : str

        Returns: list[str]
        '''
        comp_wds = []

        if prefix == self.root:
            if self.final:
                comp_wds += [acc + prefix]
            if len(self.children) != 0:
                for child in self.children.values():
                    comp_wds += child._compl("", acc + prefix)
            return comp_wds
        elif len(prefix) == 0:
            if self.final:
                comp_wds += [acc + self.root]
            if len(self.children) != 0:
                for child in self.children.values():
                    comp_wds += child._compl("", acc + self.root)
            return comp_wds
        else:
            first = prefix[:1]
            next = prefix[:1]
            if first != self.root:
                return comp_wds
            elif next not in self.children:
                return comp_wds
            else:
                comp_wds += self.children[next]._compl(prefix[1:], acc + first)
                return comp_wds


    def num_completions(self, prefix):
        '''
        Return the number of completions of the given prefix.

        Parameters:
          prefix : str

        Returns: int
        '''
        return len(self.completions(prefix))


class TrieOrthographer:
    """
    Class for a trie-based orthographer
    """

    def __init__(self):
        '''
        Constructor

        Parameters:
          none

        Initialize dictionary of empty tries, one per letter.
        '''
        self.tries = {}
        for char in 'abcdefghijklmnopqrstuvwxyz':
            self.tries[char] = Trie(char)

    def insert(self, word):
        '''
        Insert the word into the orthographer if it consists only of lowercase
        letters.

        Parameters:
          word : str

        Returns: (does not return a value)
        '''
        lowercase = True

        for character in word:
            if ord(character) < 97 or ord(character) > 122:
                lowercase = False
                break

        if lowercase:
            self.tries[word[:1]].insert(word)

    def insert_from_file(self, filename):
        '''
        Read the named file, insert words (one per line in file).

        Parameters:
          filename : str

        Returns: (does not return a value)
        '''
        with open(filename) as f:
            for line in f:
                self.insert(line.strip())

    def contains(self, word):
        '''
        Check presence of given word in the orthographer.

        Parameters:
          word : str

        Returns: boolean
        '''
        return self.tries[word[:1]].contains(word)

    def completions(self, prefix):
        '''
        Return all completions given prefix. The returned list is not
        guaranteed to be in any particular order.

        Parameters:
          prefix : str

        Returns: list[str]
        '''
        return self.tries[prefix[:1]].completions(prefix)

    def num_completions(self, prefix):
        '''
        Return the number of completions given prefix.

        Parameters:
          prefix : str

        Returns: int
        '''
        return len(self.completions(prefix))

    def all_words(self):
        '''
        Return all the words in the orthographer. Returned list not
        guaranteed in any particular order.

        Parameters:
          none

        Returns: list[str]
        '''
        list_of_words = []

        for trie in self.tries.values():
            list_of_words += trie.all_words()

        return list_of_words


    def num_words(self):
        '''
        Return the number of words in the orthographer.

        Parameters:
          none

        Returns: int
        '''
        total_amt_of_words = 0

        for trie in self.tries.values():
            total_amt_of_words += trie.num_words()

        return total_amt_of_words
