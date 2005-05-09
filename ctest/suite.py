#!/usr/bin/env python

# Copyright (c) 2002-2005 The TenDRA Project <http://www.tendra.org/>.
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# 1. Redistributions of source code must retain the above copyright notice,
#    this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright notice,
#    this list of conditions and the following disclaimer in the documentation
#    and/or other materials provided with the distribution.
# 3. Neither the name of The TenDRA Project nor the names of its contributors
#    may be used to endorse or promote products derived from this software
#    without specific, prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
# IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
# THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
# PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR
# CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
# EXEMPLARY OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
# PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
# OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
# WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
# OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
# ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
# $Id$

# Generic, sort of, test suite runner for TenDRA.

import ConfigParser
import errno
import getopt
import operator
import os
import time
import subprocess
import sys

class test(object):
    def __init__(self):
        self.cc = ""
        self.cc_options = ""
        self.config_file = 'suite.conf'
        self.config = ConfigParser.ConfigParser()
        self.counter = 0
        self.cwd = os.getcwd()
        self.dir = ""
        self.time_total = 0
        self.verbose = False

        print 'ctest - a Python-based test suite runner - v...'
        print '(c) 2005 The TenDRA Project'
        print

        if self.config.read(self.config_file) == []:
            sys.exit("Configuration file '%s' missing." % (self.config_file))

        if self.config.has_section('compiler'):
            if not self.config.has_option('compiler', 'cc'):
                sys.exit('No compiler value (cc) set.')
            else:
                self.cc = self.config.get('compiler', 'cc')
        
            if not self.config.has_option('compiler', 'options'):
                print('No compiler options value (options) set. Using defaults.')
            else:
                self.cc_options = self.config.get('compiler', 'options')
        else:
            # Not having a compiler section is reason to bail out.
            sys.exit('No compiler section')

    def compile(self, test):
        cc_args = self.cc + ' ' + self.cc_options + '-o test ' + test
#        rc = os.system(cc_args)
        try:        
            rc = subprocess.Popen(cc_args, stdout=subprocess.PIPE, stderr=subprocess.PIPE, close_fds=True)
            rc.wait()
        except OSError, e:
            print e.child_traceback
#        if not rc == 0:
#            rc = rc / 256
#        return rc

    def getentries(self, dentry):
        self.dir = os.path.join(self.cwd, dentry)
        if os.path.isdir(self.dir):
            os.chdir(self.dir)
            fentries = os.listdir(self.dir)
            return fentries
        else:
            print '....%s is not a directory!' % (dentry)

    def log(self, text):
        if self.verbose:
            print text

    def loop(self):
        if self.config.has_option('tests', 'directories'):
            dirs = self.config.get('tests', 'directories')
            dirs = dirs.split(' ')
            for dentry in dirs:
                print 'Suite: %s' % (dentry)
                files = self.getentries(dentry)
                for fentry in files:
                    self.run(fentry)
                print
            print '------------------------------------------------------------------------------'
            print 'Ran %d tests in %.3fs.' % (self.counter, self.time_total)
        else:
            sys.exit('No directories to traverse')

    def run(self, test):
        self.counter = self.counter + 1
        # Start timer.
        time_start = time.time()
        print '  Test: %s ...' % (test),
        if operator.eq(self.compile(test), 0):
            print 'ok'
        else:
            print 'FAILED'
        self.log('    Description: %s' % ('blah'))
        # End timer.
        time_end = time.time()
        time_elapsed = time_end - time_start
        self.time_total = self.time_total + time_elapsed
        self.log('    Test ran in %.3fs.' % (time_elapsed))

def main():
    suite = test()

    try:
        opts, args = getopt.getopt(sys.argv[1:], "hv")
    except getopt.GetoptError:
        # print help information and exit:
        usage()
        sys.exit(2)
    for o, a in opts:
        if o == "-h":
            usage()
            sys.exit()
        if o == "-v":
            suite.verbose = True

    suite.loop()

def usage():
    print 'usage: suite.py [-h] [-v]'

if __name__ == '__main__':
    main()
