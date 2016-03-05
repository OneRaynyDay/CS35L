#!/usr/bin/env python

import random, sys
from optparse import OptionParser

def generateTabs(num):
    string = ""
    for i in range(num):
        string += "        "
    return string

class comm:
    def __init__(self, files, options, parser):
        ''' Constructor for comm '''
        self.files = files
        self.options = options
        self.parser = parser
    def compare(self):
        self.newList = []
        lines1 = self.files[0].readlines()
        lines2 = self.files[1].readlines()
        ptr1 = 0
        ptr2 = 0
        # flag - if files are sorted = false, files aren't sorted = true
        flag = not (lines1 == sorted(lines1) and lines2 == sorted(lines2))
        
        if flag and not self.options.unsort:
            self.parser.error("Value Error: the input file(s) are " \
                    "not sorted. Use -u if the files are unsorted.")
        ''' unsorted situations '''
        if self.options.unsort:
            for l1 in lines1:
                for l2 in list(lines2):
                    if l1 == l2 and l2 in lines2:
                        col3 = True
                        sys.stdout.write("") if self.options.omit3 else \
                        sys.stdout.write(generateTabs(2) + l1)
                        lines2.remove(l2)
                        break;
                else:
                    sys.stdout.write("") if self.options.omit1 else \
                    sys.stdout.write(generateTabs(0) + l1)
            for l2 in lines2:
                sys.stdout.write("") if self.options.omit2 else \
                sys.stdout.write(generateTabs(1) + l2)
            return        
        
        ''' For sorted situations '''
        while ptr1 < len(lines1) and ptr2 < len(lines2):
            numTabs = 0
            if lines1[ptr1] < lines2[ptr2]:
                sys.stdout.write("") if self.options.omit1 else \
                        sys.stdout.write(generateTabs(0) + lines1[ptr1])
                ptr1+=1
                continue;
            numTabs+=1
            if lines1[ptr1] > lines2[ptr2]:
                sys.stdout.write("") if self.options.omit2 else \
                        sys.stdout.write(generateTabs(1) + lines2[ptr2])
                ptr2+=1
                continue;
            numTabs+=1
            if lines1[ptr1] == lines2[ptr2]:
                sys.stdout.write("") if self.options.omit3 else \
                        sys.stdout.write(generateTabs(2) + lines1[ptr1])
                ptr1+=1
                ptr2+=1
                continue;
        
        if ptr1 == len(lines1):
            while ptr2 < len(lines2):
                sys.stdout.write(generateTabs(1) + lines2[ptr2])
                ptr2+=1
        else:
            while ptr1 < len(lines1):
                sys.stdout.write(generateTabs(0) + lines1[ptr1])
                ptr1+=1

def main():
    NUM_FILES = 2
    usage_msg = """%prog [-123] [-u] file1 file2
    Compares two files.
	
    Options:
    -1 Suppress column 1 (lines unique to FILE1)
    -2 Suppress column 2 (lines unique to FILE2)
    -3 Suppress column 3 (lines common to FILE1 and FILE2)
    -u Allows for comm to compare unsorted input(s).
    """
    parser = OptionParser(usage=usage_msg)
    parser.add_option("-1", action="store_true", dest="omit1", \
            help="suppress column 1 (lines unique to FILE1)", default=False)
    parser.add_option("-2", action="store_true", dest="omit2", \
            help="suppress column 2 (lines unique to FILE2)", default=False)
    parser.add_option("-3", action="store_true", dest="omit3", \
            help="suppress column 3 (lines common to FILE1 and FILE2)", \
            default=False)
    parser.add_option("-u", action="store_true", dest="unsort", \
            help="Allows for comm to compare unsorted input(s).", default=False)
    options, args = parser.parse_args(sys.argv[1:])
    try: 
        f = [open(arg, 'r') if arg != '-' else sys.stdin for arg in args]
        if len(f) != NUM_FILES:
            parser.error(usage_msg)
    except IOError as err:
        parser.error("I/O error: ".
                                     format(errno))
    c = comm(f, options, parser)
    c.compare()
if __name__== "__main__":
    main()

