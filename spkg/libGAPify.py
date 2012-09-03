#!/usr/bin/env python


import re
import copy
import time
import sys
import os
import glob
import ply.lex

####################################################################################

class Lexer_C(object):
    
    def __init__(self, *args, **kwds):
        self._lex = ply.lex.lex(object=self, *args, **kwds)

    reserved_keywords = (
        # Officially reserved C keywords
        'auto', 'else', 'long', 'switch',
        'break', 'enum', 'register', 'typedef',
        'case', 'extern', 'return', 'union',
        'char', 'float', 'short', 'unsigned',
        'const', 'for', 'signed', 'void',
        'continue', 'goto', 'sizeof', 'volatile',
        'default', 'if', 'static', 'while',
        'do', 'int', 'struct', '_Packed',
        'double',
        # morally reserved keywords
        'inline', 'asm', 'size_t', 'ssize_t', 'NULL', 'FILE',
        'uint32_t', 'uint64_t', 'NDEBUG', 'errno', 'environ',
        'termios', 'termio', 'sgttyb',
        'RTLD_LAZY', 'WEXITSTATUS', 'WIFEXITED'
        )
    
    tokens = (
       'ID','INTEGER', 'FLOAT', 'STRING', 'CHAR', 
       'WHITESPACE', 'CONTINUATION', 'INCLUDEFILE', 
       'COMMENT',
       'POUND', 'STAR',
       'SEMICOLON', 
       'LPAREN', 'RPAREN',         # ( )
       'LBRACKET', 'RBRACKET',     # [ ]
       'LBRACE', 'RBRACE',         # { } 
       'LESS', 'GREATER',          # < >
       'QUOTE'
    )
    
    literals = "+-*/%|&~^=!?.,:\'"
    
    t_POUND             = r'\#'
    t_STAR              = r'\*'
    t_ID                = r'[A-Za-z_][\w_]*'
    t_LPAREN            = r'\('
    t_RPAREN            = r'\)'
    t_LBRACKET          = r'\['
    t_RBRACKET          = r'\]'
    t_LBRACE            = r'\{'
    t_RBRACE            = r'\}'
    t_SEMICOLON         = r';'
    t_QUOTE             = r'\"'
    t_FLOAT             = r'((\d+)(\.\d+)(e(\+|-)?(\d+))? | (\d+)e(\+|-)?(\d+))([lL]|[fF])?'
    t_INTEGER           = r'(((((0x)|(0X))[0-9a-fA-F]+)|(\d+))([uU][lL]|[lL][uU]|[uU]|[lL])?)'
    t_LESS              = r'<'
    t_GREATER           = r'>'
    t_INCLUDEFILE       = r'<[\w_\.]+>'

    # Whitespace
    def t_WHITESPACE(self, t):
        r'\s+'
        n_newline = t.value.count("\n")
        n_backslash_newline = t.value.count("\\\s*\n")
        t.newline_count = n_newline - n_backslash_newline
        t.lexer.lineno += t.newline_count
        return t

    # Line continuation (backslash return)
    def t_CONTINUATION(self, t):
        r'\\[ \t]*\n'
        t.lexer.lineno += 1
        return t
    
    # String literal
    def t_STRING(self, t):
        r'\"([^\\\n]|(\\(.|\n)))*?\"'
        t.lexer.lineno += t.value.count("\n")
        return t
    
    # Character constant 'c' or L'c'
    def t_CHAR(self, t):
        r'(L)?\'([^\\\n]|(\\(.|\n)))*?\''
        t.lexer.lineno += t.value.count("\n")
        return t
    
    # Comment
    def t_COMMENT(self, t):
        r'(/\*(.|\n)*?\*/)|(//.*?\n)'
        t.lexer.lineno += t.value.count("\n")
        return t        

    def t_error(self, t):
        t.type = t.value[0]
        t.value = t.value[0]
        t.lexer.skip(1)
        print "================== error ================"
        return t

    def skip_to(self, token_type):
        while True:
            tok = self.token()
            if tok.type == token_type:
                return
        raise ValueError('no token of type '+token_type+' found in source.')

    def skip_line(self):
        while True:
            tok = self.token()
            if tok.type == 'WHITESPACE' and tok.newline_count > 0:
                return
        raise ValueError('no newline found in source.')

    def input(self, data):
        self._lex.input(data)

    def token(self):
        return self._lex.token()

    def token_ns(self):
        """
        Return the next non-whitespace token
        """
        while True:
            tok = self.token()
            if (not tok) or tok.type != 'WHITESPACE':
                return tok


####################################################################################

class SourceFile(object):
    
    def __init__(self, filename):
        self.filename = filename
        f = open(filename, 'r')
        self.code = f.read()   #.decode('ascii', 'ignore')
        f.close()

    def error_function(self, msg, a, b):
        print msg, a, b
        sys.exit()
    
    def type_lookup_function(self, namd):
        return False
        
    def lexer(self, input=None, **kwds):
        lex = Lexer_C(**kwds)
        # lex = ply.lex.lex(object=self, **kwds)
        if input is None:
            lex.input(self.code)
        else:
            lex.input(input)
        return lex

    def tokenize(self):
        tokens = []
        lexer = self.lexer()
        while True:
            tok = lexer.token()
            if not tok: break
            tokens.append(tok)
        return tokens

    def without_cpp_bodies(self):
        lexer = self.lexer()
        output = []
        while True:
            tok = lexer.token()
            if not tok: break
            if tok.type == 'POUND':
                tok = lexer.token_ns()
                if tok.value != 'define':
                    output.append('#...\n')
                    lexer.skip_line()
                    continue
                tok = lexer.token_ns()
                output.append('#define '+tok.value+'\n')
                lexer.skip_line()
                continue
            output.append(tok.value)
        print ''.join(output)

    def cpp_defines(self):
        lexer = self.lexer()
        defines = set()
        while True:
            tok = lexer.token()
            if not tok: break
            if tok.type == 'POUND':
                tok = lexer.token_ns()
                if tok.value != 'define':
                    lexer.skip_line()
                    continue
                tok = lexer.token_ns()
                defines.add(tok.value)
                lexer.skip_line()
        return defines
                
    def all_global_identifiers(self):
        lexer = self.lexer()
        identifiers = set()
        brace_level = 0
        while True:
            tok = lexer.token_ns()
            if not tok: break
            if tok.type == 'LBRACE':
                brace_level += 1
            elif tok.type == 'RBRACE':
                brace_level -= 1
            if brace_level > 0:
                continue
            if tok.type == 'LPAREN':
                tok = lexer.token_ns()
                paren_level = 1
                if tok.type == 'RPAREN':
                    paren_level -= 1
                if tok.type == 'STAR':   
                    tok = lexer.token_ns()
                    identifiers.add(tok.value)   # function pointer typedef
                while paren_level > 0:
                    tok = lexer.token()
                    if tok.type == 'LPAREN':
                        paren_level += 1
                    if tok.type == 'RPAREN':
                        paren_level -= 1
            elif tok.type == 'POUND':
                tok = lexer.token_ns()
                if tok.value == 'define':
                    tok = lexer.token_ns()
                    identifiers.add(tok.value)   #define foo bar
                lexer.skip_line()
            elif tok.type == 'ID':
                identifiers.add(tok.value)
        identifiers.difference_update(Lexer_C.reserved_keywords)
        autoconf_defines = [ i for i in identifiers if i.startswith('HAVE_') ]
        identifiers.difference_update(autoconf_defines)
        identifiers.difference_update([ i for i in identifiers if i.startswith('_') ])
        return identifiers

    def add_prefix(self, prefix, identifiers, string_replacements=()):
        """
        Add ``prefix`` to the given ``identifiers`` in the source
        """
        output = ''
        input = self.code
        for pattern, replacement in string_replacements:
            input = re.sub(pattern, replacement, input)
        lexer = self.lexer(input=input)
        while True:
            tok = lexer.token()
            if not tok: break
            if tok.type == 'ID' and tok.value in identifiers:
                output += (prefix + tok.value)
            else:
                output += tok.value
        return output

    def mangle(self, prefix, identifiers, string_replacements=()):
        print 'rewriting '+self.filename+' with prefix '+prefix
        output = self.add_prefix(prefix, identifiers, string_replacements)
        f = open(self.filename, 'w')
        f.write(output)
        f.close()


####################################################################################

class SourceCollection(object):
    
    def __init__(self, directory):
        if os.path.isfile(directory):
            self.headers = []
            self.sources = [SourceFile(directory)]
        else:
            self.headers = map(SourceFile, glob.glob(os.path.join(directory, '*.h')))
            self.sources = map(SourceFile, glob.glob(os.path.join(directory, '*.c')))

    def identifiers(self):
        result = set()
        for f in self.headers + self.sources:
            result.update(f.all_global_identifiers())
        result.difference_update(self.exceptions)
        return result

####################################################################################

class SourceCollection_GAP(SourceCollection):

    exceptions = ( 
        # Stuff that appears in conditional #if / #endif
        'TCSETA', 'TCSETAW',
        'TZ_RELATORS', 'TZ_LENGTHTIETZE', 'TZ_GENERATORS', 'TZ_NUMRELS', 'TZ_TOTAL', 
        'TZ_LENGTHS', 'TZ_NUMGENS', 'TZ_FREEGENS', 'TZ_FLAGS', 'TZ_INVERSES',
        'assert',
        # from config.h
        'SYS_ARCH', 'VERSION', 'SYS_IS_CYGWIN32', 'PACKAGE_URL', 'SYS_IS_DARWIN', 
        'CONFIGNAME', 'C_STACK_ALIGN', 'RETSIGTYPE', 'LT_OBJDIR', 'PACKAGE_STRING', 
        'PACKAGE_BUGREPORT', 'SIZEOF_VOID_P', 'ALIGNOF_LONG', 'WORDS_BIGENDIAN', 
        'PACKAGE_TARNAME', 'STDC_HEADERS', 'PACKAGE', 'PACKAGE_VERSION', 'PACKAGE_NAME',
        # result of precprocessor hackery
        'FuncFREXP_MACFLOAT', 'FuncINTFLOOR_MACFLOAT', 'FuncSTRING_MACFLOAT'
        )

    def mangle(self):
        identifiers = self.identifiers()
        for f in self.headers + self.sources:
            f.mangle('libGAP_', identifiers)

        

####################################################################################

if __name__ == "__main__":
    #home = os.path.dirname(os.path.realpath(sys.argv[0]))
    #sys.path.append(os.path.join(home, 'pycparser'))
    if len(sys.argv) > 1:
        dirname = sys.argv[1]
        print "Mangling identifiers in "+dirname
        src = SourceCollection_GAP(dirname)
        src.mangle()
    else:
        print("Please provide a directory name as argument")

        
