#!/usr/bin/env python2.7
# -*- coding : utf-8 -*-

'''
def args_deco(state):
    def lker_func_deco(func):
        def real_deco(arg):
            print 'now state:' + state
            #func with no args
            print 'func deco prefix'
            ret = func(arg)
            print 'func deco postfix'
        return real_deco
    return lker_func_deco
'''

def args_deco(name):
    def lker_func_deco(func):
        def real_deco_1(arg):
            print 'deco name:' + name
            print 'func deco prefix'
            ret = func(arg)
            print 'func deco postfix'

        def real_deco_2(arg):
            print 'real_deco_2'
            print 'func deco prefix'
            ret = func(arg)
            print 'func deco postfix'

        if name == 'deco_1':
            return real_deco_1
        elif name == 'deco_2':
            return real_deco_2
    return lker_func_deco

@args_deco('deco_1')
def ok(arg):
    print 'func ok with param:' + arg

@args_deco('deco_2')
def fail(arg):
    print 'func fail with param:' + arg

def main():
    ok('such a happy day')
    fail('fuck')

if __name__ == '__main__':
    main()
